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
 * <b>Main Control</b>을 담당하는 클래스로써, 소리바다 서버에 
 * 로그인하고, 검색요청을 하며 이벤트리스너를 등록/해제하는 등의 
 * 메소드를 가지고 있다.
 * <p>
 * 다음은 간단한 사용예제이다.
 * <p>
 * <pre><code>
 * 
 * UzooGate gate = new UzooGate("rath", "pass"); // 로그인한다.
 * // 처음 실행이므로 반드시 검색DB를 update해야한다.
 * gate.updateDatabase(); 
 * gate.addSearchListener( new SearchListener() {
 *     public void foundMP3( SearchEvent e )
 *     {
 *         System.out.println( e.getFile() );
 *         if( e.getFilename().indexOf("덩크")!=-1 )
 *         {
 *             Download down = e.download();
 *             down.start();
 *         }
 *     }
 * });
 * gate.search( "이승환", 5000 );
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
	 * 인스턴스를 생성하고 Gateway 정보를 얻어온다.
	 *
	 * @exception  IOException  Gateway 정보를 얻어오는데 실패했을 경우
	 */
	public UzooGate() throws IOException
	{
		loadGateway();
	}

	/**
	 * 인스턴스를 생성하고 Gateway 정보를 얻어온 후 곧바로 login을 한다.
	 * 이 생성자는 무인자 생성자를 부른뒤, 
	 * {@link #login(java.lang.String,java.lang.String) login} 메소드를 부른것과
	 * 같은 동작을 한다.
	 *
	 * @exception  IOException  Gateway 정보를 얻어오는데 실패했거나, 로그인에 
	 *                          실패하였을 경우
	 */
	public UzooGate( String username, String password ) throws IOException
	{		
		this();
		login( username, password );
	}

	/**
	 * 자신의 아이디를 반환한다.
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
	 * 검색 클라이언트들의 목록을 새로 받아온다. 만약, login하지 않고 
	 * 호출하였을 경우에는 IllegalStateException을 던질 것이다.
	 *
	 * @return  검색된 클라이언트의 총 갯수. (무효 클라이언트 제외)
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
	 * 검색이 될때마다 발송될 search 리스너를 추가한다.
	 */
	public synchronized void addSearchListener( SearchListener l )
	{
		if(!listeners.contains(l))
			listeners.add(l);
	}

	/**
	 * 검색이벤트를 발송한다.
	 */
	protected synchronized void fireSearchEvent( SearchEvent e )
	{
		for(Enumeration enum=listeners.elements(); enum.hasMoreElements(); )
			((SearchListener)enum.nextElement()).foundMP3(e);
	}

	/**
	 * 검색이 될때마다 발송되던 search 리스너를 제거한다.
	 */
	public synchronized void removeSearchListener( SearchListener l )
	{
		listeners.remove(l);
	}

	/**
	 * 주어진 keyword로 Uzoo에서 mp3 파일을 검색한다. 
	 * 검색이 종료되거나 인위적으로 멈추지 않는다면, 
	 * 이 메소드는 blocking 된다.
	 * <p>
	 * 만약 5초간 아무런 검색결과가 도착하지 않는다면, 
	 * 진행되던 검색은 종료될것이다. 대신 5초라는 공백기간이 
	 * 없다면 생길때까지 계속 검색될 것이다.
	 *
	 * 현재 검색을 중간에 취소하는 방법이 없다. 고려하도록 하라.
	 * 
	 * @param  keyword  공백(0x20)을 구분으로 하는 검색키워드.
	 */
	public int search( String keyword ) throws IOException
	{
		return search( keyword, 0 );
	}

	/**
	 * 주어진 keyword로 Uzoo에서 mp3 파일을 검색한다. 
	 * 검색이 종료되거나 인위적으로 멈추지 않는다면, 
	 * 이 메소드는 blocking 된다.
	 * <p>
	 * 만약, 검색도중 search 메소드를 다시 부른다면, IOExcetion이 던져질 것이다.
	 * 검색은 udp port binding을 필요로하므로 multiple instance를 가질 수 없다.
	 * 
	 * @param  keyword  공백(0x20)을 구분으로 하는 검색키워드.
	 * @param  timeout  검색결과를 읽어올 제한 시간 (millisecond단위)
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
	 * 현재 검색중이던 작업을 중지한다.
	 */
	public void stopSearch()
	{
		if( this.socket!=null )
		{
			socket.close();
		}
	}

	/**
	 * Login하였을때 얻은 property 중 단일 value를 갖는 property의 문자열을 찾아
	 * 반환한다. 만약, 요청한 key가 여러개의 value를 가지고 있다면, 
	 * index 0 에 있는 value만을 반환한다.
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
	 * Login하였을때 얻은 property 중 여러개의 value를 갖는 property의 
	 * 문자열들의 StringList를 반환한다.
	 */
	public StringList getProperties( String key )
	{
		return (StringList)infoMap.get(key);
	}

	/**
	 * Login하였을때 얻은 모든 property들을 담고 있는 Map을 반환한다.
	 */
	public Map getPropertiesMap()
	{
		return this.infoMap;
	}

	/**
	 * 로그인 Response 정보를 parsing하여 내부 Map에 보관하는 메소드이다.
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
