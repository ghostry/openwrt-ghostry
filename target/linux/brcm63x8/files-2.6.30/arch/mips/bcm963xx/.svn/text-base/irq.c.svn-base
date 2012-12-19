/*
<:copyright-gpl 
 Copyright 2002 Broadcom Corp. All Rights Reserved. 

 This program is free software; you can distribute it and/or modify it 
 under the terms of the GNU General Public License (Version 2) as 
 published by the Free Software Foundation. 

 This program is distributed in the hope it will be useful, but WITHOUT 
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
 for more details. 

 You should have received a copy of the GNU General Public License along 
 with this program; if not, write to the Free Software Foundation, Inc., 
 59 Temple Place - Suite 330, Boston MA 02111-1307, USA. 
:>
*/
/*
 * Interrupt control functions for Broadcom 963xx MIPS boards
 */

#include <asm/atomic.h>

#include <linux/delay.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/linkage.h>

#include <asm/irq.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <asm/signal.h>
#include <bcm_map_part.h>
#include <bcm_intr.h>


#if defined(CONFIG_SMP)
    #define AFFINITY_OF(d) (*(d)->affinity)
#else
    #define AFFINITY_OF(d) ((void)(d), CPU_MASK_CPU0)
#endif

#if IRQ_BITS == 64
    #define IRQ_TYPE uint64
#else
    #define IRQ_TYPE uint32
#endif

volatile IrqControl_t * brcm_irq_ctrl[NR_CPUS];
spinlock_t brcm_irqlock;

#if defined(CONFIG_SMP)
extern DEFINE_PER_CPU(unsigned int, ipi_pending);
#endif

static void irq_dispatch_int(void)
{
    int cpu = smp_processor_id();
    IRQ_TYPE pendingIrqs;
    static IRQ_TYPE irqBit;

    static uint32 isrNumber = (sizeof(irqBit) * 8) - 1;

    spin_lock(&brcm_irqlock);
    pendingIrqs = brcm_irq_ctrl[cpu]->IrqStatus & brcm_irq_ctrl[cpu]->IrqMask;
    spin_unlock(&brcm_irqlock);

    if (!pendingIrqs) {
        return;
    }

    while (1) {
        irqBit <<= 1;
        isrNumber++;
        if (isrNumber == (sizeof(irqBit) * 8)) {
            isrNumber = 0;
            irqBit = 0x1;
        }
        if (pendingIrqs & irqBit) {
            unsigned int irq = isrNumber + INTERNAL_ISR_TABLE_OFFSET;
            spin_lock(&brcm_irqlock);
            if (irq >= INTERRUPT_ID_EXTERNAL_0 && irq <= INTERRUPT_ID_EXTERNAL_3) {
                PERF->ExtIrqCfg |= (1 << (irq - INTERRUPT_ID_EXTERNAL_0 + EI_CLEAR_SHFT));      // Clear
            }
#if defined(CONFIG_BCM96368) || defined(CONFIG_BCM96816)
            else if (irq >= INTERRUPT_ID_EXTERNAL_4 && irq <= INTERRUPT_ID_EXTERNAL_5) {
                PERF->ExtIrqCfg1 |= (1 << (irq - INTERRUPT_ID_EXTERNAL_4 + EI_CLEAR_SHFT));      // Clear
            }
#endif
            spin_unlock(&brcm_irqlock);
            do_IRQ(irq);
            break;
        }
    }
}

#ifdef CONFIG_BCM_HOSTMIPS_PWRSAVE
extern void BcmPwrMngtResumeFullSpeed (void);
#endif


asmlinkage void plat_irq_dispatch(void)
{
    u32 cause;

#ifdef CONFIG_BCM_HOSTMIPS_PWRSAVE
    BcmPwrMngtResumeFullSpeed();
#endif

    while((cause = (read_c0_cause() & read_c0_status() & CAUSEF_IP))) {
        if (cause & CAUSEF_IP7)
            do_IRQ(MIPS_TIMER_INT);
        else if (cause & CAUSEF_IP0)
            do_IRQ(INTERRUPT_ID_SOFTWARE_0);
        else if (cause & CAUSEF_IP1)
            do_IRQ(INTERRUPT_ID_SOFTWARE_1);
#if defined (CONFIG_SMP)
        else if (cause & (CAUSEF_IP2 | CAUSEF_IP3))
#else 
        else if (cause & CAUSEF_IP2)
#endif
            irq_dispatch_int();
    }
}


