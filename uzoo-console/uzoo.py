#! /usr/bin/env python
# ex:ts=4
#
# = Uzoo Client Library with Demo =
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
#	notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#	notice, this list of conditions and the following disclaimer in the
#	documentation and/or other materials provided with the distribution.
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

import time, os, re
UZOO_RELEASE = '1.1.3'


def dotint(v):
	dotstr = str(v)
	left = dotstr[:len(dotstr)%3]
	right = re.findall('...', dotstr[len(dotstr)%3:])
	if left:
		right.insert(0, left)
	return ','.join(right)

class ConsoleSlider:
	def __init__ (self, max, initpos, slidertype='down'): # 'down' or 'search'
		self.type = slidertype
		self.barfill = -1
		self.max = max
		self.initpos = initpos
		self.sessmax = max - initpos
		try:
			import fcntl, termios, struct
			s = struct.pack("HHHH", 0, 0, 0, 0)
			self.cols = struct.unpack("HHHH", fcntl.ioctl(sys.stdout.fileno(),
								termios.TIOCGWINSZ, s))[1]
		except:
			self.cols = 78
		self.barsize = self.cols - 12 # 4(percent) + 2([]) + 4(spaces) + 2(endmark)
		self.barsize -= len(dotint(max)) # done value
		self.barfmt = '\r%%-4s[%%s>%%s] %%-%ds ' % len(dotint(max))
		if self.type == 'search':
			self.barsize -= 14 # '(%d found) %s '
		else:
			self.barsize -= 22
		self.st = time.time()
		self.update(0)
	
	def update (self, value, *ext):
		newfill = int( float(value+self.initpos) * self.barsize / self.max )
		if 1: # newfill != self.barfill:
			self.barfill = newfill
			sys.stdout.write(self.barfmt % 
				( str(int(newfill * 100 / self.barsize))+'%',
				  '='*(newfill - 1),
			   	  ' '*(self.barsize-newfill),
				  dotint(value) ) )

			if self.type == 'down' and value * 30 >= self.sessmax: # over 3%
				elapsed = time.time() - self.st
				estimated = int(float(self.sessmax) / value * elapsed - elapsed)
				sys.stdout.write("%7.2fK/s   ETA %02d:%02d" % 
					( float(value) / elapsed / 1024,
					  int(estimated/60),
					  int(estimated%60) ) ) # int is for py3k
			elif self.type == 'search' and ext:
				sys.stdout.write('(%d found) %s ' % (ext[0], ext[1]))
			sys.stdout.flush()
	
	def end (self):
		print


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

Player = None

class Winamp:
	name = 'winamp'
	exepath = r'C:\Program Files\Winamp\winamp.exe'
	def enqueue(self, path):
		os.spawnv(os.P_NOWAIT, self.exepath, ["/ADD "+path])
	def play(self, path):
		os.spawnv(os.P_NOWAIT, self.exepath, [path])

try:
	if os.name in ['nt', 'dos']:
		if os.access(Winamp.exepath, os.F_OK):
			Player=Winamp
except:
	pass

if __name__ == '__main__':
	import getpass, os
	import sys, socket
	import uzoolib
	from uzoolib import UzooError

	print "Uzoo Client for console / Release %s [Rev. %s]" % (
					UZOO_RELEASE, "$Revision$".split()[1] )
	print "================================================================="
	print "* Please visit http://sf.net/projects/soriuzoo for informations."
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
			uzoolib.register(id, password)
		except UzooError, why:
			print "=> Registration Error ::", why
			raise SystemExit
		print "=> Done! (waiting few seconds for db update)"
		time.sleep(3)
	else:
		password = getpass.getpass('Password: ')

	port = 9001
	while 1:
		try:
			s = uzoolib.Uzoo(id, password, port=port)
		except UzooError, why:
			if why.errno == uzoolib.UZ_BINDERR:
				port += 1
				continue
			else:
				print "=> Login Error ::", why
				raise SystemExit
		else:
			break
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
		try:
			results = s.do_query(keywords.split(), 10, sliderctrl=ConsoleSlider)
		except KeyboardInterrupt:
			print "\n=> Stopped Searching."
            continue
        else:
		    if not results:
		    	print "=> No such song ;)"
		    	continue

		print "=> Search Result"
		print "No.   Size   Length Bitrate  Filename"
		print "================================================================="
		c = 0
		for r in results:
			print "%3d %8s %5s	%3s %s" % (
				c, r.size, r.length, r.bitrate, r.filename)
			c += 1
		print "================================================================="
		print "=> %d song(s) found." % len(results)

		while 1:
			ans = raw_input("Download which? ('q' for search others) >>> ")
			if ans and ans[0] == 'q':
				break

			try:
				dest = results[int(ans)]
			except ValueError:
				continue
			except IndexError:
				print "=> Please select one of listed above."
				continue
			
			resume, overwrite = 0, 0
			print "=> Downloading.... '%s'" % dest.filename
			while 1:
				try:
					dest.download(sliderctrl=ConsoleSlider, 
								allow_resume=resume, allow_overwrite=overwrite)
				except UzooError, why:
					if why.errno == uzoolib.UZ_WOULDRESUME:
						ans = raw_input('Resume Download Process ? ')
						if ans and ans[0].lower() == 'y':
							resume = 1
							continue
					elif why.errno == uzoolib.UZ_FILEEXIST:
						ans = raw_input('Overwrite the file ? ')
						if ans and ans[0].lower() == 'y':
							overwrite = 1
							continue
					else:
						print "=> Downloading Error:", why.msg
				except socket.error, why:
					print "=> Connection Error on Downloading:", why[1]
				except KeyboardInterrupt:
					print "\n=> User Interrupt"
					try:
						ans = raw_input("Remove not completed file ? ")
						if ans and ans[0].lower() == 'y':
							os.remove(dest._filepath(1))
					except IndexError:
						pass
					except OSError:
						pass
				else:
					print "=> Download Complete!"
					if Player:
						ans = raw_input("Do you want to play it with %s? "
								"('y' to play, 'e' to enqueue it) " % Player.name)
						if ans and ans[0].lower() == 'y':
							Player().play(dest._filepath(0))
						elif ans and ans[0].lower() == 'e':
							Player().enqueue(dest._filepath(0))
				break

