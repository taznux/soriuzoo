/* 
 * @(#)DownloadEvent.java
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
/**
 *
 * @author Jangho Hwang, rath@xrath.com
 * @version 1.0.000, $Id$, since 2002/02/17
 */
public class DownloadEvent extends EventObject
{
	public static final int DOWNLOAD_START = 0;
	public static final int DOWNLOAD_PROGRESS = 1;
	public static final int DOWNLOAD_ERROR = 2;
	private int id;
	private int percent; 
	private Throwable e = null;

	public DownloadEvent( Object src, int id )
	{
		super(src);
		this.id = id;
	}

	public void setError( Throwable e )
	{
		this.e = e;
	}

	public void setDownloadedPercent( int percent )
	{
		this.percent = percent;
	}

	public int getDownloadedPercent()
	{
		return this.percent;
	}

	public Throwable getError()
	{
		return this.e;
	}

	public int getId()
	{
		return this.id;
	}
};