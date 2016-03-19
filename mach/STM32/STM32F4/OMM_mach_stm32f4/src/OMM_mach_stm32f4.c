/*
 * STM32F4_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>

#include <stdlib.h>
#include <OMM_machine_common.h>

#include <gpio_common.h>

static void MACH_STM32F4_gpio_setup(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

static void set_gpio(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
		case 0:
			if(val == GPIO_COMMON_HIGH)
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
			else if (val == GPIO_COMMON_LOW)
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			break;
		case 1:
			if(val == GPIO_COMMON_HIGH)
				GPIO_SetBits(GPIOD, GPIO_Pin_15);
			else if (val == GPIO_COMMON_LOW)
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);
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

