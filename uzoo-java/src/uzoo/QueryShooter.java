/*
 * @(#)QueryShooter.java
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

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.StringTokenizer;

import uzoo.net.InetSocketAddress;
/**
 * 모든 검색클라이언트들에게 일괄적으로 검색요청 UDP packet을 
 * 발송하는 스레드이다.
 * <p>
 * 이 외에도 UDP 패킷 손실을 고려하여 각 요청 패킷당 Mark를 
 * 관리하여 적당히(default 30회) 재요청을 시도한다.
 * 물론, 검색결과를 받으면 받았다고 mark를 하기 때문에 처리된 검색클라이언트에게
 * 재요청하게 되는 일은 결코 일어나지 않는다.
 * 
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2002/01/28
 */
public class QueryShooter extends Thread
{
	private ArrayList list = null;
	private int listsize;
	private byte[] queryData = null;
	private static final int START_COUNT = 94;

	private DatagramSocket socket = null;
	private boolean[] isComplete = null;
	private long[] pingTable = null;
	private int completeCount = 0;
	private int loopCount = 1;

	public QueryShooter( String keyword, InetSocketAddress local, ArrayList list )
		throws IOException
	{
		setName( "QueryShooter: " + keyword );
		setPriority( MAX_PRIORITY );

		this.queryData = createQueryPacket( keyword, local );		
		this.list = (ArrayList)list.clone();
		this.listsize = list.size();

		isComplete = new boolean[ START_COUNT + list.size() ];
		pingTable = new long[ START_COUNT + list.size() ];
	}

	/**
	 * UDP 패킷을 발송할 socket을 설정한다.
	 * <b>Note</b> : QueryShooter를 start하기 전에 반드시 설정해주어야 한다.
	 */
	public void setSocket( DatagramSocket socket )
	{
		this.socket = socket;
	}

	private byte[] createQueryPacket( String keyword, InetSocketAddress local )
		throws IOException
	{
		StringBuffer queryString = new StringBuffer();
		StringTokenizer st = new StringTokenizer(keyword, " ");
		while( st.hasMoreTokens() )
		{
			queryString.append( '+' );
			queryString.append( st.nextToken() );
			queryString.append( '\n' );
		}

		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		bos.write( 0x01 );
		bos.write( local.getBytes() );

		bos.write( 0x00 ); 
		bos.write( 0x00 );

		/** 검색요청 Flag인것으로 사려된다 */
		bos.write( 0x51 );
		bos.write( 0x3a );

		bos.write( queryString.toString().getBytes() );
		
		return bos.toByteArray();
	}

	/**
	 * Response를 받은 Index를 mark함으로하여 중복 request하지 않도록 
	 * 마크한다.
	 *
	 * @return 응답시간.
	 */
	public long mark( int index )
	{
		synchronized( isComplete )
		{
			isComplete[index] = true;
		}
		completeCount++;
		return System.currentTimeMillis() - pingTable[index];
	}

	/**
	 * 주어진 index가 mark 된 것인지 확인한다.
	 */
	public boolean isMark( int index )
	{
		boolean isMark = false;
		synchronized( isComplete )
		{
			isMark = isComplete[index];
		}
		return isMark;
	}

	/**
	 * 검색이 종료되었는지 확인한다.
	 */
	public boolean isSearchComplete()
	{
		return !this.isAlive();
	}

	/**
	 * 검색 클라이언트에게 일괄적으로 쿼리를 전송한다.
	 * UDP 손실을 고려하여 100번에 한번씩 30ms 적당히 쉬어준다.
	 * <p>
	 * System property로 <b>uzoo.query.interval</b>과 <b>uzoo.query.sleep</b>을 
	 * 설정함으로 해서 udp 송신 주기를 결정할 수 있다.
	 */
	protected void requestQuery() throws Exception
	{
		DatagramPacket packet = new DatagramPacket( queryData, queryData.length );
		int sended = 0;

		int interval = Integer.getInteger("uzoo.query.interval", 10).intValue();
		long sleep = Integer.getInteger("uzoo.query.sleep", 100).intValue();

		for(int i=0; i<listsize; i++)
		{
			if( isComplete[START_COUNT+i] )
				continue;
			InetSocketAddress addr = (InetSocketAddress)list.get(i);

			queryData[7] = (byte)(((i+START_COUNT) >> 0) & 0xff);
			queryData[8] = (byte)(((i+START_COUNT) >> 8) & 0xff);
			packet.setAddress( addr.getInetAddress() );
			packet.setPort( addr.getPort() );
			socket.send( packet );

			pingTable[i+START_COUNT] = System.currentTimeMillis();

			if((++sended%interval)==0)
				Thread.currentThread().sleep(sleep);
		}
	}

	/**
	 * UDP 패킷 손실을 고려하여 재요청 횟수를 설정한다.
	 * 이 값을 설정하면, mark와 유동적으로 상호작용하여 
	 * loopCount 만큼 무효한 request들에대해 재요청을 하기 때문에
	 * 그만큼 많은 검색결과를 얻어올 확률이 높아진다.
	 * 단 너무 값이 크면 무리가 된다. 100을 넘지 않길 바란다.
	 *
	 * @deprecated 더이상 사용되지 않는다.
	 */
	public void setLoopCount( int loopCount )
	{
		this.loopCount = loopCount;
	}

	/**
	 * UDP 패킷 손실을 고려하여 설정된 재요청 횟수를 얻어온다.
	 * default 값은 30이다.
	 *
	 * @deprecated 더이상 사용되지 않는다.
	 */
	public int getLoopCount()
	{
		return this.loopCount;
	}

	/** 
	 * Thread loop
	 */
	public void run()
	{
		try	
		{
			requestQuery();
		}
		catch( InterruptedException e ) {}
		catch( SocketException e ) {}
		catch( Exception e ) 
		{
			e.printStackTrace();
		}
	}
}