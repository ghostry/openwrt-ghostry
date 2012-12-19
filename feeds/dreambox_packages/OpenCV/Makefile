#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=OpenCV
PKG_VERSION:=2.4.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=@SF/opencvlibrary/files/opencv-unix/2.4.0/
PKG_SOURCE_URL:=http://nchc.dl.sourceforge.net/project/opencvlibrary/files/opencv-unix/2.4.0/
#PKG_MD5SUM:=0d2a089bfbfa550e0c65618a171fb3c4

PKG_FIXUP = libtool

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/OpenCV/Default
#  SUBMENU:=Instant Messaging
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=OpenCV
  MAINTAINER:=lintel <lintel.huang@gmail.com>
  URL:=http://www.OpenCV.org/
endef

define Package/OpenCV/Default/description
 Weechat is fast, light & extensible IRC client.
endef


define Package/OpenCV
$(call Package/OpenCV/Default)
 DEPENDS:=+libjpeg +libpng +libffmpeg +libswscale +libiconv +bzip2 +gtk +gtkmm +gtkperf $(ICONV_DEPENDS)
endef

define Package/OpenCV/description
$(call Package/OpenCV/Default/description)
endef

CMAKE_OPTIONS+= \
	-DCMAKE_STRIP=ON \
#	-DCMAKE_INSTALL_PREFIX=$(STAGING_DIR)/usr \
	-BZIP2_LIBRARIES=$(STAGING_DIR)/usr/lib \
# 	--enable-static \
	-DHAVE_CUDA=OFF \
#	-DBUILD_TESTS=OFF \
	-ZLIB_INCLUDE_DIR=$(STAGING_DIR)/usr/include \
	-ZLIB_LIBRARY=$(STAGING_DIR)/usr/lib \
	-DWITH_QT=ON \
	-DWITH_GTK=ON \
	-WITH_QT_OPENGL=OFF \

TARGET_LDFLAGS += \
	-L$(ICONV_PREFIX)/lib \
	-Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Build/InstallDev
	mkdir -p $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr $(1)/
endef


define Package/OpenCV/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,OpenCV))
