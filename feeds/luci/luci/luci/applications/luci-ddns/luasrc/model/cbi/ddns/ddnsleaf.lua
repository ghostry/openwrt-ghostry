--[[
LuCI - Lua Configuration Interface

Copyright 2011 flyzjhz <flyzjhz@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: ddns.lua 6588 2010-11-29 15:14:50Z jow $
]]--

require("luci.tools.webadmin")

m = Map("ddns", translate("Dynamic DNS"),
	translate("Dynamic DNS allows that your router can be reached with a fixed hostname while having a dynamically changing IP address."))

m.redirect = luci.dispatcher.build_url("admin/services/ddns")

if not arg[1] or m.uci:get("ddns", arg[1]) ~= "service" then
	luci.http.redirect(m.redirect)
	return
end



s = m:section(NamedSection, arg[1], "service" , "")
s.addremove = false
s.anonymous = false

s:option(Flag, "enabled", translate("Enable"))

svc = s:option(ListValue, "service_name", translate("Service"))
svc.rmempty = false

local services = { }
local fd = io.open("/usr/lib/ddns/services", "r")
if fd then
	local ln
	repeat
		ln = fd:read("*l")
		local s = ln and ln:match('^%s*"([^"]+)"')
		if s then services[#services+1] = s end
	until not ln
	fd:close()
end

local v
for _, v in luci.util.vspairs(services) do
	svc:value(v)
end

function svc.cfgvalue(...)
	local v = Value.cfgvalue(...)
	if not v or #v == 0 then
		return "-"
	else
		return v
	end
end

function svc.write(self, section, value)
	if value == "-" then
		m.uci:delete("ddns", section, self.option)
	else
		Value.write(self, section, value)
	end
end

svc:value("-", "-- "..translate("custom").." --")


url = s:option(Value, "update_url", translate("Custom update-URL"))
url:depends("service_name", "-")
url.rmempty = true

weburl=s:option(Value, "update_url", translate("Custom update-URL"))

weburl3322 = s:option( DummyValue,"weburl3322", translate("register url"),
translate("<a target=\"_blank\" href='http://www.3322.org'>http://www.3322.org</a>"))
weburl3322:depends("service_name", "3322.org")

weburlchangip = s:option( DummyValue,"weburlchangip", translate("register url"),
translate("<a target=\"_blank\" href='http://www.changeip.com'>http://www.changeip.com</a>"))
weburlchangip:depends("service_name", "changeip.com")

weburldyndns = s:option( DummyValue,"weburldyndns", translate("register url"),
translate("<a target=\"_blank\" href='http://www.dyndns.org'>http://www.dyndns.org</a>"))
weburldyndns:depends("service_name", "dyndns.org")


weburlzoneedit = s:option( DummyValue,"weburlzoneedit", translate("register url"),
translate("<a target=\"_blank\" href='http://www.zoneedit.com'>http://www.zoneedit.comg</a>"))
weburlzoneedit:depends("service_name", "zoneedit.com")

weburlfree_editdns = s:option( DummyValue,"weburlfree_editdns", translate("register url"),
translate("<a target=\"_blank\" href='http://free.editdns.net'>http://free.editdns.net</a>"))
weburlfree_editdns:depends("service_name", "free.editdns.net")


weburlno_ip = s:option( DummyValue,"weburlno_ip", translate("register url"),
translate("<a target=\"_blank\" href='http://www.no-ip.com'>http://www.no-ip.com</a>"))
weburlno_ip:depends("service_name", "no-ip.com")
weburlno_ip:depends("service_name", "noip.com")


weburlfreedns_afraid = s:option( DummyValue,"weburlfreedns_afraid", translate("register url"),
translate("<a target=\"_blank\" href='http://freedns.afraid.org'>http://freedns.afraid.org</a>"))
weburlfreedns_afraid:depends("service_name", "freedns.afraid.org")

weburlhe_net = s:option( DummyValue,"weburlhe_net", translate("register url"),
translate("<a target=\"_blank\" href='http://dns.he.net'>http://dns.he.net</a>"))
weburlhe_net:depends("service_name", "he.net")

weburldnsmax = s:option( DummyValue,"weburldnsmax", translate("register url"),
translate("<a target=\"_blank\" href='http://www.dnsmax.com'>http://www.dnsmax.com</a>"))
weburldnsmax:depends("service_name", "dnsmax.com")

weburlthatip = s:option( DummyValue,"weburlthatip", translate("register url"),
translate("<a target=\"_blank\" href='http://www.thatip.com'>http://www.thatip.com</a>"))
weburlthatip:depends("service_name", "thatip.com")


weburlnamecheap = s:option( DummyValue,"weburlnamecheap", translate("register url"),
translate("<a target=\"_blank\" href='http://www.namecheap.com'>http://www.namecheap.com</a>"))
weburlnamecheap:depends("service_name", "namecheap.com")


neiwang = s:option(Flag, "neiwang", translate("Intranet"),translate("Secondary route setting"))
neiwang:depends("service_name", "3322.org")
neiwang:depends("service_name", "dyndns.org")

neiwang.disabled = 0



s:option(Value, "domain", translate("Hostname")).rmempty = true

s:option(Value, "username", translate("Username")).rmempty = true

pw = s:option(Value, "password", translate("Password"))
pw.rmempty = true
pw.password = true
	
iface = s:option(ListValue, "ip_network", translate("Network"))
iface.rmempty = true
luci.tools.webadmin.cbi_add_networks(iface)


return m

