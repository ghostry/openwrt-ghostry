#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=u-boot
PKG_VERSION:=2010.03
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE:=u-boot-2010.03-s3c24xx-openwrt.tar.bz2
PKG_SOURCE_URL:=http://openwrt-arm.googlecode.com/files/
#PKG_MD5SUM:=2bf5ebf497dddc52440b1ea386cc1332
PKG_CAT:=bzcat

include $(INCLUDE_DIR)/package.mk

define Package/uboot-s3c24xx
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_s3c24xx
  TITLE:=U-Boot for s3c24xx boards
  URL:=http://www.denx.de/wiki/U-Boot
  MENU:=1
endef

UBOOT_CONFIG=$(call qstrip,$(CONFIG_MINI2440_UBOOT_TARGET))

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) smdk2440_config
	$(MAKE) -C $(PKG_BUILD_DIR) CROSS_COMPILE=$(TARGET_CROSS)
endef

define Build/InstallDev
	mkdir -p $(BIN_DIR)
	dd if=$(PKG_BUILD_DIR)/u-boot.bin of=$(BIN_DIR)/u-boot-s3c24xx.bin bs=128k conv=sync
endef


$(eval $(call BuildPackage,uboot-s3c24xx))
