#! /usr/local/bin/python
# ex:ts=4
#
# = Uzoo Client Library =
#
# $Id$
#
# Copyright (c) 2002 Uzoo Project, SourceForge.
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


def bada_unpack(asrbuf):
	bada = StringIO(asrbuf)
	if asrbuf.startswith('Version'):
		bada.readline()
	fishes = []
	
	while 1:
		pkt = map(ord, list(bada.read(6)))
		if len(pkt) < 6:
			break

		magicnum = [0x00, 0xa5, 0xc3, 0x77][(pkt[1] & 0x0c) >> 2]
		nonmagics = [pkt[1]>>i & 1 for i in (7,6,5,4)]
		ip = [pkt[2+i] ^ (not (pkt[1]>>(4+i) & 1) and magicnum or 0)
					for i in range(4)]
		ip = '%d.%d.%d.%d' % (ip[1], ip[3], ip[2], ip[0])
		fishes.append((ip, pkt[0] + ((pkt[1] & 3) << 8) + 9000))
	
	return fishes

def bada_pack(addr):
	ip, port = addr
	sip = [chr(int(n) ^ 0xa5) for n in ip.split('.')]
	port1, port2 = (port-9000)%256, int((port-9000)/256)
	if port2 > 3:
		raise ValueError, "Port out of range"
	r = chr(port1) + chr(port2 | 0x04) + sip[3] + sip[0] + sip[2] + sip[1]
	return r


class QueryFactory:
	
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

	def download (self, fsize_past, dir='.', sliderctrl=None):
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		try:
			sock.connect((self.addr[0], int(self.downport)))
		except socket.error, why:
			if why[0] == ECONNREFUSED:
				raise UzooError, "Connection Refused"
			else:
				raise socket.error, why

		sock.send("GETMP3\r\nFilename: %s\r\nPosition: %d\r\n\
PortM: 9999\r\nUsername: %s\r\n\r\n" % (self.path, fsize_past, self.username) )
		buff = ''
		while buff.find('\r\n\r\n') < 0:
			buff += sock.recv(1024)
		rcv = buff.split('\r\n\r\n', 1)

		header = rcv[0].split()
		if int(header[2]) == 0 and len(rcv) > 1:
			f = open(self.filename+".SORI", "ab")
			f.write(rcv[1])

			length = int(self.fsize.findall(rcv[0])[0])
			if sliderctrl:
				sliderctrl = sliderctrl(length)

			read = len(rcv[1]) + fsize_past
			try:
				while read < length:
					buff = sock.recv(32768)
					if not buff:
						break
					read += len(buff)
					f.write(buff)
					if sliderctrl:
						sliderctrl.update(read)
			except socket.error, why:
				if why[0] == ECONNRESET:
					raise UzooError, "Connection reset by peer."
				else:
					raise socket.error, why

			f.close()
			if sliderctrl:
				sliderctrl.end()
		elif int(header[2]) == 100:
			raise UzooError, 'User Limit Exceeded'
		else:
			raise UzooError, 'Unknown Error: %d/%s' % (int(header[2]), ' '.join(header[3:]))


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
		q = QueryFactory((self.ip, self.port), keywords)
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

