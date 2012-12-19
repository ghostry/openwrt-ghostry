#
# Copyright (C) 2010-2012 OpenWrt-DreamBox
#
#  lintel<lintel.huang@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=mips
BOARD:=brcm63x8
BOARDNAME:=Broadcom BCM63x8
FEATURES:=squashfs  usb atm pci pcmcia
LINUX_VERSION:=2.6.30.10
#SUBTARGETS=rg100a db120

include $(INCLUDE_DIR)/target.mk

#DEFAULT_PACKAGES += wpad-mini kmod-switch gpioctl kmod-usb-core kmod-usb2 \
#		kmod-input-gpio-buttons kmod-input-evdev  kmod-leds-gpio \
#		kmod-bcm63xx-spi kmod-button-hotplug

DEFAULT_PACKAGES += gpioctl \

define Target/Description
	Build firmware images for Broadcom based xDSL/routers
	currently supports BCM6328 BCM6358 based devices with DSL Support.
	(e.g. P-660, RG100A-CA)
endef

$(eval $(call BuildTarget))
