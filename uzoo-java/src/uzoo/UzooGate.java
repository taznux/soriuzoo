/*
 * @(#)UzooGate.java
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

import java.io.*;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.SocketException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import rath.util.StringList;

import uzoo.io.ASRInputStream;
import uzoo.io.ResultReader;
import uzoo.event.SearchEvent;
import uzoo.event.SearchListener;
import uzoo.net.InetSocketAddress;
/**
 * <b>Main Control</b>�� ����ϴ� Ŭ�����ν�, �Ҹ��ٴ� ������ 
 * �α����ϰ�, �˻���û�� �ϸ� �̺�Ʈ�����ʸ� ���/�����ϴ� ���� 
 * �޼ҵ带 ������ �ִ�.
 * <p>
 * ������ ������ ��뿹���̴�.
 * <p>
 * <pre><code>
 * 
 * UzooGate gate = new UzooGate("rath", "pass"); // �α����Ѵ�.
 * // ó�� �����̹Ƿ� �ݵ�� �˻�DB�� update�ؾ��Ѵ�.
 * gate.updateDatabase(); 
 * gate.addSearchListener( new SearchListener() {
 *     public void foundMP3( SearchEvent e )
 *     {
 *         System.out.println( e.getFile() );
 *         if( e.getFilename().indexOf("��ũ")!=-1 )
 *         {
 *             Download down = e.download();
 *             down.start();
 *         }
 *     }
 * });
 * gate.search( "�̽�ȯ", 5000 );
 *
 * </code></pre>
 * 
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2002/01/28
 */
public class UzooGate
{
	private String version = null;
	private String gateway = null;
	private String username = null, password = null;

	private HashMap infoMap = new HashMap();
	private ArrayList serverList = new ArrayList();
	private Vector listeners = new Vector();

	private DatagramSocket socket = null;

	/**
	 * �ν��Ͻ��� �����ϰ� Gateway ������ ���´�.
	 *
	 * @exception  IOException  Gateway ������ �����µ� �������� ���
	 */
	public UzooGate() throws IOException
	{
		loadGateway();
	}

	/**
	 * �ν��Ͻ��� �����ϰ� Gateway ������ ���� �� ��ٷ� login�� �Ѵ�.
	 * �� �����ڴ� ������ �����ڸ� �θ���, 
	 * {@link #login(java.lang.String,java.lang.String) login} �޼ҵ带 �θ��Ͱ�
	 * ���� ������ �Ѵ�.
	 *
	 * @exception  IOException  Gateway ������ �����µ� �����߰ų�, �α��ο� 
	 *                          �����Ͽ��� ���
	 */
	public UzooGate( String username, String password ) throws IOException
	{		
		this();
		login( username, password );
	}

	/**
	 * �ڽ��� ���̵� ��ȯ�Ѵ�.
	 */
	public String getUsername()
	{
		return this.username;
	}

	private void loadGateway() throws IOException
	{
		InputStream in = new URL("http://www.soribada.com/gateway.txt").openStream();
		BufferedReader br = new BufferedReader( new InputStreamReader(in) );

		String ver = br.readLine(); // version information.
		this.version = ver.substring( ver.indexOf(':')+1 ).trim();
		
		String IS = br.readLine();
		this.gateway = IS.substring( IS.indexOf('=')+1 );
		br.close();
		in.close();
	}

	/**
	 * Login to soribada server and fetch initial information.
	 */
	public void login( String username, String password ) throws IOException
	{
		this.username = username;
		this.password = password;

		System.setProperty("uzoo.username", username);

		URL url = new URL(gateway+"?username="+username+"&password="+password+"&version="+version);
		InputStream in = url.openStream();

		try	{
			parseInformation(in);
		}
		finally	{
			in.close();
		}
	}	

	/**
	 * �˻� Ŭ���̾�Ʈ���� ����� ���� �޾ƿ´�. ����, login���� �ʰ� 
	 * ȣ���Ͽ��� ��쿡�� IllegalStateException�� ���� ���̴�.
	 *
	 * @return  �˻��� Ŭ���̾�Ʈ�� �� ����. (��ȿ Ŭ���̾�Ʈ ����)
	 */
	public int updateDatabase() throws IOException
	{
		if( !infoMap.containsKey("ASR") )
			throw new IllegalStateException("not login");

		serverList.clear();

		ASRInputStream asr = null;
		try
		{
			asr = new ASRInputStream( 
				new URL(getProperty("ASR")+"?action=gimme&username="+
				username+"&password="+password).openStream() );
			InetSocketAddress addr = null;
			while( (addr=asr.readAddress())!=null )
			{
				if(addr.isValidate())
					serverList.add( addr );
			}
		}
		finally
		{
			if( asr!=null )
				asr.close();
		}
		return serverList.size();
	}

