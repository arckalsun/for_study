#!/usr/bin/env python
# update_hosts.py -- update your hosts to cross The Great Firewall Of China.
# https://github.com/racaljk/hosts
# https://raw.githubusercontent.com/racaljk/hosts/master/hosts
# Please run as administrator/Root



import urllib2,os,time,socket

# analyze OS windows/linux
if (os.name == "nt"):#windows
	root = os.getenv("SystemRoot")
	hosts = root+"\System32\drivers\etc\hosts"
else:#linux or unix
	hosts = "/etc/hosts"

hostname = socket.gethostname()

#Backup hosts file	
t = time.strftime("%Y%m%d%H%M%S",time.localtime())
hosts_bak = hosts+"_"+t+".bak"
print "Backup your hosts to "+hosts_bak
try:
	os.rename(hosts,hosts_bak)
except OSError:
	print "Backup failed! Please run as administrator/Root"
	exit(1)


	 
# get hosts	
print "Connecting ..."
response = urllib2.urlopen('https://raw.githubusercontent.com/racaljk/hosts/master/hosts')
hosts_text = response.read()
print " Done !"


# Write hosts

f = open(hosts,'w')

f.write(hosts_text)
f.close()
response.close()
if os.name == 'posix':
	os.system("sed -i '9a  127.0.1.1"+"\t"+hostname+"' /etc/hosts")