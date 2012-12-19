--[[
LuCI - Lua Configuration Interface
]]--



m = Map("pptpd", translate("PPTP VPN Server"),translate("This is PPTP VPN Server ."))

s = m:section(TypedSection, "setting", translate("setting"))
s.addremove = false
s.anonymous = true

enable = s:option(Flag, "enable", translate("PPTP VPN Server"),translate("Enable or Disable VPN Server."))




s = m:section(TypedSection, "conf", translate("ppptpd conf"))
s.addremove = false
s.anonymous = true


stimeout = s:option(Value, "stimeout", translate("stimeout"),translate("stimeout"))
stimeout.rmempty = true

serverip = s:option(Value, "serverip", translate("Server IP"),translate("VPN Server IP addr. ; default: 10.0.0.1"))
serverip.rmempty = true
serverip.datatype = "ip4addr"

clientip = s:option(Value, "clientip", translate("Client ip"),translate("VPN Client IP addr.; default: 10.0.0.2-254"))
clientip.rmempty = true


s = m:section(TypedSection, "pptpd", "option ppptpd")
s.addremove = false
s.anonymous = true

dns = s:option(Value, "dns", translate("DNS"),translate("DNS IP addr.; default: 8.8.8.8"))
dns.rmempty = true

mppe = s:option(Flag, "mppe", translate("MPPE Encryption"),translate("Enable or Disable  MPPE Encryption."))
mppe.rmempty = true

nat = s:option(Flag, "nat", translate("NAT Forward"),translate("Enable or Disable  NAT Forward."))
nat.rmempty = true

mtu = s:option(Value, "mtu", translate("mtu"),translate("mtu; default: 1482"))
mtu.rmempty = true

mru = s:option(Value, "mru", translate("mru"),translate("mru; default: 1482"))
mru.rmempty = true

name = s:option(Value, "name", translate("name"),translate("ppptpd name.; default: pptp-server"))
name.rmempty = true

lcp_echo_failure = s:option(Value, "lcp_echo_failure", translate("lcp_echo_failure"),translate("lcp-echo-failure.; default: 3"))
lcp_echo_failure.rmempty = true

lcp_echo_interval = s:option(Value, "lcp_echo_interval", translate("lcp_echo_interval"),translate("lcp-echo-interval.; default: 60"))
lcp_echo_interval.rmempty = true

s = m:section(TypedSection, "pptpduser", "ppptpd user pass etc.,")
s.addremove = true
s.anonymous = true
s.template = "cbi/tblsection"

enable = s:option(Flag, "enable", translate("enable"))

USERNAME = s:option(Value, "USERNAME", translate("USERNAME"),translate("USERNAME"))
USERNAME.rmempty = true

PROVIDER = s:option(Value, "PROVIDER", translate("PROVIDER"),translate("PROVIDER;default: *"))
PROVIDER.default = "*"
PROVIDER.rmempty = true

PASSWORD = s:option(Value, "PASSWORD", translate("PASSWORD"),translate("PASSWORD"))
PASSWORD.rmempty = true
PASSWORD.password = true


IPADDRESS = s:option(Value, "IPADDRESS", translate("IPADDRESS"),translate("IPADDRESS; default: *"))
IPADDRESS.default = "*"
IPADDRESS.rmempty = true

return m







