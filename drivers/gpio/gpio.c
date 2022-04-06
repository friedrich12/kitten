/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */
#include "gpio.h"

#define mmio_read32(offset)         *((volatile uint32_t *)(ahci_dev.bar_vaddr + (offset)))
#define mmio_write32(offset, value) *((volatile uint32_t *)(ahci_dev.bar_vaddr + (offset))) = (value)

static vaddr_t SUNXI_PIO_BASE = 0;
spinlock_t lock;

int sunxi_gpio_set_cfgpin(unsigned int pin, unsigned int val)
{
        unsigned long flags;
	unsigned int cfg;
	unsigned int bank	= GPIO_BANK(pin);
	unsigned int index	= GPIO_CFG_INDEX(pin);
	unsigned int offset = GPIO_CFG_OFFSET(pin);

//        printk(" I GOT HERE 1 \n");
	if (SUNXI_PIO_BASE == 0) {
		return -1;
	}

  //      printk(" I GOT HERE 2 \n");
	struct sunxi_gpio * pio =
		&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];


    //    printk(" I GOT HERE 3 \n");
	spin_lock_irqsave(&lock, flags);
        {

      //          printk(" I GOT HERE 4 \n");
                cfg = *(&pio->cfg[0] + index);

        //        printk(" I GOT HERE 5 \n");
	        cfg &= ~(0xf << offset);
	        cfg |= val << offset;


          //      printk(" I GOT HERE 6 \n");
                *(&pio->cfg[0] + index) = cfg;
	        //writel((phys_addr_t) cfg, (phys_addr_t) (&pio->cfg[0] + index) );


            //    printk(" I GOT HERE 7 \n");
        }
        spin_unlock_irqrestore(&lock, flags);


        //printk(" I GOT HERE 8 \n");

	return 0;
}


int sunxi_gpio_get_cfgpin(unsigned int pin)
{
	unsigned int cfg;
	unsigned int bank	= GPIO_BANK(pin);
	unsigned int index	= GPIO_CFG_INDEX(pin);
	unsigned int offset = GPIO_CFG_OFFSET(pin);

	if (SUNXI_PIO_BASE == 0) {
		return -1;
	}

	struct sunxi_gpio * pio =
		&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

	//cfg = readl(&pio->cfg[0] + index);
	cfg = *(&pio->cfg[0] + index);
        cfg >>= offset;

	return (cfg & 0xf);
}


int sunxi_gpio_output(unsigned int pin, unsigned int val)
{
	unsigned int dat;
        unsigned int flags;
	unsigned int bank = GPIO_BANK(pin);
	unsigned int num  = GPIO_NUM(pin);

	if (SUNXI_PIO_BASE == 0) {
		return -1;
	}

	struct sunxi_gpio * pio =
		&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

        spin_lock_irqsave(&lock, flags);
        {
	        //dat = readl(&pio->dat);
	        dat = *(&pio->dat);
                if (val){
		        dat |= 1 << num;
                }else{
		        dat &= ~(1 << num);
                }
                *(&pio->dat) = dat;
	       // writel(dat, &pio->dat);
        }
        spin_unlock_irqrestore(&lock, flags);

	return 0;
}


int sunxi_gpio_input(unsigned int pin)
{
	unsigned int dat;
	unsigned int bank = GPIO_BANK(pin);
	unsigned int num  = GPIO_NUM(pin);

	if (SUNXI_PIO_BASE == 0) {
		return -1;
	}

	struct sunxi_gpio * pio =
		&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

	//dat = readl(&pio->dat);
	dat = *(&pio->dat);
        dat >>= num;

	return (dat & 0x1);
}

int test_gpios(){

        sunxi_gpio_set_cfgpin(SUNXI_GPB(1), SUNXI_GPIO_OUTPUT);

        printk("I GOT HERE\n");
        
        while(1){
                sunxi_gpio_output(SUNXI_GPB(1), 0);
                sunxi_gpio_output(SUNXI_GPB(1), 1);
        }
}

int sunxi_gpio_init()
{
        printk("GPIO DRIVER UP\n");

	paddr_t addr_start, addr_offset, addr;
	vaddr_t		 pc;

        // Alignment stuff
	addr_start	= SW_PORT_IO_BASE & PAGE_MASK;
	addr_offset = SW_PORT_IO_BASE & ~PAGE_MASK;

        printk("sunxi gpio base start: paddr=0x%016lx\n", addr_start);

        // MAP IN MEMORY
        printk("PAGE SIZE %d", PAGE_SIZE);
        pc = (vaddr_t) ioremap_nocache(addr_start, PAGE_SIZE * 2); 

	SUNXI_PIO_BASE = pc;
	SUNXI_PIO_BASE += addr_offset;

        printk("SIZE OF uintptr_t %d", sizeof(uintptr_t));
        printk("addr_offset: 0x%016lx", addr_offset);
	printk("gpiobase: vaddr=0x%016lx\n", SUNXI_PIO_BASE);
	printk("gpiobase: paddr=0x%016lx\n", virt_to_phys(SUNXI_PIO_BASE));

        //test_gpios();

        printk("GPIO DONE\n");

	return 0;
}

DRIVER_INIT("late", sunxi_gpio_init);
