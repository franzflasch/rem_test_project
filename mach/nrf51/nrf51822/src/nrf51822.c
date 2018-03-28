#include <stdlib.h>
#include <OMM_machine_common.h>
#include <nrf_delay.h>
#include <nrf_gpio.h>

#include <gpio_common.h>

void OMM_busy_delay(uint32_t val)
{
	nrf_delay_ms(val);
}

static void MACH_NRF51822_gpio_setup(void)
{
	nrf_gpio_range_cfg_output(18,19);
}

static void set_gpio(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
		case 0:
			if(val == GPIO_COMMON_HIGH)
				nrf_gpio_pin_set(18);
			else if (val == GPIO_COMMON_LOW)
				nrf_gpio_pin_clear(18);
			break;
		case 1:
			if(val == GPIO_COMMON_HIGH)
				nrf_gpio_pin_set(19);
			else if (val == GPIO_COMMON_LOW)
				nrf_gpio_pin_clear(19);
			break;
		default:
			break;
	}
}

static void MACH_NRF51822_gpio_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
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

	MACH_NRF51822_gpio_setup();
	GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_NRF51822_gpio_set, NULL, NULL);

	machine.pdev_list = &pdevs[0];

	return &machine;
}