// bill
void disable_brcm_irqsave(unsigned int irq, unsigned long stateSaveArray[])
{
    int cpu;
    struct irq_desc *desc = irq_desc + irq;
    unsigned long flags;

    // Test for valid interrupt.
    if ((irq >= INTERNAL_ISR_TABLE_OFFSET ) && (irq <= INTERRUPT_ID_LAST))
    {
        // Disable this processor's interrupts and acquire spinlock.
        spin_lock_irqsave(&brcm_irqlock, flags);

        // Loop thru each processor.
        for_each_cpu_mask(cpu, AFFINITY_OF(desc))
        {
            // Save original interrupt's enable state.
            stateSaveArray[cpu] = brcm_irq_ctrl[cpu]->IrqMask & (((IRQ_TYPE)1) << (irq - INTERNAL_ISR_TABLE_OFFSET));

            // Clear each cpu's selected interrupt enable.
            brcm_irq_ctrl[cpu]->IrqMask &= ~(((IRQ_TYPE)1) << (irq - INTERNAL_ISR_TABLE_OFFSET));
        }

        // Release spinlock and enable this processor's interrupts.
        spin_unlock_irqrestore(&brcm_irqlock, flags);
    }
}


// bill
void restore_brcm_irqsave(unsigned int irq, unsigned long stateSaveArray[])
{
    int cpu;
    struct irq_desc *desc = irq_desc + irq;
    unsigned long flags;

    // Disable this processor's interrupts and acquire spinlock.
    spin_lock_irqsave(&brcm_irqlock, flags);

    // Loop thru each processor.
    for_each_cpu_mask(cpu, AFFINITY_OF(desc))
    {
        // Restore cpu's original interrupt enable (off or on).
        brcm_irq_ctrl[cpu]->IrqMask |= stateSaveArray[cpu];
    }

    // Release spinlock and enable this processor's interrupts.
    spin_unlock_irqrestore(&brcm_irqlock, flags);
}




void enable_brcm_irq(unsigned int irq)
{
    int cpu;
    struct irq_desc *desc = irq_desc + irq;
    unsigned long flags;

    spin_lock_irqsave(&brcm_irqlock, flags);

    if( irq >= INTERNAL_ISR_TABLE_OFFSET ) {
        for_each_cpu_mask(cpu, AFFINITY_OF(desc)) {
            brcm_irq_ctrl[cpu]->IrqMask |= (((IRQ_TYPE)1)  << (irq - INTERNAL_ISR_TABLE_OFFSET));
        }
    }
    else if ((irq == INTERRUPT_ID_SOFTWARE_0) || (irq == INTERRUPT_ID_SOFTWARE_1)) {
        set_c0_status(0x1 << (STATUSB_IP0 + irq - INTERRUPT_ID_SOFTWARE_0));
    }

    if (irq >= INTERRUPT_ID_EXTERNAL_0 && irq <= INTERRUPT_ID_EXTERNAL_3) {
        PERF->ExtIrqCfg &= ~(1 << (irq - INTERRUPT_ID_EXTERNAL_0 + EI_INSENS_SHFT));    // Edge insesnsitive
        PERF->ExtIrqCfg |= (1 << (irq - INTERRUPT_ID_EXTERNAL_0 + EI_LEVEL_SHFT));      // Level triggered
        PERF->ExtIrqCfg &= ~(1 << (irq - INTERRUPT_ID_EXTERNAL_0 + EI_SENSE_SHFT));     // Low level
        PERF->ExtIrqCfg |= (1 << (irq - INTERRUPT_ID_EXTERNAL_0 + EI_CLEAR_SHFT));      // Clear
        PERF->ExtIrqCfg |= (1 << (irq - INTERRUPT_ID_EXTERNAL_0 + EI_MASK_SHFT));       // Unmask
    }
#if defined(CONFIG_BCM96368) || defined(CONFIG_BCM96816)
    else if (irq >= INTERRUPT_ID_EXTERNAL_4 && irq <= INTERRUPT_ID_EXTERNAL_5) {
        PERF->ExtIrqCfg1 &= ~(1 << (irq - INTERRUPT_ID_EXTERNAL_4 + EI_INSENS_SHFT));    // Edge insesnsitive
        PERF->ExtIrqCfg1 |= (1 << (irq - INTERRUPT_ID_EXTERNAL_4 + EI_LEVEL_SHFT));      // Level triggered
        PERF->ExtIrqCfg1 &= ~(1 << (irq - INTERRUPT_ID_EXTERNAL_4 + EI_SENSE_SHFT));     // Low level
        PERF->ExtIrqCfg1 |= (1 << (irq - INTERRUPT_ID_EXTERNAL_4 + EI_CLEAR_SHFT));      // Clear
        PERF->ExtIrqCfg1 |= (1 << (irq - INTERRUPT_ID_EXTERNAL_4 + EI_MASK_SHFT));       // Unmask
    }
#endif

    spin_unlock_irqrestore(&brcm_irqlock, flags);
}


