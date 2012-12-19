--[[
LuCI - Lua Configuration Interface

]]--

module("luci.controller.n2n", package.seeall)

function index()

	if nixio.fs.access("/etc/config/n2n") then
	local page

	page = entry({"admin", "services", "n2n"}, cbi("n2n"), _("N2N VPN"), 92)
	page.i18n = "n2n"
	page.dependent = true
	end
end
