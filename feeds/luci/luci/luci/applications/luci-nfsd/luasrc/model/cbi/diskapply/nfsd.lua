require("luci.tools.webadmin")
--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>
Copyright 2008 Jo-Philipp Wich <xm@leipzig.freifunk.net>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: samba.lua 5927 2010-03-25 14:50:26Z jow $
]]--

m = Map("nfsd", translate("NFS server for UNIX-like systems","NFS"),
	translate("Probably the most secure and fastest NFS server for UNIX-like systems.", "nfsd setting page"))

s = m:section(TypedSection,"nfsd","nfs")
s.anonymous = true
s.addremove = false

--enable = s:option(Flag, "enable", translate("Enable"),"Enable FTP Serve")
enable = s:option(Flag, "enable", translate("Enable"),
        translate("Enable NFS Serve"))
enable.default = false
--enable.disabled = 0
--enable.enabled = 1
enable.optional = false
enable.rmempty = false


s = m:section(TypedSection, "nfsshare", translate("nfsshare"))
s.template = "cbi/tblsection"
s.addremove = true
s.anonymous = true

enable = s:option(Flag, "enable", translate("Enable"))
enable.default = false
--enable.disabled = 0
--enable.enabled = 1
enable.optional = false
enable.rmempty = false

s:option(Value, "name", translate("Name"))

pth = s:option(Value, "path", translate("Path"))
if nixio.fs.access("/etc/config/fstab") then
        pth.titleref = luci.dispatcher.build_url("admin", "diskapply", "fstab")
end


return m
