--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: status.lua 6583 2010-11-28 18:01:07Z jow $
]]--
module("luci.controller.admin.externaldevice", package.seeall)

function index()

	if nixio.fs.access("/etc/config/printer") then
		entry({"admin", "externaldevice", "printer"}, cbi("externaldevice/printer"), _("printer"), 40)
			end
	if nixio.fs.access("/etc/config/camera") then
		entry({"admin", "externaldevice", "camera"}, cbi("externaldevice/camera"), _("camera"), 50)
			end

end


