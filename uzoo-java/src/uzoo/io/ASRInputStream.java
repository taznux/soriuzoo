/*
 * @(#)ASRInputStream.java
 *
 * Copyright (c) 2001-2002 Jang-ho Hwang,
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */
package uzoo.io;

import java.io.ByteArrayOutputStream;
import java.io.BufferedInputStream;
import java.io.InputStream;
import java.io.IOException;

import uzoo.UzooException;
import uzoo.net.InetSocketAddress;
/**
 * ASR 문서내용 (각 검색클라이언트들이 저장되어있는)을 읽어주는 
 * InputStream이다.
 * <p>
 * 이 InputStream으로 읽을 대상 스트림에는 검색 클라이언트들의
 * 주소(Host와 Port number)들이 제공되는데, 현재 
 * 완벽한 parsing을 하지 못한다. 
 * <p>
 * perky님의 말에 의하면 실패률은 5% 미만이라고 한다.
 * 
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2001/01/28
 */
public class ASRInputStream extends BufferedInputStream
{
	private String version = null;
	private byte[] buffer = new byte[ 6 ];

	/**
	 * 주어진 inputstream으로 ASRInputStream 객체를 생성한다.
	 */
	public ASRInputStream( InputStream in ) throws IOException
	{
		super( in );
		gatherVersion();
	}
	 
	private void gatherVersion() throws IOException
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream(20);
		int buf;
		int offset = 0;
		while( (buf=read())!=-1 )
		{
			if( buf=='\n' )
				break;
			bos.write( buf );
		}
	
		if( buf==-1 )
			throw new IOException( "stream closed" );
		
		/* Build version */	
		String line = new String(bos.toByteArray());
		
		try {	
			int i0 = line.indexOf(':');
			String header = line.substring(0,i0).trim();
			this.version = line.substring(i0+1).trim();

			if( !header.equals("Version") )
				throw UzooException.getInstance(version);
		} catch( ArrayIndexOutOfBoundsException e ) {}
	}

	/**
	 * 검색 클라이언트의 목록 스트림에서 하나를 읽어온다.
	 * <p>
	 * 끝에 도달했으면, null을 반환할 것이다.
	 * 만약, 끝에 Block size가 올바르지 않아도, 남은 바이트를 무시하고, 
	 * null을 반환할 것이다.
	 */
	public synchronized InetSocketAddress readAddress() throws IOException
	{
		int readlen = 0;
		int offset = 0;
		while( offset!=buffer.length )
		{
			readlen = read(buffer, offset, buffer.length-offset);
			if( readlen==-1 )
				return null;
			offset += readlen;
		}
	
		fixBlock();
		return parseAddress( buffer );
	}

	/**
	 * 주어진 buffer(실제로 0~5의 index만 사용)를 인간이 인식할 수 있는
	 * 인터넷 주소형식으로 변형하여 InetSocketAddress 인스턴스를 생성하여
	 * 반환한다.
	 */
	public static InetSocketAddress parseAddress( byte[] buffer ) throws IOException
	{
		int port = 9000 + unsign(buffer[0]);
		int encodeCase = (int)buffer[1];

		int xor;
		int plus;

		switch(encodeCase)
		{
		case 4:
			xor = 1;
			plus = 164;	
			break;
		case 8:
			xor = 3;
			plus = 192;	
			break;
		case 12:
			xor = 7;
			plus = 112;	
			break;
		default:
			return new InetSocketAddress();
		}

		StringBuffer host = new StringBuffer(18);
		host.append( decode(buffer[3],xor,plus) ); 
		host.append( '.' );
		host.append( decode(buffer[5],xor,plus) );
		host.append( '.' );
		host.append( decode(buffer[4],xor,plus) );
		host.append( '.' );
		host.append( decode(buffer[2],xor,plus) );

		return new InetSocketAddress( host.toString(), port );
	}
	
	/**
	 * 6블럭짜리가 아닌 경우를 대비하여 0x01이 나올때까지
	 * mark하면서 나가다가 0x01이 발견되면, reset하도록 되어있다.
	 */
	private void fixBlock() throws IOException
	{
		mark(0);
		int buf;
		while( (buf=read())!=-1 )
		{
			if( buf==0x01 )
			{
				reset();
				return;
			}
			mark(0);
		}
	}

	private static int decode( byte b, int xor, int plus )
	{
		return (unsign(b) ^ xor + plus) % 256;
	}

	private static int unsign( byte b )
	{
		return b < 0 ? (int)b + 0x100 : (int)b;
	}

	/**
	 * 이 ASR 문서의 Version 번호를 얻어온다.
	 */
	public String getVersion()
	{
		return this.version;
	}

}
