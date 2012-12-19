require("luci.tools.webadmin")

--[[

config 'mldonkey'
	option 'name' 'mldonkey_openwrtcn'
	option 'enable' '1'
	option 'download_dir' '/tmp/sda1/mldonkey'
 	option  gui_port  4001
 	option  http_port 4080
 	option  telnet_port 4000
 	option  allowed_ips 0.0.0.0-255.255.255.255
 	option  max_hard_upload_rate  |max_hard_upload_rate|
 	option  max_hard_download_rate  |max_hard_download_rate|
 	option  max_hard_upload_rate_2  |max_hard_upload_rate_2|
 	option  max_hard_download_rate_2  |max_hard_download_rate_2|
  option  max_opened_connections  |max_opened_connections|
 	option  max_opened_connections_2  |max_opened_connections_2|
  option  max_upload_slots  |max_upload_slots|
]]--

require("luci.sys")
local uci = require "luci.model.uci".cursor()
local lanipaddr = uci:get("network", "lan", "ipaddr") or "192.168.1.1"
local mldonkeyport = uci:get_first("mldonkey", "mldonkey", "http_port") or "4080"


m = Map("mldonkey", translate("mldonkey_desc"),
                    translate("mldonkey_desc about"))

s = m:section(TypedSection, "mldonkey", translate("mldonkey_set"))
s.anonymous = true
s.addremove = false

s:option(DummyValue,"mldonkeyweb" ,translate("<a target=\"_blank\" href='http://"..lanipaddr..":"..mldonkeyport.."'>MLDonkey Web Intelface</a> "),translate("Open the MLDonkey Web"))

enabled = s:option(Flag, "enable", translate("Enable"))
enabled.disabled = 0
enabled.optional = false
enabled.rmempty = false


name = s:option(Value, "name", translate("name"),
          translate("name_desc"))
name.optional = false
name.rmempty = false

download_dir = s:option(Value, "download_dir", translate("download_dir"),
          translate("download_dir_desc"))
download_dir.optional = false
download_dir.rmempty = false
if nixio.fs.access("/etc/config/fstab") then
        download_dir.titleref = luci.dispatcher.build_url("admin", "diskapply", "fstab")
end

gui_port = s:option(Value, "gui_port", translate("gui_port"),
          translate("gui_port_desc"))
gui_port.optional = false
gui_port.rmempty = false


http_port = s:option(Value, "http_port", translate("http_port"),
          translate("http_port_desc"))
http_port.optional = false
http_port.rmempty = false


telnet_port = s:option(Value, "telnet_port", translate("telnet_port"),
          translate("telnet_port_desc"))
telnet_port.optional = false
telnet_port.rmempty = false

allowed_ips = s:option(Value, "allowed_ips", translate("allowed_ips"),
          translate("allowed_ips_desc"))
allowed_ips.optional = false
allowed_ips.rmempty = false

max_hard_upload_rate = s:option(Value, "max_hard_upload_rate", translate("max_hard_upload_rate"),
          translate("max_hard_upload_rate_desc"))
max_hard_upload_rate.optional = false
max_hard_upload_rate.rmempty = false

max_hard_download_rate = s:option(Value, "max_hard_download_rate", translate("max_hard_download_rate"),
          translate("max_hard_download_rate_desc"))
max_hard_download_rate.optional = false
max_hard_download_rate.rmempty = false

max_hard_upload_rate_2 = s:option(Value, "max_hard_upload_rate_2", translate("max_hard_upload_rate_2"),
          translate("max_hard_upload_rate_2_desc"))
max_hard_upload_rate_2.optional = false
max_hard_upload_rate_2.rmempty = false

max_hard_download_rate_2 = s:option(Value, "max_hard_download_rate_2", translate("max_hard_download_rate_2"),
          translate("max_hard_download_rate_2_desc"))
max_hard_download_rate_2.optional = false
max_hard_download_rate_2.rmempty = false

max_opened_connections = s:option(Value, "max_opened_connections", translate("max_opened_connections"),
          translate("max_opened_connections_desc"))
max_opened_connections.optional = false
max_opened_connections.rmempty = false

max_opened_connections_2 = s:option(Value, "max_opened_connections_2", translate("max_opened_connections_2"),
          translate("max_opened_connections_2_desc"))
max_opened_connections_2.optional = false
max_opened_connections_2.rmempty = false

return m

