#!/bin/sh
[ -e /etc/functions.sh ] && . /etc/functions.sh || . ./functions.sh
[ -x /sbin/modprobe ] && {
	insmod="modprobe"
	rmmod="$insmod -r"
} || {
	insmod="insmod"
	rmmod="rmmod"
}
 
add_insmod() {
	eval "export isset=\${insmod_$1}"
	case "$isset" in
		1) ;;
		*) {
			[ "$2" ] && append INSMOD "$rmmod $1 >&- 2>&-" "$N"
			append INSMOD "$insmod $* >&- 2>&-" "$N"; export insmod_$1=1
		};;
	esac
}

[ -e /etc/config/network ] && {
	# only try to parse network config on openwrt

	find_ifname() {(
		reset_cb
		include /lib/network
		scan_interfaces
		config_get "$1" ifname
	)}
} || {
	find_ifname() {
		echo "Interface not found."
		exit 1
	}
}

parse_matching_rule() {
	local var="$1"
	local section="$2"
	local options="$3"
	local prefix="$4"
	local suffix="$5"
	local proto="$6"
	local mport=""
	local ports=""

	append "$var" "$prefix" "$N"
	for option in $options; do
		case "$option" in
			proto) config_get value "$section" proto; proto="${proto:-$value}";;
		esac
	done
	config_get type "$section" TYPE
	case "$type" in
		classify) unset pkt; append "$var" "-m mark --mark 0";;
		default) pkt=1; append "$var" "-m mark --mark 0";;
		reclassify) pkt=1;;
	esac
	append "$var" "${proto:+-p $proto}"
	for option in $options; do
		config_get value "$section" "$option"
		
		case "$pkt:$option" in
			*:srchost)
				append "$var" "-s $value"
			;;
			*:dsthost)
				append "$var" "-d $value"
			;;
			*:layer7)
				add_insmod xt_opendpi

				append "$var" "-m opendpi --$value"
			;;
			*:ports|*:srcports|*:dstports)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				lproto=${lproto:-tcp}
				case "$proto" in
					""|tcp|udp) append "$var" "-m ${proto:-tcp -p tcp} -m multiport";;
					*) unset "$var"; return 0;;
				esac
				case "$option" in
					ports)
						config_set "$section" srcports ""
						config_set "$section" dstports ""
						config_set "$section" portrange ""
						append "$var" "--ports $value"
					;;
					srcports)
						config_set "$section" ports ""
						config_set "$section" dstports ""
						config_set "$section" portrange ""
						append "$var" "--sports $value"
					;;
					dstports)
						config_set "$section" ports ""
						config_set "$section" srcports ""
						config_set "$section" portrange ""
						append "$var" "--dports $value"
					;;
				esac
				ports=1
			;;
			*:portrange)
				config_set "$section" ports ""
				config_set "$section" srcports ""
				config_set "$section" dstports ""
				value="$(echo "$value" | sed -e 's,-,:,g')"
				case "$proto" in
					""|tcp|udp) append "$var" "-m ${proto:-tcp -p tcp} --sport $value --dport $value";;
					*) unset "$var"; return 0;;
				esac
				ports=1
			;;
			*:connbytes)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				add_insmod ipt_connbytes
				append "$var" "-m connbytes --connbytes $value --connbytes-dir both --connbytes-mode bytes"
			;;
			*:tos)
                                add_insmod ipt_tos
                                case "$value" in
                                        !*) append "$var" "-m tos ! --tos $value";;
                                        *) append "$var" "-m tos --tos $value"
                                esac
                        ;;
			*:dscp)
                                add_insmod ipt_dscp
				dscp_option="--dscp"
                                [ -z "${value%%[EBCA]*}" ] && dscp_option="--dscp-class"
				case "$value" in
                                       	!*) append "$var" "-m dscp ! $dscp_option $value";;
                                       	*) append "$var" "-m dscp $dscp_option $value"
                                esac
                        ;;
			*:direction)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				if [ "$value" = "out" ]; then
					append "$var" "-o $device"
				elif [ "$value" = "in" ]; then
					append "$var" "-i $device"
				fi
			;;
			1:pktsize)
				value="$(echo "$value" | sed -e 's,-,:,g')"
				add_insmod ipt_length
				append "$var" "-m length --length $value"
			;;
			1:limit)
				add_insmod ipt_limit
				append "$var" "-m limit --limit $value"
			;;
			1:tcpflags)
				case "$proto" in
					tcp) append "$var" "-m tcp --tcp-flags ALL $value";;
					*) unset $var; return 0;;
				esac
			;;
			1:mark)
				config_get class "${value##!}" classnr
				[ -z "$class" ] && continue;
				case "$value" in
					!*) append "$var" "-m mark ! --mark $class";;
					*) append "$var" "-m mark --mark $class";;
				esac
			;;
			1:TOS)
				add_insmod ipt_TOS
				config_get TOS "$rule" 'TOS'
				suffix="-j TOS --set-tos "${TOS:-"Normal-Service"}
			;;
			1:DSCP)
				add_insmod ipt_DSCP
				config_get DSCP "$rule" 'DSCP'
				[ -z "${DSCP%%[EBCA]*}" ] && set_value="--set-dscp-class $DSCP" \
				|| set_value="--set-dscp $DSCP"
				suffix="-j DSCP $set_value"
			;;
		esac
	done
	append "$var" "$suffix"
	case "$ports:$proto" in
		1:)	parse_matching_rule "$var" "$section" "$options" "$prefix" "$suffix" "udp";;
	esac
}

