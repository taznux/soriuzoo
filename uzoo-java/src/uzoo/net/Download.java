/* 
 * @(#)Download.java
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
package uzoo.net;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.BufferedInputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Properties;

import uzoo.MP3File;
/**
 * �־��� mp3 ������ ������ �ٿ�ε����ִ� Ŭ�����̴�.
 * �ٿ�ε��߿� �Ͼ�� ��(���ϿϷ�, ����ġ ���� ����)����.
 * ���� DownloadEvent�� ������ �� �ִ�.
 * 
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2002/01/29
 */
public class Download extends Thread
{
	public static final int ERR_ATTEMPT_CONNECT = 0;
	public static final int ERR_UNKNOWN_ERROR = 9;

	private File dir = null;
	private MP3File file = null;

	private volatile long offset = 0;
	private long filesize;
	private long filesizeS;
	private Properties prop = new Properties();

	private Socket socket = null;
	private BufferedInputStream in = null;
	private OutputStream out = null;

	public Download( File dir, MP3File file )
	{
		super( file.getFilename() );
		setPriority( MAX_PRIORITY );
		
		this.dir = dir;
		this.file = file;
	}

	/**
	 * �ٿ�ε�� ���� ��ü�� ���´�.
	 */
	public MP3File getFile()
	{
		return this.file;
	}

	/*
	 * �̺�Ʈ �����ʸ� �޾Ƽ�, 
	 * 
	 * - �ٿ�ε� �Ϸ�
	 * - ���� ���� 
	 * - ���� ���� ���� 
	 * - ���� �����Ͽ����� 100 User Limit ����
	 * - �ۼ�Ʈ ���� �̺�Ʈ
	 * - �� ���� ����
	 */

	/**
	 * ���� �ٿ�ε�� ���� ũ�⸦ ���´�.
	 */
	public long getDownloadedFileSize()
	{
		return this.offset;
	}

	/**
	 * �ٿ�ε��� ������ ��ü ũ�⸦ ���´�.
	 */
	public long getFileSize()
	{
		return this.filesize;
	}

	/**
	 * ���� �ٿ�ε��� ��з��� �����ش�.
	 */
	public int getDownloadedPercent()
	{
		return (int)(offset/filesizeS);
	}

	private void makeConnection() throws IOException
	{
		InetSocketAddress addr = file.getAddress();
		this.socket = new Socket(addr.getHostAddress(), addr.getPort());
		this.in = new BufferedInputStream(socket.getInputStream());
		this.out = socket.getOutputStream();
	}

	private void closeAll() 
	{
		if( in!=null )
		{
			try {
				in.close();
			} catch( Exception e ) {}
			in = null;
		}
		if( out!=null )
		{
			try {
				out.close();
			} catch( Exception e ) {}
			out = null;
		}
		if( socket!=null )
		{
			try {
				socket.close();
			} catch( Exception e ) {}
			socket = null;
		}
	}

	/**
	 * ������ readLine �޼ҵ�� ���������, 
	 * EOF�϶� null�� ��ȯ�ϴ� ���� �ƴ϶�,
	 * CRLF�� �������� 2�� ������ null�� ��ȯ�Ѵ�.
	 * <p>
	 * �׸��� ������ CRLF�� �����Ѵ�.
	 */
	protected String readLine() throws IOException
	{
		StringBuffer sb = new StringBuffer();

		int buf;
		while( (buf=in.read())!=-1 )
		{
			if( buf=='\r' )
			{
				in.mark(0);
				if( in.read()=='\n' )
				{
					if( sb.length()!=0 )
						return sb.toString();
					return null;
				}
				else
					in.reset();
				continue;
			}
			sb.append( (char)buf );
		}
		if( buf==-1 )
			return null;
		
		return sb.toString();
	}

	/**
	 * ������ ������ �ٿ�ε� �޴´�.
	 */
	protected void writeFile( File toStore ) throws IOException
	{
		FileOutputStream fos = new FileOutputStream(toStore, true);
		try
		{
			long poffset=0L;
			long ll = System.currentTimeMillis();
			
			int pre = 0;

			byte[] buf = new byte[ 4096 ];
			int readlen;
			while( (readlen=in.read(buf))!=-1 )
			{
				fos.write( buf, 0, readlen );
				fos.flush();
				offset += readlen;
				int percent = getDownloadedPercent();
				if( percent!=pre )
				{
					pre = percent;					
					// firePercentModifyEvent
					System.out.print( percent + "% " );
				}
			}
		}
		finally
		{
			fos.close();
		}
	}

	/**
	 * Thread loop
	 */
	public void run()
	{
		int state = ERR_ATTEMPT_CONNECT;
		try
		{
			makeConnection();
			state = ERR_UNKNOWN_ERROR;

			File toDownload = new File(dir, file.getFilename());
			long position = toDownload.exists() ? toDownload.length() : 0L;
	
			StringBuffer request = new StringBuffer();
			request.append("GETMP3");
			request.append("\r\n");
			request.append("Filename: ");
			request.append(file.getPath());
			request.append("\r\n");
			request.append("Position: ");
			request.append(position);
			request.append("\r\n");
			request.append("PortM: 9999\r\n");
			request.append("Username: ");
			request.append(System.getProperty("uzoo.username"));
			request.append("\r\n\r\n");

			System.out.println( request );

			out.write( request.toString().getBytes() );
			out.flush();

			String line = null;
			while( (line=readLine())!=null )
			{
				System.out.println( line );
				int i0 = line.indexOf(':');
				if( i0!=-1 )
				{
					String key = line.substring(0, i0).trim();
					String value = line.substring(i0+1).trim();
					prop.setProperty(key, value);
				}
			}
	
			this.filesize = Long.parseLong(
				prop.getProperty("Filesize",String.valueOf(file.getSize())) );
			this.filesizeS = filesize / 100L;

			writeFile(toDownload);
		}
		catch( Throwable e ) 
		{
			processError( state, e );
		}
		finally
		{
			closeAll();
		}
	}

	private void processError( int state, Throwable e )
	{
		e.printStackTrace();
	}
};