void __disable_ack_brcm_irq(unsigned int irq)
{
    int cpu;
    struct irq_desc *desc = irq_desc + irq;

    if( irq >= INTERNAL_ISR_TABLE_OFFSET ) {
        for_each_cpu_mask(cpu, AFFINITY_OF(desc)) {
            brcm_irq_ctrl[cpu]->IrqMask &= ~(((IRQ_TYPE)1) << (irq - INTERNAL_ISR_TABLE_OFFSET));
        }
    }
}


void disable_brcm_irq(unsigned int irq)
{
    unsigned long flags;

    spin_lock_irqsave(&brcm_irqlock, flags);
    __disable_ack_brcm_irq(irq);
    if ((irq == INTERRUPT_ID_SOFTWARE_0) || (irq == INTERRUPT_ID_SOFTWARE_1)) {
        clear_c0_status(0x1 << (STATUSB_IP0 + irq - INTERRUPT_ID_SOFTWARE_0));
    }
    spin_unlock_irqrestore(&brcm_irqlock, flags);
}


void ack_brcm_irq(unsigned int irq)
{
    unsigned long flags;

    spin_lock_irqsave(&brcm_irqlock, flags);
    __disable_ack_brcm_irq(irq);

#if defined(CONFIG_SMP)
    if (irq == INTERRUPT_ID_SOFTWARE_0) {
        int this_cpu = smp_processor_id();
        int other_cpu = !this_cpu;
        per_cpu(ipi_pending, this_cpu) = 0;
        mb();
        clear_c0_cause(1<<CAUSEB_IP0);
        if (per_cpu(ipi_pending, other_cpu)) {
            set_c0_cause(1<<CAUSEB_IP0);
        }
    }
#else
    if (irq == INTERRUPT_ID_SOFTWARE_0) {
        clear_c0_cause(1<<CAUSEB_IP0);
    }
#endif

    if (irq == INTERRUPT_ID_SOFTWARE_1) {
        clear_c0_cause(1<<CAUSEB_IP1);
    }

    spin_unlock_irqrestore(&brcm_irqlock, flags);
}


void mask_ack_brcm_irq(unsigned int irq)
{
    unsigned long flags;

    spin_lock_irqsave(&brcm_irqlock, flags);
    __disable_ack_brcm_irq(irq);

#if defined(CONFIG_SMP)
    if (irq == INTERRUPT_ID_SOFTWARE_0) {
        int this_cpu = smp_processor_id();
        int other_cpu = !this_cpu;
        per_cpu(ipi_pending, this_cpu) = 0;
        mb();
        clear_c0_cause(1<<CAUSEB_IP0);
        if (per_cpu(ipi_pending, other_cpu)) {
            set_c0_cause(1<<CAUSEB_IP0);
        }
        clear_c0_status(1<<STATUSB_IP0);
    }
#else
    if (irq == INTERRUPT_ID_SOFTWARE_0) {
        clear_c0_status(1<<STATUSB_IP0);
        clear_c0_cause(1<<CAUSEB_IP0);
    }
#endif

    if (irq == INTERRUPT_ID_SOFTWARE_1) {
        clear_c0_status(1<<STATUSB_IP1);
        clear_c0_cause(1<<CAUSEB_IP1);
    }

    spin_unlock_irqrestore(&brcm_irqlock, flags);
}


void unmask_brcm_irq_noop(unsigned int irq)
{
}

void set_brcm_affinity(unsigned int irq, const struct cpumask *mask)
{
    int cpu;
    struct irq_desc *desc = irq_desc + irq;
    unsigned long flags;

    spin_lock_irqsave(&brcm_irqlock, flags);

    if( irq >= INTERNAL_ISR_TABLE_OFFSET ) {
        for_each_online_cpu(cpu) {
            if (cpu_isset(cpu, *mask) && !(desc->status & IRQ_DISABLED)) {
                brcm_irq_ctrl[cpu]->IrqMask |= (((IRQ_TYPE)1)  << (irq - INTERNAL_ISR_TABLE_OFFSET));
            }
            else {
                brcm_irq_ctrl[cpu]->IrqMask &= ~(((IRQ_TYPE)1) << (irq - INTERNAL_ISR_TABLE_OFFSET));
            }
        }
    }

    spin_unlock_irqrestore(&brcm_irqlock, flags);
}

#define ALLINTS_NOTIMER IE_IRQ0

static struct irq_chip brcm_irq_chip = {
    .name = "BCM63xx",
    .enable = enable_brcm_irq,
    .disable = disable_brcm_irq,
    .ack = ack_brcm_irq,
    .mask = disable_brcm_irq,
    .mask_ack = mask_ack_brcm_irq,
    .unmask = enable_brcm_irq,
    .set_affinity = set_brcm_affinity
};

