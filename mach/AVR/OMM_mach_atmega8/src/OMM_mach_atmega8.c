/*
 * OMM_mach_avr_mini_wi.c
 *
 *  Created on: Feb 24, 2015
 *      Author: fflasch
 */

#include <avr/io.h>
#include <OMM_machine_common.h>

#include <gpio_common.h>
#include <stdio.h>


static void GPIO_DRV_setup(void)
{
	#define GPIO_NR_PINS  1
	#define LED_PORT PORTB
	#define LED_DDR  DDRB
	#define LED_PIN0  PB1

	LED_DDR  |= (1 << LED_PIN0);
}

static void set_gpio(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
		case 0:
			if(val == GPIO_COMMON_HIGH)
				LED_PORT |= (1 << LED_PIN0);
			else if (val == GPIO_COMMON_LOW)
				LED_PORT &= ~(1 << LED_PIN0);
			break;
		default:
			break;
	}
}

static void MACH_GPIO_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
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

	GPIO_DRV_setup();
	GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_GPIO_set, NULL);

	machine.pdev_list = &pdevs[0];

	return &machine;
}
