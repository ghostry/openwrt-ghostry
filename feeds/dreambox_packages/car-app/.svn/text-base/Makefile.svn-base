#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=car-app
PKG_RELEASE:=1
PKG_VERSION:=1.0

include $(INCLUDE_DIR)/package.mk

define Package/car-app
  SECTION:=net
  CATEGORY:=Network
  TITLE:=WiFi-Car Server

endef

define Package/car-app/description
	Servers for wifi-car
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) CFLAGS="$(TARGET_CFLAGS) -I$(LINUX_DIR)/include"
endef

define Package/car-app/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/car-server $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/car-test $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/car-autorun $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/car-server.init $(1)/etc/init.d/car-server
endef

$(eval $(call BuildPackage,car-app))
