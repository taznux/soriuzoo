#include "uzooparser.h"
#include <qurloperator.h>
#include <qhostaddress.h>
#include <qsocketnotifier.h>
#include <qnetworkprotocol.h>
#include <qstring.h>
#include <qtimer.h>
#include <qregexp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
//#undef DEBUG_UZOO
/****************************************************************************
 * Constructor and destructor and init Function, and private function
 ***************************************************************************/
UzooParser::UzooParser(QObject *parent , const char*name)
	: QObject(parent,name)
{
	initLookUpTable();
	clientsInfo = new QArray<AsrArray>(7500);
	recvMaxNum = 500;
	myPort = 9001;

//	/* Timer를 호출하여 시간간격을 두고 클라이언트들에게 메세지를 보낸다.*/
	timer = new QTimer(this);
	connect (timer, SIGNAL(timeout()), this, SLOT(slotSendMessageToClients()));

	sockfd = ::socket(AF_INET ,SOCK_DGRAM , 0);
	socketDevice = new QSocketDevice(sockfd,QSocketDevice::Datagram);
	QSocketNotifier *read = new QSocketNotifier(sockfd , QSocketNotifier::Read);
	connect(read,SIGNAL(activated(int)),
		this,SLOT(slotRecvMessageFromClients()));
}
UzooParser::~UzooParser()
{
	close(sockfd);
}
void
UzooParser::startParser(const QString &asrurl , const QString &myip , 
	const QString &searchstring)
{
	clientsInfoIndex = 0;
	sendCounter = 0;
	recvCounter = 0;

	emit sendMessage("Start Parser",2000);
	initAsrUrl(asrurl);
	initSearchString(searchstring); // 이게 먼저 와야 한다.
	initMyIP(myip);					// 이거 보다.
}
void
UzooParser::initAsrUrl(const QString &asrurl)
{
	QUrlOperator *asr = new QUrlOperator(asrurl);
	connect( asr , SIGNAL(data(const QByteArray& , QNetworkOperation*)),
		this ,SLOT(slotRecvAsrProtocolMessage(const QByteArray&)));
	connect( asr , SIGNAL( finished(QNetworkOperation*)),
		this , SLOT(slotFinished()));
	asr->get();
}
void
UzooParser::initMyIP(const QString &myip)
{
	uchar b1;
	uchar b2;
	uchar ip1;
	uchar ip2;
	uchar ip3;
	uchar ip4;
	
		/* 헉~ 단방에 인코딩을~ */
	transrate_encoding(myPort, myip , b1 ,b2 , ip1, ip2, ip3, ip4);

	/* message에 자신의 주소를 적어준다. 물론 encoding이 필요하지*/
	message.send_data[0] = 0x01;
	message.send_data[1] = b1; //포트 변환
	message.send_data[2] = b2; //magic number;
	message.send_data[3] = ip1;
	message.send_data[4] = ip2;
	message.send_data[5] = ip3;
	message.send_data[6] = ip4;
	// left data[7] , [8] 
	message.send_data[9] = 0x51;
	message.send_data[10]= 0x3a;
	//cout << "ENDINITMYIP\n";
}
void
UzooParser::initSearchString(const QString &searchstring_)
{
	QString searchString("+");
	searchString.append( searchstring_.local8Bit().simplifyWhiteSpace() );
	searchString.replace( QRegExp(" ") , "\n+" );
	searchString.append("\n");

	/* 보낼 전체 길이를 정할수 있다. */
	message.send_data = new uchar[11 + searchString.length() ];
	message.send_len = 11+ searchString.length();
	memcpy(&(message.send_data[11]) , 
		searchString.latin1() , sizeof(uchar)*(searchString.length()));
	/* 이제 남은건 counter뿐이다!!! 실제적으로 메시지를 보낼때 정한다.*/
}
void
UzooParser::initLookUpTable()
{
/*	for(int i=0 ; i <= 255 ; i++)
	{
        for(int k=0 ; k <= 255 ; k++)
        {
            if ( (k^1 + 164)%256 == i)
            {
                lookUpTable[i] = k;
				cout << k << "," ;
                break;
            }
        }
    }*/
	uchar lookUpTable_copy[] = {
		165,164,167,166,161,160,163,162,173,172,175,174,169,168,171,170,
		181,180,183,182,177,176,179,178,189,188,191,190,185,184,187,186,
		133,132,135,134,129,128,131,130,141,140,143,142,137,136,139,138,
		149,148,151,150,145,144,147,146,157,156,159,158,153,152,155,154,
		229,228,231,230,225,224,227,226,237,236,239,238,233,232,235,234,
		245,244,247,246,241,240,243,242,253,252,255,254,249,248,251,250,
		197,196,199,198,193,192,195,194,205,204,207,206,201,200,203,202,
		213,212,215,214,209,208,211,210,221,220,223,222,217,216,219,218,
		37,36,39,38,33,32,35,34,45,44,47,46,41,40,43,42,53,52,55,54,49,
		48,51,50,61,60,63,62,57,56,59,58,5,4,7,6,1,0,3,2,13,12,15,14,9,
		8,11,10,21,20,23,22,17,16,19,18,29,28,31,30,25,24,27,26,101,100,
		103,102,97,96,99,98,109,108,111,110,105,104,107,106,117,116,119,
		118,113,112,115,114,125,124,127,126,121,120,123,122,69,68,71,70,
		65,64,67,66,77,76,79,78,73,72,75,74,85,84,87,86,81,80,83,82,93,
		92,95,94,89,88,91,90 };
	for(int i=0 ; i < 256 ; i++)
	{
		lookUpTable[i] = lookUpTable_copy[i];
	}
}
uchar
UzooParser::decoding(int magic , uchar data)
{
	uchar result;
    switch(magic)
    {
        case(1)://01
            result = data^0xa5;
            break;
        case(2)://10
            result = data^0xc3;
            break;
        case(3)://11
            result = data^0x77; 
            break;
        default:
            cerr << "Error missing decoding value\n";
            return 0;
    }
    return result;
}
void
UzooParser::send()
{
	timer->stop();
	timer->start(1, false); // 0.001초 간격으로 계속 호출한다.
}
/* 메세지를 받으면 당연히 분석을 해야지 */
void
UzooParser::transrate_decoding(uchar b1 , uchar b2 , uchar ip1, uchar ip2,
	uchar ip3 , uchar ip4 , 
	int &_port , uchar &_ip1 , uchar &_ip2 ,uchar &_ip3 , uchar &_ip4)
{
	_port = b1 + ((b2&3)<<8) + 9000;
	uchar magic   = (b2&12)>>2;   /* 00001100 = 12  */
	uchar undecode= (b2&240)>>4;  /* 11110000 = 240 */

	/* 1000 = 8
	 * 0100 = 4
	 * 0010 = 2
	 * 0001 = 1
	 */
		/* 물론 undecode가 0이면 당연히 모두 디코딩 처리한다. */
	if ( (undecode&8) == 0) /* 뒤에서 첫번째 ip1 디코딩을 해야한다.*/
	{
		ip4 = decoding(magic , ip4 );
	}	/* 물론 예외적으로 어떠한 값이 존재하면 디코딩 예외를 한다.*/
	if ( (undecode&4) == 0) /* 뒤에서 두번째 ip2  "" */
	{
		ip3 = decoding(magic , ip3 );
	}
	if ( (undecode&2) == 0) /* 뒤에서 세번째 ip3  "" */
	{
		ip2 = decoding(magic , ip2 );
	}
	if ( (undecode&1) == 0) /* 뒤에서 네번째 ip4  "" */
	{
		ip1 = decoding(magic , ip1 );
	}
	
	/* ip배열을 재정리 한다. */
	_ip1 = ip2;
	_ip2 = ip4;
	_ip3 = ip3;
	_ip4 = ip1;
}
/* 메세지를 보낼라면 당연히 암호화 시켜야지 */
void
UzooParser::transrate_encoding(int port , QString address ,
	uchar &b1, uchar &b2, uchar &ip1, uchar &ip2 ,uchar &ip3 ,uchar &ip4)
{
	// b2는 당연히 4이고, 포트는 왠만해서.....9255를 넘지 않으면 좋겠다.
	b1 = ( (port-9000)&255); 		// 255 = 11111111
	b2 = ( (port-9000)&768 )>>8;
	b2 = b2+ 4;	// 768 = 1100000000 , 4 = 00000100
    address.append(".");

	int fIndex = 0;
    uchar tempMyIP[4];
    for(int i=0 ; i < 4 ; i++)
    {
        int nIndex;
        bool ok;
        nIndex = address.find(".", fIndex);
        tempMyIP[i] =
            (uchar) (address.mid(fIndex, nIndex - fIndex )).toInt(&ok,10);
        fIndex = nIndex+1;
        if (ok == false)
        {
            cerr << "Error Dont have strange number\n";
            return;
        }
    }
	ip1 = encoding(tempMyIP[3]);
	ip2 = encoding(tempMyIP[0]);
	ip3 = encoding(tempMyIP[2]);
	ip4 = encoding(tempMyIP[1]);
}
/* encoding in Header */
/****************************************************************************
 * END  Constructor and destructor and init Function 
 ***************************************************************************/

