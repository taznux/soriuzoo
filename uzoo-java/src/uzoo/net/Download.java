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
import uzoo.io.Writable;
/**
 * 주어진 mp3 파일을 실제로 다운로드해주는 클래스이다.
 * 다운로드중에 일어나는 일(파일완료, 예상치 못한 오류)등은.
 * 따로 DownloadEvent로 제어할 수 있다.
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
	private File toDownload = null;
	private long filesize;
	private long filesizeS;
	private Properties prop = new Properties();
	private int returnCode = -1;

	private Socket socket = null;
	private BufferedInputStream in = null;
	private OutputStream out = null;

	private OutputStream relayOut = null;
	private Writable relayWritable = null;

	private boolean isHandshake = false;

	public Download( File dir, MP3File file )
	{
		super( file.getFilename() );
		setPriority( MAX_PRIORITY );
		
		this.dir = dir;
		this.file = file;
	}

	/**
	 * 다운로드시, 파일시스템이 아닌 주어진 output stream으로
	 * Relay 되도록 한다.
	 */
	public void setRelay( OutputStream out )
	{
		this.relayOut = out;
	}

	/**
	 * 다운로드시, 파일시스템이 아닌 주어진 writable 인터페이스로
	 * Relay 되도록 한다.
	 */
	public void setRelay( Writable out )
	{
		this.relayWritable = out;
	}

	/**
	 * 다운로드될 파일 객체를 얻어온다.
	 */
	public MP3File getFile()
	{
		return this.file;
	}

	/*
	 * 이벤트 리스너를 달아서, 
	 * 
	 * - 다운로드 완료
	 * - 연결 실패 
	 * - 연결 직후 (리턴값, 메시지와 함께)
	 * - 퍼센트 변경 이벤트
	 * - 그밖의 예외
	 * - 스레드 종료 이벤트
	 */

	/**
	 * 현재 다운로드된 파일 크기를 얻어온다.
	 */
	public long getDownloadedFileSize()
	{
		return this.offset;
	}

	/**
	 * 다운로드할 파일의 전체 크기를 얻어온다.
	 */
	public long getFileSize()
	{
		return this.filesize;
	}

	/**
	 * 현재 다운로드한 백분률을 보여준다.
	 */
	public int getDownloadedPercent()
	{
		return (int)(offset/filesizeS);
	}

	private void makeConnection() throws IOException
	{
		InetSocketAddress addr = file.getAddress();
		this.socket = new Socket(addr.getHostAddress(), addr.getPort());
		this.socket.setSoTimeout( 60000 );
		this.in = new BufferedInputStream(socket.getInputStream());
		this.out = socket.getOutputStream();
	}

	public void closeAll() 
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
	 * 기존의 readLine 메소드와 비슷하지만, 
	 * EOF일때 null을 반환하는 것이 아니라,
	 * CRLF를 연속으로 2번 만나면 null을 반환한다.
	 * <p>
	 * 그리고 라인은 CRLF로 구분한다.
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
	 * 실제로 파일을 다운로드 받는다.
	 */
	protected void writeFile( File toStore ) throws IOException
	{
		downloadImpl( new FileOutputStream(toStore.getAbsolutePath(), true) );
	}

	protected void downloadImpl( OutputStream out ) throws IOException
	{
		try
		{			
			int pre = 0;

			byte[] buf = new byte[ 4096 ];
			int readlen;
			while( (readlen=in.read(buf))!=-1 )
			{
				out.write( buf, 0, readlen );
				out.flush();
				offset += readlen;
				int percent = getDownloadedPercent();
				if( percent!=pre )
				{
					pre = percent;					
					// firePercentModifyEvent
				}
			}
		}
		finally
		{
			out.close();
		}
	}

	protected void downloadImpl( Writable out ) throws IOException
	{
		try
		{
			int pre = 0;

			byte[] buf = new byte[ 4096 ];
			int readlen;
			while( (readlen=in.read(buf))!=-1 )
			{
				out.write( buf, 0, readlen );
				offset += readlen;
				int percent = getDownloadedPercent();
				if( percent!=pre )
				{
					pre = percent;	
					if( percent==100 )
						break;
					// firePercentModifyEvent
				}
			}
		}
		finally
		{
			out.closeOut();			
		}
	}

	/**
	 * 파일 수신요청에 대한 응답정보를 얻어온다.
	 * Succeded 이면 성공이고, 나머지는 모두 에러다.
	 * 만약 handshake하기 전에 이 메소드를 부른다면, null을 반환할 것이다.
	 */
	public String getReturnMessage()
	{
		return prop.getProperty("MTP");
	}

	/**
	 * 파일 수신을 위한 prepare를 한다.
	 * 만약 return code가 0이라면 start를 하여 파일수신을 시작하도록 하라.
	 *
	 * 
	 * @return     에러코드. (에러가 없을때는 0을 반환할 것이다.)
	 * @exception  IOException  연결에 실패하였을때
	 */
	public int handshake() throws IOException
	{
		makeConnection();

		long position = 0L;
		toDownload = new File(dir, file.getFilename());
		if( relayOut==null )	
		{
			position = toDownload.exists() ? toDownload.length() : 0L;
		}

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

		this.returnCode = -1;
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
			else
			{
				if( line.startsWith("MTP 1.0") )
				{
					returnCode = Integer.parseInt(line.substring(8, 11));
					prop.setProperty("MTP", line.substring(12).trim());
				}
			}
		}

		this.filesize = Long.parseLong(
			prop.getProperty("Filesize",String.valueOf(file.getSize())) );
		this.filesizeS = filesize / 100L;

		isHandshake = true;

		return returnCode;
	}

	/**
	 * Thread loop
	 */
	public void run()
	{
		int state = ERR_ATTEMPT_CONNECT;
		try
		{
			if( !isHandshake )
				handshake();
			if( returnCode!=0 )
				throw new IOException(returnCode+" "+prop.getProperty("MTP"));

			if( relayOut==null && relayWritable==null )
				writeFile(toDownload);
			else
			if( relayOut!=null )
				downloadImpl( relayOut );
			else
			if( relayWritable!=null )
				downloadImpl( relayWritable );
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
