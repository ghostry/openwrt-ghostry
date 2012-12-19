#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=reaver
PKG_VERSION:=1.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://reaver-wps.googlecode.com/files
PKG_MD5SUM:=05441dda7bacfcbe1e831c85d1ea3bc9

include $(INCLUDE_DIR)/package.mk

define Package/reaver
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=wireless
  TITLE:=Brute force attack against Wifi Protected Setup
  URL:=https://code.google.com/p/reaver-wps/
  DEPENDS:=+libpcap
#  DEPENDS:=+libpcap +sqlite3 +libsqlite3-dev
endef

define Package/reaver/description
  Reaver targets the external registrar functionality mandated by the WiFi
  Protected Setup specification.
  Access points will provide authenticated registrars with their current
  wireless configuration (including the WPA PSK), and also accept a new
  configuration from the registrar.
endef

CONFIGURE_PATH:=src

MAKE_PATH:=src

TARGET_CFLAGS+=$(TARGET_CPPFLAGS)

define Package/reaver/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/reaver $(1)/usr/bin/
endef

$(eval $(call BuildPackage,reaver)) 

