/* 
 * @(#)ResultReader.java
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

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.FilterInputStream;

import uzoo.MP3File;
import uzoo.net.InetSocketAddress;
/**
 * Uzoo�� �˻��� ��û������, �� �˻�Ŭ���̾�Ʈ�κ��� ����
 * �˻������ ���� �о���� �� �ְ� �ϴ� Reader Ŭ�����̴�.
 * 
 * @author Jang-ho Hwang, rath@xrath.com 
 * @version $Id$, since 2002/01/28
 */
public class ResultReader extends FilterInputStream
{
	private ByteArrayOutputStream bos = new ByteArrayOutputStream();
	private InetSocketAddress address = null;
	private int index;

	private String owner = null;

	/**
	 * �˻���� packet�� �о��ִ� reader�� �����Ѵ�.
	 * 
	 * @param  in  UDP�� ���� ByteArrayInputStream���� ������ byte[]
	 */
	public ResultReader( InputStream in ) throws IOException
	{
		super( in );

		in.skip( 1L ); // 0x01
		byte[] buf = new byte[6];
		in.read( buf );
		
		this.address = ASRInputStream.parseAddress(buf);
		this.index = in.read() | (in.read() << 8);
		in.skip(2L); // 0x52, 0x3a

		this.owner = readLine();
		this.address.setPort( Integer.parseInt(readLine()) );
	}

	/**
	 * �� �˻�������� ������ ������ ���� ���̵�(Soribada username)�� 
	 * ���´�.
	 */
	public String getFileOwner()
	{
		return this.owner;
	}

	/**
	 * �� �˻������ ������ �ε��� ���� �о�´�.
	 */
	public int getIndex()
	{
		return this.index;
	}

	/**
	 * �� �˻������ ������ ������� Address�� ���´�.
	 * �� �ּҴ� TCP�� mp3�� �ٿ�ε� �޴µ� ���� �ּ��̴�.
	 */
	public InetSocketAddress getAddress()
	{
		return this.address;
	}

	/**
	 * ������ �д´�. EOF�ų� 0�� �߰ߵǸ� null�� ��ȯ�Ѵ�.
	 */
	public String readLine() throws IOException
	{
		bos.reset();

		int buf;
		while( (buf=in.read())!=-1 )
		{
			if( buf==0 )
				break;

			if( buf=='\r' ) 
				continue;
			if( buf=='\n' ) 
				break;
			bos.write(buf);
		}

		if( buf<=0 ) 
			return null;

		return new String(bos.toByteArray());
	}

	private String[] info = new String[6];

	/**
	 * �� �˻�������� mp3 ���� ���� ���� �ϳ��� �о�´�.
	 * ���̻� ������ ���ٸ� null�� ��ȯ�� ���̴�.
	 */
	public MP3File readFile() throws IOException
	{
		for(int i=0; i<info.length; i++)
		{
			info[i] = readLine();
			if( info[i]==null )
				return null;
		}

		MP3File file = new MP3File();
		file.setAddress( this.address );
		file.setPath( info[0] );
		file.setSize( Long.parseLong(info[1]) );
		file.setPlayingTime( info[2] );
		file.setRate( info[3] );
		file.setArtist( info[4] );
		file.setTitle( info[5] );

		skipCRLF();
		return file;
	}

	/**
	 * �� ���������� �����ϱ� ���� padding�Ȱ͵��̳� ������� �͵���
	 * ��� skip �ع�����.
	 * <p>
	 * �̴� �� ������� \r\n\r\n�� ���еǾ����� �����̴�. 
	 * �̰��� ������� �ʴ´ٸ�, �߰��� ���� �̻��� �޽����鶧����
	 * ������ ���� ���̴�.
	 */
	private void skipCRLF() throws IOException
	{
		int buf;
		while( (buf=in.read())!=-1 )
		{
			if( buf=='\r' && 
				in.read()=='\n' &&
				in.read()=='\r' &&
				in.read()=='\n' )
				return;
		}
	}
}