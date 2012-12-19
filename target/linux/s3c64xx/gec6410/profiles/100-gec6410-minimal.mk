#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/gec6410-minimal
  NAME:=GEC6410 (minimal)
  PACKAGES:=
endef

define Profile/gec6410-minimal/Description
	minimal Package set compatible with the GEC6410 hardware
endef
$(eval $(call Profile,gec6410-minimal))

