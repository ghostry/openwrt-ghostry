#
# Copyright (C) 2008-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=mipsel
BOARD:=ramips
BOARDNAME:=Ralink RT288x/RT3xxx
SUBTARGETS:=rt288x rt305x rt3883
#CFLAGS:=-Os -pipe -mips32r2 -mtune=mips32r2 -fno-caller-saves
CFLAGS:=-Os -pipe -mips32r2 -mtune=mips32r2 -funit-at-a-time
FEATURES:=squashfs

LINUX_VERSION:=2.6.32.59

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES+=\
	kmod-leds-gpio kmod-input-core kmod-input-polldev \
	kmod-input-gpio-buttons kmod-button-hotplug \
	kmod-rt2x00-lib kmod-rt2x00-pci kmod-rt2800-lib kmod-rt2800-pci wpad-mini maccalc swconfig

define Target/Description
	Build firmware images for Ralink RT288x/RT3xxx based boards.
endef

$(eval $(call BuildTarget))
