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
	
	this->rs_p = &rs;		// 주소,포트,아이디,패스,파일사이즈를 쓴다
	this->myid = myid;
	nowSize = 0;	// 현재 다운로드된 사이즈
	canIdownload = false;
	setDownLoadPath(".");
	// Client에 TCP로 연결한다.
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
		// 경로가 존재하지 않으면 자신의 계정에 담는다.
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
	// 처음 스트링에 Succeded가 있으면 파일 존재 확인
	int bytes = bytesAvailable();
	char *string = new char[bytes];
	this->flush();

	readBlock( string , bytes );
	if ( canIdownload == false && QString(string).find("Succeded") >= 0)
	{
		if (downloadfile.exists() == true)
		{
			// 파일이 이미 존재한다면
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
		timer->start(3000); // 3초간격으로 데이타가 없으면 종료한다.*/
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
		if ( nowSize >=  rs_p->filesize ) // 다 받았다면
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
