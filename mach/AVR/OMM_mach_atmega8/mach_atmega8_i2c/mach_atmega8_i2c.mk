PKG_NAME := MACH_ATMEGA8_I2C

# What are the dependencies of this PKG? Please list them here
PKG_DEPS := OPENMICROMAKE
PKG_DEPS += I2C_COMMON

PKG_SRC := mach_atmega8_i2c.c

PKG_INC := .

$(call omm_arch_package,AVR8,ATMEGA8)