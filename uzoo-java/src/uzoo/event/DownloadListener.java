/*
 * @(#)DownloadListener.java
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

/**
 * 특정 mp3파일을 다운로드하면서 일어나는 이벤트들을 청취할 수 있게
 * 해주는 EventListener interface이다.
 * 
 * @author Jangho Hwang, rath@xrath.com
 * @version 1.0.000, $Id$, since 2002/02/17
 */
public interface DownloadListener 
{
	/**
	 * 앞 처리를 끝내고 파일 다운로드가 시작되었다는 것을 알려준다.
	 */
	public void downloadStart( DownloadEvent e );
	
	/**
	 * 다운로드 퍼센트가 바뀌었을때마다 알려준다.
	 */
	public void downloadProgress( DownloadEvent e );

	/**
	 * 다운로드 작업중 예외가 발생한 사실을 통지해준다.
	 */
	public void downloadError( DownloadEvent e );
};