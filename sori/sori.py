#! /usr/bin/env python

# Shell ORiented interface for Uzoo.
# Copyright (C) 2002 by A Lee <alee@debian.org>.
#
# This software is free; you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2, or (at your option) any later version.

import sys, os, re, time, urllib
import struct, select, socket, dospath
from errno import *
from cStringIO import StringIO
try: from cPickle import dump, load
except: from Pickle import dump, load

SORIBADA_VERSION = '1.94'
SORIBADA_GATEWAY = 'http://www.soribada.com/gateway.txt'
sori_dir = os.environ.get('HOME', '.') + '/.sori'
config_file = sori_dir + '/config'
hosts_file = sori_dir + '/hosts'
songs_file = sori_dir + '/songs'
status_file = sori_dir + '/status'


class ConsoleSlider:
	def __init__ (self, max, initpos, slidertype='down'):
		self.type = slidertype
		self.barfill = -1
		self.max = max
		self.initpos = initpos
		self.sessmax = max - initpos
		try:
			import fcntl, termios
			s = struct.pack("HHHH", 0, 0, 0, 0)
			self.cols = struct.unpack("HHHH",
				fcntl.ioctl(sys.stdout.fileno(), termios.TIOCGWINSZ, s))[1]
		except: self.cols = 78
		self.barsize = self.cols - 30
		self.st = time.time()
		self.update(0)
	
	def update (self, value, *ext):
		newfill = int( float(value+self.initpos) * self.barsize / self.max )
		if newfill != self.barfill:
			self.barfill = newfill
			sys.stdout.write('\r[%s%s] %d%%' % ('='*newfill,
				' ' * (self.barsize-newfill), newfill * 100 / self.barsize))
			if self.type == 'down' and value * 20 >= self.sessmax:
				elapsed = time.time() - self.st
				estimated = int(float(self.sessmax) / value * elapsed - elapsed)
				sys.stdout.write('  %d kB/s  %d:%02d left ' % 
				(value / elapsed / 1024, int(estimated/60), int(estimated%60)))
			elif self.type == 'search' and ext:
				sys.stdout.write(' (%d songs found)' % (ext[0]))
			sys.stdout.flush()
	
	def end (self):
		print


def load_config(config_file):
	for line in open(config_file, 'r').readlines():
		item = line.split('=')
		if item[0].strip() == 'username': username = item[1].strip()
		if item[0].strip() == 'password': password = item[1].strip()
		if item[0].strip() == 'port': port = int(item[1].strip())
	return username, password, port

def save_config(config_file, username, password, port=9001):
	if not 9000 < port < 9901: port = 9001
	if port not in range(9001, 9898, 16): port = (port / 16) * 16 + 9
	general = "[General]\nusername=%s\npassword=%s\nport=%s\n"
	config = general % (username, password, port)
	open(config_file, 'w').write(config)

def bada_unpack(asrbuf):
	bada = StringIO(asrbuf)
	if asrbuf.startswith('Version'):
		bada.readline()
	hosts = []
	while 1:
		pkt = map(ord, list(bada.read(6)))
		if len(pkt) < 6: break
		magicnum = [0x00, 0xa5, 0xc3, 0x77][(pkt[1] & 0x0c) >> 2]
		nonmagics = [pkt[1]>>i & 1 for i in (7,6,5,4)]
		ip = [pkt[2 + i] ^ (not (pkt[1] >> (4 + i) & 1) and magicnum or 0)
			for i in range(4)]
		ip = '%d.%d.%d.%d' % (ip[1], ip[3], ip[2], ip[0])
		hosts.append((ip, pkt[0] + ((pkt[1] & 3) << 8) + 9000))
	return hosts

def bada_pack(addr):
	ip, port = addr
	sip = [chr(int(n) ^ 0xa5) for n in ip.split('.')]
	port1, port2 = (port-9000)%256, int((port-9000)/256)
	if port2 > 3: raise ValueError, "Port out of range"
	return chr(port1) + chr(port2 | 0x04) + sip[3] + sip[0] + sip[2] + sip[1]