	/**
	 * �˻��� �ɶ����� �߼۵� search �����ʸ� �߰��Ѵ�.
	 */
	public synchronized void addSearchListener( SearchListener l )
	{
		if(!listeners.contains(l))
			listeners.add(l);
	}

	/**
	 * �˻��̺�Ʈ�� �߼��Ѵ�.
	 */
	protected synchronized void fireSearchEvent( SearchEvent e )
	{
		for(Enumeration enum=listeners.elements(); enum.hasMoreElements(); )
			((SearchListener)enum.nextElement()).foundMP3(e);
	}

	/**
	 * �˻��� �ɶ����� �߼۵Ǵ� search �����ʸ� �����Ѵ�.
	 */
	public synchronized void removeSearchListener( SearchListener l )
	{
		listeners.remove(l);
	}

	/**
	 * �־��� keyword�� Uzoo���� mp3 ������ �˻��Ѵ�. 
	 * �˻��� ����ǰų� ���������� ������ �ʴ´ٸ�, 
	 * �� �޼ҵ�� blocking �ȴ�.
	 * <p>
	 * ���� 5�ʰ� �ƹ��� �˻������ �������� �ʴ´ٸ�, 
	 * ����Ǵ� �˻��� ����ɰ��̴�. ��� 5�ʶ�� ����Ⱓ�� 
	 * ���ٸ� ���涧���� ��� �˻��� ���̴�.
	 *
	 * ���� �˻��� �߰��� ����ϴ� ����� ����. ����ϵ��� �϶�.
	 * 
	 * @param  keyword  ����(0x20)�� �������� �ϴ� �˻�Ű����.
	 */
	public int search( String keyword ) throws IOException
	{
		return search( keyword, 0 );
	}

	/**
	 * �־��� keyword�� Uzoo���� mp3 ������ �˻��Ѵ�. 
	 * �˻��� ����ǰų� ���������� ������ �ʴ´ٸ�, 
	 * �� �޼ҵ�� blocking �ȴ�.
	 * <p>
	 * ����, �˻����� search �޼ҵ带 �ٽ� �θ��ٸ�, IOExcetion�� ������ ���̴�.
	 * �˻��� udp port binding�� �ʿ���ϹǷ� multiple instance�� ���� �� ����.
	 * 
	 * @param  keyword  ����(0x20)�� �������� �ϴ� �˻�Ű����.
	 * @param  timeout  �˻������ �о�� ���� �ð� (millisecond����)
	 */
	public int search( String keyword, final int timeout ) 
		throws IOException
	{
		socket = new DatagramSocket(9001);
		socket.setSoTimeout(15000);
		
		QueryShooter shooter = null;
		try {
		shooter = new QueryShooter( keyword, 
			new InetSocketAddress(getProperty("MYIP"), 9001), 
			this.serverList );
		shooter.setSocket( socket );
		shooter.start();
		}
		catch( Exception e ) { socket.close(); }

		/** Terminater thread */
		if( timeout!=0 )
			new Thread( new Runnable() {
				public void run()
				{
					try {
						Thread.currentThread().sleep(timeout);
					} catch( InterruptedException e ) {}
					stopSearch();
				}
			}).start();
		/** ------------ */

		DatagramPacket packet = new DatagramPacket(new byte[8192], 8192);

		int files = 0;
		try
		{
			while( !shooter.isSearchComplete() )
			{
				socket.receive(packet);
				
				byte[] b = packet.getData();
				if( b[0]==0x01 && b[9]==0x52 && b[10]==0x3a )
				{
					ResultReader srr = new ResultReader(new ByteArrayInputStream(b));
					int index = srr.getIndex();
					if( shooter.isMark(index) )
						continue;
					long ping = shooter.mark( index );
					
					MP3File file = null;
					while( (file=srr.readFile())!=null )
					{
						file.setPingTime(ping);
						fireSearchEvent( new SearchEvent(this, file, index) );
						files++;
					}
				}

				for(int i=8191; i>=0; i--)
					b[i] = 0;
			}
		}
		catch( InterruptedIOException e ) {}
		catch( SocketException e ) {}
		catch( IOException e ) {
			e.printStackTrace();
		}
		finally
		{
			shooter.interrupt();
			socket.close();
			socket = null;
		}		

		return files;
	}

