#ifndef GPIO_H
#define GPIO_H

#include "bitops.h"
#include <lwk/driver.h>
#include <lwk/pci/pci.h>
#include <lwk/interrupt.h>
#include <arch/fixmap.h>
#include <arch/io.h>
#include <lwk/blkdev.h>
#include <lwk/delay.h>
#include <lwk/spinlock.h>

#define BGPIOF_BIG_ENDIAN BIT(0)
#define BGPIOF_UNREADABLE_REG_SET BIT(1) /* reg_set is unreadable */
#define BGPIOF_UNREADABLE_REG_DIR BIT(2) /* reg_dir is unreadable */
#define BGPIOF_BIG_ENDIAN_BYTE_ORDER BIT(3)
#define BGPIOF_READ_OUTPUT_REG_SET BIT(4) /* reg_set stores output value */
#define BGPIOF_NO_OUTPUT BIT(5)			  /* only input */
#define BGPIOF_NO_SET_ON_INPUT BIT(6)
#define GPIO_LINE_DIRECTION_IN 1
#define GPIO_LINE_DIRECTION_OUT 0


struct gpio_chip {
	const char *		 label;
	struct gpio_device * gpiodev;
	struct device *		 parent;
	struct module *		 owner;

	int (*request)(struct gpio_chip * gc,
				   unsigned int		  offset);
	void (*free)(struct gpio_chip * gc,
				 unsigned int		offset);
	int (*get_direction)(struct gpio_chip * gc,
						 unsigned int		offset);
	int (*direction_input)(struct gpio_chip * gc,
						   unsigned int		  offset);
	int (*direction_output)(struct gpio_chip * gc,
							unsigned int	   offset,
							int				   value);
	int (*get)(struct gpio_chip * gc,
			   unsigned int		  offset);
	int (*get_multiple)(struct gpio_chip * gc,
						unsigned long *	   mask,
						unsigned long *	   bits);
	void (*set)(struct gpio_chip * gc,
				unsigned int	   offset,
				int				   value);
	void (*set_multiple)(struct gpio_chip * gc,
						 unsigned long *	mask,
						 unsigned long *	bits);
	int (*set_config)(struct gpio_chip * gc,
					  unsigned int		 offset,
					  unsigned long		 config);
	int (*to_irq)(struct gpio_chip * gc,
				  unsigned int		 offset);

	void (*dbg_show)(struct seq_file *	s,
					 struct gpio_chip * gc);

	int (*init_valid_mask)(struct gpio_chip * gc,
						   unsigned long *	  valid_mask,
						   unsigned int		  ngpios);

	int (*add_pin_ranges)(struct gpio_chip * gc);

	int					 base;
	u16					 ngpio;
	u16					 offset;
	const char * const * names;
	bool				 can_sleep;

	//#if IS_ENABLED(CONFIG_GPIO_GENERIC)
	unsigned long (*read_reg)(void __iomem * reg);
	void (*write_reg)(void __iomem * reg, unsigned long data);
	bool be_bits;
	void __iomem * reg_dat;
	void __iomem * reg_set;
	void __iomem * reg_clr;
	void __iomem * reg_dir_out;
	void __iomem * reg_dir_in;
	bool		   bgpio_dir_unreadable;
	int			   bgpio_bits;
	spinlock_t	   bgpio_lock;
	unsigned long  bgpio_data;
	unsigned long  bgpio_dir;
	//#endif /* CONFIG_GPIO_GENERIC */

#ifdef CONFIG_GPIOLIB_IRQCHIP
	/*
	 * With CONFIG_GPIOLIB_IRQCHIP we get an irqchip inside the gpiolib
	 * to handle IRQs for most practical cases.
	 */

	/**
	 * @irq:
	 *
	 * Integrates interrupt chip functionality with the GPIO chip. Can be
	 * used to handle IRQs for most practical cases.
	 */
	struct gpio_irq_chip irq;
#endif /* CONFIG_GPIOLIB_IRQCHIP */

	/**
	 * @valid_mask:
	 *
	 * If not %NULL, holds bitmask of GPIOs which are valid to be used
	 * from the chip.
	 */
	unsigned long * valid_mask;

#if defined(CONFIG_OF_GPIO)
	/*
	 * If CONFIG_OF_GPIO is enabled, then all GPIO controllers described in
	 * the device tree automatically may have an OF translation
	 */

	/**
	 * @of_node:
	 *
	 * Pointer to a device tree node representing this GPIO controller.
	 */
	struct device_node * of_node;

	/**
	 * @of_gpio_n_cells:
	 *
	 * Number of cells used to form the GPIO specifier.
	 */
	unsigned int of_gpio_n_cells;

	/**
	 * @of_xlate:
	 *
	 * Callback to translate a device tree GPIO specifier into a chip-
	 * relative GPIO number and flags.
	 */
	int (*of_xlate)(struct gpio_chip *			   gc,
					const struct of_phandle_args * gpiospec,
					u32 *						   flags);
#endif /* CONFIG_OF_GPIO */
};

#endif
