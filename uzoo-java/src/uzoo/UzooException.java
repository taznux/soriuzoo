/*
 * @(#)UzooException.java
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

import java.io.IOException;
/**
 * 서버로부터 받은 오류를 표현하는 예외클래스이다.
 *
 * @author Jang-ho Hwang, rath@xrath.com 
 * @version $Id$, since 2002/01/28
 */
public class UzooException extends IOException
{
	private int header = -1;

	/**
	 * 생성자.
	 */
	public UzooException( int header, String msg )
	{
		super( msg );

		this.header = header;
	}

	/**
	 * Soribada 서버로부터 받은 에러메시지를 Header와 message부분을
	 * 분리하여 UzooException의 인스턴스를 생성해준다.
	 *
	 * @param  rawmsg  서버로부터 받은 에러메시지
	 */
	public static UzooException getInstance( String rawmsg )
	{
		int i0 = rawmsg.indexOf(' ');
		int header = Integer.parseInt( rawmsg.substring(0,i0) );
		String msg = rawmsg.substring(i0+1);

		return new UzooException( header, msg );
	}

	/**
	 * 숫자로 구성된 오류코드를 반환한다.
	 */
	public int getErrorCode()
	{
		return this.header;
	}
}