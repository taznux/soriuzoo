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
	
	setListIndex(listIndex); // 나중에 보낼 리스트인덱스 번호
	this->rs = rs;	// 주소,포트,아이디,패스,파일사이즈를 쓴다
	this->myid = myid;
	nowSize = 0;	// 현재 다운로드된 사이즈
	canIdownload = false;
	setDownLoadPath(".");

	// 연결한다.
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
void	// 이건 생성자에 포함시키지 않는다.
UzooSocket::setDownLoadPath(const QString &str_)
{
	QString str = str_;
	if(QFile(str).exists() != true)
	{
		// 경로가 존재하지 않으면 자신의 계정에 담는다.
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
	// 처음 스트링에 Succeded가 있으면 파일 존재 확인
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
		timer->start(3000); // 3초간격으로 데이타가 없으면 종료한다.
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
		if ( nowSize >=  rs.filesize ) // 다 받았다면
		{
			emit sendState(listIndex,3);
			emit end(this);
			// 소켓을 종료해야한다.
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
