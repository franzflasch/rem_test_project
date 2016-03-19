PKG_NAME := mach_atmega8
PKG_SRC := src/OMM_mach_atmega8.c
PKG_DEPS := omm_common
PKG_DEPS += gpio_common

include scripts/OMM_package_rules.mk

#define Package/$(PKG_NAME)/Info
#	$(info Package info:)
#	$(info $(PKG_NAME))
#	$(info $(PKG_SRC))
#endef

#define Package/Download/$(PKG_NAME)
#	$(info Hey I am overriding the default download method!:)
#endef

#define Package/Build/$(PKG_NAME)
#	$(info overiding default $(PKG_NAME) build)
#endef

$(eval $(call Package/Setup,$(PKG_NAME)))
