# Package name
PKG_NAME := ATMEGA8_UART

# What are the dependencies of this PKG? Please list them here
#PKG_DEPS :=

# Used defines for this project
#PKG_DEFS := "F_CPU=1000000"

# Describe local package sources here
PKG_SRC := src/uart_avr.c

# just take all c files in the source folder:
#PKG_SRC := $(wildcard $(BASEDIR)/src/*.c)
#PKG_SRC := $(subst $(BASEDIR)/,,$(PKG_SRC))	# remove basedir when using wildcard search as the basedir will be added later anyways

# Describe local include headers
PKG_INC := inc/

$(call omm_arch_mach_package,AVR8,ATMEGA8)
