/*
 * STM32F4_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stdlib.h>
#include <OMM_machine_common.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include <gpio_common.h>

static void MACH_STM32F4_gpio_setup(void)
{
	/* Enable GPIOD clock. */
	/* Manually: */
	// RCC_AHB1ENR |= RCC_AHB1ENR_IOPDEN;
	/* Using API functions: */
	rcc_periph_clock_enable(RCC_GPIOD);

	/* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
	/* Manually: */
	// GPIOD_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 4) + 2));
	// GPIOD_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((8 - 8) * 4));
	/* Using API functions: */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO15);
}

static void set_gpio(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
		case 0:
			if(val == GPIO_COMMON_HIGH)
				gpio_set(GPIOD, GPIO12);
			else if (val == GPIO_COMMON_LOW)
				gpio_clear(GPIOD, GPIO12);
			break;
		case 1:
			if(val == GPIO_COMMON_HIGH)
				gpio_set(GPIOD, GPIO14);
			else if (val == GPIO_COMMON_LOW)
				gpio_clear(GPIOD, GPIO14);
			break;
		default:
			break;
	}
}

static void MACH_STM32F4_gpio_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
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

	MACH_STM32F4_gpio_setup();
	GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_STM32F4_gpio_set, NULL);

	machine.pdev_list = &pdevs[0];

	return &machine;
}

