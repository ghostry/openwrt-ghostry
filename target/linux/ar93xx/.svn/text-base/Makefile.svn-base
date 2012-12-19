#
# Copyright (C) 2008-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=mips
BOARD:=ar93xx
BOARDNAME:=Atheros AR913x/AR934x Trunk 
FEATURES:=squashfs jffs2 targz
CFLAGS:=-Os -pipe -mips32r2 -mtune=mips32r2 -funit-at-a-time

LINUX_VERSION:=2.6.32.48

include $(INCLUDE_DIR)/target.mk

DEFAULT_PACKAGES += \
	kmod-leds-gpio kmod-input-core kmod-input-polldev \
	kmod-input-gpio-buttons kmod-button-hotplug swconfig \
	kmod-ath9k wpad-mini

define Target/Description
	Build firmware images for Atheros AR913x/AR934x based boards.
endef

$(eval $(call BuildTarget))
