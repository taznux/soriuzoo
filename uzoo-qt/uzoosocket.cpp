#include "uzoosocket.h"

#include <iostream.h>
#include <qcstring.h>
#include <qtimer.h>
#include <qdir.h>
#include <qhostaddress.h>

#define kor(x) QString::fromLocal8Bit(x)
UzooSocket::UzooSocket(QObject *parent ,const char*name, ResultSearch &rs,
	int listIndex , const QString &myid ) : QSocket(parent,name)
{
	connect(this,SIGNAL(connected()),this,SLOT(slotSend()));
	connect(this,SIGNAL(readyRead()),this,SLOT(slotRecvData()));
	connect(this,SIGNAL(connectionClosed()),this,SLOT(slotConnectionClosed()));
	connect(this,SIGNAL(delayedCloseFinished()),
			this,SLOT(slotDelayedCloseFinished()));
	connect(this,SIGNAL(error(int)),this,SLOT(slotError(int)));
	
	setListIndex(listIndex); // ���߿� ���� ����Ʈ�ε��� ��ȣ
	this->rs = rs;	// �ּ�,��Ʈ,���̵�,�н�,���ϻ���� ����
	this->myid = myid;
	nowSize = 0;	// ���� �ٿ�ε�� ������
	canIdownload = false;
	setDownLoadPath(".");

	// �����Ѵ�.
	this->connectToHost( rs.address , rs.port );
}
UzooSocket::~UzooSocket()
{
	close();
}
void
UzooSocket::setListIndex(int index)
{
	listIndex = index;
}
void	// �̰� �����ڿ� ���Խ�Ű�� �ʴ´�.
UzooSocket::setDownLoadPath(const QString &str_)
{
	QString str = str_;
	if(QFile(str).exists() != true)
	{
		// ��ΰ� �������� ������ �ڽ��� ������ ��´�.
		str = QDir::homeDirPath();	
	}
	int index= rs.path.findRev("\\");
	int len = rs.path.length();
	downloadfile.setName(kor(str + "/" + rs.path.right(len- index -1)) );
	mp3data.setDevice(&downloadfile);
}
void
UzooSocket::slotSend()
{
	QString senddata;
	senddata.append("GETMP3\r\nFilename: ");
	senddata.append(rs.path);
	senddata.append("\r\nPosition: 0\r\nPortM: 9999\r\nUsername: ");
	senddata.append(myid);
	senddata.append("\r\n\r\n");
	writeBlock( senddata.latin1() , senddata.length() );
}
void
UzooSocket::slotRecvData()
{
	// ó�� ��Ʈ���� Succeded�� ������ ���� ���� Ȯ��
	int bytes = bytesAvailable();
	char *string = new char[bytes];
	this->flush();

	readBlock( string , bytes );
	if ( canIdownload == false && QString(string).find("Succeded") >= 0)
	{
		if (downloadfile.exists() == true)
		{
			emit sendState(listIndex,9);
			this->close();
		}
		canIdownload = true;	
		canIdownload =  downloadfile.open(IO_WriteOnly | IO_Append); 
		
		emit start(this);
		emit sendState(listIndex , 1);

		QTimer *timer = new QTimer(this);
		connect(timer,SIGNAL(timeout()),this,SLOT(slotInspect()));
		timer->start(3000); // 3�ʰ������� ����Ÿ�� ������ �����Ѵ�.
		return;
	}
	else if(canIdownload == false && QString(string).find("User Limit"))
	{
		emit sendState(listIndex, 6);
		this->close();
	}
	else if(canIdownload == false && QString(string).find("File Not Found"))
	{
		emit sendState(listIndex, 7);
		this->close();
	}
	else if(canIdownload == false && QString(string).find("Invalid Command"))
	{
		emit sendState(listIndex,8);
		this->close();
	}
	if (canIdownload == true)
	{
		mp3data.writeRawBytes( string , bytes );
		nowSize = nowSize + bytes;
		emit sendFileSize( listIndex , nowSize );
		emit sendState(listIndex , 2);
		canIdownload = true;
		if ( nowSize >=  rs.filesize ) // �� �޾Ҵٸ�
		{
			emit sendState(listIndex,3);
			emit end(this);
			// ������ �����ؾ��Ѵ�.
			this->close();
		}
	}
}
void
UzooSocket::slotConnectionClosed()
{
	emit sendState(listIndex, 10 );
}
void
UzooSocket::slotDelayedCloseFinished()
{
	emit sendState(listIndex, 11);
}
void
UzooSocket::slotError(int num)
{	
	num =0;
	emit sendState(listIndex , 5);
}
void
UzooSocket::slotInspect()
{
}
