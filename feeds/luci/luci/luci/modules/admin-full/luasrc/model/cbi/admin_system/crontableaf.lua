--[[
LuCI - Lua Configuration Interface

Copyright 2011 flyzjhz <flyzjhz@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: ddns.lua 6588 2010-11-29 15:14:50Z jow $
]]--

require("luci.tools.webadmin")

m = Map("cron", translate("Scheduled Tasks"),
	translate("This is the system crontab in which scheduled tasks can be defined."))

m.redirect = luci.dispatcher.build_url("admin/system/crontab")

if not arg[1] or m.uci:get("cron", arg[1]) ~= "task" then
	luci.http.redirect(m.redirect)
	return
end



task = m:section(NamedSection, arg[1], "task" , "")
task.addremove = false
task.anonymous = false

task.create = function(...)
	local sid = TypedSection.create(...)
	if sid then
		luci.http.redirect(task.extedit % sid)
		return
	end
end


enable = task:option(Flag, "enabled", translate("Enable"))

task_task_task=task:option(Value, "task_name", translate("task name"),translate("task name desc"))

task_Everyday=task:option(Flag, "task_Everyday", translate("Everyday"),translate("task Everyday desc"))
task_Everyday.disabled = 0

task_Monday=task:option(Flag, "task_Monday", translate("Monday"))
task_Monday.disabled = 0

task_Tuesday=task:option(Flag, "task_Tuesday", translate("Tuesday"))
task_Tuesday.disabled = 0

task_Wednesday=task:option(Flag, "task_Wednesday", translate("Wednesday"))
task_Wednesday.disabled = 0

task_Thursday=task:option(Flag, "task_Thursday", translate("Thursday"))
task_Thursday.disabled = 0

task_Friday=task:option(Flag, "task_Friday", translate("Friday"))
task_Friday.disabled = 0

task_Sartuday=task:option(Flag, "task_Sartuday", translate("Sartuday"))
task_Sartuday.disabled = 0

task_Sunday=task:option(Flag, "task_Sunday", translate("Sunday"))
task_Sunday.disabled = 0

