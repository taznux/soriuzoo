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
}
UzooConfigImpl::~UzooConfigImpl()
{
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
			ts << infoString[7] << kor("false") << "\n";
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
UzooConfigImpl::slotFindPlayer()
{
}
void
UzooConfigImpl::slotDownLoadFolder()
{
}


