--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>
Copyright 2008 Jo-Philipp Wich <xm@leipzig.freifunk.net>
Copyright 2011 flyzjhz <flyzjhz@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: ddns.lua 6588 2010-11-29 15:14:50Z jow $
]]--

require("luci.tools.webadmin")

local fs   = require "nixio.fs"
local util = require "nixio.util"

m = Map("ddns", translate("Dynamic DNS"),
	translate("Dynamic DNS allows that your router can be reached with a fixed hostname while having a dynamically changing IP address."))

s = m:section(TypedSection, "goble", "")
s.addremove = false
s.anonymous = true

s:option(Flag, "enabled", translate("Enable"),translate("Enable intelvel update"))
s:option(Value, "check_interval",translate("Check for changed IP every"),translate("interval minute")).default = 100

crontab = s:option( DummyValue,"crontab", translate("intelvel update"))
crontab.titleref = luci.dispatcher.build_url("admin", "system", "crontab")


service = m:section(TypedSection, "service", "")
service.anonymous = true
service.addremove = true
service.template = "cbi/tblsection"
service.extedit  = luci.dispatcher.build_url("admin/services/ddns/ddnsleaf/%s")

service.create = function(...)
	local sid = TypedSection.create(...)
	if sid then
		luci.http.redirect(service.extedit % sid)
		return
	end
end


service:option(Flag, "enabled", translate("Enable"))

service_name=service:option(DummyValue, "service_name", translate("Service"))

function service_name.cfgvalue(self, s)
	return self.map:get(s, "service_name") or "3322.org"
end

domain = service:option(DummyValue, "domain", translate("Hostname"))
function domain.cfgvalue(self, s)
	return self.map:get(s, "domain") or "abcd.3322.org"
end

uptime = service:option(DummyValue, "uptime", translate("ddns update time","ddns update time"))
uptime.optional = false
uptime.rmempty = false
function uptime.cfgvalue(self, s)
	return self.map:get(s, "uptime") or "0"
end


ipaddr = service:option(DummyValue, "ipaddr", translate("ip address","ip address"))
ipaddr.optional = false
ipaddr.rmempty = false
function ipaddr.cfgvalue(self, s)
	return self.map:get(s, "ipaddr") or "*.*.*.*"
end

return m

