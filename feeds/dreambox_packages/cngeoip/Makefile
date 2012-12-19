# 
# Copyright (C) 20009-2011 OpenWrt.org.cn
#
include $(TOPDIR)/rules.mk

PKG_NAME:=cngeoip
PKG_VERSION:=0.1.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/cngeoip
  SECTION:=utils
  CATEGORY:=Base system
  DEPENDS:=+iptables +iptables-mod-filter +kmod-ipt-geoip +iptables-mod-geoip
  TITLE:=band fair share among PCs
  PKGARCH:=all
endef

define Package/cngeoip/description
 The geoip database for china, you know what this mean! 
 you have to patch xtables-addons Makefile to produce xt_geoip ipks. 
endef

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/cngeoip/install
	$(INSTALL_DIR) $(1)
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,cngeoip))