def parse_reply(songs, packet):
	try:
		bf = StringIO(packet[12:])
		ip = bada_unpack(packet[1:7])[0][0]
		id = bf.readline().strip()
		port = int(bf.readline())
	except: return songs
	for data in bf.read().split('\n\r\n'):
		if not data.strip(): continue
		data = [s.strip() for s in data.split('\n')][:6]
		if len(data) == 6:
			[path, size, length, bitrt, singer, title] = data
			songs.append((ip, port, path, size, length, bitrt, singer, title))
	return songs

def register(username, password, gender=0, age=15, email="sori@bada.com"):
	registerurl = "http://www.soribada.com/soribada.phtml"
	registerurl += "?action=register&username=%s&password=%s"
	registerurl += "&speed=1&gender=%d&age=%d&email=%s&mailing=0"
	res = urllib.urlopen(registerurl %
		(username, password, gender, age, email)).read()
	if res.split()[3] != '000':
		print "Error: %s" % res.split(' ', 3)[-1]
		sys.exit()

def update(username, password, port=9001):
	loginurl = ''
	try: socket.socket(socket.AF_INET, socket.SOCK_DGRAM).bind(('', port))
	except socket.error: pass
	for line in urllib.urlopen(SORIBADA_GATEWAY).readlines():
		if line.split('=')[0] == 'IS':
			loginurl = line.split('=', 1)[-1].strip()
			break
	if not loginurl: print "Error: server doesn't served login gateway"
	info = urllib.urlopen('%s?username=%s&password=%s&version=%s' %
		(loginurl,username,password,SORIBADA_VERSION)).read().replace('\r','')
	if not info.startswith('Version'):
		print "Error: %s" % info.split('\n')[0]
		sys.exit()
	ip = re.compile('MYIP\n([^\n]*)\n').findall(info)[0]
	badaurl = re.compile('ASR\n([^\n]*)\n').findall(info)[0]
	hosts = urllib.urlopen('%s?action=gimme&username=%s&password=%s' %
		(badaurl, username, password) ).read()
	hosts = bada_unpack(hosts)
	return (ip, port), hosts
	
def search(hosts, keywords, maximum=1000, sliderctrl=None):
	(ip, port) = hosts[0]
	hosts = hosts[1]
	count = 94
	packet = ('\x01%s%%s\x51\x3a%s' %
		(bada_pack((ip, port)), ''.join(['+%s\n' % k for k in keywords])))
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.setblocking(0)
	sock.bind(('', port))
	casr = 0
	st = time.time()
	songs = []
	sfds = [sock.fileno()]
	resolution = 0.1
	throwunit = 15
	sweeptime = 3.0
	lastscan = 0
	scanend = 0
	if sliderctrl: sliderctrl = sliderctrl(len(hosts), 0, slidertype='search')
	while scanend < time.time():
		if not scanend and lastscan + resolution < time.time():
			error = ''
			try:
				for i in range(casr, casr+throwunit):
					count += 1
					sock.sendto(packet % struct.pack('<H', count), hosts[i])
				casr = i + 1
			except socket.error, why:
				casr = i
				error += 's'
			except IndexError:
				error += 'e'
				scanend = time.time() + sweeptime
		if select.select(sfds, [], [], resolution):
			try:
				while 1:
					r = sock.recvfrom(8192)
					if r: songs = parse_reply(songs, r[0])
					else: break
			except socket.error, why:
				if why[0] not in [EAGAIN, EWOULDBLOCK, ECONNRESET]:
					raise socket.error, why
				error += 'r'
			if sliderctrl: sliderctrl.update(casr, len(songs), error)
	sock.close()
	if sliderctrl: sliderctrl.end()
	return songs

def listsong(songs):
	print "=> Search Results"
	print "No.   Size   Length Bitrate  Filename"
	print "=" * 70
	for i in range(len(songs)):
		print ("%5d. %8s  %5s %4s  %s" % (i + 1, songs[i][3],
			songs[i][4], songs[i][5], dospath.split(songs[i][2])[1]))
	print "=" * 70
	print "=> %d song(s) found." % len(songs)

