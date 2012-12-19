#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# sav

include $(TOPDIR)/rules.mk

PKG_NAME:=mediatomb
PKG_VERSION:=0.12.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/mediatomb
PKG_BUILD_DEPENDS:=libexif sqlite3 id3lib libiconv file expat libpthread

include $(INCLUDE_DIR)/package.mk

define Package/mediatomb
  SECTION:=multimedia
  CATEGORY:=Multimedia
  DEPENDS:=+libexif +libsqlite3 +id3lib +libiconv-full +libcharset +iconv +file +libexpat +libpthread
  TITLE:=A powerfull UPNP media server
  URL:=http://www.mediatomb.cc/
endef

CONFIGURE_ARGS += \
	--prefix=/usr \
	--disable-inotify \
	--enable-id3lib \
	--enable-libexif \
	--enable-libmagic \
	--disable-libextractor \
	--enable-protocolinfo-extension \
	--disable-libjs \
	--disable-ffmpeg \
	--disable-tombdebug \
	--disable-upnpdebug \
	--disable-youtube \
	--disable-mysql \
	--enable-pthread-lib \

ifneq ($(CONFIG_USE_UCLIBC),)

CONFIGURE_ARGS += \
	--with-iconv-h=$(STAGING_DIR)/usr/lib/libiconv-full/include/ \
	--with-iconv-libs=$(STAGING_DIR)/usr/lib/libiconv-full/lib/ \

endif


define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		HOSTCC="$(HOSTCC)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		all install
endef

define Package/mediatomb/install
	$(INSTALL_DIR) $(1)/etc/mediatomb
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/share
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/mediatomb $(1)/usr/bin/
	$(CP)  $(PKG_INSTALL_DIR)/usr/share/* $(1)/usr/share/
	$(INSTALL_DATA)  ./files/config.xml $(1)/etc/mediatomb/
	$(INSTALL_BIN)  ./files/mediatomb.init $(1)/etc/init.d/mediatomb
endef

$(eval $(call BuildPackage,mediatomb))