config_cb() {
	option_cb() {
		return 0
	}

	# Section start
	case "$1" in
		interface)
			config_set "$2" "classgroup" "Default"
			config_set "$2" "upload" "128"
		;;
		classify|default|reclassify)
			option_cb() {
				append options "$1"
			}
		;;
	esac

    # Section end
	config_get TYPE "$CONFIG_SECTION" TYPE
	case "$TYPE" in
		interface)
			config_get_bool enabled "$CONFIG_SECTION" enabled 1
			[ 1 -eq "$enabled" ] || return 0
			config_get classgroup "$CONFIG_SECTION" classgroup
			config_set "$CONFIG_SECTION" ifbdev "$C"
			C=$(($C+1))
			append INTERFACES "$CONFIG_SECTION"
			config_set "$classgroup" enabled 1
			config_get device "$CONFIG_SECTION" device
			[ -z "$device" ] && {
				device="$(find_ifname ${CONFIG_SECTION})"
				config_set "$CONFIG_SECTION" device "${device:-eth0}"
			}
		;;
		classgroup) append CG "$CONFIG_SECTION";;
		classify|default|reclassify)
			case "$TYPE" in
				classify) var="ctrules";;
				*) var="rules";;
			esac
			config_get target "$CONFIG_SECTION" target
			config_set "$CONFIG_SECTION" options "$options"
			append "$var" "$CONFIG_SECTION"
			unset options
		;;
	esac
}


enum_classes() {
	local c="0"
	config_get classes "$1" classes
	config_get default "$1" default
	for class in $classes; do
		c="$(($c + 1))"
		config_set "${class}" classnr $c
		case "$class" in
			$default) class_default=$c;;
		esac
	done
	class_default="${class_default:-$c}"
}

cls_var() {
	local varname="$1"
	local class="$2"
	local name="$3"
	local type="$4"
	local default="$5"
	local tmp tmp1 tmp2
	config_get tmp1 "$class" "$name"
	config_get tmp2 "${class}_${type}" "$name"
	tmp="${tmp2:-$tmp1}"
	tmp="${tmp:-$tmp2}"
	export ${varname}="${tmp:-$default}"
}

tcrules() {
	dir=/usr/lib/qos
	[ -e $dir/tcrules.awk ] || dir=.
	echo "$cstr" | awk \
		-v device="$dev" \
		-v linespeed="$rate" \
		-f $dir/tcrules.awk
}

start_interface() {
	local iface="$1"
	local num_ifb="$2"
	config_get device "$iface" device
	config_get_bool enabled "$iface" enabled 1
	[ -z "$device" -o 1 -ne "$enabled" ] && {
		return 1 
	}
	config_get upload "$iface" upload
	config_get_bool halfduplex "$iface" halfduplex
	config_get download "$iface" download
	config_get classgroup "$iface" classgroup
	config_get_bool overhead "$iface" overhead 0
	
	download="${download:-${halfduplex:+$upload}}"
	enum_classes "$classgroup"
	for dir in ${halfduplex:-up} ${download:+down}; do
		case "$dir" in
			up)
				[ "$overhead" = 1 ] && upload=$(($upload * 98 / 100 - (15 * 128 / $upload)))
				dev="$device"
				rate="$upload"
				dl_mode=""
				prefix="cls"
			;;
			down)
				[ "$(ls -d /proc/sys/net/ipv4/conf/ifb* 2>&- | wc -l)" -ne "$num_ifb" ] && add_insmod ifb numifbs="$num_ifb"
				config_get ifbdev "$iface" ifbdev
				[ "$overhead" = 1 ] && download=$(($download * 98 / 100 - (80 * 1024 / $download)))
				dev="ifb$ifbdev"
				rate="$download"
				dl_mode=1
				prefix="d_cls"
			;;
			*) continue;;
		esac
		cstr=
		for class in $classes; do
			cls_var pktsize "$class" packetsize $dir 1500
			cls_var pktdelay "$class" packetdelay $dir 0
			cls_var maxrate "$class" limitrate $dir 100
			cls_var prio "$class" priority $dir 1
			cls_var avgrate "$class" avgrate $dir 0
			cls_var qdisc "$class" qdisc $dir ""
			cls_var filter "$class" filter $dir ""
			config_get classnr "$class" classnr
			append cstr "$classnr:$prio:$avgrate:$pktsize:$pktdelay:$maxrate:$qdisc:$filter" "$N"
		done
		append ${prefix}q "$(tcrules)" "$N"
		export dev_${dir}="ifconfig $dev up txqueuelen 5 >&- 2>&-
