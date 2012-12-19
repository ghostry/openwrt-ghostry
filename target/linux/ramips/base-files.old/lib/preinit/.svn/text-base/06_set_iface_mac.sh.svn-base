#
# Copyright (C) 2011 OpenWrt.org
#

ralink_set_mac() {
	local part
	local mac
	local skip="${1:-4}"

	[ -z $(which maccalc) ] && return

	. /etc/functions.sh

	part=$(find_mtd_part "factory")
	[ -z $part ] && return
#Switch and WLAN
	mac=$(dd bs=1 skip=${skip} count=6 if=$part 2>/dev/null | maccalc bin2mac)
	[ -z $mac ] && return

	mac=$(maccalc or "$mac" "02:00:00:00:00:00")
	ifconfig eth0 hw ether $mac 2>/dev/null
}

preinit_set_mac_address() {
	. /lib/ramips.sh

	case $(ramips_board_name) in
	nw718)
		ralink_set_mac
		;;
	rt-n13)
		ralink_set_mac
		;;
	hg256)
		ralink_set_mac 73732
		;;
	hg255d)
		ralink_set_mac
		;;
	esac
}

boot_hook_add preinit_main preinit_set_mac_address
