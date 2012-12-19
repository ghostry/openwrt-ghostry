#
# Copyright (C) lintel<lintel.huang@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=opendpi
PKG_VERSION:=1.3.0
PKG_RELEASE:=1
PKG_SOURCE_URL:=http://opendpi.googlecode.com/files/

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_FIXUP:=libtool
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define KernelPackage/ipt-opendpi
  SUBMENU:=Netfilter Extensions
  TITLE:= OpenDPI net netfilter module
  DEPENDS:=@!LINUX_2_4  +kmod-ipt-compat-xtables +libpcap
  KCONFIG:=CONFIG_NF_CONNTRACK \
	   CONFIG_NF_CONNTRACK_EVENTS=y	 
  FILES:=$(PKG_BUILD_DIR)/wrapper/src/xt_opendpi.$(LINUX_KMOD_SUFFIX)
 AUTOLOAD:=$(call AutoLoad,46,xt_opendpi)

endef

define Package/iptables-mod-opendpi
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Firewall
  TITLE:=Extensions for iptables-module-opendpi
  DEPENDS:= @!LINUX_2_4 +iptables +kmod-ipt-opendpi +iptables-mod-conntrack
  URL:=http://www.opendpi.org/
endef

EXTRA_CFLAGS:=

MAKE_OPTS:= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	OPENDPI_PATH=$(PKG_BUILD_DIR) \
	SUBDIRS="$(PKG_BUILD_DIR)/wrapper"

define Build/Prepare
$(call Build/Prepare/Default)
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r ./src/wrapper $(PKG_BUILD_DIR)/
endef

define Build/Compile
$(call Build/Compile/Default)
#	$(MAKE) -C "$(LINUX_DIR)" \
#		$(MAKE_OPTS) \
#		modules
	$(MAKE) -C $(PKG_BUILD_DIR)/wrapper/src OPENDPI_PATH=$(PKG_BUILD_DIR) KERNEL_DIR:=$(LINUX_DIR) \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)"

	$(MAKE) -C $(PKG_BUILD_DIR)/wrapper/ipt \
		OPENDPI_PATH=$(PKG_BUILD_DIR)  \
		$(TARGET_CONFIGURE_OPTS) \
		STAGING_DIR="$(STAGING_DIR)" \
		CFLAGS="$(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I$(PKG_BUILD_DIR)/wrapper/ipt/opendpi_cpy/include -I$(PKG_BUILD_DIR)/wrapper/src -fPIC"       \
		LDFLAGS="$(TARGET_LDFLAGS) -L$(STAGING_DIR)/usr/lib"  \
		all
endef

define Package/iptables-mod-opendpi/install
	mkdir -p  $(1)/usr/lib/iptables
	$(CP) $(PKG_BUILD_DIR)/wrapper/ipt/libxt_opendpi.so $(1)/usr/lib/iptables
endef

$(eval $(call KernelPackage,ipt-opendpi))
$(eval $(call BuildPackage,iptables-mod-opendpi))
