/*
 * STM32F1_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stdio.h>
#include <stdlib.h>
#include <OMM_machine_common.h>
#include <gpio_common.h>
#include <unistd.h>

void OMM_busy_delay(uint32_t val)
{
	usleep(val*1000);
}

static void linux_gpio_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
{
	printf("Setting gpio %d to %d\n", pin, val);
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

	GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, linux_gpio_set, NULL, NULL);

	machine.pdev_list = &pdevs[0];

	return &machine;
}

