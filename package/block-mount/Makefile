#
# Copyright (C) 2006-2009 OpenWrt.org
# Copyright 2010 Vertical Communications
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=block-mount
PKG_VERSION:=0.1.0
PKG_RELEASE:=2.1

include $(INCLUDE_DIR)/package.mk

define Package/block-mount/Default
  SECTION:=base
  CATEGORY:=Base system
endef

define Package/block-mount
  $(call Package/block-mount/Default)
  TITLE:=Block device mounting and checking
endef

define Package/block-mount/description
  Scripts used to mount and check block devices (filesystems and swap)
endef

define Package/block-mount-allsupport
  $(call Package/block-mount/Default)
  TITLE:= mounting support uuid ntfs-3g ext..
  DEPENDS:= +blkid +swap-utils +libext2fs +e2fsprogs +ntfs-3g +fdisk +uuidgen +tune2fs +block-hotplug
endef

define Package/block-mount-allsupport/description
 block-mount package add blkid swap-utils libext2fs e2fsprogs ntfs-3g fdisk uuidgen tune2fs package
endef

define Package/block-hotplug
  $(call Package/block-mount/Default)
  TITLE:=Automount and autocheck block devices
  DEPENDS:=+block-mount +hotplug2
endef

define Package/block-hotplug/description
  Scripts used to automatically check and mount filesystem and/or swap
endef

define Build/Compile
endef

define Package/block-mount/conffiles
/etc/config/fstab
endef

define Package/block-mount-allsupport/install

endef


define Package/block-mount/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/fstab.init $(1)/etc/init.d/fstab
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DATA) ./files/fstab.config $(1)/etc/config/fstab
	$(INSTALL_DIR) $(1)/lib/functions
	$(INSTALL_DATA) ./files/mount.sh $(1)/lib/functions/
	$(INSTALL_DATA) ./files/fsck.sh $(1)/lib/functions/
	$(INSTALL_DATA) ./files/block.sh $(1)/lib/functions/
	$(INSTALL_DIR) 	$(1)/usr/bin
	$(INSTALL_BIN) ./files/disk_info $(1)/usr/bin/disk_info
endef

define Package/block-hotplug/install
	$(INSTALL_DIR) $(1)/etc/hotplug.d/block
	#$(INSTALL_DATA) ./files/10-swap $(1)/etc/hotplug.d/block/
	$(INSTALL_DATA) ./files/20-fsck $(1)/etc/hotplug.d/block/
	$(INSTALL_DATA) ./files/40-mount $(1)/etc/hotplug.d/block/
endef

$(eval $(call BuildPackage,block-mount))
$(eval $(call BuildPackage,block-mount-allsupport))
$(eval $(call BuildPackage,block-hotplug))