def showsong(no, item):
	print "Number  : %d" % (no + 1,)
	print "Filename: %s" % dospath.split(item[2])[1]
	print "Singer  : %s" % item[6]
	print "Title   : %s" % item[7]
	print "Filesize: %s" % item[3]
	print "Length  : %s" % item[4]
	print "Bitrate : %s" % item[5]
	print "Location: %s:%s" % (item[0], item[1])
	print "Fullpath: %s" % item[2]
	print ""

def update_status(status_file, pid, item=None):
	if os.access(status_file, os.F_OK):
		status = load(open(status_file, 'r'))
	else: status = {}
	if item:
		status[pid] = item
		dump(status, open(status_file, 'w'))
	else:
		del status[pid]
	if status: dump(status, open(status_file, 'w'))
	else: os.remove(status_file)

def download(username, item, sliderctrl=ConsoleSlider):
	file = dospath.split(item[2])[1]
	file = re.compile('[ _][ _]*').sub('_', file)
	file = re.compile('[_-]*[-\[\]\(\)\{\}][_-]*').sub('-', file)
	file = re.compile('^[_-]*').sub('', file)
	file = re.compile('[-_]*\.[mM][pP]3$').sub('.mp3', file)
	localfile = os.path.join(os.getcwd(), file)

	if sliderctrl: print ('Starting to download: %s' % file)
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((item[0], item[1]))
	sock.send("GETMP3\r\nFilename: %s\r\nPosition: 0\r\nPortM: 9999\r\nUsername: %s\r\n\r\n" % (item[2], username))
	buff = ''
	while buff.find('\r\n\r\n') < 0:
		buff += sock.recv(1024)
	rcv = buff.split('\r\n\r\n', 1)
	fsize = re.compile("Filesize: ([0-9]+)")
	header = rcv[0].split()
	length = int(fsize.findall(rcv[0])[0])

	if int(header[2]) == 0 and len(rcv) > 1:
		update_status(status_file, os.getpid(), (int(time.time()), length, localfile))
		f = open(localfile, "w")
		f.write(rcv[1])
		if sliderctrl: sliderctrl = sliderctrl(length, 0)
		read = len(rcv[1])
		while read < length:
			buff = sock.recv(32768)
			if not buff: break
			read += len(buff)
			f.write(buff)
			if sliderctrl: sliderctrl.update(read)
		f.close()
		update_status(status_file, os.getpid())
		if sliderctrl:
			sliderctrl.end()
			print ('Download completed: %s' % file)
	elif int(header[2]) == 100:
		print ('User Limit Exceeded: %s' % file)
	else:
		print ('Unknown Error: %d/%s' % (int(header[2]), ' '.join(header[3:])))

def show_status(status_file):
	if os.access(status_file, os.F_OK): status = load(open(status_file, 'r'))
	else: status = {}
	print ' PID  TimeLeft  Speed  Percent  File'
	print '=' * 70
	for pid in status.keys():
		time_elaps = int(time.time()) - status[pid][0]
		totalsize = status[pid][1]
		localfile = status[pid][2]
		if os.access(localfile, os.F_OK):
			downsize = int(os.stat(localfile)[6])
			time_remain = ((totalsize - downsize) / downsize) * time_elaps
			percent = downsize * 100 / totalsize
			if time_elaps: speed = (downsize / time_elaps) / 1024
			else: speed = 0
			print ('%6d %6d %4dKB/s %3d%% %s' % (pid, time_remain, speed, percent, localfile))
		else:
			update_status(status_file, pid)
	print '=' * 70
	

