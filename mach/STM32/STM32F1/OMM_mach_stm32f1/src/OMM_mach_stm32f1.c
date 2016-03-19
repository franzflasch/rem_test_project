/*
 * STM32F1_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stm32f10x.h>
#include <stm32f10x_conf.h>

#include <stdlib.h>
#include <OMM_machine_common.h>

#include <gpio_common.h>

static void MACH_STM32F1_gpio_setup(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void set_gpio(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
		case 0:
			if(val == GPIO_COMMON_HIGH)
				GPIO_SetBits(GPIOC, GPIO_Pin_8);
			else if (val == GPIO_COMMON_LOW)
				GPIO_ResetBits(GPIOC, GPIO_Pin_8);
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

	MACH_STM32F1_gpio_setup();
	GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_STM32F1_gpio_set, NULL);

	machine.pdev_list = &pdevs[0];

	return &machine;
}