/*
 * Asr파싱을 위한 슬롯함수들 
 *
 */
void
UzooParser::slotRecvAsrProtocolMessage(const QByteArray &byte)
{
	if (clientsInfoIndex == 0 ) emit startAsrParser();

	int byteLen = byte.size();
	QArray<uchar> byteUchar( byteLen );
	// 만약 처음의 필요없는 바이트는 제외시킨다.
/*	QString except("Version : 1.0");
	int 	exceptLen = except.length();
	if ( QString( byte.data()).left(exceptLen) == except )
	{
		//cout << "FirstAsrString \n";
		byteUchar.resize( byteLen - exceptLen );
		for(int i=0 ; i<(int)byteLen -exceptLen ; i++)
		{
			byteUchar[i] = (uchar)byte[i+exceptLen];
		}
	}
	else
	{*/
		for(int i=0 ; i <(int)byteLen ; i++)
		{
			byteUchar[i] = (uchar)byte[i];
		}
/*	}*/
	/* 이제부터 byteUchar 배열을 사용하고, 이제 저장고에 저장한다.*/
	/* 처음 시작 바이트를 찾는다. 1을 6바이트 간격으로 있을때 그전 6바이트
	 * 씩 검색하여 처음 부분을 찾는다. */
	int i=0;
	int guessIndex=0;
	int firstIndex=0;
	while(1)
	{
		if (byteUchar[i]   == 0x01 && 
			byteUchar[i+6] == 0x01)// &&
	//		byteUchar[i+12]== 0x01)
		{
			guessIndex = i;
			break;
		}
		i++;
	}
	firstIndex = guessIndex;
	/* 이제 처음이 될 인덱스도 구했다. firstIndex */
	/* 그리고 대상이 되는 바이트는 byteUchar 이다 */
	for(int i= firstIndex ; i < (int)byteUchar.size() ;/**/ )
	{
		if (i+5 >= (int) byteUchar.size() ) break;
		uchar b1 = (uchar)byteUchar[i+0];
		uchar b2 = (uchar)byteUchar[i+1];
		uchar ip1= (uchar)byteUchar[i+2];
		uchar ip2= (uchar)byteUchar[i+3];
		uchar ip3= (uchar)byteUchar[i+4];
		uchar ip4= (uchar)byteUchar[i+5];
		//cout << (int) b1 << " " << (int)b2 << " " << endl;
		//cout << (int) ip1 << " " <<(int)ip2<<" "<<(int)ip3<<" "<<(int)ip4<<endl;

			/* 앗싸~~~ 한방에 번역을 합니다 저장은 뒤쪽 두개 */
		transrate_decoding( b1,b2,ip1,ip2,ip3,ip4,
			clientsInfo->at(clientsInfoIndex).port ,
			clientsInfo->at(clientsInfoIndex).ip1 ,
			clientsInfo->at(clientsInfoIndex).ip2 ,
			clientsInfo->at(clientsInfoIndex).ip3 ,
			clientsInfo->at(clientsInfoIndex).ip4 );
		clientsInfoIndex++;// 저장 갯수가 된다!
		i = i+6;
	}
	emit sendMessage("Recv Clients Ip" , 2000);
}
void
UzooParser::slotFinished()
{
	//clientsInfo->resize( clientsInfoIndex  );
	clientsInfoIndex = 0;
	emit endAsrParser();

	// 검색을 시작한다.
	send();
}
void
UzooParser::slotSendMessageToClients()
{
	if ( sendCounter >= (int)clientsInfo->size()  )
	{
		//타이머를 종료하고, 카운더도 초기화시킨다.
		timer->stop();
		return;
	}
	/* 마지막으로 SendMessage.send_data의 카운터 부분을 채운다. */
	memcpy( &(message.send_data[7]) , &(sendCounter) , sizeof(ushort));
	QString address;
	address.sprintf("%d.%d.%d.%d",
		clientsInfo->at(sendCounter).ip1,
		clientsInfo->at(sendCounter).ip2,
		clientsInfo->at(sendCounter).ip3,
		clientsInfo->at(sendCounter).ip4);
#ifdef DEBUG_UZOO
	cout << "Client Ip:" <<address.latin1() << endl;
#endif
	QHostAddress theirAddress;
	theirAddress.setAddress( address);
	
	socketDevice->writeBlock( 
		(char*)message.send_data , (uint)message.send_len ,
		theirAddress , clientsInfo->at(sendCounter).port );

	emit nowRecvSendUDPClients(recvCounter ,  sendCounter);
	sendCounter++;
}
void
UzooParser::slotRecvMessageFromClients()
{
	if ( recvCounter == recvMaxNum ) {
		// timer를 중지한다.
		timer->stop();
	}
	int MAXLEN = 10000;
	uchar string[MAXLEN];

	socketDevice->readBlock((char*)string , (uint) MAXLEN);
	// 이제 string을 디코딩해야 한다..
	uchar b1 = string[1];
	uchar b2 = string[2];
	uchar ip1 = string[3];
	uchar ip2 = string[4];
	uchar ip3 = string[5];
	uchar ip4 = string[6];
	
	RecvMessage rmessage;
	uchar _ip1;
	uchar _ip2;
	uchar _ip3;
	uchar _ip4;
		/* 역시 단박에 디코딩 */
	transrate_decoding(b1, b2, ip1, ip2, ip3, ip4, 
			rmessage.port ,_ip1 , _ip2 , _ip3 ,_ip4 );
	QString address;
	address.sprintf("%d.%d.%d.%d", _ip1 , _ip2 , _ip3 , _ip4);
	rmessage.address = address;
	rmessage.message = QString( (char*) &string[11] );
#ifdef DEBUG_UZOO
	cout << "START###########################################\n";
	cout << "RecvMessage address:" << rmessage.address.latin1() << endl;
	cout << "RecvMessage message:" << rmessage.message.latin1() << endl;
	cout << "END#############################################\n";
#endif
	recvCounter++;
	emit sendClientMessage( rmessage );
	emit sendMessage("Recv Client Message" ,2000);
	emit nowRecvSendUDPClients( recvCounter ,  sendCounter);
}
