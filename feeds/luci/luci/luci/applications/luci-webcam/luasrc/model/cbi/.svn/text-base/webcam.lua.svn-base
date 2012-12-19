
m = Map("mjpg-streamer", translate("mjpg-streamer webcam"),translate(" mjpg-streamer webcam. "))

s = m:section(TypedSection, "mjpg-streamer", "")
s.addremove = false
s.anonymous = false

s:tab("general", translate("General Settings"))
s:tab("preview", translate("video monitor"))




e=s:taboption("general",ListValue, "enabled", translate("webcam"),translate("enable or disable mjpg-streamer webcam. "))


e:value("true","Enabled")
e:value("false","Disabled")
e.optional = ture


device=s:taboption("general",Value, "device", translate("device"))

device.rmempty = true
device:value("/dev/video0","/dev/video0")
device:value("/dev/video1","/dev/video1")


resolution=s:taboption("general",Value, "resolution", translate("resolution"))
resolution:value("640x480","640x480")
resolution:value("320x240","320x240")
resolution.optional = ture

resolution.rmempty = true

fps=s:taboption("general",Value, "fps", translate("fps"))
device.rmempty = true
fps:value("1","1")
fps:value("2","2")
fps:value("3","3")
fps:value("4","4")
fps:value("5","5")
fps:value("6","6")
fps:value("7","7")
fps:value("8","9")
fps:value("9","9")
fps:value("10","10")

port=s:taboption("general",Value, "port", translate("port"))
port:value("8080","8080")
port.rmempty = true

s:taboption("general",Flag, "PassWordLogin", translate("PassWord Login"),translate("Enable or disable password login webcam."))

username=s:taboption("general",Value, "username", translate("username"))
username:value("root","root")
username.rmempty = true

password=s:taboption("general",Value, "password", translate("password"))
password.rmempty = true
password.password = true

s:taboption("general", DummyValue,"opennewwindow" ,translate("<br /><p align=\"justify\"><script type=\"text/javascript\">function openwindowwebcam(){window.open('http://' + location.hostname + ':' + document.getElementById('cbid.mjpg-streamer.core.port').value + '/javascript_simple.html','webcam')}</script><input type=\"button\" class=\"cbi-button cbi-button-apply\" value=\"Play video\" onclick=\"openwindowwebcam()\" /></p>"))

s:taboption("general", DummyValue,"link" ,translate("<br /><a href=\"http://hi.baidu.com/f_fx/blog/category/Linux%20Openwrt\" target=\"_blank\">sutuo&#39;s blog</a>"))

videomonitor=s:taboption("preview", DummyValue,"video" ,translate("<br /><div id=\"videodiv\" ><p align=\"center\"><input type=\"button\" value=\"play\" class=\"cbi-button cbi-button-apply\" onclick=\"javascript:document.getElementById('videoframe').src ='http://' + location.hostname + ':' + document.getElementById('cbid.mjpg-streamer.core.port').value + '/javascript_simple.html'\" />&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"stop\" class=\"cbi-button cbi-button-reset\" onclick=\"javascript:document.getElementById('videoframe').src ='about:blank'\" /></p><iframe id=\"videoframe\" scrolling=\"no\" border=\"0\" name=\"lantk\" width=\"640\" height=\"480\" frameBorder=\"0\" src=\"about:blank\" align=\"center\"></iframe></div>"))



function s.parse(self, ...)
	TypedSection.parse(self, ...)
	os.execute("/etc/init.d/mjpg-streamer restart>/var/log/mjpg-streamer.log")
	os.execute("/etc/init.d/mjpg-streamer enable>/var/log/mjpg-streamer.log")
end

return m
