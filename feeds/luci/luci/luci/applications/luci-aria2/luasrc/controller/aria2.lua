--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>
Copyright 2008 Jo-Philipp Wich <xm@leipzig.freifunk.net>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0
]]--

module("luci.controller.aria2", package.seeall)

function index()
	require("luci.i18n")
	luci.i18n.loadc("aria2")
	
	if not nixio.fs.access("/etc/config/aria2") then
		return
	end

	local page
	page = entry({"admin", "diskapply", "aria2"}, cbi("aria2"), _("aria2 Downloader"))
	page.i18n = "aria2"
	page.dependent = true
end
