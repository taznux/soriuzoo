/* 
 * @(#)SearchEvent.java
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
package uzoo.event;

import java.util.EventObject;
import uzoo.MP3File;
/**
 * 파일이 하나 검색될때마다 발생되는 이벤트 클래스이다.
 * 
 * @author Jang-ho Hwang, rath@xrath.com
 * @version $Id$, since 2002/01/28
 */
public class SearchEvent extends EventObject
{
	private MP3File file;
	private int index;
	
	/**
	 * 검색이벤트를 생성한다.
	 * 
	 * @param  src    이벤트를 일으킨 source 객체.
	 * @param  file   검색된 파일 정보
	 * @param  index  이 파일에 대한 고유 인덱스
	 */
	public SearchEvent( Object src, MP3File file, int index )
	{
		super( src );

		this.file = file;
		this.index = index;
	}

	/**
	 * 검색된 파일정보 객체를 반환한다.
	 */
	public MP3File getFile()
	{
		return this.file;
	}

	/** 
	 * 파일의 고유 인덱스를 반환한다.
	 */
	public int getIndex()
	{
		return this.index;
	}
}