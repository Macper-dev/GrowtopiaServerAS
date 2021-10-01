print("Server Launcher (c) Growtopia Noobs")
addRed=False
try:
	with open('C:\\Windows\\System32\\drivers\\etc\\hosts', 'r') as file:
		if "127.0.0.1 growtopia1.com" in file.read():
			print("Record growtopia1.com to localhost already found!")
		else:
			addRed=True;
		file.close()
	if addRed:
		with open('C:\\Windows\\System32\\drivers\\etc\\hosts', 'a') as file:
			file.write('\r\n127.0.0.1 growtopia1.com')
		print("Record growtopia1.com to localhost was added!")
		file.close()
except:
	print("Windows hosts failed... Trying linux version (Maybe wine?)")
	try:
		with open('\\etc\\hosts', 'r+') as file:
			if "127.0.0.1 growtopia1.com" in file.read():
				print("Record growtopia1.com to localhost already found!")
			else:
				addRed=True;
			file.close()
		if addRed:
			with open('\\etc\\hosts', 'a') as file:
				file.write('\n127.0.0.1 growtopia1.com')
			print("Record growtopia1.com to localhost was added!")
			file.close()
	except:
		print("Unknown error while modifying hosts file???")
		print("Try run application as Administrator/Root or try to add host data manualy.")
try:
	import subprocess
	subprocess.Popen([r"server.exe"])
except:
	print("Server.exe not found? Move all files to same directory and relaunch or launch server.exe manually.")
import sys
httpd=None
try:
	if sys.version_info[0] is 3:
		import http.server
		print("Launching HTTP server! (Python 3.x)")
		class ServerHandler(http.server.BaseHTTPRequestHandler):
			def do_POST(self):
				self.send_response(200)
				self.end_headers()
				self.wfile.write(str.encode("server|127.0.0.1\nport|17091\ntype|1\n#maint|Mainetrance message (Not used for now) -- Growtopia Noobs\n\nbeta_server|127.0.0.1\nbeta_port|17091\n\nbeta_type|1\nmeta|localhost\nRTENDMARKERBS1001"))
		server_address = ('', 80)
		httpd = http.server.HTTPServer(server_address, ServerHandler)
		print("HTTP server is running! Don't close this or GT will be unable to connect!")
		httpd.serve_forever()
	else:
		import SimpleHTTPServer
		import SocketServer
		print("Launching HTTP server! (Python 2.x)")
		class ServerHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
			def do_POST(self):
				self.send_response(200)
				self.end_headers()
				self.wfile.write("server|127.0.0.1\nport|17091\ntype|1\n#maint|Mainetrance message (Not used for now) -- Growtopia Noobs\n\nbeta_server|127.0.0.1\nbeta_port|17091\n\nbeta_type|1\nmeta|localhost\nRTENDMARKERBS1001")
		#Handler = SimpleHTTPServer.SimpleHTTPRequestHandler
		Handler = ServerHandler
		httpd = SocketServer.TCPServer(("", 80), Handler)
		print("HTTP server is running! Don't close this or GT will be unable to connect!")
		httpd.serve_forever()
except:
	print("Port 80 is probably already used? Try close anything what can be running there or try run this app as Admin.")