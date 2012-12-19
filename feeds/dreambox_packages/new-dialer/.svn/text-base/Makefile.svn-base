#
# Copyright (C) 2010 Jo-Philipp Wich <xm@subsignal.org>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=new-dialer
PKG_RELEASE:=1.2.2007.5

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/new-dialer/default

endef

define Package/new-dialer
  SECTION:=net
  CATEGORY:=Network
  TITLE:=new-dialer
  MAINTAINER:=Emong <emongxx@gmail.com>
  $(Package/new-dialer/default)
endef

define Package/new-dialer/description
 new-dialer helps you do something.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/new-dialer/conffiles
endef

define Package/new-dialer/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ghca $(1)/usr/bin/new-dialer
	$(CP) ./files/* $(1)
endef


$(eval $(call BuildPackage,new-dialer))
