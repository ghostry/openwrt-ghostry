--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: status.lua 6583 2010-11-28 18:01:07Z jow $
]]--
module("luci.controller.admin.diskapply", package.seeall)

function index()


		entry({"admin", "diskapply"}, cbi("admin_system/fstab"), _("diskapply"), 55).index = true
		entry({"admin", "diskapply", "fstab"}, cbi("admin_system/fstab"), _("Mount Points"), 1)
		entry({"admin", "diskapply", "fstab", "mount"}, cbi("admin_system/fstab/mount"), nil).leaf = true
		entry({"admin", "diskapply", "fstab", "swap"},  cbi("admin_system/fstab/swap"),  nil).leaf = true



	entry({"admin", "diskapply", "diskinfo"}, call("action_diskinfo"), _("Diskinfo"), 2)

	if nixio.fs.access("/etc/config/transmission") then
		entry({"admin", "diskapply", "Transmission"}, cbi("diskapply/transmission"), _("Transmission"), 11).i18n = "diskapply"
	end

	if nixio.fs.access("/etc/config/mldonkey") then
		entry({"admin", "diskapply", "mldonkey"}, cbi("diskapply/mldonkey"), _("mldonkey"), 13).i18n = "diskapply"
	end

	if nixio.fs.access("/etc/config/vsftpd") then
		entry({"admin", "diskapply", "vsftpd"}, cbi("diskapply/vsftpd"), _("vsftpd"), 30).i18n = "diskapply"
	end

	if nixio.fs.access("/etc/config/nfsd") then
		entry({"admin", "diskapply", "nfsd"}, cbi("diskapply/nfsd"), _("nfsd"), 40).i18n = "diskapply"
	end

end

function action_diskinfo()
local fdisklist = luci.util.exec("fdisk -l")
	luci.template.render("admin_diskapply/fstab", {fdisklist=fdisklist})
end


