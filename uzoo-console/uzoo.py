#! /usr/local/bin/python
# ex:ts=4
#
# = Uzoo Client Library with Demo =
#
# $Id$
#
# Copyright (c) 2002 Hye-Shik Chang <perky@fallin.lv>. Seoul.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

import urllib, re, sys
from cStringIO import StringIO
import struct, select
import socket, time, dospath
from errno import *

SORIBADA_VERSION = '1.94'

class UzooError(Exception):
	def __init__(self, msg):
		self.msg = msg
		Exception.__init__(self, msg)

unpack = {
	4: lambda x: (x ^ 1 + 164) % 256,
	8: lambda x: (x ^ 3 + 192) % 256,
	12: lambda x: (x ^ 7 + 112) % 256,
}

def bada_unpack(bada):
	bada = StringIO(bada)
	fishes = []
	
	while 1:
		phead = bada.read(2)
		while len(phead) < 2 or not unpack.has_key(ord(phead[1])):
			while bada.read(1) not in ['\x01', '']:
				pass
			phead = '\x01' + bada.read(1)
			if len(phead) < 2:
				break
		ip = bada.read(4)
		if len(ip) < 4:
			break
		upack = unpack[ord(phead[1])]
		fishes.append( (
			'%d.%d.%d.%d' % tuple([upack(ord(ip[i])) for i in (1,3,2,0)]),
			9000 + ord(phead[0])
		) )
	
	return fishes

def bada_pack(addr):
	ip, port = addr
	sip = [chr(unpack[4](int(n))) for n in ip.split('.')]
	return chr(port-9000) + '\x04' + sip[3] + sip[0] + sip[2] + sip[1]


class QueryPacket:
	
	def __init__ (self, addr, keywords):
		self.packet = '\x01%s%%s\x51\x3a%s' % (
			bada_pack(addr), ''.join(['+%s\n' % k for k in keywords]) )
		self.count = 94
	
	def __call__ (self):
		self.count += 1
		return self.packet % struct.pack('<H', self.count)


def parse_reply(packet, username):
	try:
		bf = StringIO(packet[12:])
		addr = bada_unpack(packet[1:7])[0]
		id = bf.readline().strip()
		downport = int(bf.readline())
	except:
		return []

	r = []
	for data in bf.read().split('\n\r\n'):
		if not data.strip():
			continue

		try:
			r.append( MP3Location(data, addr, id, downport, username) )
		except:
			pass
	return r


class MP3Location:
	
	fsize = re.compile("Filesize: ([0-9]+)")
	
	def __init__ (self, packet, addr, id, downport, username):
		self.username = username
		self.addr = addr
		self.downport = downport
		self.id = id
		data = [s.strip() for s in packet.split('\n')][:6]
		if len(data) == 6:
			[self.path, self.size, self.length,
			 self.bitrate, self.singer, self.title] = data
			self.filename = dospath.split(self.path)[1]
		else:
			print "WRONG", repr(data)
			raise ValueError, "Wrong Packet Found :: <<<" + repr(data) + ">>>"

	def download (self, dir='.', sliderctrl=None):
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((self.addr[0], int(self.downport)))
		sock.send("GETMP3\r\nFilename: %s\r\nPosition: 0\r\n\
PortM: 9999\r\nUsername: %s\r\n\r\n" % (self.path, self.username) )
		buff = ''
		while buff.find('\r\n\r\n') < 0:
			buff += sock.recv(1024)
		rcv = buff.split('\r\n\r\n', 1)

		header = rcv[0].split()
		if int(header[2]) == 0 and len(rcv) > 1:
			f = open(self.filename, "wb")
			f.write(rcv[1])

			length = int(self.fsize.findall(rcv[0])[0])
			if sliderctrl:
				sliderctrl = sliderctrl(length)

			read = len(rcv[1])
			while read < length:
				buff = sock.recv(32768)
				if not buff:
					break
				read += len(buff)
				f.write(buff)
				if sliderctrl:
					sliderctrl.update(read)

			f.close()
			if sliderctrl:
				sliderctrl.end()
		elif int(header[2]) == 100:
			raise UzooError, 'User Limit Exceeded'
		else:
			raise UzooError, 'Unknown Error: %d/%s' % (int(header[2]), ' '.join(header[3:]))


class ConsoleSlider:
	def __init__ (self, max):
		self.barfill = -1
		self.max = max
		self.barsize = 60 # fcntl?
		self.st = time.time()
		self.update(0)
	
	def update (self, value):
		newfill = int( float(value) * self.barsize / self.max )
		if newfill != self.barfill:
			self.barfill = newfill
			sys.stdout.write('\r[%s%s] %3d%% %d kB/s' % ('='*newfill,
			    ' '*(self.barsize-newfill), newfill * 100 / self.barsize,
				value/(time.time()-self.st)/1024 ) )
			sys.stdout.flush()
	
	def end (self):
		print


