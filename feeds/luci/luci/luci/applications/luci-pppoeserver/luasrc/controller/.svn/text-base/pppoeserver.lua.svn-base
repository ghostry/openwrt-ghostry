--[[
LuCI - Lua Configuration Interface

]]--

module("luci.controller.pppoeserver", package.seeall)

function index()
	if nixio.fs.access("/etc/config/pppoeserver") then

	local page
	page = entry({"admin", "services", "pppoeserver"}, cbi("pppoeserver"), _("PPPOE SERVER"), 90)
	page.i18n = "pppoeserver"
	page.dependent = true
	end

end
