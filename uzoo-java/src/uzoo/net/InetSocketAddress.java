/*
 * @(#)InetSocketAddress.java
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

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.StringTokenizer;
/**
 * JDK 1.4의 java.net.InetSocketAddress와 같은 기능을 하는 
 * 클래스이다. 
 * 단, JDK 1.4 미만의 사용자를 위해 만들어둔다.
 * 
 * @author Jang-ho Hwang, rath@xrath.com 
 * @version $Id$, since 2002/01/28
 */
public class InetSocketAddress
{
	private String host;
	private int port;

	public InetSocketAddress()
	{

	}

	public InetSocketAddress( String host, int port )
	{
		this.host = host;
		this.port = port;
	}

	/**
	 * 올바른 Remote 주소인지 검사한다. 
	 * <p>
	 * {@link uzoo.io.ASRInputStream ASRInputStream} 클래스를 통해 주소를 
	 * 읽을 경우 5%에 포함되어 host,port를 알아내지 못하였을 경우,
	 * 이 메소드는 false를 반환할 것이다.
	 */
	public boolean isValidate()
	{
		return this.host!=null;
	}

	public String getHostAddress()
	{
		return this.host;
	}

	public InetAddress getInetAddress() throws UnknownHostException
	{
		return InetAddress.getByName(this.host);
	}

	public int getPort()
	{
		return this.port;
	}

	public void setPort( int port )
	{
		this.port = port;
	}

	/**
	 * 6byte 블록으로 Encode한 byte[]를 반환한다.
	 */
	public byte[] getBytes()
	{
		if( host==null )
			return null;

		byte[] b = new byte[ 6 ];
		b[0] = (byte)(this.port - 9000);
		b[1] = 4; // Hard specified 
		
		// 3 0 2 1 
		// 5 2 4 3
		StringTokenizer st = new StringTokenizer( this.host, "." );
		b[3] = encode(Integer.parseInt(st.nextToken()));
		b[5] = encode(Integer.parseInt(st.nextToken()));
		b[4] = encode(Integer.parseInt(st.nextToken()));
		b[2] = encode(Integer.parseInt(st.nextToken()));
		return b;
	}

	private byte encode( int n )
	{
		return (byte)((n ^ 1 + 164) % 256);
	}

	/** 
	 * 이 객체의 문자형태값을 얻어온다.
	 */
	public String toString()
	{
		if(host==null)
			return "Invalidated socket address";

		return host + ":" + port;
	}
}