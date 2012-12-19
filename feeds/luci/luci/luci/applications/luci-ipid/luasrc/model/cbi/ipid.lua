require("luci.tools.webadmin")

--[[
config 'qos_settings' 
 	option 'enable' '0'
	option 'UP' '100'
	option 'DOWN' '500'
	option qos_scheduler 1

config 'qos_ip' 
  option 'enable' '0' 
  option 'limit_ip' '192.168.1.5' 
  option 'UPLOADR' '2'
  option 'DOWNLOADR' '2'
	option 'UPLOADC' '15'
	option 'DOWNLOADC' '15'
	option 'UPLOADR2' '1'
	option 'UPLOADC2' '5'
	option 'DOWNLOADR2' '1'
	option 'DOWNLOADC2' '2'

config 'qos_nolimit_ip' 
  option 'enable' '0' 
  option 'limit_ip' '192.168.1.6' 

]]--

local sys = require "luci.sys"

m = Map("ipid", translate("ipid title","IPID"),
                translate("ipid title desc","ipid title desc"))

s = m:section(TypedSection, "ipid_ttl", translate("qos ipid ttl setting","qos ipid ttl setting"),
translate("IPID TTL set desc","IPID TTL set desc"))
s.anonymous = true
s.addremove = false


ipid_enable = s:option(Flag, "ipid_pace", translate("IPID enable", "IPID enable"),
                         translate("IPID set desc","IPID set desc"))
ipid_enable.default = false
ipid_enable.optional = false
ipid_enable.rmempty = false
ipid_enable.disabled = 0

ttl_enable = s:option(Flag, "ttl_enable", translate("TTL enable", "TTL enable"),
                         translate("TTL set desc","TTL set desc"))
ttl_enable.default = false
ttl_enable.optional = false
ttl_enable.rmempty = false
ttl_enable.disabled = 0

ttl_set = s:option(Value, "ttl_set", translate("ttl set","ttl set"),
          translate("ttl set desc","ttl set desc"))
ttl_set.optional = false
ttl_set.rmempty = true
ttl_set.default =128
ttl_set:value (128, 128)
ttl_set:value (64, 64)
ttl_set:depends("ttl_enable", "1")


ttl_inc = s:option(Value, "ttl_inc", translate("ttl inc","ttl inc"),
          translate("ttl inc desc","ttl inc desc"))
ttl_inc.optional = false
ttl_inc.rmempty = true
ttl_inc.default =1
ttl_inc:value (1, 1)
ttl_inc:value (2, 2)
ttl_inc:value (3, 3)
ttl_inc:depends("ttl_enable", "1")


return m

