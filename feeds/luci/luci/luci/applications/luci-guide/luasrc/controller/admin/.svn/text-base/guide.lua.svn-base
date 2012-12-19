--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>
Copyright 2008-2009 Jo-Philipp Wich <xm@subsignal.org>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: system.lua 6562 2010-11-27 04:55:38Z jow $
]]--

local is6358 = luci.util.exec("cat /proc/cpuinfo|grep -c 96358VW2") or 0 
local is6358 = tonumber(is6358) 

module("luci.controller.admin.guide", package.seeall)

function index()
	entry({"admin", "guide"}, call("action_guide"), _("Quick Guide"), 1)
end

--------------------------------------------------start quick guide----------------------------------------

 uci = require "luci.model.uci".cursor()

function action_guide()

	require("luci.model.uci")

  -- Determine state
	local keep_avail   = true
	local step         = tonumber(luci.http.formvalue("step") or 0)

	-- Step 0: route mode select
if step == 0 then

	luci.template.render("admin_system/guide", {
			step=0,
		} )

	-- Step 1:  wan setting  uci set route mode
	elseif step == 1 then
if  is6358 >= 1 then
      if luci.http.formvalue("cbid.route.model") then
       local route_model = tonumber(luci.http.formvalue("cbid.route.model"))
         if route_model == 1 then
          --uci:set("network", "wan", "ifname", "eth0")
        luci.util.exec("uci set network.wan.ifname=eth0")
        end
         if route_model == 2 then
         -- uci:set("network", "wan", "ifname", "eth1.1")
        luci.util.exec("uci set network.wan.ifname=\"eth1.1\"")
        end
    uci:save("network")
    uci:commit("network")

    end
end

		luci.template.render("admin_system/guide", {
			step=1,

		} )

	-- Step 2: web lan setting ,uci set wan 
	elseif step == 2 then
		 uci = luci.model.uci.cursor()

if luci.http.formvalue("cbid.network.wan.proto") then
       network_wan_proto = luci.http.formvalue("cbid.network.wan.proto") 
    uci:set("network", "wan", "proto", network_wan_proto)
end

if luci.http.formvalue("cbid.network.wan.ipaddr") then
       network_wan_ipaddr = luci.http.formvalue("cbid.network.wan.ipaddr") 
      uci:set("network", "wan", "ipaddr", network_wan_ipaddr) 
end

if luci.http.formvalue("cbid.network.wan.netmask") then
       network_wan_netmask = luci.http.formvalue("cbid.network.wan.netmask") 
     uci:set("network", "wan", "netmask", network_wan_netmask)
end

if luci.http.formvalue("cbid.network.wan.gateway") then
       network_wan_gateway = luci.http.formvalue("cbid.network.wan.gateway") 
      uci:set("network", "wan", "gateway", network_wan_gateway) 
end

if luci.http.formvalue("cbid.network.wan.username") then
       network_wan_username = luci.http.formvalue("cbid.network.wan.username") 
      uci:set("network", "wan", "username", network_wan_username) 
 luci.util.exec("echo usrtname >>/tmp/use")
end

if luci.http.formvalue("cbid.network.wan.password") then
       network_wan_password = luci.http.formvalue("cbid.network.wan.password") 
      uci:set("network", "wan", "password", network_wan_password) 
end

if luci.http.formvalue("cbid.network.wan.dns") then
       network_wan_dns = luci.http.formvalue("cbid.network.wan.dns") 
      uci:set("network", "wan", "dns", network_wan_dns) 
end

if luci.http.formvalue("cbid.network.wan.macaddr") then
       network_wan_macaddr = luci.http.formvalue("cbid.network.wan.macaddr") 
      uci:set("network", "wan", "macaddr", network_wan_macaddr) 
end

uci:save("network")
		luci.template.render("admin_system/guide", {
			step=2,

		} )


	-- Step 3: uci set lan and save all data--
	elseif step == 3 then
		 uci = luci.model.uci.cursor()
if luci.http.formvalue("cbid.network.wan.ipaddr") then
       network_wan_ipaddr = luci.http.formvalue("cbid.network.wan.ipaddr") 
      uci:set("network", "wan", "ipaddr", network_wan_ipaddr) 
end
if luci.http.formvalue("cbid.network.wan.netmask") then
       network_wan_netmask = luci.http.formvalue("cbid.network.wan.netmask") 
      uci:set("network", "wan", "netmask", network_wan_netmask)

end

if luci.http.formvalue("cbid.network.wan.macaddr") then
       network_wan_macaddr = luci.http.formvalue("cbid.network.wan.macaddr") 
      uci:set("network", "wan", "macaddr", network_wan_macaddr) 
 
end
uci:save("network")
		luci.template.render("admin_system/guide", {
			step=3,
		} )
elseif step == 4 then
 uci = luci.model.uci.cursor()
		local uci = luci.model.uci.cursor()
		uci:load("network")
		uci:commit("network")
    luci.util.exec("ifup wan")
		luci.template.render("admin_system/guide", {
			step=4,
		} )
end
end
