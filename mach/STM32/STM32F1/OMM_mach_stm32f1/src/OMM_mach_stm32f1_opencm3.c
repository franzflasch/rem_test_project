/*
 * STM32F1_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stdlib.h>
#include <OMM_machine_common.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include <gpio_common.h>

/* Set STM32 to 24 MHz. */
static void MACH_STM32F1_clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_24mhz();
}

static void MACH_STM32F1_gpio_setup(void)
{
	/* Enable GPIOC clock. */
	rcc_periph_clock_enable(RCC_GPIOC);

	/* Set GPIO8/9 (in GPIO port C) to 'output push-pull'. */
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO8);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO9);
}

static void set_gpio(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
		case 0:
			if(val == GPIO_COMMON_HIGH)
				gpio_set(GPIOC, GPIO8);
			else if (val == GPIO_COMMON_LOW)
				gpio_clear(GPIOC, GPIO8);
			break;
		case 1:
			if(val == GPIO_COMMON_HIGH)
				gpio_set(GPIOC, GPIO9);
			else if (val == GPIO_COMMON_LOW)
				gpio_clear(GPIOC, GPIO9);
			break;
		default:
			break;
	}
}

static void MACH_STM32F1_gpio_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
{
	if(gpio->mode == ACTIVE_LOW)
	{
		if(val == GPIO_COMMON_HIGH)
			set_gpio(pin, GPIO_COMMON_LOW);
		else
			set_gpio(pin, GPIO_COMMON_HIGH);
	}
	else
	{
		set_gpio(pin, val);
	}
}


OMM_machine_t __attribute__((weak)) *machine_setup(void)
{
	static OMM_machine_t machine =
	{
			.name = "OpenMicroMake"
	};

	static gpio_controller_t gpio;
	static OMM_platform_devices pdevs[] =
	{
			{"gpio_0", &gpio },
			{NULL, NULL}
	};

	MACH_STM32F1_clock_setup();
	MACH_STM32F1_gpio_setup();
	GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_STM32F1_gpio_set, NULL, NULL);

	machine.pdev_list = &pdevs[0];

	return &machine;
}

