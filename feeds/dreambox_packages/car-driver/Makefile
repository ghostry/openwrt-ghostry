#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=car-driver
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/car-driver
  SUBMENU:=Other modules
  TITLE:=Car-Drivers for WiFi-Car
  DEPENDS:=@GPIO_SUPPORT
  FILES:=$(PKG_BUILD_DIR)/car_driver.$(LINUX_KMOD_SUFFIX)
  AUTOLOAD:=$(call AutoLoad,10,car_driver)
endef

MAKE_OPTS:= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	SUBDIRS="$(PKG_BUILD_DIR)"

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)

ifeq ($(CONFIG_TARGET_s3c24xx),y)
	$(CP) ./src/car_driver_s3c24xx.c $(PKG_BUILD_DIR)/car_driver.c
endif
ifeq ($(CONFIG_TARGET_s3c64xx),y)
	$(CP) ./src/car_driver_s3c64xx.c $(PKG_BUILD_DIR)/car_driver.c
endif
	$(CP) ./src/Makefile $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,car-driver))
