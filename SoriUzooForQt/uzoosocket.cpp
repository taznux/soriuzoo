#include "uzoosocket.h"
#include <iostream.h>
#include <qcstring.h>
#include <qtimer.h>

#define kor(x) QString::fromLocal8Bit(x)
UzooSocket::UzooSocket(const QString &path , const QString &id ,
	QObject *parent ,const char*name) : QSocket(parent,name)
{
	connect(this,SIGNAL(connected()),this,SLOT(slotSend()));
	connect(this,SIGNAL(readyRead()),this,SLOT(slotRecvData()));
	connect(this,SIGNAL(connectionClosed()),this,SLOT(slotConnectionClosed()));
	connect(this,SIGNAL(delayedCloseFinished()),
			this,SLOT(slotDelayedCloseFinished()));
	connect(this,SIGNAL(error(int)),this,SLOT(slotError(int)));

	this->path = path;
	this->id = id;
	nowSize = 0;
	int index= path.findRev("\\");
	int len = path.length();
	canIdownload = false;
	downloadfile.setName(kor((path.right(len- index -1)) ));
	mp3data.setDevice( &downloadfile);
	
}
UzooSocket::~UzooSocket()
{
	close();
	//cout << "Destroctor!!\n";
}
void
UzooSocket::connectTo(QString &address, int port)
{
	connectToHost( address, port );
}
void
UzooSocket::setTotalFileSize(long totalsize)
{
	totalFileSize = totalsize;
}
void
UzooSocket::setListIndex(int index)
{
	listIndex = index;
}
void
UzooSocket::slotSend()
{
	QString senddata;
	senddata.append("GETMP3\r\nFilename: ");
	senddata.append(path);
	senddata.append("\r\nPosition: 0\r\nPortM: 9999\r\nUsername: ");
	senddata.append(id);
	senddata.append("\r\n\r\n");
	//cout << "Final : " << senddata.latin1() << endl;
	writeBlock( senddata.latin1() , senddata.length() );
}
void
UzooSocket::slotRecvData()
{
	// 처음 스트링에 Succeded가 있으면 파일 존재 확인
	int bytes = bytesAvailable();
	char *string = new char[bytes];
	//this->flush();

	readBlock( string , bytes );
	if ( canIdownload == false && QString(string).find("Succeded") >= 0)
	{
		if (downloadfile.exists() == true)
		{
			emit sendMessage("Exist File");
			this->close();
		}
		canIdownload = true;	
		canIdownload =  downloadfile.open(IO_WriteOnly | IO_Append); 

		emit sendMessage("Start DownLoad");

		QTimer *timer = new QTimer(this);
		connect(timer,SIGNAL(timeout()),this,SLOT(slotInspect()));
		timer->start(3000); // 3초간격으로 데이타가 없으면 종료한다.
		return;
	}
	else if(canIdownload == false && QString(string).find("User Limit"))
	{
		emit sendMessage("User Limit");
		this->close();
	}
	else if(canIdownload == false && QString(string).find("File Not Found"))
	{
		emit sendMessage("File Not Found");
		this->close();
	}
	else if(canIdownload == false && QString(string).find("Invalid Command"))
	{
		emit sendMessage("Invalid Command");
		this->close();
	}
	if (canIdownload == true)
	{
		mp3data.writeRawBytes( string , bytes );
		nowSize = nowSize + bytes;
		emit sendFileSize( listIndex , nowSize );
		canIdownload = true;
		if ( nowSize >=  totalFileSize ) // 다 받았다면
		{
			emit sendMessage("Finished download");
			// 소켓을 종료해야한다.
			this->close();
		}
	}
}
void
UzooSocket::slotConnectionClosed()
{
	emit sendMessage("ConnectionClosed");
}
void
UzooSocket::slotDelayedCloseFinished()
{
	emit sendMessage("DelayedCloseFinished");
}
void
UzooSocket::slotError(int num)
{	
	num =0;
	emit sendMessage("Socket Error");
}
void
UzooSocket::slotInspect()
{
}
