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
 * Ư�� mp3������ �ٿ�ε��ϸ鼭 �Ͼ�� �̺�Ʈ���� û���� �� �ְ�
 * ���ִ� EventListener interface�̴�.
 * 
 * @author Jangho Hwang, rath@xrath.com
 * @version 1.0.000, $Id$, since 2002/02/17
 */
public interface DownloadListener 
{
	/**
	 * �� ó���� ������ ���� �ٿ�ε尡 ���۵Ǿ��ٴ� ���� �˷��ش�.
	 */
	public void downloadStart( DownloadEvent e );
	
	/**
	 * �ٿ�ε� �ۼ�Ʈ�� �ٲ���������� �˷��ش�.
	 */
	public void downloadProgress( DownloadEvent e );

	/**
	 * �ٿ�ε� �۾��� ���ܰ� �߻��� ����� �������ش�.
	 */
	public void downloadError( DownloadEvent e );
};