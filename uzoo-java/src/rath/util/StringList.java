/*
 * @(#)StringList.java	  1.0    01/29/2001
 *
 * Copyright (c) 2001, JangHo Hwang
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 	1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 	2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 	3. Neither the name of the JangHo Hwang nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *    $Id$ 
 */
package rath.util;
/**
 * Vectoró�� ���� ��������, ���빰�� String�̶�� ������ �ִ�.
 * ��ſ�, Cast�ϴµ� �ʿ��� ����� ������ �� �ִ�.
 * ���� �����ڿ� �ʱ� capacity�� �������� ������
 * �������� ���ϰ� �����ν�, �氢���� �������ִ� Ŭ�����̴�.
 * <p>
 * ���� ��� �޼ҵ嵵 synchronized�Ǿ� ���� �����Ƿ�,
 * ���� �ӵ��� synchronized Ű���带 ����� �ͺ��� 4�� ������.
 *
 * @version $Id$ 
 * @author JangHo Hwang, windrath@hanmail.net
 */
public class StringList implements java.io.Serializable, Cloneable
{
	private String[] strings = null;
	private int elementCount;

	/**
	 * StringList ��ü�� �����Ѵ�.
	 *
	 * @param    capacity     Initial capacity�� �����Ѵ�.
	 */
	public StringList(int capacity)
	{
		strings = new String[capacity];
	}

	private void ensureCapacity( int minCapacity )
	{
		int oldCapacity = strings.length;
		if (minCapacity > oldCapacity)
		{
			String[] oldData = strings;
			int newCapacity = oldCapacity * 2;
			if( newCapacity < minCapacity )
			{
				newCapacity = minCapacity;
			}
			strings = new String[newCapacity];
			System.arraycopy(oldData, 0, strings, 0, elementCount+1-1 );
		}
	}

	/**
	 * �� ����Ʈ�� �־��� str�� ���ԵǾ��ִ��� Ȯ���Ѵ�.
	 */
	public boolean contains( String str )
	{
		for(int i=0; i<elementCount; i++)
		{
			if( strings[i].equals(str) )
				return true;
		}
		return false;
	}

	/**
	 * ���� ���빰�� ũ�⸦ ��ȯ�Ѵ�.
	 *
	 * @return    String���빰�� ũ��.
	 */
	public int size()
	{
		return elementCount;
	}

	/**
	 * index�� ��ġ�� ���ڿ��� ��ȯ�Ѵ�.
	 *
	 * @param    index    ������ ���ڿ��� ��ġ.
	 * @return    Ư�� ��ġ�� �ִ� ���ڿ�
	 */
	public String get( int index )
	{
		return strings[index];
	}

	public int getInteger( int index )
	{
		return Integer.parseInt( strings[index] );
	}

	public boolean getBoolean( int index )
	{
		return Boolean.valueOf( strings[index] ).booleanValue();
	}

	/**
	 * index�� ��ġ�� ���ڿ��� �����Ѵ�.
	 * �����Ѵٴ� ���� null�� ����ٴ� ���̴�.
	 * ������ remove�� �Ѵٰ��ؼ� size�� �������� ���� ���̴�.
	 *
	 * @param    index    ������ ���ڿ��� ��ġ.
	 */
	public void remove( int index )
	{
		strings[index] = null;
	}

	/**
	 * Ư�� ��ġ�� Ư�� ���ڿ��� ��ġ��Ų��.
	 *
	 * @param    index    ��ü��ų ��ġ
	 * @param    str    ��ü�� ���ڿ�
	 */
	public void setAt(int index, String str)
	{
		strings[index] = str;
	}

	/**
	 * StringArray�� ���ڿ��� �ϳ� �߰��Ѵ�.
	 * ������ ���ڸ� ��� ensureCapacity�޼ҵ带 ���ؼ�
	 * ���� �迭�� ũ�⸦ Ȯ���Ѵ�.
	 *
	 * @param    str    �߰��� ���ڿ�
	 */
	public void add( String str )
	{
		ensureCapacity(elementCount+1);
		strings[elementCount++] = str;
	}

	public void add( Object o )
	{
		add( String.valueOf(o) );
	}

	/**
	 * StringArray�� �����ϴ� ��� ���ڿ���
	 * �����Ѵ�.
	 */
	public void removeAll()
	{
		for(int i=0; i<elementCount; i++)
			strings[i] = null;
		elementCount = 0;
	}

	/**
	 * ���� ����Ʈ�� ���ִ� ������
	 * String �迭�� �����Ͽ� ��ȯ�Ѵ�.
	 *
	 * @return   String[] ������ ���빰.
	 */
	public String[] toArray()
	{
		String[] str = new String[ elementCount ];
		System.arraycopy( strings, 0, str, 0, elementCount );
		return str;
	}

	/**
	 * ���� StringList�� �ִ� ��� �ڷḦ
	 * Iterator�������� ��ȯ�Ѵ�.
	 */
	public Stringator iterator()
	{
		return new Stringator()
		{
			private int offset = 0;

			public boolean hasNext()
			{
				return offset<elementCount;
			}

			public String next()
			{
				return strings[offset++];
			}

			public void remove()
			{
				strings[offset] = null;
			}
		};
	}

    /**
     * �����Ѵ�. 
     */
    public synchronized Object clone()
    {
        try
        {
            StringList v = (StringList)super.clone();
            v.strings = new String[elementCount];
            System.arraycopy(strings, 0, v.strings, 0, elementCount);
            return v;
        }
        catch( CloneNotSupportedException e )
        {
            throw new InternalError();
        }
    }

	/**
	 * �� StringArray�� ��Ÿ�� �� �ִ� ��� ���ڿ��� ��ȯ�Ѵ�.
	 *
	 * @return    �� StringArray�� ��Ÿ�� �� �ִ� ���ڿ�.
	 */
	public String toString()
	{
		StringBuffer sb = new StringBuffer();
		sb.append( "[" );
		for(int i=0; i<elementCount; i++)
		{
			sb.append( strings[i] );
			if( (i+1)!=elementCount )
				sb.append( ", " );
		}
		sb.append( "]" );
		return sb.toString();
	}
}
