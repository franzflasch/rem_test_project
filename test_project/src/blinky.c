#include <stdint.h>
#include <OMM_machine_common.h>
#include <gpio_common.h>
#include <cordic.h>
#include <stdio.h>


int main (void)
{
	int sin = 0;
	int cos = 0;
	uint8_t gpio_val = 0;
	gpio_controller_t *gpio = NULL;

	OMM_machine_t *machine = machine_setup();

	gpio = OMM_get_pdev_by_name(machine, "gpio_0");
	//gpio = OMM_get_pdev_by_index(machine, 0);
	cordic_sincos(3, 10, &sin, &cos);

    while (1)
    {
    	gpio_val ^= 1 << 0;
    	GPIO_set(gpio, 0, gpio_val);
    	GPIO_set(gpio, 1, !gpio_val);
    	OMM_busy_delay(1500);
    }
}
