--[[
LuCI - Lua Configuration Interface
]]--



m = Map("pppoeserver", translate("PPPOE Server"),translate("This is pppoe Server ."))

s = m:section(TypedSection, "global", translate("global"))
s.addremove = false
s.anonymous = true

enable = s:option(Flag, "enable", translate("PPPOE Server"),translate("Enable or Disable Server."))



s = m:section(TypedSection, "conf", translate("pppoe server conf"))
s.addremove = false
s.anonymous = true



serverip = s:option(Value, "serverip", translate("Server IP"),translate("PPPOE Server IP addr. ; default: 10.0.0.1"))
serverip.rmempty = true
serverip.datatype = "ip4addr"

clientip = s:option(Value, "clientip", translate("Client ip"),translate("PPPOE Client start IP addr.; default: 10.0.0.2"))
clientip.rmempty = true
clientip.datatype = "ip4addr"

num = s:option(Value, "num", translate("Client num"),translate("PPPOE Client num.; default: 50"))
num.rmempty = true


mtu = s:option(Value, "mtu", translate("mtu"),translate("mtu; default: 1482"))
mtu.rmempty = true

mru = s:option(Value, "mru", translate("mru"),translate("mru; default: 1482"))
mru.rmempty = true

stimeout = s:option(Value, "timeout", translate("timeout"),translate("timeout"))
stimeout.rmempty = true


lcp_echo_failure = s:option(Value, "lcp_echo_failure", translate("lcp_echo_failure"),translate("lcp-echo-failure.; default: 2"))
lcp_echo_failure.rmempty = true

lcp_echo_interval = s:option(Value, "lcp_echo_interval", translate("lcp_echo_interval"),translate("lcp-echo-interval.; default: 10"))
lcp_echo_interval.rmempty = true


s = m:section(TypedSection, "pppoeuser", "pppoe user pass etc.,")
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