	/**
	 * ���� �˻����̴� �۾��� �����Ѵ�.
	 */
	public void stopSearch()
	{
		if( this.socket!=null )
		{
			socket.close();
		}
	}

	/**
	 * Login�Ͽ����� ���� property �� ���� value�� ���� property�� ���ڿ��� ã��
	 * ��ȯ�Ѵ�. ����, ��û�� key�� �������� value�� ������ �ִٸ�, 
	 * index 0 �� �ִ� value���� ��ȯ�Ѵ�.
	 */
	public String getProperty( String key )
	{
		Object o = infoMap.get(key);
		if( o==null )
			return null;
		if( o instanceof String )
			return (String)o;
		else
		if( o instanceof StringList )
			return ((StringList)o).get(0);
		return null;
	}

	/**
	 * Login�Ͽ����� ���� property �� �������� value�� ���� property�� 
	 * ���ڿ����� StringList�� ��ȯ�Ѵ�.
	 */
	public StringList getProperties( String key )
	{
		return (StringList)infoMap.get(key);
	}

	/**
	 * Login�Ͽ����� ���� ��� property���� ��� �ִ� Map�� ��ȯ�Ѵ�.
	 */
	public Map getPropertiesMap()
	{
		return this.infoMap;
	}

	/**
	 * �α��� Response ������ parsing�Ͽ� ���� Map�� �����ϴ� �޼ҵ��̴�.
	 * <p>
	 */
	protected void parseInformation( InputStream in ) throws IOException
	{
		BufferedReader br = new BufferedReader( new InputStreamReader(in) );

		String header = br.readLine(); 
		int i0 = header.indexOf(':');
		if( i0==-1 )
			throw new IOException( "Illegal response header (couldn't find ':')" );
		String headerName = header.substring( 0, i0 ).trim();
		String headerValue = header.substring( i0+1 ).trim();

		if( !headerName.equals("Version") )
			throw UzooException.getInstance(headerValue);

		String line = null;
		String key = null;
		StringList values = new StringList(3);
		boolean modeKey = true;
		boolean multipleValues = false;
		boolean multipleLine = false;

		while( (line=br.readLine())!=null )
		{
			if(modeKey)
			{
				key = line;
				if( line.endsWith(" BEGIN") )
				{
					key = line.substring(0, line.indexOf(' '));
					multipleValues = true;
				}
				else
				if( line.equals("MYIP") ||
					line.equals("COVERZIP") ||
					line.equals("UPGRADE") )
					multipleLine = true;					

				modeKey = false;				
				continue;
			}

			if(multipleValues)
			{
				if( line.equals(key + " END") )
				{
					multipleValues = false;
					modeKey = true;
					infoMap.put( key, values.clone() );
					values.removeAll();
					continue;
				}
				values.add( line );
			}
			else
			if(multipleLine)
			{
				if( line.trim().length()==0 )
				{
					multipleLine = false;
					modeKey = true;
					infoMap.put( key, values.clone() );
					values.removeAll();
					continue;
				}
				values.add( line );
			}
			else
			{					
				modeKey = true;
				infoMap.put( key, line );
			}
		}
	}

	static boolean isFirst = true;

	public static void main( String[] args ) throws Exception
	{
		final UzooGate uzoo = new UzooGate("windrath", "bandelas");
		System.out.println( uzoo.updateDatabase() );
		long ll = System.currentTimeMillis();
		uzoo.addSearchListener( new SearchListener() {
			private int cc = 0;
			public void foundMP3( SearchEvent e )
			{
				MP3File file = e.getFile();
				System.out.println( (++cc) + ": " + file );

				if( !isFirst )
				{
					isFirst= false;
					uzoo.stopSearch();
					uzoo.net.Download down = file.download();
					down.start();
				}
			}
		});
		int count = uzoo.search(args[0]);
		System.out.println( count + " song(s) found" );
		System.out.println( "Time: " + (System.currentTimeMillis()-ll) );
	}
}
