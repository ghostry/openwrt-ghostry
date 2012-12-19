Source-Makefile: feeds/packages/libs/zaptel-1.4.x/Makefile
Package: kmod-zaptel14
Submenu: Other modules
Version: <LINUX_VERSION>+1.4.12.1-4
Depends: 
Provides: 
Section: kernel
Category: Kernel modules
Title: Zaptel (kernel module)
Maintainer: OpenWrt Developers Team <openwrt-devel@openwrt.org>
Source: zaptel-1.4.12.1.tar.gz
Type: ipkg
Description:  This package contains the Zaptel ztdummy driver.  Broken on x86 due to lack
 of RTC on some hardware.
@@

Package: kmod-zaptel14-dummy
Submenu: Other modules
Version: <LINUX_VERSION>+1.4.12.1-4
Depends:  +kmod-zaptel14 @TARGET_x86:@BROKEN
Provides: 
Section: kernel
Category: Kernel modules
Title: Zaptel Dummy (timer; kernel module)
Maintainer: OpenWrt Developers Team <openwrt-devel@openwrt.org>
Source: zaptel-1.4.12.1.tar.gz
Type: ipkg
Description: Zaptel Dummy (timer; kernel module)
@@

Package: kmod-zaptel14-wcusb
Submenu: Other modules
Version: <LINUX_VERSION>+1.4.12.1-4
Depends:  +kmod-zaptel14
Provides: 
Section: kernel
Category: Kernel modules
Title: Zaptel (kernel module)
Maintainer: OpenWrt Developers Team <openwrt-devel@openwrt.org>
Source: zaptel-1.4.12.1.tar.gz
Type: ipkg
Description:  This package contains the Zaptel S100U usb driver.
@@

Package: kmod-zaptel14-wctdm
Submenu: Other modules
Version: <LINUX_VERSION>+1.4.12.1-4
Depends:  +kmod-zaptel14
Provides: 
Section: kernel
Category: Kernel modules
Title: Zaptel (kernel module)
Maintainer: OpenWrt Developers Team <openwrt-devel@openwrt.org>
Source: zaptel-1.4.12.1.tar.gz
Type: ipkg
Description:  This package contains the Zaptel wctdm driver.
@@

Package: zaptel14-util
Version: 1.4.12.1-4
Depends:  +kmod-zaptel14 +zaptel14-libtonezone +libnewt
Provides: 
Section: utils
Category: Utilities
Title: Zaptel utils
Maintainer: OpenWrt Developers Team <openwrt-devel@openwrt.org>
Source: zaptel-1.4.12.1.tar.gz
Type: ipkg
Description:  This package contains the zaptel utils.
http://ftp.digium.com/pub/zaptel/releases
@@

Package: zaptel14-libtonezone
Version: 1.4.12.1-4
Depends:  +kmod-zaptel14
Provides: 
Section: libs
Category: Libraries
Title: Zaptel libtonezone (library)
Maintainer: OpenWrt Developers Team <openwrt-devel@openwrt.org>
Source: zaptel-1.4.12.1.tar.gz
Type: ipkg
Description:  This package contains the libraries for accessing zaptel/dummy drivers.
http://ftp.digium.com/pub/zaptel/releases
@@


