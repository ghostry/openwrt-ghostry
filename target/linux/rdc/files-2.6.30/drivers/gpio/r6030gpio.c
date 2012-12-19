/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <linux/module.h>
#include <linux/pci.h>
#include <linux/spinlock.h>
#include <asm/gpio.h>

#define DATAREG1        0x4c    // GPIO data register I address
#define DATAREG2        0x88    // GPIO data register II address

#define PIN_COUNT       59
#define PIN_BYTES       8

struct r6030gpio {
    spinlock_t lock;
    struct pci_dev *pdev;       // PCI device which the GPIO is on
    struct gpio_chip gpio;
    u8 requested[PIN_BYTES];    // pins requested
    u8 inputs[PIN_BYTES];       // pins configured as input
#ifdef CONFIG_PM
    u8 saved[PIN_BYTES];        // registers saved state
#endif
};

static int r6030gpio_request(struct gpio_chip *gpio, unsigned pin)
{
    struct r6030gpio *rg = container_of(gpio, struct r6030gpio, gpio);
    unsigned long flags;

    spin_lock_irqsave(&rg->lock, flags);
    rg->requested[pin/8] |= 1 << (pin&0x7);
    spin_unlock_irqrestore(&rg->lock, flags);
    return 0;
}

static void r6030gpio_free(struct gpio_chip *gpio, unsigned pin)
{
    struct r6030gpio *rg = container_of(gpio, struct r6030gpio, gpio);
    unsigned long flags;

    spin_lock_irqsave(&rg->lock, flags);
    rg->requested[pin/8] &= ~(1 << (pin&0x7));
    spin_unlock_irqrestore(&rg->lock, flags);
}

static void gpio_write(struct r6030gpio *rg, int pin, int val)
{
    int byte, reg;
    u8 regval;

    byte = pin / 8;
    reg = (byte >= 4 ? DATAREG2 : DATAREG1) + byte;
    pin &= 0x7;
    pci_read_config_byte(rg->pdev, reg, &regval);
    if( val )
        regval |= 1 << pin;
    else
        regval &= ~(1 << pin);
    regval |= rg->inputs[byte];     // keep input registers pulled high
    pci_write_config_byte(rg->pdev, reg, regval);
}

static int r6030gpio_direction_input(struct gpio_chip *gpio, unsigned pin)
{
    struct r6030gpio *rg = container_of(gpio, struct r6030gpio, gpio);
    unsigned long flags;

    spin_lock_irqsave(&rg->lock, flags);
    rg->inputs[pin/8] |= 1 << (pin&0x7);
    gpio_write(rg, pin, 1);
    spin_unlock_irqrestore(&rg->lock, flags);

    return 0;
}

static int r6030gpio_get(struct gpio_chip *gpio, unsigned pin)
{
    struct r6030gpio *rg = container_of(gpio, struct r6030gpio, gpio);
    unsigned long flags;
    int reg;
    u8 regval;

    spin_lock_irqsave(&rg->lock, flags);
    reg = (pin >= 32 ? DATAREG2 : DATAREG1) + pin/8;
    pci_read_config_byte(rg->pdev, reg, &regval);
    spin_unlock_irqrestore(&rg->lock, flags);
    return (regval & (1 << (pin&0x7))) != 0;
}

static int r6030gpio_direction_output(struct gpio_chip *gpio,
                    unsigned pin, int val)
{
    struct r6030gpio *rg = container_of(gpio, struct r6030gpio, gpio);
    unsigned long flags;

    spin_lock_irqsave(&rg->lock, flags);
    rg->inputs[pin/8] &= ~(1 << (pin&0x7));
    gpio_write(rg, pin, val);
    spin_unlock_irqrestore(&rg->lock, flags);
    return 0;
}

static void r6030gpio_set(struct gpio_chip *gpio,
                unsigned pin, int val)
{
    struct r6030gpio *rg = container_of(gpio, struct r6030gpio, gpio);
    unsigned long flags;

    spin_lock_irqsave(&rg->lock, flags);
    gpio_write(rg, pin, val);
    spin_unlock_irqrestore(&rg->lock, flags);
}

static void r6030gpio_setup(struct r6030gpio *rg)
{
    struct gpio_chip *c = &rg->gpio;

//    c->label = rg->pdev->dev.bus_id;
    c->label = dev_name(&rg->pdev->dev);               
    c->owner = THIS_MODULE;
    c->request = r6030gpio_request;
    c->free = r6030gpio_free;
    c->direction_input = r6030gpio_direction_input;
    c->get = r6030gpio_get;
    c->direction_output = r6030gpio_direction_output;
    c->set = r6030gpio_set;
    c->dbg_show = NULL;
    c->base = 0;
    c->ngpio = PIN_COUNT;
    c->can_sleep = 0;
}

