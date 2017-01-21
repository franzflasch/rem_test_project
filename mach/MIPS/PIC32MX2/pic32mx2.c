/*
 * PIC32MX2_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stdint.h>
#include <mx2/sfr.h>
#include <mx2/config.h>

#include <stdlib.h>
#include <OMM_machine_common.h>
#include <gpio_common.h>

// Configuration bits:
// - Internal 8Mhz OSC with PLL -> 40Mhz
// - JTAG enabled
DECLARE_CONFIG(0, 0x7FFFFFFF); 
DECLARE_CONFIG(1, 0xFFF4EFF9); 
DECLARE_CONFIG(2, 0xFFF9F9D9); 
DECLARE_CONFIG(3, 0xFFFFFFFF);

void OMM_busy_delay(uint32_t val)
{
    uint32_t j = 0;
    for(j=0;j<(val*1000);j++)
            __asm__("nop");
}

static void MACH_PIC32MX2_gpio_setup(void)
{
   // set RB0 and RB1 as output
   TRISBCLR = 3;

   // set outputs to zero
   LATBCLR = 3;
}

static void set_gpio(uint8_t pin, uint8_t val)
{
    switch(pin)
    {
        case 0:
            if(val == GPIO_COMMON_HIGH)
                LATBINV |= (1<<0);
            else if (val == GPIO_COMMON_LOW)
                LATBINV &= ~(1<<0);
            break;
        case 1:
            if(val == GPIO_COMMON_HIGH)
                LATBINV |= (1<<1);
            else if (val == GPIO_COMMON_LOW)
                LATBINV &= ~(1<<1);
            break;
        default:
            break;
    }
}

static void MACH_PIC32MX2_gpio_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
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

    MACH_PIC32MX2_gpio_setup();
    GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_PIC32MX2_gpio_set, NULL, NULL);

    machine.pdev_list = &pdevs[0];

    return &machine;
}

