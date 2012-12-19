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

m = Map("vsftpd", translate("FTP server for UNIX-like systems","vsftpd"),
	translate("Probably the most secure and fastest FTP server for UNIX-like systems.", "vsftpd setting page"))

s = m:section(TypedSection,"vsftpd","FTP")
s.anonymous = true
s.addremove = false

--enable = s:option(Flag, "enable", translate("Enable"),"Enable FTP Serve")
enable = s:option(Flag, "enable", translate("Enable"),
        translate("Enable FTP Serve"))
enable.default = false
--enable.disabled = 0
--enable.enabled = 1
enable.optional = false
enable.rmempty = false


write_enable = s:option(Flag, "write_enable", translate("Write"),
        translate("write_enable"))
write_enable.default = false
write_enable.optional = false
write_enable.rmempty = false


--anonymous_enable = s:option(Flag, "anonymous_enable", translate("anonymous_enable"),
--        translate("anonymous_enable"))
--anonymous_enable.default = false
--anonymous_enable.optional = false
--anonymous_enable.rmempty = false

anon_upload_enable = s:option(Flag, "anon_upload_enable", translate("Upload"),
        translate("anon_upload_enable"))
anon_upload_enable.default = false
anon_upload_enable.optional = false
anon_upload_enable.rmempty = false

anon_mkdir_write_enable = s:option(Flag, "anon_mkdir_write_enable", translate("Mkdir"),
        translate("anon_mkdir_write_enable"))
anon_mkdir_write_enable.default = false
anon_mkdir_write_enable.optional = false
anon_mkdir_write_enable.rmempty = false

anon_other_write_enable = s:option(Flag, "anon_other_write_enable", translate("Other write"),
        translate("anon_other_write_enable"))
anon_other_write_enable.default = false
anon_other_write_enable.optional = false
anon_other_write_enable.rmempty = false

return m
