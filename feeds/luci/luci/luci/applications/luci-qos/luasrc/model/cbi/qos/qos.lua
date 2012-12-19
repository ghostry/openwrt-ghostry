--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: qos.lua 7239 2011-06-25 23:17:54Z jow $
]]--

local wa = require "luci.tools.webadmin"
local fs = require "nixio.fs"

m = Map("qos", translate("Quality of Service"),
	translate("With <abbr title=\"Quality of Service\">QoS</abbr> you " ..
		"can prioritize network traffic selected by addresses, " ..
		"ports or services."))

s = m:section(TypedSection, "interface", translate("Interfaces"))
s.addremove = true
s.anonymous = false

e = s:option(Flag, "enabled", translate("Enable"))
e.rmempty = false

c = s:option(ListValue, "classgroup", translate("Classification group"))
c:value("Default", translate("default"))
c.default = "Default"

s:option(Flag, "overhead", translate("Calculate overhead"))

s:option(Flag, "halfduplex", translate("Half-duplex"))

s:option(Value, "download", translate("Download speed (kbit/s)"))

s:option(Value, "upload", translate("Upload speed (kbit/s)"))
--[[
s = m:section(TypedSection, "classify", translate("Classification Rules"))
s.template = "cbi/tblsection"
s.anonymous = true
s.addremove = true
s.sortable  = true

t = s:option(ListValue, "target", translate("Target"))
t:value("Priority", translate("priority"))
t:value("Express", translate("express"))
t:value("Normal", translate("normal"))
t:value("Bulk", translate("low"))
t.default = "Normal"

srch = s:option(Value, "srchost", translate("Source host"))
srch.rmempty = true
srch:value("", translate("all"))
wa.cbi_add_knownips(srch)

dsth = s:option(Value, "dsthost", translate("Destination host"))
dsth.rmempty = true
dsth:value("", translate("all"))
wa.cbi_add_knownips(dsth)

l7 = s:option(ListValue, "layer7", translate("Service"))
l7.rmempty = true
l7:value("", translate("all"))
l7:value("ssh", translate("ssh"))
l7:value("http", translate("http"))
l7:value("qq", translate("qq"))
l7:value("hf", translate("hf"))
l7:value("thunder", translate("thunder"))
l7:value("warcraft3", translate("warcraft3"))
l7:value("bittorrent", translate("bittorrent"))
l7:value("pplive", translate("pplive"))
l7:value("ppstream", translate("ppstream"))
l7:value("sip", translate("sip"))
l7:value("rdp", translate("rdp"))
l7:value("vnc", translate("vnc"))

p = s:option(Value, "proto", translate("Protocol"))
p:value("", translate("all"))
p:value("tcp", "TCP")
p:value("udp", "UDP")
p:value("icmp", "ICMP")
p.rmempty = true

ports = s:option(Value, "ports", translate("Ports"))
ports.rmempty = true
ports:value("", translate("all"))

bytes = s:option(Value, "connbytes", translate("Number of bytes"))
--]]
return m