task_time=task:option(ListValue, "task_time", translate("time"))
task_time:value("0:00", translate("0:00"))
task_time:value("0:15", translate("0:15"))
task_time:value("0:30", translate("0:30"))
task_time:value("0:45", translate("0:45"))
task_time:value("1:00", translate("1:00"))
task_time:value("1:15", translate("1:15"))
task_time:value("1:30", translate("1:30"))
task_time:value("1:45", translate("1:45"))
task_time:value("2:00", translate("2:00"))
task_time:value("2:15", translate("2:15"))
task_time:value("2:30", translate("2:30"))
task_time:value("2:45", translate("2:45"))
task_time:value("3:00", translate("3:00"))
task_time:value("3:15", translate("3:15"))
task_time:value("3:30", translate("3:30"))
task_time:value("3:45", translate("3:45"))
task_time:value("4:00", translate("4:00"))
task_time:value("4:15", translate("4:15"))
task_time:value("4:30", translate("4:30"))
task_time:value("4:45", translate("4:45"))
task_time:value("5:00", translate("5:00"))
task_time:value("5:15", translate("5:15"))
task_time:value("5:30", translate("5:30"))
task_time:value("5:45", translate("5:45"))
task_time:value("6:00", translate("6:00"))
task_time:value("6:15", translate("6:15"))
task_time:value("6:30", translate("6:30"))
task_time:value("6:45", translate("6:45"))
task_time:value("7:00", translate("7:00"))
task_time:value("7:15", translate("7:15"))
task_time:value("7:30", translate("7:30"))
task_time:value("7:45", translate("7:45"))
task_time:value("8:00", translate("8:00"))
task_time:value("8:15", translate("8:15"))
task_time:value("8:30", translate("8:30"))
task_time:value("8:45", translate("8:45"))
task_time:value("9:00", translate("9:00"))
task_time:value("9:15", translate("9:15"))
task_time:value("9:30", translate("9:30"))
task_time:value("9:45", translate("9:45"))
task_time:value("10:00", translate("10:00"))
task_time:value("10:15", translate("10:15"))
task_time:value("10:30", translate("10:30"))
task_time:value("10:45", translate("10:45"))
task_time:value("11:00", translate("11:00"))
task_time:value("11:15", translate("11:15"))
task_time:value("11:30", translate("11:30"))
task_time:value("11:45", translate("11:45"))
task_time:value("12:00", translate("12:00"))
task_time:value("12:15", translate("12:15"))
task_time:value("12:30", translate("12:30"))
task_time:value("12:45", translate("12:45"))
task_time:value("13:00", translate("13:00"))
task_time:value("13:15", translate("13:15"))
task_time:value("13:30", translate("13:30"))
task_time:value("13:45", translate("13:45"))
task_time:value("14:00", translate("14:00"))
task_time:value("14:15", translate("14:15"))
task_time:value("14:30", translate("14:30"))
task_time:value("14:45", translate("14:45"))
task_time:value("15:00", translate("15:00"))
task_time:value("15:15", translate("15:15"))
task_time:value("15:30", translate("15:30"))
task_time:value("15:45", translate("15:45"))
task_time:value("16:00", translate("16:00"))
task_time:value("16:15", translate("16:15"))
task_time:value("16:30", translate("16:30"))
task_time:value("16:45", translate("16:45"))
task_time:value("17:00", translate("17:00"))
task_time:value("17:15", translate("17:15"))
task_time:value("17:30", translate("17:30"))
task_time:value("17:45", translate("17:45"))
task_time:value("18:00", translate("18:00"))
task_time:value("18:15", translate("18:15"))
task_time:value("18:30", translate("18:30"))
task_time:value("18:45", translate("18:45"))
task_time:value("19:00", translate("19:00"))
task_time:value("19:15", translate("19:15"))
task_time:value("19:30", translate("19:30"))
task_time:value("19:45", translate("19:45"))
task_time:value("20:00", translate("20:00"))
task_time:value("20:15", translate("20:15"))
task_time:value("20:30", translate("20:30"))
task_time:value("20:45", translate("20:45"))
task_time:value("21:00", translate("21:00"))
task_time:value("21:15", translate("21:15"))
task_time:value("21:30", translate("21:30"))
task_time:value("21:45", translate("21:45"))
task_time:value("22:00", translate("22:00"))
task_time:value("22:15", translate("22:15"))
task_time:value("22:30", translate("22:30"))
task_time:value("22:45", translate("22:45"))
task_time:value("23:00", translate("23:00"))
task_time:value("23:15", translate("23:15"))
task_time:value("23:30", translate("23:30"))
task_time:value("23:45", translate("23:45"))
task_time:value("everym_5", translate("every_5_minute"))
task_time:value("everym_15", translate("every_15_minute"))
task_time:value("everym_30", translate("every_30_minute"))
task_time:value("everyh_1", translate("every_1_hour"))
task_time:value("everyh_12", translate("every_12_hour"))
task_time:value("everyh_24", translate("every_24_hour"))
task_time:value("custom", translate("every-custom-minute"))


task_minute=task:option(Value, "task_minute", translate("minute"),translate("custom minute"))
task_minute:depends( "task_time" , "custom" )

task_task=task:option(Value, "task_task", translate("task command"),translate("command desc"))
task_task:value("reboot", translate("reboot"))
task_task:value("halt", translate("halt"))
task_task:value("wifi up", translate("Wifi Up"))
task_task:value("wifi down", translate("Wifi Down"))
task_task:value("ifup wan", translate("Wan Up"))
task_task:value("ifdown wan", translate("Wan Down"))
task_task:value("/usr/lib/ddns/dynamic_dns_updater.sh scheduler", translate("ddns UP"))
task_task:value("sh /tmp/qosv4/qos_scheduler", translate("qosv4 scheduler"))


return m