tc qdisc del dev $dev root >&- 2>&-
tc qdisc add dev $dev root handle 1: htb default ${class_default}0
tc class add dev $dev parent 1: classid 1:1 htb  rate ${rate}kbit ceil ${rate}kbit"
	done
	[ -n "$download" ] && {
		add_insmod cls_u32
		add_insmod em_u32
		add_insmod act_connmark
		add_insmod act_mirred
		add_insmod sch_ingress
	}
	if [ -n "$halfduplex" ]; then
		export dev_up="tc qdisc del dev $device root >&- 2>&-
tc qdisc add dev $device root handle 1: htb
tc filter add dev $device parent 1: protocol ip prio 10 u32 match u32 0 0 flowid 1:1 action connmark action mirred egress redirect dev ifb$ifbdev"
	elif [ -n "$download" ]; then
		append dev_${dir} "tc qdisc del dev $device ingress >&- 2>&-
tc qdisc add dev $device ingress
tc filter add dev $device parent ffff: protocol ip prio 1 u32 match u32 0 0 flowid 1:1 action connmark action mirred egress redirect dev ifb$ifbdev" "$N"
	fi
	add_insmod cls_fw
	add_insmod sch_htb
	add_insmod sch_sfq
	add_insmod sch_red

	cat <<EOF
${INSMOD:+$INSMOD$N}${dev_up:+$dev_up
tc class add dev $device parent 1:1 classid 1:10 htb rate 15kbps ceil "$upload"kbit prio 1
tc class add dev $device parent 1:1 classid 1:20 htb rate 20kbps ceil "$upload"kbit prio 2
tc class add dev $device parent 1:1 classid 1:30 htb rate 10kbps ceil "$upload"kbit prio 3 
tc class add dev $device parent 1:1 classid 1:4 htb rate 10kbps ceil $(($upload * 80 /100))kbit 
tc class add dev $device parent 1:4 classid 1:40 htb rate 5kbps ceil $(($upload * 80 /100))kbit prio 4 
tc class add dev $device parent 1:4 classid 1:50 htb rate 5kbps ceil $(($upload * 80 /100))kbit prio 5 
tc filter add dev $device parent 1: prio 1 protocol ip handle 1 fw flowid 1:10
tc filter add dev $device parent 1: prio 2 protocol ip handle 2 fw flowid 1:20
tc filter add dev $device parent 1: prio 3 protocol ip handle 3 fw flowid 1:30
tc filter add dev $device parent 1: prio 4 protocol ip handle 4 fw flowid 1:40
tc filter add dev $device parent 1: prio 4 protocol ip handle 9 fw flowid 1:40
tc filter add dev $device parent 1: prio 5 protocol ip handle 5 fw flowid 1:50
$clsq
}${ifbdev:+$dev_down
tc class add dev ifb$ifbdev parent 1:1 classid 1:10 htb rate 30kbps ceil "$download"kbit prio 1
tc class add dev ifb$ifbdev parent 1:1 classid 1:20 htb rate 50kbps ceil "$download"kbit prio 2
tc class add dev ifb$ifbdev parent 1:1 classid 1:3 htb rate 100kbps ceil $(($download * 85 /100))kbit 
tc class add dev ifb$ifbdev parent 1:3 classid 1:30 htb rate 50kbps ceil $(($download * 85 /100))kbit prio 3
tc class add dev ifb$ifbdev parent 1:3 classid 1:40 htb rate 50kbps ceil $(($download * 85 /100))kbit prio 4
tc filter add dev ifb$ifbdev parent 1: prio 1 protocol ip handle 1 fw flowid 1:10
tc filter add dev ifb$ifbdev parent 1: prio 2 protocol ip handle 2 fw flowid 1:20
tc filter add dev ifb$ifbdev parent 1: prio 3 protocol ip handle 3 fw flowid 1:30
tc filter add dev ifb$ifbdev parent 1: prio 4 protocol ip handle 4 fw flowid 1:40
$d_clsq
$d_clsl
$d_clsf
}
EOF
	unset INSMOD clsq clsf clsl d_clsq d_clsl d_clsf dev_up dev_down
}

