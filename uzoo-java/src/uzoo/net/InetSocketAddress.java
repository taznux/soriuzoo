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
 * JDK 1.4�� java.net.InetSocketAddress�� ���� ����� �ϴ� 
 * Ŭ�����̴�. 
 * ��, JDK 1.4 �̸��� ����ڸ� ���� �����д�.
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
	 * �ùٸ� Remote �ּ����� �˻��Ѵ�. 
	 * <p>
	 * {@link uzoo.io.ASRInputStream ASRInputStream} Ŭ������ ���� �ּҸ� 
	 * ���� ��� 5%�� ���ԵǾ� host,port�� �˾Ƴ��� ���Ͽ��� ���,
	 * �� �޼ҵ�� false�� ��ȯ�� ���̴�.
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
	 * 6byte ������� Encode�� byte[]�� ��ȯ�Ѵ�.
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
	 * �� ��ü�� �������°��� ���´�.
	 */
	public String toString()
	{
		if(host==null)
			return "Invalidated socket address";

		return host + ":" + port;
	}
}