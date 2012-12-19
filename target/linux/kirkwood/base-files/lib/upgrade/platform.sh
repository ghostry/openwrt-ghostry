#
# Copyright (C) 2009 OpenWrt.org
#

. /lib/kirkwood.sh

PART_NAME=firmware
RAMFS_COPY_DATA=/lib/kirkwood.sh

CI_BLKSZ=65536
CI_LDADR=0x80060000



platform_check_image() {
	local board=$(kirkwood_board_name)
	local magic="$(get_magic_word "$1")"
	local magic_long="$(get_magic_long "$1")"
	[ "$ARGC" -gt 1 ] && return 1
     	case "$board" in
         # hardware with padded uImage + padded rootfs
         'ddnasv1')
                [ "${magic}" != '2705' ] && {
                        echo "Invalid image type ${magic}."
                        return 1
                }
                return 0
                ;;
         'ddnasv2')
                [ "${magic}" != '2705' ] && {
                        echo "Invalid image type ${magic}."
                        return 1
                }
                return 0
                ;;
         # Netgear WNR854T has extra header before uImage
         'Netgear WNR854T')
                [ "${magic}" != '8519' ] && {
                        echo "Invalid image type ${magic}."
                        return 1
                }
                return 0
                ;;
        esac

        echo "Sysupgrade is not yet supported on ${hardware}."
        return 1
}

platform_do_upgrade() {
	local board=$(kirkwood_board_name)

	case "$board" in
	ddnas )
		default_do_upgrade "$ARGV"
		;;
	*)
		echo "is not ddnas"
		;;
	esac
}

disable_watchdog() {
	killall watchdog
	( ps | grep -v 'grep' | grep '/dev/watchdog' ) && {
		echo 'Could not disable watchdog'
		return 1
	}
}

append sysupgrade_pre_upgrade disable_watchdog
