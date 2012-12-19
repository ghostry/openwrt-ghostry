module("luci.controller.ipid", package.seeall)

function index()
	
	if nixio.fs.access("/etc/config/ipid") then
	local page
	page = entry({"admin", "network", "ipid"}, cbi("ipid"),  _("IPID"), 60)
	page.i18n = "qosv4"
	page.dependent = true
	end

end
