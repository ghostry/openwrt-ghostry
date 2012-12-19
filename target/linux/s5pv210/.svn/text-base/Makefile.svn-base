#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=s5pv210
BOARDNAME:=Samsung S5PV210
FEATURES:=jffs2 squashfs
CFLAGS:=-O2 -pipe -march=armv7-a -mtune=cortex-a8 -funit-at-a-time -mfpu=vfp -mfloat-abi=softfp
SUBTARGETS:=tiny210 mini210

LINUX_VERSION:=2.6.35.7

#DEVICE_TYPE=phone

define Target/Description
	S5PV210 arm
endef

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += kmod-gpio-dev gpioctl

$(eval $(call BuildTarget))