if __name__ == '__main__':
	if len(sys.argv) > 1: command = sys.argv[1]
	else: command = None

	if os.access(config_file, os.F_OK):
		username, password, port = load_config(config_file)
	elif command and command != 'config':
		print "You need to run `sori config' first."
		sys.exit()

	if command == 'config':
		try:
			import getpass
			if not os.access(sori_dir, os.F_OK): os.mkdir(sori_dir)
			print "=" * 70
			print "* Shell ORiented Interface for Uzoo"
			print "* Visit http://sf.net/projects/soriuzoo for information."
			print "* If you want to register new ID, type 'new' in ID."
			print "=" * 70
			username = raw_input('Soribada username : ')
			if username == 'new':
				username = raw_input('Enter new username: ')
				while 1:
					password = getpass.getpass('Enter new password: ')
					password_c = getpass.getpass('Retype new password: ')
					if password != password_c:
						print "=> Sorry, passwords do not match. Try again."
					else: break
				print "=> Registering..."
				register(username, password)
				print "=> Done! (wait few seconds for db update)"
			else: password = getpass.getpass('Soribada password : ')
			try: port = int(raw_input('Port(default 9001): '))
			except ValueError: port = 9001
			save_config(config_file, username, password, port)
		except EOFError: print; sys.exit()
		except KeyboardInterrupt: print; sys.exit()

	elif command == 'update':
		try:
			print "=> Updating available hosts list."
			hosts = update(username, password, port)
			print "=> %d hosts are online." % len(hosts[1])
			dump(hosts, open(hosts_file, 'w'))
		except KeyboardInterrupt: print "\nUser interrupt."

	elif command in ['find', 'search']:
		try:
			if len(sys.argv) > 2:
				if (os.access(hosts_file, os.F_OK) and
						time.time() - os.stat(hosts_file)[-1] < 1800):
					hosts = load(open(hosts_file, 'r'))
				else:
					print "=> Updating available hosts list."
					hosts = update(username, password, port)
					dump(hosts, open(hosts_file, 'w'))
				print "=> Searching in %s hosts." % len(hosts[1])
				songs = search(hosts, sys.argv[2:], 10, sliderctrl=ConsoleSlider)
				dump(songs, open(songs_file, 'w'))
				listsong(songs)
			else: print "You need to sepecify PATTERN."
		except IOError: pass
		except KeyboardInterrupt: print "\nUser interrupt."

	elif command == 'list':
		if os.access(songs_file, os.F_OK):
			try:
				songs = load(open(songs_file, 'r'))
				listsong(songs)
			except IOError: pass
			except KeyboardInterrupt: print "User interrupt."
		else: print "You need to run `sori find PATTERN' first."

	elif command in ['show', 'get', 'bgget']:
		if not os.access(songs_file, os.F_OK):
			print "You need to run `sori find PATTERN' first."
		elif len(sys.argv) > 2:
			if command == 'bgget':
				pid = os.fork()
				if pid:
					print ('New pid is %s.' % pid)
					os._exit(0)
					os.setpgrp()
					os.umask(0)
			try: songs = load(open(songs_file, 'r'))
			except KeyboardInterrupt: print "\nUser interrupt."
			for no in sys.argv[2:]:
				try:
					no = int(no) - 1
					if -1 < no < len(songs):
						if command == 'get': download(username, songs[no])
						elif command == 'bgget': download(username, songs[no], None)
						else: showsong(no, songs[no])
					else: print "%s: Out of range." % (no + 1)
				except KeyboardInterrupt:
					update_status(status_file, os.getpid())
					print "\nUser interrupt."
				except socket.error, why: print why[1]
				except ValueError: print "Wrong NUMBER."
		else: print "You need to sepecify NUMBER."
	
	elif command == 'status':
		try:
			show_status(status_file)
		except IOError: pass
		except KeyboardInterrupt: print "User interrupt."

	else:
		print """SORI 0.1 - Shell ORiented Interface for Uzoo
Usage: sori config
       sori update
       sori {find|search} pattern
       sori list
       sori {show|get|bgget} number1 [number2 ...]
	   sori status

sori is a simple command line interface for searching and
downloading mp3s from soribada community.

Commands:
   config - Enter the username and password.
   update - Update available hosts list.
   find   - Search songs and save the results.
   search - Same with find.
   list   - List again search results.
   show   - Show information of selected song(s).
   get    - Download selected song(s).
   bgget  - Download song(s) on a background process.
   status - Show current download status."""
