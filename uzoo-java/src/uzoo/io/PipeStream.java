/* 
 * @(#)PipeStream.java
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

import java.io.IOException;
import java.io.InputStream;
/**
 * Pipe 개념을 사용하여 입력을 출력으로 돌려주는 클래스이다.
 * <p>
 * 생성자에서 주는 buffer 크기는 중요하지 않다. 원래 
 * 사용목적은 버퍼를 주고, 버퍼가 넘어갈만큼 read를 해주지 않을 경우
 * 버퍼가 계속 차고 버퍼가 꽉 차면 Buffer Overflow 예외를 던지려 하였으나,
 * 다소 치사한것 같아, 버퍼가 꽉 찰때마다 0.5 사이즈씩 realloc을 하는 방식으로
 * 변경되었다.
 * 
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2002/01/30
 */
public class PipeStream extends InputStream implements Writable 
{
	private boolean isClose = false;
	private boolean isBlock = false;

	private byte[] buffer = null;
	/** 
	 * writer 가 써야할 offset 
	 */
	private int woff = 0;
	/** 
	 * reader 가 읽어야할 offset 
	 */
	private int roff = 0;

	public PipeStream()
	{
		this( 8192 );
	}

	public PipeStream( int bufsize )
	{
		this.buffer = new byte[bufsize];
	}

	public synchronized void write( int b ) throws IOException
	{
		if( isClose ) 
			throw new IOException("Pipe closed");

		this.buffer[woff++] = (byte)b;

		if(woff==buffer.length) woff = 0;
		if(woff==roff) 
		{
			byte[] old = buffer; 
			int remain = old.length - woff;
			this.buffer = new byte[ old.length * 2 ];
			System.arraycopy( old, 0, buffer, 0, woff );
			System.arraycopy( old, woff, buffer, buffer.length-remain, remain );
			roff = buffer.length - remain;

			System.out.println( "Realloc Buffer: " + buffer.length );
		}

		if( isBlock )
		{
			synchronized(this) {
				notify();
			}
		}
	}
	
	public void write( byte[] b ) throws IOException
	{
		write( b, 0, b.length );
	}

	public void write( byte[] b, int off, int len ) throws IOException
	{
		for(int i=off; i<len; i++)
			write( b[off+i] );
	}

	public synchronized void closeOut()
	{
		this.isClose = true;
		if( isBlock )
		{
			synchronized(this) {
				notify();
			}
		}
	}

	/**
	 *
	 */
	public synchronized int read() throws IOException
	{
		if( woff==roff ) 
		{
			if( isClose ) 
				return -1;
			try {				
				synchronized(this) {
					isBlock = true;
					wait();
				}
			} catch( InterruptedException e ) {}
			isBlock = false;
			if( isClose )
				return -1;
		}
		int ret = buffer[roff++];
		if( roff==buffer.length )
			roff = 0;
		return ret < 0 ? ret+0x100 : ret;	
	}

	public synchronized void close() throws IOException
	{
		closeOut();
		super.close();		
	}

	/**
	 * 이 클래스를 테스트해볼 수 있는 main method이다.
	 */
	public static void main( String[] args ) throws Exception
	{
		long ll = System.currentTimeMillis();
		final PipeStream pis = new PipeStream(65536);

		new Thread( new Runnable() {
			public void sleep( long ms ) throws InterruptedException
			{
				Thread.currentThread().sleep(ms);
			}
			public void run()
			{
				try {
				for(int i=0; i<4230309; i++)
				{	
					pis.write(8);
				}
				pis.closeOut();
				System.out.println( "Close" );
				} catch( Exception e ) { e.printStackTrace(); }
			}
		}).start();

		int count = 0;		
		byte[] buf = new byte[ 1024 ];
		int readlen = 0;

		while( (readlen=pis.read(buf))!=-1 )
		{
			count += readlen;
		}
		System.out.println( "Count: " + count );
		System.out.println( "Time: " + (System.currentTimeMillis()-ll) );
	}
}