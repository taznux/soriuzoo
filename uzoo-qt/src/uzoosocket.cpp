#include "uzoosocket.h"
#include "uzooparser.h"	// <-- ResultSearch

#include <iostream.h>
#include <qcstring.h>
#include <qtimer.h>
#include <qdir.h>
#include <qhostaddress.h>

#define kor(x) QString::fromLocal8Bit(x)
UzooSocket::UzooSocket(QObject *parent ,const char*name, ResultSearch &rs,
						const QString &myid ) : QSocket(parent,name)
{
	connect(this,SIGNAL(connected()),this,SLOT(slotSend()));
	connect(this,SIGNAL(readyRead()),this,SLOT(slotRecvData()));
	connect(this,SIGNAL(connectionClosed()),this,SLOT(slotConnectionClosed()));
	connect(this,SIGNAL(delayedCloseFinished()),
			this,SLOT(slotDelayedCloseFinished()));
	connect(this,SIGNAL(error(int)),this,SLOT(slotError(int)));
	
	this->rs_p = &rs;		// �ּ�,��Ʈ,���̵�,�н�,���ϻ���� ����
	this->myid = myid;
	nowSize = 0;	// ���� �ٿ�ε�� ������
	canIdownload = false;
	setDownLoadPath(".");
	// Client�� TCP�� �����Ѵ�.
	this->connectToHost( rs_p->address , rs_p->port );

	isFirst = true; // Downloding Message
}
UzooSocket::~UzooSocket()
{
	close();
}
void	
UzooSocket::setDownLoadPath(const QString &str_)
{
	QString str = str_;
	if(QFile(str).exists() != true)
	{
		// ��ΰ� �������� ������ �ڽ��� ������ ��´�.
		str = QDir::homeDirPath();	
	}
	downloadfile.setName(kor(str + "/" + rs_p->filename ) );
	rs_p->downpath = downloadfile.name();
	mp3data.setDevice(&downloadfile);
}
void
UzooSocket::slotSend()
{
	QString senddata;
	senddata.append("GETMP3\r\nFilename: ");
	senddata.append(rs_p->path);
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
			// ������ �̹� �����Ѵٸ�
			rs_p->state = FILE_EXIST;
			emit state(*rs_p);
			emit sendMessage("File Exist",2000);
			this->close();
			return;
		}
		canIdownload = true;	
		canIdownload =  downloadfile.open(IO_WriteOnly | IO_Append); 
		
		rs_p->state = START;
		emit start(*rs_p);
		emit state(*rs_p);
		emit sendMessage("DownLoad Start",2000);

		/*QTimer *timer = new QTimer(this);
		connect(timer,SIGNAL(timeout()),this,SLOT(slotInspect()));
		timer->start(3000); // 3�ʰ������� ����Ÿ�� ������ �����Ѵ�.*/
		return;
	}
	else if(canIdownload == false && QString(string).find("User Limit"))
	{
		rs_p->state = USER_LIMIT;
		emit state(*rs_p);
		emit sendMessage("User Limit",2000);
		this->close();
	}
	else if(canIdownload == false && QString(string).find("File Not Found"))
	{
		rs_p->state = FILE_NOT_FOUND;
		emit state(*rs_p);
		emit sendMessage("File Not Found",2000);
		this->close();
	}
	else if(canIdownload == false && QString(string).find("Invalid Command"))
	{
		rs_p->state = INVALID_COMMAND;
		emit state(*rs_p);
		emit sendMessage("Invalid Command",2000);
		this->close();
	}
	if (canIdownload == true)
	{
		mp3data.writeRawBytes( string , bytes );
		nowSize = nowSize + bytes;
		rs_p->downsize = nowSize;
		rs_p->state = DOWNLOADING;
		if ( isFirst == true )
		{
			emit state(*rs_p);
			isFirst = false;
		}

		canIdownload = true;
		if ( nowSize >=  rs_p->filesize ) // �� �޾Ҵٸ�
		{
			rs_p->state = FINISHED;
			emit end(*rs_p);
			emit state(*rs_p);
			emit sendMessage("Finished",2000);
			this->close();
		}
	}
}
void
UzooSocket::slotConnectionClosed()
{
	rs_p->state = CONNECTION_CLOSED;
	emit state(*rs_p);
}
void
UzooSocket::slotDelayedCloseFinished()
{
	rs_p->state = DELAYED_CLOSE_FINISHED;
	emit state(*rs_p);
}
void
UzooSocket::slotError(int num)
{	
	num =0;	
	rs_p->state = ERROR;
	emit state(*rs_p);
}
void
UzooSocket::slotInspect()
{
}
