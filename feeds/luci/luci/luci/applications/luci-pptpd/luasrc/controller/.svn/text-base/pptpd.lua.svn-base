--[[
LuCI - Lua Configuration Interface

]]--

module("luci.controller.pptpd", package.seeall)

function index()

	if nixio.fs.access("/etc/config/pptpd") then
	local page 

	page = entry({"admin", "services", "pptpd"}, cbi("pptpd"), _("PPTP VPN"), 90)
	page.i18n = "pptpd"
	page.dependent = true
	end

end
