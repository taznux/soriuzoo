#include "uzooconfigimpl.h"

#include <qspinbox.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qdir.h>
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qcstring.h>
#include <qobject.h>
#include <qtextview.h>

#include <iostream.h>
#include <stdlib.h>
#define kor(x) QString::fromLocal8Bit(x)

UzooConfigImpl::UzooConfigImpl(QWidget*parent,const char*name,bool modal,
	int fl): UzooConfig(parent,name,modal,fl)
{
	versionLineEdit->setEnabled(false);
	passwdLineEdit->setEchoMode(QLineEdit::Password);
	connect(versionCheckBox,SIGNAL(toggled(bool)),
			this,SLOT(slotVersionEdited(bool)));

	infoString[0]	= kor("��Ŭ���̾�Ʈ�� �����ο�  :");
	infoString[1]	= kor("��ü �����ο�            :");
	infoString[2]	= kor("����� ��Ʈ              :");
	infoString[3]	= kor("�ִ� ��� ����           :");
	infoString[4]	= kor("���ε� ����              :");
	infoString[5]	= kor("�ٿ�ε� ����            :");
	infoString[6]	= kor("�÷��̾�                 :");
	infoString[7]	= kor("�÷��̾� ����            :");
	infoString[8]	= kor("�÷��̾� ���۽ð�(��)    :");
	infoString[9]	= kor("�����ID                 :");
	infoString[10]	= kor("��й�ȣ                 :");
	infoString[11]	= kor("�ڵ�����                 :");
	infoString[12]	= kor("�Ҹ��ٴ� ����            :");

	loadFileInfo();
	updateDialog();
	initTextFile();
}
UzooConfigImpl::~UzooConfigImpl()
{
}
void
UzooConfigImpl::initTextFile()
{
	developerTextView->setText(kor(
	"soriuzoo developer list<br>"
	"Analysis/Design<br>"
	"<b>Chang,Hye-Shik</b> perky@users.sourceforge.net<br>"
	"Qt Developer<br>"
	"<b>Lee,Jae-il</b> <a href=""mailto://sonegy@hanmail.net"">sonegy@hanmail.net</a><br>"
	));
	
	
	licenseTextView->setText(kor(
	"<CENTER><h1>GNU General Public License</h1></CENTER>

    <HR>
    <BLOCKQUOTE><P>
    This is an unofficial translation of the GNU General Public License into Korean. It
    was not published by the Free Software Foundation, and does not legally state the
    distribution terms for software that uses the GNU GPL--only the original English text
    of the GNU GPL does that. However, I hope that this translation will help Korean
    speakers understand the GNU GPL better.
    </BLOCKQUOTE>
    <HR>

    <P>
    �� ������ ���� ����Ʈ���� ���(Free Software Foundation)�� GNU General Public
    License�� �ѱ���� ������ ���̴�.
    <P>
    �� ������ GNU General Public License�� �����ϰ� �ִ� ȣ������ ������ ������ ������
    ���� ���� ����鿡�� �˸��� ���� ������� �ۼ��Ǿ����� ���� ����Ʈ���� �����
    ���� ������ ��޵� ���� ����. �̴� ������ ������ �ǵ��ϰ� �ִ� ������� �ְ����
    �ʰ� ���������� ��ȿ�ϱ� ���ؼ� ����Ǿ�� �� �籹�� ���� ������ ����� ���ռ�
    ���ο� ���� ���������� ���� �۾��� ���� ����� �ʿ��ϱ� �����̴�. ����, ����
    ����Ʈ���� ����� �����̳� �ؼ����� �������� ���ؼ� �߻��� �� �� ������
    ���ɼ��� �̿��� �����ϰ� ������ ��� �ִ� ����� ������ ���� ���� ����鿡��
    ȫ���Ϸ��� ��ݵ� ������ �ѱ��� �������� ���������� �������� �������ν�
    �縳��ų �� ���� ���̴�.
    <P>
    ���� ����Ʈ���� ����� GNU General Public License�� �ǹ��� ������ ���, ����
    ������ GNU General Public License�� ���ؼ� ���� �� ������ ȿ���� �ùٸ��� �߻���
    �� ������ �ǰ��ϰ� �ִ�. �� �������� ������ ����� �������� ���ϼ� ���ο� ����
    ������ ��ġ�� ���� ���̸� �̷� ���ؼ� �߱�� �� ���� ���� �� �������� ������
    ���ؼ� ��� ������ ������ ���� �ʴ´�.
    <P>
    Original Copy: <A HREF=""http://www.gnu.org/copyleft/gpl.html"">GNU General Public License</A> <BR>
    Korean Translator: 1998 Song Changhun ��â�� <A HREF=""mailto:chsong@cyber.co.kr"">chsong@cyber.co.kr</A>
    <P>

    <hr>

    <h3>�� ��</h3>

    <UL>
    <LI>GNU GENERAL PUBLIC LICENSE
      <UL>
      <LI>�� ��(�� ��)
      <LI>������ ����, ������ ���� ���ǰ� ����
      <LI>GPL�� �ǹ��� �����ϴ� ���
      </UL>
    </UL>

    <P>

    <hr>

    <h2>GNU GENERAL PUBLIC LICENSE</h2>

    <P>
    Version 2, June 1991

    <PRE>
    Copyright (C) 1989, 1991 <A HREF=""http://www.fsf.org"">Free Software Foundation</A>, Inc.
    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
    ���۱ǰ� ��� �㰡�� ���� �� ������ ��õǴ� ��,
    ��� ���� ��ü�� ���� ������ ���糪 ���鵵 �������� ���ȴ�.
    ��, ������ ���� ������ ÷���� ������ �ʴ´�.
    </PRE>

    <h2>�� ��</h2>

    ����Ʈ��� ���� ��κ��� ���̼����� �ش� ����Ʈ��� ���� ������ ������
    ������ �����Ϸ��� ���� �� �������� �Ѵ�. �׷���, GNU General Public License�� ����
    ����Ʈ��� ���� ������ ������ ������ ȣ�������� �����ϱ� ���ؼ� �����Ǿ���.
    ���� ����Ʈ���� ����� �����ϴ� ��κ��� ����Ʈ������� GNU General Public
    License�� ������ ���ؼ� �����ǰ� ������ ������ ���� ����� ���� ȿ�����̶��
    �ǴܵǴ� ���̺귯�� �����ƾ(library subroutine)�� ���, ������ ������ GNU Library
    General Public License�� ���������� �����ϰ� �ִ�. ���� ����Ʈ����� �̸�
    ����Ϸ��� ��� ����� ���ؼ� ������ ������ �ϸ��� �Բ� �絵�Ǵ� ����Ʈ���
    �ǹ��ϸ� ���α׷� �������� ������ ���� ��� ���α׷����� �� �������� �����
    �� �ִ�.
    <P>
    ���� ����Ʈ��� ����� �� ���Ǵ� '����'��� �ܾ��� �ǹ̴� �������� ������
    ������ �ƴ� ���ӵ��� �ʴ´ٴ� ���������� ������ �ǹ��ϸ� GNU General Public
    License�� ���� ����Ʈ��� �̿��� ������ ����, ������ ���� ��� ���� ������ ���
    ������ ������ ���������� �����Ѵ�. ���⿡�� �ҽ� �ڵ��� ���� �Ǵ� �Ϻθ�
    �����ؼ� ������ ���α׷����� ������Ű�ų� ���ο� ���α׷��� â���� �� �ִ�
    ������ ���ԵǸ� �ڽſ��� �絵�� �̷��� ������ �Ǹ����� ���� ��Ȯ�ϰ� �ν��� ��
    �ֵ��� �ϱ� ���� ���� ���� ���ԵǾ� �ִ�.
    <P>
    GNU General Public License�� �� ������ ����Ʈ���� �Ǿ絵���� �Ǹ��� �����ϴ� Ư��
    ���װ� �ܼ����� �������� ÷����Ű�� ���ϰ� �����ν� ����ڵ��� �������� ������
    �Ǹ��� �����ϰ� �ִ�. ���� ����Ʈ������ ���۰� ������ �����ϰ� �ִ� �������
    �̷��� ���������� �Ǹ� �絵 ������ �ؼ��ؾ߸� �Ѵ�.
    <P>
    ���� ���, Ư�� ���α׷��� ������ ��� �絵�ڴ� �Ǿ絵�ڿ��� �ڽ��� �絵�޾Ҵ�
    ��� �Ǹ��� ���� ���ο� ������� �״�� �����ؾ߸� �Ѵ�. �ҽ� �ڵ忡 ���� ���
    �Ǹ� ���� ���⿡ ���ԵǾ�� �ϸ� �̿� ���� ���׵��� ��������ν�
    �Ǿ絵�ڵ鿡�� �׵��� �絵���� �Ǹ��� �� �� �ֵ��� �ؾ� �Ѵ�.
    <P>
    ���� ����Ʈ���� ����� ������ ���� �� ���� ����� ���ؼ� �ݺ��Ǵ� �絵�� ����
    ����� ����� �Ǹ��� ��ȣ�Ѵ�: (1) ���۱��� ���������ν� ���α׷� �����ڵ���
    �Ǹ��� ��ȣ�Ѵ�. (2) ���۱��� �絵�� ���� �������� ���ؼ� ��ȿ�� ������ ȿ����
    ���� GNU General Public License�� ���ؼ� ����Ʈ������ ������ ����, ���� � ����
    ����Ʈ���� �Ǿ絵���� �Ǹ��� ���������� �����Ѵ�.
    <P>
    ���� ����Ʈ������ ����ڵ��� �������� �絵 ������ ���ؼ� ����Ʈ���� ��ü��
    ������ ������ ���� ������ �߻��� �� ������ �̴� ������ �����ڿ� ����
    ����Ʈ��� ���� ������ �ƴ� �� �ִٴ� �������� ���ؼ� �ν��ϰ� �־�� �Ѵ�.
    GNU General Public License�� ���� ����Ʈ��� ���� ��� ������ ������ ��������
    ���� ������ �̷��� ������ ����Ǿ��� �����̸� �̴� ���α׷� �������ڿ� ����
    ����Ʈ���� ����� �����ο� Ȱ���� �����ϴ� �������� �����̱⵵ �ϴ�.
    <P>
    Ư�� ������ ���� ����Ʈ������ ������ �����ϴ� ����� ���ۿ� ����. ����, ����
    ����Ʈ��� ������ ��� �������� ���� ������ Ư�㸦 ����� ���۹��� �Բ�
    ���Խ�Ű�� �������ν� �̿� ���� ������ ���ѵ��� �ʵ��� �ϴ� ���� �ּ���
    ����̴�. GNU General Public License�� �̷��� ������ ��ó�ϱ� ���ؼ� Ư�㰡 ����
    ���۹��� �� ���̼����� ��Ư�� �ټ�(����, &quot;����&quot;�̶� �Ѵ�)���� ����������
    ����ϴ� ��쿡 ���ؼ� ���� ����Ʈ����� �Բ� ����� �� �ֵ��� �����ϰ� �ִ�.
    <P>
    ����(copying)�� ����(modification), ����(distribution) � ���õ� ��ü���� ���ǰ�
    ������ ������ ����.
    <P>

    <h2>������ ����, ������ ���� ���ǰ� ����</h2>

    <P>
    <strong>�� 0 ��.</strong>
    �� ���̼����� GNU General Public License�� ������ ���� ������ �� �ִٴ�
    ������ ���۱��ڿ� ���ؼ� ��õ� ��� ��ǻ�� ���α׷� ���۹��� ���ؼ� �����ϰ�
    ����ȴ�. ��ǻ�� ���α׷� ���۹�(����, &quot;���α׷�&quot;�̶� �Ѵ�)�̶� Ư��
    ���α׷��̳� �̿� ���õ� ��Ÿ ���۹��� �ǹ��ϰ� &quot;2���� ���α׷�&quot;�̶�
    ���۱ǹ��� ������ ���� ���α׷��� ���� �Ǵ� ��� �κ��� �����ϰų� �ٸ�
    ���α׷��� ������ ������ ������ �� �ִ� ���� ������ ���ؼ� â�۵� ���ο�
    ���α׷��� �̿� ���õ� ���۹��� �ǹ��Ѵ�(���ķ� �ٸ� ���α׷��� ������
    ������ ���ٸ� ���� ���� ������ ������ ���ԵǴ� ������ �����Ѵ�) &quot;�Ǿ絵��&quot;��
    GNU General Public License�� ������ ���ؼ� ���α׷��� �絵���� ����� �ǹ��Ѵ�.
    <P>
    �� ���̼����� ���α׷��� ���� ������ ����, ���� ������ ���ؼ��� ����ȴ�.
    ����, ���α׷��� �����Ű�� ������ ���ѵ��� ������ ���α׷��� ���࿡ ����
    ������� ���� ��ü�� ���� ������� ���� ���ο� ������� ������� 2����
    ���α׷��� �������� ���� ���ؼ� �� ���̼����� ������ ������ �� �ִ�. 2����
    ���α׷��� ���� ���δ� 2���� ���α׷� �ȿ����� ���α׷��� ������ ����
    �Ǵ��Ѵ�.
    <P>
    <strong>�� 1 ��.</strong>
    �Ǿ絵�ڴ� ���α׷��� ���� ������ �������� �ʴ´ٴ� ��ǰ� ���۱���
    �Բ� ����ϴ� ��, �絵���� �ҽ� �ڵ��� ���� �Ǵ� �Ϻθ� ��� ���� ��ü��
    ���ؼ��� �����ؼ� ������ �� �ִ�. �Ǿ絵�ڰ� ���α׷��� �ҽ� �ڵ带 �������
    ���� ���α׷��� ���� ������ �Ῡ�Ǿ� �ִٴ� ��ǰ� �� ���̼����� ���ؼ� �����
    ���׵��� �絵���� �״�� �������Ѿ� �ϸ� GNU General Public License ������ �Բ�
    �����ؾ� �Ѵ�.
    <P>
    �������� ������ ���, �������� �����ϱ� ���ؼ� �ҿ�� ��� ����ϱ� ���ؼ�
    �������� ����� �Ǹ��� �� ������ ���� �Ǹſ� ���� �������� ȯ���� �����ϴ�
    ������ ������ ������ �� �ִ�.
    <P>
    <strong>�� 2 ��.</strong>
    �Ǿ絵�ڴ� �ڽ��� �絵���� ���α׷��� ���� �Ǵ� �Ϻθ� ������ �� ������
    �̸� ���ؼ� 2���� ���α׷��� â���� �� �ִ�. ���۵� ���α׷��̳� â�۵� 2����
    ���α׷��� �ҽ� �ڵ�� �� 1 ���� ������ ���ؼ� ������ ���׵��� ������Ű��
    ���ǿ� ���ؼ� �����ؼ� ������ �� �ִ�.

    <OL TYPE=""a"">
    <LI>
      ���۵� ������ ������ ���۵� ��ǰ� ���۵� ��¥�� ��������� Ȯ�ε� ��
      �ֵ��� �ۼ��Ǿ�� �Ѵ�.<P>
    <LI>
      �����ϰų� �����Ϸ��� ���۹��� ���� �Ǵ� �Ϻΰ� �絵���� ���α׷���
      �κ��� �Ļ��� ���̶�� ���۵� ���α׷��� ���� �������̳� ���ǹ� �� ü��
      ���� ��� �Ǹ��� ���߿��� �������� ����ؾ� �Ѵ�.<P>
    <LI>
      ���۵� ���α׷��� �Ϲ����� ���� ���°� ��ɾ� �Է� ��Ŀ� ���� ��ȭ ��
      ���� �� ���, ���۵� ���α׷��� �̷��� ��ȭ�� ������ �����ϰ� �� ��Ǿ���
      �� ���۱ǿ� ���� ���װ� ���α׷��� ���� ������ �Ῡ�Ǿ� �� �ٴ� �����
      ���۵� ���α׷��� �� ���̼����� ������ ���ؼ� �ٽ� ���� �ؼ� ������ ��
      �ִٴ� ���װ� GNU General Public License�� ������ �� �ִ� ����� �Բ� ����
      ���Ŀ� ���� �Ǵ� ȭ���� ���ؼ� ��µ� �� �ֵ� �� �ۼ��Ǿ�� �Ѵ�(���� ����:
      �絵���� ���α׷��� ��ȭ�� ������ �� �߰� �ִ� �ϴ��� ������� ����
      ȯ�濡�� ������ ���׵��� ��µ��� �ʴ� ���¿��� ���, �̸� ������ ���α׷�
      ���� ���� ���׵��� ��½� Ű�� �ʾƵ� �ȴ�)<P>
    </OL>

    <P>
    �� ���׵��� ���۵� �κ��� ���Ե� 2���� ���α׷� ��ü�� ����ȴ�. ����, ���
    ���۹��� 2���� ���α׷��� ���ԵǾ� �ִ� �κа� ������ ���̶� �ϴ��� �װ���
    �絵���� ���α׷����κ��� �Ļ��� ���� �ƴ϶� ������ ���� ���۹��� ������ ����
    ����� ������ ���� ���, �� ���۹��� �������� ���� �������� �� ���̼�����
    �������� ������� �ʴ´�. �׷���, �̷��� ���۹��� 2���� ���α׷��� ���ԵǾ�
    �Բ� �����ȴٸ� �������� ���۱ǰ� ���� ���ؿ� ������� �������� ��ü ���۹�
    ��ΰ� �� ���̼����� ���ؼ� �����Ǿ�� �ϸ� ��ü ���۹��� �Ϻ� �Ǵ� ���ο� ����
    ������ ��� �Ǹ��� ���߿��� �������� �絵�Ǿ�� �Ѵ�.
    <P>
    �̷��� ������ �������� ���۹��� ���� ���۱����� �Ǹ��� ���ҽ�Ű���� ����
    �ƴ϶� 2 ���� ���α׷����κ��� �ݺ������� �Ļ��ǰų� �̷��� ���α׷����� ���
    ���� �������� ���ؼ� �� ���̼����� �������� �����ϰ� �����ϱ� ���� ���̴�.
    <P>
    ���α׷�(�Ǵ� 2���� ���α׷�)���� �ܼ��� �����ϰų� ������ �������� �Բ�
    ������ ���� ���� �̵��� �Ļ��� ���۹��� �������� �ʴ� �� �� ���̼����� ���ؼ�
    �����ȴ�.
    <P>
    <strong>�� 3 ��.</strong> �Ǿ絵�ڴ� ������ ���� �� �ϳ��� ������Ű�� ���ǿ� ���ؼ� �� 1 �װ� �� 2
    ���� ������ ���� ���α׷�(�Ǵ� �� 2 ���� ������ ���� 2 ���� ���α׷�)�� ����
    �ڵ峪 ���� ���·� �����ؼ� ������ �� �ִ�.

    <OL TYPE=""a"">
    <LI>
      ���� �ڵ峪 ���� ���¿� �ش��ϴ� �ҽ� �ڵ��� ���θ� �� 1 �װ� �� 2 ����
      ������ ���� ��ǻ�Ͱ� �Է¹ްų� ������ �� �ִ� ���·� ����Ʈ ������
      ������ ���ؼ� �Ϲ������� ���Ǵ� ���� ��ü�� ���ؼ� �Բ� �� ���ؾ� �Ѵ�.<P>
    <LI>
      ���� �ڵ峪 ���� ���¿� �ش��ϴ� �ҽ� �ڵ��� ���θ� �ּ��� 3�� �̻�
      ������ �� �ִ� �μ⹰�� ���·� �� 1 �װ� �� 2 ���� ������ ����
      ����Ʈ������ ������ ���ؼ� �Ϲ������� ���Ǵ� ���� ��ü�� ���ؼ� ����
      �Ǻ� ���ϴ� ��븸�� �ΰ��ؼ� ���߿��� �絵�� �� �ֵ��� �Բ� �����ؾ�
      �Ѵ�.<P>
    <LI>
      ���� �ڵ峪 ���� ���¿� �ش��ϴ� �ҽ� �ڵ��� ���θ� ����� �� �ִ�
      ����� ���� ������ �Բ� �����ؾ� �Ѵ�(�� �׸��� �񿵸����� ������ �׸�
      2)�� ���ؼ� ���� �ڵ峪 ���� ������ �������� ������ ���� ���� �� ����� ��
      �ִ�)
    </OL>

    <P>
    ���۹��� ���� �ҽ� �ڵ�� �ش� ���۹��� �����ϱ� ���ؼ� �Ϲ������� ��ȣ�Ǵ�
    ǥ�� ������ �ǹ��ϰ� ���๰�� ���� �ҽ� �ڵ�� �ùٸ��� ����Ǳ� ���ؼ� �ʿ���
    ���� �������̽� ���� ����, �����ϰ� ��ġ�� ���ؼ� �ʿ��� ��ũ��Ʈ ���� ���
    �����Ѵ�. �׷���, �����Ϸ��� Ŀ�ΰ� ���� �ü���� �ֿ� �κе鿡 ���� �ҽ�
    �ڵ峪 ���̳ʸ� ���´� ���α׷��� �̷��� �κе�� ���� ������� �ʴ� �� �Բ�
    �������� �ʾƵ� �����ϴ�.
    <P>
    ���� �ڵ峪 ���� ���¸� Ư�� ��ҷκ��� ������ �� �ֵ��� ����ϴ� �������
    ������ ���, ������ ��ҷκ��� �ҽ� �ڵ带 ������ �� �ֵ��� ����ϴ� ����
    �Ǿ絵�ڿ��� �ҽ� �ڵ带 ���� �ڵ峪 ���� ���¿� �Բ� ������ �� ���� ��������
    �ʾҴ� �ϴ��� �ҽ� �ڵ带 �Բ� �����ϴ� ������ �����Ѵ�.
    <P>
    <strong>�� 4 ��.</strong> �� ���̼����� ���ؼ� ��������� ���α׷��� �絵���� �ʾҴٸ� �絵����
    ���α׷��� ���� ������ ����, ������ ���̼��� ������ ���� ���� ���� �� �� ����.
    �̿� ���õ� ��� ������ ���������� ��ȿ�̸� �� ���̼������� �����ϰ� �ִ�
    ������ ��� �Ǹ��� �ڵ������� �Ҹ�ȴ�. ��, �� ���̼����� ������ ������ �ʰ�
    �絵���� ���α׷��̶� �ϴ��� �̸� ������� ���̼��� �絵 ������ ���� �ٽ�
    �������� ���, ���α׷��� �ٽ� �絵���� �� 3�� �Ǿ絵�ڴ� �� ���̼�����
    �ؼ��ϴ� �����Ͽ��� ������ �Ǹ��� ������ �� �ִ�.
    <P>
    <strong>�� 5 ��.</strong> �Ǿ絵�ڴ� ���α׷��� �絵�� ���� �� ���̼����� �������� �������ν� ��
    ���̼����� �������� �޾Ƶ����� ���� �� �ִ�. �� ���, �Ǿ絵�ڿ��Դ� ���α׷���
    ���� �ܼ��� ��븸�� ���Ǹ� ���α׷��� 2���� ���α׷��� ���� ���۰� ����
    ������ ������ �ʴ´�. �̴� �Ǿ絵�ڰ� ���̼����� �������� �������ν� �߻���
    ������ ���� �����̴�. ����, ���α׷�(�Ǵ� 2���� ���α׷�)�� �����ϰų�
    �����ϴ� ������ ������ ����, ������ ���� �� ���̼����� ������ ���ǵ��� ���
    �޾Ƶ��̰ڴٴ� �������� ���Ƿ� �����Ѵ�.
    <P>
    <strong>�� 6 ��.</strong> �Ǿ絵�ڿ� ���ؼ� ���α׷�(�Ǵ� 2���� ���α׷�)�� �ݺ������� ������
    ���, �� �ܰ迡���� �Ǿ絵�ڴ� �� ���̼����� ������ ���� ���α׷��� ������ ����,
    ������ ���� ������ ������ ���α׷� �絵�ڷκ��� �絵���� ������ �ڵ�������
    ���ֵȴ�. ���α׷�(�Ǵ� 2���� ���α׷�)�� �絵�� ���� �Ǿ絵���� �Ǹ��� ������
    �� �ִ� ��� ���׵� �������� ÷���� �� ������ �� ������ �� ���̼����� ��������
    �ؼ��ϵ��� ������ �� ����.
    <P>
    <strong>�� 7 ��.</strong> ������ �ǰ��̳� Ư��� ħ�ؿ� ���� ���� �Ǵ� Ư�� ������ ���ѵ��� �ʴ�
    �� ���� �ٸ� ������� ���ؼ� �� ���̼����� ������ ��ġ�Ǵ� ����� �߻��Ѵ�
    �ϴ��� �� ���̼����� ��ġ�Ǵ� �������� �� ���̼����� ���� ���� ���� �켱����
    ���� ������ �ʴ´�. ����, ������ ����̳� ���� � ���ؼ� �� ���̼�����
    ����Ǵ� ���׵��� �ΰ��ȴ� �ϴ��� �� ���̼����� �������� �Բ� ������Ű�鼭
    �ش� ���α׷��� ������ �� ���ٸ� �� ���α׷��� ������ �����ȴ�. ���� ���, Ư��
    Ư�� ���� ���̼����� ���� �Ǵ� �������� �絵 ����� ���ؼ� ���α׷��� ��������
    �����ϴ� ���� ������� �ʴ´ٸ� �� ���α׷��� �� ���̼����� ������ ���ؼ�
    �����Ǵ� ���α׷���� �Բ� ������ �� ����.
    <P>
    Ư�� ��Ȳ���� �� ������ �Ϻκ��� ����� �� ���� ��쿡�� �ش� �κ��� ������
    ������ �κе��� �����Ű�� �� ������ ���θ� �����Ű�� ���ؼ��� �ٸ� ��Ȳ��
    ���ǵ��� �ʿ��ϴ�.
    <P>
    �� ������ ������ Ư�㳪 ���� ħ�� ���� ������ �����ϰų� �ش� �Ǹ��� ��������
    �������� ���� �ƴ϶� GNU General Public License�� �������� ������ ���ؼ� ����
    ����Ʈ������ ���� ü�踦 ���������� ��ȣ�ϱ� ���� ���̴�. ���� ������� ����
    ü�迡 ���� �ŷ��ִ� ������ ����� �����ν� ����Ʈ������ �پ��� �о߿� ����
    ������ �� �־���. ����Ʈ��� ��� ���� ü�踦 ���ؼ� ������ ���ΰ���
    �����ϴ� ���� �������� �����ڿ� ���������� ������ �޷����� �Ϲ� ����ڵ���
    ������ �� �ִ� ������ �ƴ� ���̴�.
    <P>
    �� ������ ��ӵǴ� �� ���̼����� ������� ���ؼ� �߿��ϰ� ��޵ǰ� �ִ� ������
    ���� ��Ȯ�ϰ� �����ϴ� �� ������ �� ���̴�.
    <P>
    <strong>�� 8 ��.</strong> Ư��ǰ� ���۱��� ���� ó�� ��Ŀ� ���ؼ� Ư�� �������� ���α׷���
    ������ ����� �Բ� �Ǵ� ���������� ������ ���, �� ���̼����� ���ؼ� ���α׷���
    ������ �������ڴ� ������ �߻����� �ʴ� ������ ���ؼ� �̸� �����Ѵٴ� ��������
    ������ ���� ������ ������ �� ������ �̷��� ������ �� ���̼����� �Ϻη� ���ֵȴ�.
    <P>
    <strong>�� 9 ��.</strong> ���� ����Ʈ���� ����� GNU General Public License�� �����ϰų� ������ ��
    �ִ�. �����ǰų� �����Ǵ� ������ ���ο� ������ ���ɿ� ���� ����������
    �����ǰ����� �� �ٺ� ������ �ٲ��� ���� ���̴�.
    <P>
    GNU General Public License�� ��� ������ �ٸ� ���� ��ȣ�� ������ ���̴�. �絵����
    ���α׷��� Ư�� ������ ���̼����� ����ϰ� �ִٸ� �ش� ���� �Ǵ� �� ������
    ���̼����� ����Ǹ� ������ ������� ���� ���� ��� ������ ���̼�����
    �����ص� �����ϴ�.
    <P>
    <strong>�� 10 ��.</strong> ���α׷��� �Ϻθ� �� ���̼����� ���� ������ �ٸ� ���� ���α׷��� �Բ�
    ������ ���, �ش� ���α׷��� �����ڷκ��� ������ ���� ������ �޾ƾ� �Ѵ�. ����
    ����Ʈ���� ����� ���۱��� ���� �ִ� ����Ʈ��� ����ϱ� ���ؼ��� ����
    ����Ʈ���� ����� ������ ���� �Ѵ�. ���� ����Ʈ���� ����� ���� ��ǿ� ���ؼ�
    ���� ������ �� �� �ִ�. ���� ����Ʈ���� ����� ���� ����Ʈ������ 2����
    ���۹����� ��� �����ο� ���·� ������Ű���� ������ ����Ʈ������ �Ϲ�����
    ������ ��Ȱ���� ������Ű���� ���ؿ� �ٰ��ؼ� ���� ���θ� ������ ���̴�.
    <P>
    <strong>������ �Ῡ</strong>
    <P>
    <strong>�� 11 ��.</strong> �� ���̼����� ���� ���α׷��� �������� �絵�ǹǷ� ���� ���� ����ϴ�
    �ѵ� ������ ��� ������ ������ �������� �ʴ´�. ��, ���α׷��� ���۱��ڿ� ��
    3�� �����ڿ� ���ؼ� ���� �Ǵ� ���������� Ư�� ������ ���� ���α׷��� ���ռ�
    ���θ� �����ϱ� ���� ��쳪 ����� �Ǹſ� ���� ������ ������ �����ȴٴ� ������
    �������� ��õǾ� �ִ� ���� ���ܷ� �Ѵ�. �� ��쵵 �ش� ���α׷� ��ü�� ����
    �ִ� �ٿ����� ������ �Ῡ�� ������ ���� ����. ���α׷��� ���α׷��� ���࿡ ����
    �߻��� �� �ִ� ������ ��� �Ǿ絵�ڿ��� �μ��Ǹ� �̿� ���� ���� �� ������ ����
    ���� ��� ���� ��� �Ǿ絵�ڰ� �δ��Ѵ�.
    <P>
    <strong>�� 12 ��.</strong> ���۱��ڳ� �� 3�� �����ڰ� ���α׷��� �ջ� ���ɼ��� ������ �˰� �־���
    �ϴ��� �߻��� �ս��� ���� ���Կ� ���ؼ� ��ȣ�ǰ� �ְų� ���۱��ڳ� ���α׷�
    ��ü�� ���� ������ �������� �ʴ´ٴ� ������ ���α׷��� ���۵� ���α׷��� �Բ�
    �Ǵ� ���������� ������ �����ڰ� �������� ������ ������ ������ ��찡 �ƴ϶��
    ���α׷��� ����̳� ������ �̼����� ���ؼ� �߻��� �ս��� ��� �Ǿ絵����
    å���̴�. �߻��� �ս��� �Ϲݼ��̳� Ư���� �Ӹ� �ƴ϶� ������ ��߼� �� �ʿ�����
    ������� �ʴ´�.

    <h3>������ ����, ������ ���� ���ǰ� ������ ��.</h3>

    <h2>�������� �ǹ��� �����ϴ� ���</h2>

    <P>
    ������ ���α׷��� ���� ���� ����鿡�� �����ϰ� ���Ǳ⸦ ���Ѵٸ� ��
    ���α׷��� �� ���̼����� ������ ���� �����Ӱ� �����ǰ� ������ �� �ֵ��� ����
    ����Ʈ����� ����� ���� �ּ��� ����̴�.
    <P>
    ������ ���� ���׵��� ���α׷��� ÷�������ν� �ش� ���α׷��� ���� ����Ʈ�����
    ���� �� �ִ�. ���α׷��� ���� ������ �������� �ʴ´ٴ� ����� ���� ȿ��������
    ������ �� �ִ� ����� �ҽ� �ڵ尡 ���ԵǾ� �ִ� ��� ������ ���� �κп� �̷���
    ���׵��� ����ϴ� ���̴�. ������ ���ϵ��� �ּ��� ���۱ǰ� GPL�� ����� �� �ִ�
    ����� ����ؾ߸� �Ѵ�.

    <PRE>
    <var>
    ���α׷��� �̸��� �뵵�� ���� ������ ���ؼ� �� ���� ����Ѵ�.
    </var>
    Copyright (C) 19<var>yy</var>  <var>���α׷� �������� �̸�</var>
    �� ���α׷��� ���� ����Ʈ�����̴�. ����Ʈ������ �Ǿ絵�ڴ�
    ���� ����Ʈ����  ����� GNU General Public License�� ������
    ���ؼ� �� ���α׷��� ���۵� 2���� ���α׷��� �Բ� �Ǵ� ����������
    ������ �� �ִ�.
    �� ���α׷��� ���� �����ϰ� ���� �� ������� �������
    �����ǰ� ������ ��ǰ�� ���� ��� ������ ������ ���� �ʴ´�.
    ���� �ڼ��� ���׿� ���ؼ��� GNU General Public  License��
    �����ϱ� �ٶ���.
    GNU General Public License�� �� ���α׷��� �Բ� �����ȴ�.
    ����, �� ������ �����Ǿ� �ִٸ� ���� ����Ʈ���� ��ܿ� �����ϱ�
    �ٶ���(���� ����Ʈ���� ���: Free  Software Foundation, Inc.,
    59 Temple Place - Suite 330, Boston, MA 02111-1307, USA)
    </PRE>

    ����, ���α׷� �����ڿ� ���� �Ǵ� ���� ������ ���ؼ� ������ �� �ִ� ������
    �����ؾ� �Ѵ�.
    <P>
    ����, �� ���α׷��� ��ɾ� �Է� ��Ŀ� ���� ��ȭ�� ������ ���ϰ� �ִٸ�
    ���α׷��� ��ȭ�� ������� ����Ǵ� �ʱ� ���¿��� ������ ���� ���� ������
    ��½��Ѿ� �Ѵ�.

    <Pre>
    Gnomovision version 69, Copyright (C) 19<var>yy���α׷� �������� �̸�</var>
    Gnomovision�� ��ǰ�� ���� ��� ������ ������ �������� �ʴ´�.
    ���� �ڼ��� ������ 'show w' ��ɾ �̿��ؼ� ���õ� ������
    ����� ���� �ٶ���. �� ���α׷��� ���� ����Ʈ�����̸� Ư�� ��������
    ������Ű�� �����Ͽ��� ������� �� �ִ�. ������ ���� �ش� ������
    'show c' ��ɾ ���ؼ� ������ �� �ִ�.
    </PRE>

    <P>
    <samp>'show w'</samp>�� <samp>'show c'</samp>�� General Public License�� �ش� �κ��� �����ϱ� ���� ������
    ��ɾ��̴�. ����, �� ��ɾ���� ���콺�� �̿��ϰų� �޴� ����� �����ϴ� ����
    ���α׷��� ������ ���� ���� �������� ������ �� ���� ���̴�.
    <P>
    ����, ���α׷� �����ڰ� �б��� ����� ���� ��ü�� ����� ���Ǿ� �ִٸ�
    ���α׷��� �����ο� ������ ���ؼ� ����ֳ� �ش� ��������� ���� ���α׷���
    ���� ���۱��� �����Ѵٴ� ���Ǹ� ���� �Ѵ�. ���� ���, ������ ���� ������ �� ��
    �ִ�.

    <PRE>
    ����� James Hacker�� ���ؼ� �ۼ���
    'Gnomovision' ���α׷��� �����
    ��� ���۱��� �����Ѵ�.
    1989�� 4�� 1��
    Yoyodye, Inc., �λ���: Ty Coon
    ����: <var> Ty Coon�� ����</var>
    </PRE>

    <P>
    �� ���̼����� ���� ����Ʈ����� ������ ���α׷��� ���� ����Ʈ����� �Բ�
    ����ϴ� ���� ������� �ʴ´�. ����, �ۼ��� ���α׷��� ���̺귯�� �����ƾ��
    ���� ���α׷��� ��쿡�� �̸� ���� ����Ʈ���� ������ ���� ���α׷��� �Բ�
    ��������ν� ���� ȿ�������� Ȱ��� �� �ִٰ� ������ ���� ���� ���̴�. �̷���
    ���� �� ���̼��� ��ſ� GNU Library General Public License�� ��������ν� �ұ���
    ������ ������ų �� ���� ���̴�."));
}
void
UzooConfigImpl::saveFileInfo()
{
	info.biggestClient	= myserver1SpinBox->text().toShort();
	info.biggestEvery 	= myserver2SpinBox->text().toShort();
	info.userPort		= userportSpinBox->text().toShort();
	info.biggestSearch	= searchSpinBox->text().toShort();
	
	info.uploadPath = "";
	for(int i=0 ; i <(int)upFolderComboBox->count() ; i++){
		info.uploadPath.append( upFolderComboBox->text(i)+QString("\n")) ;
	}
	info.downloadPath	= downFolderLineEdit->text();
	info.defaultPlayerPath= playerLineEdit->text();
	if (startPlayerCheckBox->isChecked() == true)
		info.playerEnable = "true";
	else if (startPlayerCheckBox->isChecked() == false)
		info.playerEnable = "false";
	info.playerStartTime= laterPlayerSpinBox->text().toShort();
	
	info.userid = useridLineEdit->text();
	info.passwd = passwdLineEdit->text();
	if ( autoLoginCheckBox->isChecked() == true)
	{
		info.autoLogin = "true";
	}else
	{
		info.autoLogin = "false";
	}
	info.version		= versionLineEdit->text();

	// ������ ���� �����Ѵ�.
	QFile infoFile(kor( QDir::homeDirPath() + "/.uzoo-qt" ));
	infoFile.remove();
	if(infoFile.open(IO_WriteOnly))
	{
		QTextStream ts(&infoFile);
		ts << infoString[0] << QString::number(info.biggestClient) << "\n";
		ts << infoString[1] << QString::number(info.biggestEvery) << "\n";
		ts << infoString[2] << QString::number(info.userPort) << "\n";
		ts << infoString[3] << QString::number(info.biggestSearch) << "\n";
		ts << infoString[4] << info.uploadPath << "\n";
		ts << infoString[5] << info.downloadPath << "\n";
		ts << infoString[6] << info.defaultPlayerPath << "\n";
		ts << infoString[7] << info.playerEnable << "\n";
		ts << infoString[8] << QString::number(info.playerStartTime)<<"\n";
		ts << infoString[9] << info.userid << "\n";
		ts << infoString[10] << info.passwd << "\n";
		ts << infoString[11] << info.autoLogin << "\n";
		ts << infoString[12] << info.version  <<"\n";
	}
	infoFile.close();

	emit sendInfo( info );
}
void
UzooConfigImpl::updateDialog()
{
	// ���������� Dialog�� �ø���.
	myserver1SpinBox->setValue( info.biggestClient);
	myserver2SpinBox->setValue( info.biggestEvery);
	userportSpinBox->setValue( info.userPort);
	searchSpinBox->setValue(info.biggestSearch);
	//upLoadPath
	downFolderLineEdit->setText(kor(info.downloadPath) );
	playerLineEdit->setText(kor( info.defaultPlayerPath) );

	if (info.playerEnable.lower() == "true")
		startPlayerCheckBox->setChecked(true);
	else if (info.playerEnable.lower() == "false")
		startPlayerCheckBox->setChecked(false);
	
	laterPlayerSpinBox->setValue(info.playerStartTime);
	useridLineEdit->setText(kor(info.userid));
	passwdLineEdit->setText(kor(info.passwd));

	if (info.autoLogin.lower() == "true")
		autoLoginCheckBox->setChecked(true);	
	else if (info.autoLogin.lower() == "false")
		autoLoginCheckBox->setChecked(false);

	versionLineEdit->setText(info.version);
}
/*
 * �������Ͽ��� ������ �����´�. ���ٸ� �⺻������ �־��ش�.
 * ���� GUI�� �� ������ ������Ʈ�Ѵ�.
 */
void
UzooConfigImpl::loadFileInfo()
{
	// ������ ���� ������ ���� �پ��� ����Ÿ�� ������ �Ѵ�.
	// ������ ��ҿ� ���������� ����, ������ �д´�.
	// ���� ���ٸ� ������~~
	QFile infoFile(kor( QDir::homeDirPath() + "/.uzoo-qt" ));
	if( !infoFile.exists()) // �������� �ʴ´ٸ�
	{	// default�� ���������� �����Ѵ�.
		if(infoFile.open(IO_WriteOnly))
		{
			QTextStream ts(&infoFile);
			ts << infoString[0] << kor("1") << "\n";
			ts << infoString[1] << kor("3") << "\n";
			ts << infoString[2] << kor("9001") << "\n";
			ts << infoString[3] << kor("500") << "\n";
			ts << infoString[4] << "\n";
			ts << infoString[5] << QDir::homeDirPath()<<"\n";
			ts << infoString[6] << kor("xmms") << "\n";
			ts << infoString[7] << kor("true") << "\n";
			ts << infoString[8] << kor("5") << "\n";
			ts << infoString[9] << "\n";
			ts << infoString[10] << "\n";
			ts << infoString[11] << kor("false") <<"\n";
			ts << infoString[12] << kor("1.94") << "\n";
		}
		infoFile.close();
	}
	// ���Ͽ��� ������ �ҷ��´�.
	if(infoFile.open(IO_ReadOnly))
	{
		QTextStream ts(&infoFile);
		int infoSize = 13;
		for(int i=0 ; i < infoSize ; i++)
		{
			QString line = ts.readLine().local8Bit();
			//cout << line.latin1() << endl;
			int findIndex = line.find(":") + 1;
			int findLen = line.length() - findIndex;
			if 
			(qstrcmp(line.left(infoString[0].local8Bit().length()).latin1()
				, infoString[0].local8Bit().data()) == 0)
			{
				info.biggestClient = line.right(findLen).toShort(); 
			}
			else if 
			(qstrcmp(line.left(infoString[1].local8Bit().length()).latin1()
				, infoString[1].local8Bit().data()) == 0)
			{
				info.biggestEvery = line.right(findLen).toShort();
			}
			else if 
			(qstrcmp(line.left(infoString[2].local8Bit().length()).latin1()
				, infoString[2].local8Bit().data()) == 0)
			{
				info.userPort = line.right(findLen).toShort();
			}
			else if 
			(qstrcmp(line.left(infoString[3].local8Bit().length()).latin1()
				, infoString[3].local8Bit().data()) == 0)
			{
				info.biggestSearch = line.right(findLen).toShort();
			}
			else if 
			(qstrcmp(line.left(infoString[4].local8Bit().length()).latin1()
				, infoString[4].local8Bit().data()) == 0)
			{
				info.uploadPath = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[5].local8Bit().length()).latin1()
				, infoString[5].local8Bit().data()) == 0)
			{
				info.downloadPath = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[6].local8Bit().length()).latin1()
				, infoString[6].local8Bit().data()) == 0)
			{
				info.defaultPlayerPath = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[7].local8Bit().length()).latin1()
				, infoString[7].local8Bit().data()) == 0)
			{
				info.playerEnable = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[8].local8Bit().length()).latin1()
				, infoString[8].local8Bit().data()) == 0)
			{
				info.playerStartTime = line.right(findLen).toShort();
			}
			else if
			(qstrcmp(line.left(infoString[9].local8Bit().length()).latin1()
					,infoString[9].local8Bit().data()) == 0)
			{
				info.userid = line.right(findLen);	
			}
			else if
			(qstrcmp(line.left(infoString[10].local8Bit().length()).latin1()
					,infoString[10].local8Bit().data()) == 0)
			{
				info.passwd = line.right(findLen);
			}
			else if
			(qstrcmp(line.left(infoString[11].local8Bit().length()).latin1()
					,infoString[11].local8Bit().data()) == 0)
			{
				info.autoLogin = line.right(findLen);
			}
			else if
			(qstrcmp(line.left(infoString[12].local8Bit().length()).latin1()
					,infoString[12].local8Bit().data()) == 0)
			{
				info.version = line.right(findLen);
			}
		}
	}
	infoFile.close();
}
/*
 * slot
 */
void
UzooConfigImpl::slotApply()
{
	saveFileInfo();
}
void
UzooConfigImpl::slotOk()
{
	saveFileInfo();
	this->hide();
}
void
UzooConfigImpl::slotCancel()
{
	this->hide();
}
void
UzooConfigImpl::slotVersionEdited(bool b)
{
	versionLineEdit->setEnabled(b);
}
void
UzooConfigImpl::slotHelpBrowser()
{
	int value = system("konqueror http://sonegy.home.uos.ac.kr/soriuzoo&");
	cout << "Return browser:"<< value << endl;
}
void
UzooConfigImpl::slotFindPlayer()
{
}
void
UzooConfigImpl::slotDownLoadFolder()
{
}


