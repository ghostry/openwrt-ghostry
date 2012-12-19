#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=mgb-tools
PKG_RELEASE:=10

PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
STAMP_PREPARED := $(STAMP_PREPARED)

include $(INCLUDE_DIR)/package.mk

define Package/mgb-tools
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=Utility for change MGB100 settings
  DEPENDS:=@TARGET_rdc
endef

define Package/mgb-tools/description
 This package contains an Utility for change MGB100 redboot settings,E.T.MAC address, 
 redboot bootcmd.AMIT firmware upgrage tool.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

target=$(firstword $(subst -, ,$(BOARD)))

MAKE_FLAGS += TARGET="$(target)"
TARGET_CFLAGS += -Dtarget_$(target)=1 -Wall


define Package/mgb-tools/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/flashamit $(1)/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mgb100cfg $(1)/sbin/
endef

$(eval $(call BuildPackage,mgb-tools))
