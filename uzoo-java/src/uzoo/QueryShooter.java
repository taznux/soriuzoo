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
 * ��� �˻�Ŭ���̾�Ʈ�鿡�� �ϰ������� �˻���û UDP packet�� 
 * �߼��ϴ� �������̴�.
 * <p>
 * �� �ܿ��� UDP ��Ŷ �ս��� ����Ͽ� �� ��û ��Ŷ�� Mark�� 
 * �����Ͽ� ������(default 30ȸ) ���û�� �õ��Ѵ�.
 * ����, �˻������ ������ �޾Ҵٰ� mark�� �ϱ� ������ ó���� �˻�Ŭ���̾�Ʈ����
 * ���û�ϰ� �Ǵ� ���� ���� �Ͼ�� �ʴ´�.
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
	 * UDP ��Ŷ�� �߼��� socket�� �����Ѵ�.
	 * <b>Note</b> : QueryShooter�� start�ϱ� ���� �ݵ�� �������־�� �Ѵ�.
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

		/** �˻���û Flag�ΰ����� ����ȴ� */
		bos.write( 0x51 );
		bos.write( 0x3a );

		bos.write( queryString.toString().getBytes() );
		
		return bos.toByteArray();
	}

	/**
	 * Response�� ���� Index�� mark�������Ͽ� �ߺ� request���� �ʵ��� 
	 * ��ũ�Ѵ�.
	 *
	 * @return ����ð�.
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
	 * �־��� index�� mark �� ������ Ȯ���Ѵ�.
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
	 * �˻��� ����Ǿ����� Ȯ���Ѵ�.
	 */
	public boolean isSearchComplete()
	{
		return !this.isAlive();
	}

	/**
	 * �˻� Ŭ���̾�Ʈ���� �ϰ������� ������ �����Ѵ�.
	 * UDP �ս��� ����Ͽ� 100���� �ѹ��� 30ms ������ �����ش�.
	 * <p>
	 * System property�� <b>uzoo.query.interval</b>�� <b>uzoo.query.sleep</b>�� 
	 * ���������� �ؼ� udp �۽� �ֱ⸦ ������ �� �ִ�.
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
	 * UDP ��Ŷ �ս��� ����Ͽ� ���û Ƚ���� �����Ѵ�.
	 * �� ���� �����ϸ�, mark�� ���������� ��ȣ�ۿ��Ͽ� 
	 * loopCount ��ŭ ��ȿ�� request�鿡���� ���û�� �ϱ� ������
	 * �׸�ŭ ���� �˻������ ���� Ȯ���� ��������.
	 * �� �ʹ� ���� ũ�� ������ �ȴ�. 100�� ���� �ʱ� �ٶ���.
	 *
	 * @deprecated ���̻� ������ �ʴ´�.
	 */
	public void setLoopCount( int loopCount )
	{
		this.loopCount = loopCount;
	}

	/**
	 * UDP ��Ŷ �ս��� ����Ͽ� ������ ���û Ƚ���� ���´�.
	 * default ���� 30�̴�.
	 *
	 * @deprecated ���̻� ������ �ʴ´�.
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