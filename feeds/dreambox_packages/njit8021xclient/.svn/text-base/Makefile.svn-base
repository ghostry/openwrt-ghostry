# 
# Copyright (C) 2012 OpenWrt.org.cn
# Copyright (C) feixiang<feixiang@openwrt.org.cn>
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=njit8021xclient
PKG_RELEASE:=1
PKG_VERSION:=1.2
PKG_SOURCE_URL:=https://github.com/downloads/liuqun/njit8021xclient/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=e56f158d6a2b10c0b72edee5eba2da9c

include $(INCLUDE_DIR)/package.mk

define Package/njit8021xclient
  SECTION:=net
  CATEGORY:=Network
	SUBMENU:=CERNET
  TITLE:=NJIT 802.1X client program
  URL:=http://liuqun.github.com/njit8021xclient
  DEPENDS:=+libpcap +libopenssl +libpthread 
endef

define Package/njit8021xclient/description
 802.1X client from Nanjing Institude of Technology,
 compatable with H3C iNode 802.1X client.
 Support H3C/iNode's private authentication protocol V2.40-V3.60
endef


define Package/njit8021xclient/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/client  $(1)/usr/sbin/njit-client
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) files/njit.init $(1)/etc/init.d/njit
	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_CONF) files/njit.conf $(1)/etc/config/njit
endef

$(eval $(call BuildPackage,njit8021xclient))