start_interfaces() {
     local C="$1"
        for iface in $INTERFACES; do
                start_interface "$iface" "$C"
        done
}

add_rules() {
	local var="$1"
	local rules="$2"
	local prefix="$3"
	
	for rule in $rules; do
		unset iptrule
		config_get target "$rule" target
		config_get target "$target" classnr
		config_get options "$rule" options

		## If we want to override the TOS field, let's clear the DSCP field first.
		[ ! -z "$(echo $options | grep 'TOS')" ] && {
			s_options=${options%%TOS}
			add_insmod ipt_DSCP
			parse_matching_rule iptrule "$rule" "$s_options" "$prefix" "-j DSCP --set-dscp 0"
			append "$var" "$iptrule" "$N"
			unset iptrule
		}

		parse_matching_rule iptrule "$rule" "$options" "$prefix" "-j MARK --set-mark $target"
		append "$var" "$iptrule" "$N"
	done
}

start_cg() {
	local cg="$1"
	local iptrules
	local pktrules
	local sizerules
	enum_classes "$cg"
	add_rules iptrules "$ctrules" "iptables -t mangle -A ${cg}_ct"
	config_get classes "$cg" classes
	for class in $classes; do
		config_get mark "$class" classnr
		config_get maxsize "$class" maxsize
		[ -z "$maxsize" -o -z "$mark" ] || {
			add_insmod ipt_length
			append pktrules "iptables -t mangle -A ${cg} -m mark --mark $mark -m length --length ${maxsize}: -j MARK --set-mark 0" "$N"
		}
	done
	add_rules pktrules "$rules" "iptables -t mangle -A ${cg}"
	for iface in $INTERFACES; do
		config_get classgroup "$iface" classgroup
		config_get device "$iface" device
		config_get ifbdev "$iface" ifbdev
		config_get upload "$iface" upload
		config_get download "$iface" download
		config_get halfduplex "$iface" halfduplex
		download="${download:-${halfduplex:+$upload}}"
		append up "iptables -t mangle -A OUTPUT -o $device -j ${cg}" "$N"
		append up "iptables -t mangle -A FORWARD -o $device -j ${cg}" "$N"
	done
	add_insmod xt_opendpi
	cat <<EOF
$INSMOD
iptables -t mangle -N Default
iptables -t mangle -N Default_ct
iptables -t mangle -A Default_ct -m mark --mark 0 -m tcp -p tcp -m multiport --ports 22,53 -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -p udp -m udp -m multiport --ports 22,53 -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -p tcp -m tcp -m multiport --ports 80,3389,3390,5900,1080,1194 -j MARK --set-mark 3

iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --hf -j MARK --set-mark 1
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --pt11 -j MARK --set-mark 1
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --warcraft -j MARK --set-mark 1
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --counterstrike -j MARK --set-mark 1
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --crossfire  -j MARK --set-mark 1

iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --qq -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --irc -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --aliwangwang -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --msn -j MARK --set-mark 2  
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --jabber -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --worldofwarcraft  -j MARK --set-mark 2
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --rdp -j MARK --set-mark 2 

iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --httpactivesync -j MARK --set-mark 3
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --http -j MARK --set-mark 3
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --telnet -j MARK --set-mark 3  
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --flash -j MARK --set-mark 3
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --ntp -j MARK --set-mark 3 
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7  --l7proto jpeg -j MARK --set-mark 3
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7  --l7proto png -j MARK --set-mark 3
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7  --l7proto gif -j MARK --set-mark 3
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7  --l7proto pdf -j MARK --set-mark 3 
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --mdns -j MARK --set-mark 3  

iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --ppstream -j MARK --set-mark 4
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --qqlive -j MARK --set-mark 4
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --bittorrent -j MARK --set-mark 4
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --ftp -j MARK --set-mark 4 
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --feidian -j MARK --set-mark 4 
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --ddl -j  MARK --set-mark 4

iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --fasttrack -j  MARK --set-mark 5 
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7 --l7proto rar -j MARK --set-mark 5 
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7 --l7proto zip -j MARK --set-mark 5
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7 --l7proto exe -j MARK --set-mark 5
iptables -t mangle -A Default_ct -m mark --mark 0 -m layer7 --l7proto tar -j MARK --set-mark 5 

iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --funshion -j MARK --set-mark 9
#iptables -t mangle -A Default_ct -m mark --mark 0 -m ipp2p --ipp2p -j MARK --set-mark 9
iptables -t mangle -A Default_ct -m mark --mark 9 -m recent --set --name funshion --rsource --rport 
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --pptv -j MARK --set-mark 8
iptables -t mangle -A Default_ct -m mark --mark 0 -m opendpi --thunder -j MARK --set-mark 8
iptables -t mangle -A Default_ct -m mark --mark 8 -m recent --set --name p2p_up --rsource --rport -j MARK --set-mark 0x4
iptables -t mangle -A Default_ct -j CONNMARK --save-mark
iptables -t mangle -A Default -m connmark --mark 0 -m recent --update --seconds 600 --name p2p_up --rsource --rport -j CONNMARK --set-mark 0x4
iptables -t mangle -A Default -m connmark --mark 0 -m recent --update --seconds 600 --name funshion --rsource --rport -j CONNMARK --set-mark 0x9
iptables -t mangle -A Default -m connmark --mark 3 -m opendpi --thunder -j CONNMARK --set-mark 4
iptables -t mangle -A Default -j CONNMARK --restore-mark
iptables -t mangle -A Default -m mark --mark 0 -j Default_ct
iptables -t mangle -A Default -m mark --mark 1 -m length --length 400: -j MARK --set-mark 0
iptables -t mangle -A Default -m mark --mark 2 -m length --length 800: -j MARK --set-mark 0
iptables -t mangle -A Default -p icmp -j MARK --set-mark 1
iptables -t mangle -A Default -p tcp -m length --length :128 -m mark  --mark 3 -m tcp --tcp-flags ALL SYN -j MARK --set-mark 2
iptables -t mangle -A Default -p tcp -m length --length :128 -m mark  --mark 3 -m tcp --tcp-flags ALL ACK -j MARK --set-mark 2
iptables -t mangle -A Default -p tcp -m length --length :128 -m mark  --mark 0 -m tcp --tcp-flags ALL SYN -j MARK --set-mark 3
iptables -t mangle -A Default -p tcp -m length --length :128 -m mark  --mark 0 -m tcp --tcp-flags ALL ACK -j MARK --set-mark 3
iptables -t mangle -A Default -m mark --mark 0 -p udp -m length --length 0: -j MARK --set-mark 4
iptables -t mangle -A Default -m mark --mark 0 -p tcp -m length --length 0: -j MARK --set-mark 4
iptables -t mangle -A Default -m mark --mark 4 -p udp -m length --length 300: -j MARK --set-mark 5
iptables -t mangle -A Default -m mark --mark 4 -p tcp -m length --length 300: -j MARK --set-mark 5
iptables -t mangle -A Default -m mark --mark 9 -p udp -m length --length 300: -j MARK --set-mark 5
iptables -t mangle -A Default -m mark --mark 9 -p tcp -m length --length 300: -j MARK --set-mark 5

iptables -t mangle -A OUTPUT -o $device -j Default
iptables -t mangle -A FORWARD -o $device -j Default
iptables -t mangle -N Default_dn >&- 2>&-
iptables -t mangle -N Default_ct_dn >&- 2>&-
iptables -t mangle -A Default_dn -j CONNMARK --restore-mark
iptables -t mangle -A Default_dn -m mark --mark 0 -j Default_ct_dn
iptables -t mangle -A INPUT -i $device -j Default_dn
iptables -t mangle -A FORWARD -i $device -j Default_dn
EOF
	unset INSMOD
}

start_firewall() {
	add_insmod ipt_multiport
	add_insmod ipt_CONNMARK
	cat <<EOF
iptables -t mangle -F
iptables -t mangle -X
EOF
	for group in $CG; do
		start_cg $group
	done
}

C="0"
INTERFACES=""
[ -e ./qos.conf ] && {
	. ./qos.conf
	config_cb
} || config_load qos

C="0"
for iface in $INTERFACES; do
	export C="$(($C + 1))"
done

case "$1" in
	all)
		start_interfaces "$C"
		start_firewall
	;;
	interface)
		start_interface "$2" "$C"
	;;
	interfaces)
		start_interfaces
	;;
	firewall)
		start_firewall
	;;
esac
