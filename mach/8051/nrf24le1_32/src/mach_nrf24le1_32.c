/*
 * 
 *  Created on: Feb 24, 2015
 *      Author: fflasch
 */

#include <stdio.h>

#include <OMM_machine_common.h>
#include <gpio_common.h>
#include <gpio.h>
#include <delay.h>

gpio_pin_id_t mach_gpio_arr[] = 
{
    GPIO_PIN_ID_P0_0
};
#define GPIO_ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

static void GPIO_DRV_setup(void)
{
    uint8_t i = 0;

    for(i=0;i<GPIO_ARR_SIZE(mach_gpio_arr);i++)
    {
        gpio_pin_configure(mach_gpio_arr[i],
                GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT |
                GPIO_PIN_CONFIG_OPTION_OUTPUT_VAL_CLEAR |
                GPIO_PIN_CONFIG_OPTION_PIN_MODE_OUTPUT_BUFFER_NORMAL_DRIVE_STRENGTH);
    }
}

static void MACH_GPIO_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
{
    if(pin > GPIO_ARR_SIZE(mach_gpio_arr))
        return;

    if(gpio->mode == ACTIVE_LOW)
    {
        if(val == GPIO_COMMON_HIGH)
            gpio_pin_val_clear(mach_gpio_arr[pin]);
        else
            gpio_pin_val_set(mach_gpio_arr[pin]);
    }
    else
    {
        if(val == GPIO_COMMON_HIGH)
            gpio_pin_val_set(mach_gpio_arr[pin]);
        else
            gpio_pin_val_clear(mach_gpio_arr[pin]);   
    }
}

void OMM_busy_delay(uint32_t val)
{
    delay_ms(val); 
}

OMM_machine_t *machine_setup(void)
{
    uint8_t gpio_val = 0;
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
    GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_GPIO_set, NULL, NULL);

    machine.pdev_list = &pdevs[0];

    return &machine;
}
