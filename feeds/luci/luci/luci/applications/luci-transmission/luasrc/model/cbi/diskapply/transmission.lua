require("luci.tools.webadmin")

--[[
config 'transmission'
	option 'config_dir' '/mnt/sda1/root'
	option 'download_dir' '/mnt/sda1/root'
	option 'speed_limit_up' '20'
	option 'speed_limit_up_enabled' '1'
	option 'rpc_whitelist' '127.0.0.1,192.168.*.*'
	option 'rpc_whitelist_enabled' '1'
	option 'queue_enabled' '1'
	option 'queue_max_downloadings' '1'
	option 'queue_max_seedings' '5'
	option 'queue_interval' '30'
	option 'enable' '1'
	option 'speed_limit_down_enabled' '0'      
	option 'speed_limit_down' '180'
	option 'rpc_authentication_required' 'true'    
	option 'rpc_enabled' 'true'
	option 'rpc_password' 'openwrtcn'                     
	option 'rpc_username' 'openwrtcn'
	option 'peer_limit_global' '300'
	option 'peer_limit_per_torrent' '80'
	option 'preallocation' '1'
	option 'peer_port' '51413'
	option 'rpc_port' '9091'
	option 'rpc_username' 'abc'
	option 'rpc_password' '123'
]]--

require("luci.sys")
local uci = require "luci.model.uci".cursor()
local lanipaddr = uci:get("network", "lan", "ipaddr") or "192.168.1.1"
local trport = uci:get_first("transmission", "transmission", "rpc_port") or "9091"


m = Map("transmission", translate("Transmission_title","Transmission"),
                    translate("Transmission_title_desc","Transmission setting page"))



s = m:section(TypedSection, "transmission", translate("Transmission_set","Transmission_set setting"))
s.anonymous = true
s.addremove = false

s:option(DummyValue,"trweb" ,translate("<a target=\"_blank\" href='http://"..lanipaddr..":"..trport.."'>Transmission Web Intelface</a> "),translate("Open the Transmission Web"))

enable = s:option(Flag, "enabled", translate("Transmission_enable", "Transmission_enable"))
enable.default = false
enable.optional = false
enable.rmempty = false

config_dir = s:option(Value, "config_dir", translate("config_dir","config dir"),
          translate("config_dir_desc","config dir default"))
config_dir.optional = false
config_dir.rmempty = false

download_dir = s:option(Value, "download_dir", translate("download_dir","download dir"),
          translate("download_dir_desc","download dir default"))
download_dir.optional = false
download_dir.rmempty = false
if nixio.fs.access("/etc/config/fstab") then
        download_dir.titleref = luci.dispatcher.build_url("admin", "diskapply", "fstab")
end

watch_dir_enabled = s:option(Flag, "watch_dir_enabled", translate("watch_dir_enabled", "watch dir enabled"),
 	translate("watch_dir_enabled_desc","watch dir enabled desc"))
watch_dir_enabled.default = false
watch_dir_enabled.optional = false
watch_dir_enabled.rmempty = false

watch_dir= s:option(Value, "watch_dir", translate("watch_dir","watch dir"),
          translate("watch_dir_desc","watch dir desc"))
watch_dir:depends("watch_dir_enabled", "1")
watch_dir.optional = false
watch_dir.rmempty = true
watch_dir.placeholder = "/mnt/sda1/transmission/watchdir"

speed_limit_up_enabled = s:option(Flag, "speed_limit_up_enabled", translate("speed_limit_up_enabled", "speed limit up enabled"))
speed_limit_up_enabled.default = false
speed_limit_up_enabled.optional = false
speed_limit_up_enabled.rmempty = false

speed_limit_up= s:option(Value, "speed_limit_up", translate("speed_limit_up","speed limit up"),
          translate("speed_limit_up_desc","speed limit up default"))
speed_limit_up.optional = false
speed_limit_up.rmempty = true
speed_limit_up.default = "20"
speed_limit_up:depends("speed_limit_up_enabled", "1")


speed_limit_down_enabled = s:option(Flag, "speed_limit_down_enabled", translate("speed_limit_down_enabled", "speed limit down enabled"))
speed_limit_down_enabled.default = false
speed_limit_down_enabled.optional = false
speed_limit_down_enabled.rmempty = false

speed_limit_down= s:option(Value, "speed_limit_down", translate("speed_limit_down","speed limit down"),
          translate("speed_limit_down_desc","speed limit down default"))
speed_limit_down.optional = false
speed_limit_down.rmempty = true
speed_limit_down.default = "100"
speed_limit_down:depends("speed_limit_down_enabled", "1")

peer_port= s:option(Value, "peer_port", translate("peer_port","peer port"),
          translate("peer_port_desc","peer port default 51413"))
peer_port.optional = false
peer_port.rmempty = false

rpc_port= s:option(Value, "rpc_port", translate("rpc_port","rpc port"),
          translate("rpc_port_desc","rpc port default 9091"))
rpc_port.optional = false
rpc_port.rmempty = false

rpc_authentication_required = s:option(Flag, "rpc_authentication_required", translate("rpc_authentication_required", "rpc authentication required"))
rpc_authentication_required.default = false
rpc_authentication_required.optional = false
rpc_authentication_required.rmempty = false


rpc_username= s:option(Value, "rpc_username", translate("rpc_username","rpc username"),
          translate("rpc_username_desc","rpc username desc default"))
rpc_username:depends("rpc_authentication_required", "1")
rpc_username.optional = false
rpc_username.rmempty = true
rpc_username.placeholder = "abc"

rpc_password= s:option(Value, "rpc_password", translate("rpc_password","rpc password"),
          translate("rpc password_desc","rpc password desc default"))
rpc_password:depends("rpc_authentication_required", "1")
rpc_password.optional = false
rpc_password.rmempty = true
rpc_password.password = true
rpc_password.placeholder = "***"

rpc_whitelist_enabled= s:option(Flag, "rpc_whitelist_enabled", translate("rpc_whitelist_enabled", "rpc whitelist enabled"))
rpc_whitelist_enabled.default = false
rpc_whitelist_enabled.optional = false
rpc_whitelist_enabled.rmempty = false

rpc_whitelist= s:option(Value, "rpc_whitelist", translate("rpc_whitelist","speed limit down"),
          translate("rpc_whitelist_desc","rpc whitelist desc default"))
rpc_whitelist.optional = false
rpc_whitelist.rmempty = true
rpc_whitelist.default = "127.0.0.1,192.168.1.*"
rpc_whitelist:depends("rpc_whitelist_enabled", "1")

peer_limit_global= s:option(Value, "peer_limit_global", translate("peer_limit_global","peer limit global"),
          translate("peer_limit_global_desc","peer limit global default 240"))
peer_limit_global.optional = false
peer_limit_global.rmempty = false

peer_limit_per_torrent= s:option(Value, "peer_limit_per_torrent", translate("peer_limit_per_torrent","peer limit per torrent"),
          translate("peer_limit_per_torrent_desc","peer limit per torrent default 60"))
peer_limit_per_torrent.optional = false
peer_limit_per_torrent.rmempty = false


preallocation= s:option(Value, "preallocation", translate("preallocation","preallocation"),
          translate("preallocation_desc","use default"))
preallocation.optional = false
preallocation.rmempty = false

cache_size_mb= s:option(Value, "cache_size_mb", translate("Cache Size in mb"),
          translate("Downloading Cache Size in mb"))

cache_size_mb.optional = true

return m

