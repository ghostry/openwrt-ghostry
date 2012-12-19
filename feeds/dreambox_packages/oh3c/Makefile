# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=oh3c
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_REV:=a6f07917debf53599d78af511d203006c024c1cb


PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://github.com/nanpuyue/OH3C.git
PKG_SOURCE_VERSION:=$(PKG_REV)


include $(INCLUDE_DIR)/package.mk

define Package/oh3c
  SECTION:=net
  CATEGORY:=Network
	SUBMENU:=CERNET
  TITLE:=OH3C 802.1X client
  URL:=http://github.com/nanpuyue/oh3c
  DEPENDS:=+python-mini
endef

define Package/oh3c/description
 OH3C 802.1X client  
endef

define Build/Compile
endef


define Package/oh3c/install
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) files/oh3c.init $(1)/etc/init.d/oh3c
	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_CONF) files/oh3c.conf $(1)/etc/config/oh3c
	$(INSTALL_DIR) $(1)/usr/share/oh3c
	$(CP) $(PKG_BUILD_DIR)/oh3c/* $(1)/usr/share/oh3c/
endef

$(eval $(call BuildPackage,oh3c))
