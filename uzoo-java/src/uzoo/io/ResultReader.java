/* 
 * @(#)ResultReader.java
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
import java.io.InputStream;
import java.io.IOException;
import java.io.FilterInputStream;

import uzoo.MP3File;
import uzoo.net.InetSocketAddress;
/**
 * Uzoo로 검색을 요청했을때, 각 검색클라이언트로부터 들어온
 * 검색결과를 쉽게 읽어들일 수 있게 하는 Reader 클래스이다.
 * 
 * @author Jang-ho Hwang, rath@xrath.com 
 * @version $Id$, since 2002/01/28
 */
public class ResultReader extends FilterInputStream
{
	private ByteArrayOutputStream bos = new ByteArrayOutputStream();
	private InetSocketAddress address = null;
	private int index;

	private String owner = null;

	/**
	 * 검색결과 packet을 읽어주는 reader를 생성한다.
	 * 
	 * @param  in  UDP로 받은 ByteArrayInputStream으로 변형된 byte[]
	 */
	public ResultReader( InputStream in ) throws IOException
	{
		super( in );

		in.skip( 1L ); // 0x01
		byte[] buf = new byte[6];
		in.read( buf );
		
		this.address = ASRInputStream.parseAddress(buf);
		this.index = in.read() | (in.read() << 8);
		in.skip(2L); // 0x52, 0x3a

		this.owner = readLine();
		this.address.setPort( Integer.parseInt(readLine()) );
	}

	/**
	 * 이 검색결과들을 제공한 파일의 주인 아이디(Soribada username)을 
	 * 얻어온다.
	 */
	public String getFileOwner()
	{
		return this.owner;
	}

	/**
	 * 이 검색결과의 고유한 인덱스 값을 읽어온다.
	 */
	public int getIndex()
	{
		return this.index;
	}

	/**
	 * 이 검색결과를 보내준 사용자의 Address를 얻어온다.
	 * 이 주소는 TCP로 mp3를 다운로드 받는데 사용될 주소이다.
	 */
	public InetSocketAddress getAddress()
	{
		return this.address;
	}

	/**
	 * 한줄을 읽는다. EOF거나 0이 발견되면 null을 반환한다.
	 */
	public String readLine() throws IOException
	{
		bos.reset();

		int buf;
		while( (buf=in.read())!=-1 )
		{
			if( buf==0 )
				break;

			if( buf=='\r' ) 
				continue;
			if( buf=='\n' ) 
				break;
			bos.write(buf);
		}

		if( buf<=0 ) 
			return null;

		return new String(bos.toByteArray());
	}

	private String[] info = new String[6];

	/**
	 * 이 검색결과에서 mp3 음악 파일 내용 하나를 읽어온다.
	 * 더이상 내용이 없다면 null을 반환할 것이다.
	 */
	public MP3File readFile() throws IOException
	{
		for(int i=0; i<info.length; i++)
		{
			info[i] = readLine();
			if( info[i]==null )
				return null;
		}

		MP3File file = new MP3File();
		file.setAddress( this.address );
		file.setPath( info[0] );
		file.setSize( Long.parseLong(info[1]) );
		file.setPlayingTime( info[2] );
		file.setRate( info[3] );
		file.setArtist( info[4] );
		file.setTitle( info[5] );

		skipCRLF();
		return file;
	}

	/**
	 * 각 결과내용들을 구분하기 위해 padding된것들이나 쓸모없는 것들을
	 * 모두 skip 해버린다.
	 * <p>
	 * 이는 각 내용들이 \r\n\r\n로 구분되어지기 때문이다. 
	 * 이것을 사용하지 않는다면, 중간에 끼는 이상한 메시지들때문에
	 * 오류를 던질 것이다.
	 */
	private void skipCRLF() throws IOException
	{
		int buf;
		while( (buf=in.read())!=-1 )
		{
			if( buf=='\r' && 
				in.read()=='\n' &&
				in.read()=='\r' &&
				in.read()=='\n' )
				return;
		}
	}
}