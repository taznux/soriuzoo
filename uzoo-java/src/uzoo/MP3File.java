/*
 * @(#)MP3File.java
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
package uzoo;

import java.io.ByteArrayInputStream;
import java.io.CharArrayWriter;
import java.io.IOException;
import java.io.File;

import uzoo.io.ASRInputStream;
import uzoo.net.InetSocketAddress;
import uzoo.net.Download;
/**
 * 검색된 mp3 파일의 정보를 포함하고 있는 엔티티성 클래스이다.
 *
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2002/01/28
 */
public class MP3File 
{
	private InetSocketAddress address;
	private String filepath;
	private long filesize;
	private String playtime;
	private String rate;
	private String artist;
	private String title;

	public void setAddress( InetSocketAddress addr )
	{
		this.address = addr;
	}

	public InetSocketAddress getAddress()
	{
		return this.address;
	}

	public void setPath( String path )
	{
		this.filepath = path;
	}

	public String getPath()
	{
		return this.filepath;
	}

	/**
	 * 파일의 전체 경로중 디렉토리부분을 제외한 파일명만을 잘라온다.
	 * 현재는 \ 를 찾아 잘라내는 방식을 사용하므로, Win32 platform의 
	 * 검색에 의존적이다.
	 */ 
	public String getFilename()
	{
		int i0 = filepath.lastIndexOf('\\');
		if(i0==-1)
			return filepath;

		return filepath.substring(i0+1);
	}

	public void setSize( long size )
	{
		this.filesize = size;
	}

	public long getSize()
	{
		return this.filesize;
	}

	public void setPlayingTime( String time )
	{
		this.playtime = time;
	}

	public String getPlayingTime()
	{
		return this.playtime;
	}

	public void setRate( String rate )
	{
		this.rate = rate;
	}

	public String getRate()
	{
		return this.rate;
	}

	public void setArtist( String artist )
	{
		this.artist = artist;
	}

	public String getArtist()
	{
		return this.artist;
	}

	public void setTitle( String title )
	{
		this.title = title;
	}

	public String getTitle()
	{
		return this.title;
	}

	public String toString()
	{
		return "Path: " + getFilename() + " (" + playtime + ") " + address;
	}

	/**
	 * 이 mp3 파일을 다운로드를 시작한다.
	 * 
	 * 다운로드될 디렉토리는 current directory로 된다.
	 */
	public Download download()
	{
		return download( new File(System.getProperty("user.dir")) );	
	}

	/**
	 * 이 mp3 파일을 다운로드를 시작한다.
	 *
	 * @param  dir  다운로드할 디렉토리 
	 */
	public Download download( File dir )
	{
		return new Download(dir, this);
	}
}