static int r6030gpio_probe(struct pci_dev *dev,
            const struct pci_device_id *pci_id)
{
    struct r6030gpio *rg;
    int err;

    rg = kzalloc(sizeof(*rg), GFP_KERNEL);
    if (!rg)
        return -ENOMEM;

    rg->pdev = dev;
    spin_lock_init(&rg->lock);
    err = pci_enable_device(dev);
    if (err) {
        printk(KERN_ERR "r6030gpio: Can't enable device.\n");
        goto err_freebg;
    }
    pci_set_master(dev);
    pci_set_drvdata(dev, rg);
    r6030gpio_setup(rg);
    err = gpiochip_add(&rg->gpio);
    if (err) {
        printk(KERN_ERR "r6030gpio: Failed to register GPIOs\n");
        goto err_release;
    }
    printk(KERN_INFO "r6030gpio: gpio base %d\n", rg->gpio.base);
    return 0;

err_release:
    pci_set_drvdata(dev, NULL);
    pci_disable_device(dev);
err_freebg:
    kfree(rg);
    return err;
}

static void r6030gpio_remove(struct pci_dev *pdev)
{
    struct r6030gpio *rg = pci_get_drvdata(pdev);

    gpiochip_remove(&rg->gpio);
    pci_disable_device(pdev);
    pci_set_drvdata(pdev, NULL);
    kfree(rg);
}

#ifdef CONFIG_PM
static int r6030gpio_suspend(struct pci_dev *pdev, pm_message_t state)
{
    struct r6030gpio *rg = pci_get_drvdata(pdev);
    unsigned long flags;
    int i, reg;

    spin_lock_irqsave(&rg->lock, flags);
    for(i = 0; i < PIN_BYTES; ++i) {
        reg = (i >= 4 ? DATAREG2 : DATAREG1) + (i & 0x3);
        pci_read_config_byte(rg->pdev, reg, &rg->saved[i]);
    }
    spin_unlock_irqrestore(&rg->lock, flags);
    pci_save_state(pdev);
    pci_disable_device(pdev);
    pci_set_power_state(pdev, pci_choose_state(pdev, state));
    return 0;
}

static int r6030gpio_resume(struct pci_dev *pdev)
{
    struct r6030gpio *rg = pci_get_drvdata(pdev);
    unsigned long flags;
    int i, err, reg;
    u8 saved;

    pci_set_power_state(pdev, 0);
    err = pci_enable_device(pdev);
    if (err)
        return err;
    pci_restore_state(pdev);
    spin_lock_irqsave(&rg->lock, flags);
    for(i = 0; i < PIN_BYTES; ++i) {
        reg = (i >= 4 ? DATAREG2 : DATAREG1) + (i & 0x3);
        // keep not requested bits unchanged
        pci_read_config_byte(rg->pdev, reg, &saved);
        saved &= ~rg->requested[i];
        saved |=  (rg->saved[i] | rg->inputs[i]) & rg->requested[i];
        pci_write_config_dword(rg->pdev, reg, saved);
    }
    spin_unlock_irqrestore(&rg->lock, flags);
    return 0;
}
#else
#define r6030gpio_suspend NULL
#define r6030gpio_resume NULL
#endif /* CONFIG_PM */

static struct pci_device_id r6030gpio_pci_tbl[] = {
    { PCI_DEVICE(PCI_VENDOR_ID_RDC, PCI_DEVICE_ID_RDC_R6030) },
    { 0, },
};
MODULE_DEVICE_TABLE(pci, r6030gpio_pci_tbl);

static struct pci_driver r6030gpio_pci_driver = {
    .name       = "r6030gpio",
    .id_table   = r6030gpio_pci_tbl,
    .probe      = r6030gpio_probe,
    .remove     = r6030gpio_remove,
    .suspend    = r6030gpio_suspend,
    .resume     = r6030gpio_resume,
};

static int r6030gpio_init(void)
{
    return pci_register_driver(&r6030gpio_pci_driver);
}
module_init(r6030gpio_init)

static void r6030gpio_exit(void)
{
    pci_unregister_driver(&r6030gpio_pci_driver);
}
module_exit(r6030gpio_exit)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafal Dabrowa");
MODULE_DESCRIPTION("GPIO on RDC r6030 southbridge");
