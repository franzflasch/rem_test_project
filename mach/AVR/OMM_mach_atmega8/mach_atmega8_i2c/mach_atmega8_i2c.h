/*
 * mach_atmega8_i2c.h
 *
 *  Created on: Mar 8, 2015
 *      Author: franz
 */

#ifndef MACH_ATMEGA8_I2C_H_
#define MACH_ATMEGA8_I2C_H_

#include <i2c_common.h>

void i2c_init(void);
uint8_t TWIM_send_byte(i2c_device_t *i2c, uint8_t val);
uint8_t TWIM_receive_byte(i2c_device_t *i2c);
uint8_t TWIM_send_msg_cmd(i2c_device_t *i2c, uint8_t cmd, uint8_t *data, uint8_t count);
uint8_t TWIM_receive_msg_cmd(i2c_device_t *i2c, uint8_t cmd, uint8_t *data, uint8_t count);



#endif /* ARCH_AVR8_OMM_MACH_ATMEGA8_MACH_ATMEGA8_I2C_MACH_ATMEGA8_I2C_H_ */
