/*
 * PIC32MX2_blinky.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#include <stdint.h>
#include <mz2048/sfr.h>
#include <config.h>

#include <stdlib.h>
#include <OMM_machine_common.h>
#include <gpio_common.h>

// Configuration bits:
// - 12MHz DIV1 MUL32 DIV2 = 192000000
// - JTAG enabled
DECLARE_CONFIG(0, 0x40007777); 
DECLARE_CONFIG(1, 0xdff4c7ff); 
DECLARE_CONFIG(2, 0xc0011fa0); 
DECLARE_CONFIG(3, 0x7b000000);
DECLARE_CP(0, 0x10000000);

#define LED_TRIS    TRISHbits.TRISH2    // macro for direction register bit of the LED pin
#define LED_LAT     LATHbits.LATH2      // macro for output register bit of the LED pin

void OMM_busy_delay(uint32_t val)
{
    uint32_t j = 0;
    for(j=0;j<(val*1000);j++)
            __asm__("nop");
}

static void MACH_PIC32MZ2048_gpio_setup(void)
{
    LED_TRIS = 0;
}

static void set_gpio(uint8_t pin, uint8_t val)
{
    switch(pin)
    {
        case 0:
            if(val == GPIO_COMMON_HIGH)
                LED_LAT |= (1<<0);
            else if (val == GPIO_COMMON_LOW)
                LED_LAT &= ~(1<<0);
            break;
        default:
            break;
    }
}

static void MACH_PIC32MZ2048_gpio_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val)
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
    //SYSTEMConfigPerformance(192000000L);

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

    MACH_PIC32MZ2048_gpio_setup();
    GPIO_init_controller(&gpio, ACTIVE_HIGH, 1, MACH_PIC32MZ2048_gpio_set, NULL, NULL);

    machine.pdev_list = &pdevs[0];

    return &machine;
}