static struct irq_chip brcm_irq_chip_no_unmask = {
    .name = "BCM63xx",
    .enable = enable_brcm_irq,
    .disable = disable_brcm_irq,
    .ack = ack_brcm_irq,
    .mask = disable_brcm_irq,
    .mask_ack = mask_ack_brcm_irq,
    .unmask = unmask_brcm_irq_noop,
    .set_affinity = set_brcm_affinity
};


void __init arch_init_irq(void)
{
    int i;

    spin_lock_init(&brcm_irqlock);

    for (i = 0; i < NR_CPUS; i++) {
        brcm_irq_ctrl[i] = &PERF->IrqControl[i];
    }

    for (i = 0; i < NR_IRQS; i++) {
        set_irq_chip_and_handler(i, &brcm_irq_chip, handle_level_irq); 
    }

    clear_c0_status(ST0_BEV);
    change_c0_status(ST0_IM, ALLINTS_NOTIMER);

#ifdef CONFIG_REMOTE_DEBUG
    rs_kgdb_hook(0);
#endif
}


// This is a wrapper to standand Linux request_irq
// Differences are:
//    - The irq won't be renabled after ISR is done and needs to be explicity re-enabled, which is good for NAPI drivers.
//      The change is implemented by filling in an no-op unmask function in brcm_irq_chip_no_unmask and set it as the irq_chip
//    - IRQ flags and interrupt names are automatically set
// Either request_irq or BcmHalMapInterrupt can be used. Just make sure re-enabling IRQ is handled correctly.

unsigned int BcmHalMapInterrupt(FN_HANDLER pfunc, unsigned int param, unsigned int irq)
{
    char *devname;
    unsigned long irqflags;

    devname = kmalloc(16, GFP_KERNEL);
    if (!devname) {
        return -1;
    }
    sprintf( devname, "brcm_%d", irq );

    set_irq_chip_and_handler(irq, &brcm_irq_chip_no_unmask, handle_level_irq);

    irqflags = IRQF_DISABLED | IRQF_SAMPLE_RANDOM;

#if defined(CONFIG_BCM96368) || defined(CONFIG_BCM96816)
    if( irq == INTERRUPT_ID_MPI ) {
        irqflags |= IRQF_SHARED;
    }
#endif

    return request_irq(irq, (void*)pfunc, irqflags, devname, (void *) param);
}

// This is a wrapper to standand Linux request_irq for the VOIP driver
// Differences are:
// The irq is not automatically enabled when the ISR is registered.
// The irq is automatically re-enabled when the ISR is done.
// Interrupts are re-enabled when the ISR is invoked.
unsigned int BcmHalMapInterruptVoip(FN_HANDLER pfunc, unsigned int param, unsigned int irq)
{
    char *devname;
    unsigned long irqflags;
    unsigned long flags;
    struct irq_desc *desc = irq_desc + irq;
	
    devname = kmalloc(16, GFP_KERNEL);
    if (!devname) {
        return -1;
    }
    sprintf( devname, "brcm_%d", irq );

    set_irq_chip_and_handler(irq, &brcm_irq_chip, handle_level_irq);

    spin_lock_irqsave(&desc->lock, flags);   
    desc->status |= IRQ_NOAUTOEN;
    desc->status &= ~IRQ_DISABLED;
    spin_unlock_irqrestore(&desc->lock, flags);

    irqflags = IRQF_SAMPLE_RANDOM;

#if defined(CONFIG_BCM96358) || defined(CONFIG_BCM96368) || defined(CONFIG_BCM96816)
    if( irq == INTERRUPT_ID_MPI ) {
        irqflags |= IRQF_SHARED;
    }
#endif

    return request_irq(irq, (void*)pfunc, irqflags, devname, (void *) param);
}

//***************************************************************************
//  void  BcmHalGenerateSoftInterrupt
//
//   Triggers a software interrupt.
//
//***************************************************************************
void BcmHalGenerateSoftInterrupt( unsigned int irq )
{
    unsigned long flags;

    local_irq_save(flags);

    set_c0_cause(0x1 << (CAUSEB_IP0 + irq - INTERRUPT_ID_SOFTWARE_0));

    local_irq_restore(flags);
}


EXPORT_SYMBOL(enable_brcm_irq);
EXPORT_SYMBOL(disable_brcm_irq);
EXPORT_SYMBOL(BcmHalMapInterrupt);
EXPORT_SYMBOL(BcmHalMapInterruptVoip);
EXPORT_SYMBOL(BcmHalGenerateSoftInterrupt);

// bill
EXPORT_SYMBOL(disable_brcm_irqsave);
EXPORT_SYMBOL(restore_brcm_irqsave);

