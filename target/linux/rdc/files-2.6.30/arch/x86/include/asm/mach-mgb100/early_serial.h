/*
  early_serial_out from openwrt
  add by Lintel

use:

  early_serial_init();  to init
  early_serial_write();  to write (must init  frist)

Example:
  early_serial_init(); 
  early_serial_write("Uncompressing Linux...\n", 512);


Mail:lintel77@qq.com

*/
static int early_serial_base = 0x3f8;  /* ttyS0 */

#define XMTRDY          0x20

#define DLAB            0x80

#define TXR             0       /*  Transmit register (WRITE) */
#define RXR             0       /*  Receive register  (READ)  */
#define IER             1       /*  Interrupt Enable          */
#define IIR             2       /*  Interrupt ID              */
#define FCR             2       /*  FIFO control              */
#define LCR             3       /*  Line control              */
#define MCR             4       /*  Modem control             */
#define LSR             5       /*  Line Status               */
#define MSR             6       /*  Modem Status              */
#define DLL             0       /*  Divisor Latch Low         */
#define DLH             1       /*  Divisor latch High        */


static int early_serial_putc(unsigned char ch)
{
        unsigned timeout = 0xffff;
        while ((inb(early_serial_base + LSR) & XMTRDY) == 0 && --timeout)
                cpu_relax();
        outb(ch, early_serial_base + TXR);
        return timeout ? 0 : -1;
}

static void early_serial_write(const char *s, unsigned n)
{
        while (*s && n-- > 0) {
                if (*s == '\n')
                        early_serial_putc('\r');
                early_serial_putc(*s);
                s++;
        }
}

#define DEFAULT_BAUD 38400

static __init void early_serial_init(void)
{
        unsigned char c;
        unsigned divisor;
        unsigned baud = DEFAULT_BAUD;
        char *e;

        outb(0x3, early_serial_base + LCR);     /* 8n1 */
        outb(0, early_serial_base + IER);       /* no interrupt */
        outb(0, early_serial_base + FCR);       /* no fifo */
        outb(0x3, early_serial_base + MCR);     /* DTR + RTS */

	baud = DEFAULT_BAUD;

        divisor = 115200 / baud;
        c = inb(early_serial_base + LCR);
        outb(c | DLAB, early_serial_base + LCR);
        outb(divisor & 0xff, early_serial_base + DLL);
        outb((divisor >> 8) & 0xff, early_serial_base + DLH);
        outb(c & ~DLAB, early_serial_base + LCR);
} 
