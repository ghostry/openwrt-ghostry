#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mhash
PKG_VERSION:=0.9.9.9
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=@SF/mhash
PKG_MD5SUM:=f91c74f9ccab2b574a98be5bc31eb280

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_CFLAGS += $(FPIC)

define Package/mhash
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=mhash library
  URL:=http://mhash.sourceforge.net/
endef

define Package/mhash/description
	libmhash is hash library that conveniently brings
	together a variety of ciphers for convenient use.
endef

define Build/Configure
	$(call Build/Configure/Default, \
		--enable-shared \
		--enable-static \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libmhash.{a,so*} $(1)/usr/lib/
endef

define Package/mhash/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libmhash.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,mhash))
