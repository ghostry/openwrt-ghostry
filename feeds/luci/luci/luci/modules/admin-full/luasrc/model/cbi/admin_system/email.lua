--[[
LuCI - Lua Configuration Interface

Copyright 2011 feixiang <feixiang@openwrt.org.cn>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

config 'emailserver'
	option 'email_enable' '1'
	option 'smtp_address' 'smtp.163.com'      
	option 'smtp_user' 'abcdef'
	option 'smtp_password' '123456' 
	   
config 'mail_address'
	option 'address' '138888888@139.com'

]]--

require("luci.tools.webadmin")

m = Map("email", translate("E-Mail"),translate("email setting"))

s = m:section(TypedSection, "emailserver", translate("email server"))
s.anonymous = true
s.addremove = false

from_address = s:option(Value, "from_address", translate("from_address","from_address"))
from_address.optional = false
from_address.rmempty = false

smtp_address = s:option( Value, "smtp_address", translate("smtp_address","smtp_address"))
smtp_address.optional = false
smtp_address.rmempty = false

smtp_user = s:option( Value, "smtp_user", translate("smtp_user","smtp_user"))
smtp_user.optional = false
smtp_user.rmempty = false

smtp_password = s:option( Value, "smtp_password", translate("smtp_password","smtp_password"))
smtp_password.optional = false
smtp_password.rmempty = false
smtp_password.password = true
smtp_password.placeholder = "***"


s = m:section(TypedSection, "mail_address", translate("mail_address","mail_address"),
 translate("mail_address_desc","mail_address_desc"))

s.template = "cbi/tblsection"
s.anonymous = true
s.addremove = true

use_enable = s:option(Flag, "use_enable", translate("Use Email", "Use Email"))
use_enable.default = false
use_enable.optional = false
use_enable.rmempty = false


address = s:option(Value, "address", translate("receive address","receive address"))
address.optional = false
address.rmempty = false

return m

