#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk


PKG_NAME:=opencv-sample
PKG_RELEASE:=1
PKG_VERSION:=1.0

include $(INCLUDE_DIR)/package.mk
#include $(INCLUDE_DIR)/nls.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS+= \
	-DCMAKE_STRIP=ON \

TARGET_LDFLAGS += \
	-L$(ICONV_PREFIX)/lib \
	-Wl,-rpath-link,$(STAGING_DIR)/usr/lib
TARGET_CFLAGS += \
	-I$(STAGING_DIR)/usr/include

define Package/opencv-sample
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=OpenCV sample
  DEPENDS:=+OpenCV
endef

define Package/opencv-sample/description
	Tool for opencv
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

#define Build/Compile
#	$(MAKE) -C $(PKG_BUILD_DIR)
#endef

define Package/opencv-sample/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/opencv_facedetect $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/opencv_drawing $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/opencv_minarea $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/catty.jpg $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/catty-left.jpg $(1)/usr/bin/
	$(CP)  $(PKG_BUILD_DIR)/haarcascade_eye.xml $(1)/usr/bin/
	$(CP)  $(PKG_BUILD_DIR)/haarcascade_frontalface_alt.xml $(1)/usr/bin/

endef

$(eval $(call BuildPackage,opencv-sample))
