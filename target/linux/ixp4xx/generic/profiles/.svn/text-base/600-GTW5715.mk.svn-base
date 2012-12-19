#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/GTWX5715
  NAME:=GTWX5715(WRV54G)
  PACKAGES:=kmod-via-velocity \
	kmod-ath5k wireless-tools \
	kmod-scsi-core \
	kmod-ata-core kmod-ata-artop \
	kmod-usb-core kmod-usb-uhci kmod-usb2 kmod-usb-storage \
	kmod-fs-ext2 kmod-fs-ext3 kmod-ath9k kmod-leds-gpio\
	kmod-spi-gpio-old kmod-spi-ks8995 kmod-ledtrig-morse
endef

define Profile/GTWX5715/Description
	Package set optimized for the Linksys WRV54G
endef
$(eval $(call Profile,GTWX5715))

