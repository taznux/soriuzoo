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

import time

class ConsoleSlider:
	def __init__ (self, max):
		self.barfill = -1
		self.max = max
		try:
			import fcntl, termios, struct
			s = struct.pack("HHHH", 0, 0, 0, 0)
			self.cols = struct.unpack("HHHH", fcntl.ioctl(sys.stdout.fileno(),
								termios.TIOCGWINSZ, s))[1]
		except:
			self.cols = 78
		self.barsize = self.cols - 30
		self.st = time.time()
		self.update(0)
	
	def update (self, value):
		newfill = int( float(value) * self.barsize / self.max )
		if newfill != self.barfill:
			self.barfill = newfill
			sys.stdout.write('\r[%s%s] %d%%' % 
				( '='*newfill,
			   	  ' '*(self.barsize-newfill),
				  newfill * 100 / self.barsize ) )
			if newfill * 20 >= self.barsize: # over 5%
				elapsed = time.time()-self.st
				estimated = int((float(self.barsize) - newfill) / newfill * elapsed)
				sys.stdout.write('  %d kB/s  %d:%02d left ' % 
					( value / elapsed / 1024,
					  int(estimated/60),
					  int(estimated%60) ) ) # int is for py3k
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

if __name__ == '__main__':
	import getpass, os
	import sys, socket
	import uzoolib
	from uzoolib import UzooError

	print "Uzoo Client for console / Release %s [Rev. %s]" % (
					uzoolib.UZOO_RELEASE, "$Revision$".split()[1] )
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

	try:
		s = uzoolib.Uzoo(id, password)
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
			ans = raw_input("Download which? ('q' for quit) >>> ")
			if ans and ans[0] == 'q':
				break
			fsize_past=0
			try:
                dest = results[int(ans)]
            except ValueError:
                continue
            except IndexError:
                print "=> Please select one of listed above."
                continue
			
			try:
				os.stat(dest.filename)
			except:
				pass
			else:
				print "=> Already download"
			try:
				fsize_past=os.stat(dest.filename+".SORI")[6]
			except:
				pass
			else:
				print "=> Resuming download"

			try:
                print "=> Downloading.... " + dest.filename
				dest.download(fsize_past, sliderctrl=ConsoleSlider)
			except UzooError, why:
				print "=> Downloading Error:", why
			except socket.error, why:
				print "=> Connection Error on Downloading:", repr(why)
			except KeyboardInterrupt:
				print "\n=> User Interrupt"
				try:
					ans = raw_input("Remove not completed file ? ")
					if ans[0].lower() == 'y':
						os.remove(dest.filename+".SORI")
					else:
						pass
				except IndexError:
					pass
			else:
				os.rename(dest.filename+".SORI",dest.filename)
				print "=> Download Complete!"
				parse_rc() # XXX: temporary for a while ;)

