--[[

LuCI UVC Streamer
(c) 2008 Yanira <forum-2008@email.de>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

$Id: p910nd.lua 7362 2011-08-12 13:16:27Z jow $

]]--

module("luci.controller.p910nd", package.seeall)

function index()
	if not nixio.fs.access("/etc/config/p910nd") then
		return
	end

	local page

	page = entry({"admin", "services", "p910nd"}, cbi("p910nd"), _("Printer server"), 60)
	page.i18n = "p910nd"
	page.dependent = true
end