class Uzoo:
	
	findbada = re.compile('ASR\n([^\n]*)\n')
	myip = re.compile('MYIP\n([^\n]*)\n')
	
	def __init__ (self, username, password, server='http://www.soribada.com', port=9001):
		self.username = username
		self.password = password
		self.port = port
		loginurl = ''
		for line in urllib.urlopen(server + '/gateway.txt').readlines():
			if line.split('=')[0] == 'IS':
				loginurl = line.split('=', 1)[-1].strip()
				break
		if not loginurl:
			raise UzooError, "server doesn't served login gateway"
		
		info = urllib.urlopen('%s?username=%s&password=%s&version=%s' % \
					(loginurl, username, password, SORIBADA_VERSION) ).read().replace('\r', '')
		if not info.startswith('Version'):
			raise UzooError, info.split('\n')[0]
		
		self.ip = self.myip.findall(info)[0]
		self.badaurl = self.findbada.findall(info)[0]

		self.update_bada()
	
	def update_bada (self):
		bada = urllib.urlopen('%s?action=gimme&username=%s&password=%s' % (
				self.badaurl, self.username, self.password) ).read()
		self.bada = bada_unpack(bada)
	
	def do_query (self, keywords, listenlimit=5.0):
		q = QueryPacket((self.ip, self.port), keywords)
		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		sock.setblocking(0)
		sock.bind(('', self.port))
		for dest in self.bada:
			while 1:
				try:
					sock.sendto(q(), dest)
				except socket.error, why:
					if why[0] in (ENOBUFS, EAGAIN, ETIMEDOUT, EWOULDBLOCK):
						time.sleep(0.5)
				else:
					break
		
		st = time.time()
		results = []
		sfds = [sock.fileno()]
		while time.time() - st < listenlimit:
			if select.select(sfds, [], [], 1.0):
				try:
					while 1:
						r = sock.recvfrom(8192)
						if r:
							results.extend( parse_reply(r[0], self.username) )
						else:
							break
				except socket.error:
					pass
		sock.close()
		return results


def register(username, password, gender=0, speed=1, age=15, email="sori@bada.com", mailing=0):
	res = urllib.urlopen("http://www.soribada.com/soribada.phtml?action=register\
&username=%s&password=%s&speed=%d&gender=%d&age=%d&email=%s&mailing=%d" % (
		username, password, speed, gender, age, email, mailing)).read()
	if res.split()[3] != '000':
		raise UzooError, res.split(' ', 3)[-1]


def parse_rc():
	import os
	dotrc = os.environ.get('HOME', '.') + '/.uzoorc'
	if not os.access(dotrc, os.F_OK):
		try:
			open(dotrc, "w").write('[uzoo]\nfirstrun=%d' % int(time.time()))
			ans = raw_input("Do you want to play it with Pado? ")
			if ans[0].lower() == 'y':
				print '=> Hehe;) just kidding.'
		except:
			pass

if __name__ == '__main__':
	import getpass

	print "Perky's Uzoo Client Demo $Revision$"
	print "==============================================================="
	print " ** This script was released under BSD License."
	print "    Please refer license declaration from source code."
	print

	print "If you want to register new ID, just type 'new' in ID."
	print "-----"
	id = raw_input('ID: ')
	if id == 'new':
		id = raw_input('New ID: ')
		while 1:
			password = getpass.getpass('Password: ')
			password_c = getpass.getpass('Once Again: ')
			if password != password_c:
				print "=> You entered different. Please input again."
			else:
				break
		print "=> Registering..."
		try:
			register(id, password)
		except UzooError, why:
			print "=> Registration Error ::", why
			raise SystemExit
		print "=> Done! (waiting few seconds for db update)"
		time.sleep(3)
	else:
		password = getpass.getpass('Password: ')

	try:
		s = Uzoo(id, password)
	except UzooError, why:
		print "=> Login Error ::", why
		raise SystemExit
	print "=> Login Successful!"
	print "=> Your IP is %s" % s.ip
	print "=> %d fishes are online" % len(s.bada)

	while 1:
		keywords = raw_input("Keywords or 'quit' or 'update' >>> ")
		if keywords == 'quit':
			break
		elif keywords == 'update':
			s.update_bada()
			print "=> %d fishes are online, now" % len(s.bada)
			continue

		print "=> Searching...."
		results = s.do_query(keywords.split())

		if not results:
			print "=> No such song ;)"
			continue

		print "=> Search Result"
		print "No.   Size   Length Bitrate  Filename"
		print "================================================================="
		c = 0
		for r in results:
			print "%3d %8s %5s    %3s %s" % (
				c, r.size, r.length, r.bitrate, r.filename)
			c += 1
		print "================================================================="
		print "=> %d song(s) found." % len(results)

		while 1:
			n = raw_input("Download which? ('q' for quit) >>> ")
			if n[0] == 'q':
				break
			print "=> Downloading.... "+results[int(n)].filename
			try:
				results[int(n)].download(sliderctrl=ConsoleSlider)
			except UzooError, why:
				print "=> Downloading Error:", why
			except KeyboardInterrupt:
				print "\n=> User Interrupt"
			else:
				print "=> Download Complete!"
				parse_rc() # XXX: temporary for a while ;)

