#include "uzoomainnet.h"
#include "uzooparser.h"
#include "uzoosocket.h"
#include <qobject.h>
#include <qurloperator.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qlistbox.h>
#include <qlcdnumber.h>
#include <qcolor.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <qtextbrowser.h>

#include <iostream.h>
#define kor(x) QString::fromLocal8Bit(x)

UzooMainNet::UzooMainNet(QWidget *parent,const char*name=0,int fl=0)
	: UzooMain(parent,name,fl)
{
	// 그림설정
	downloadPixmap = new QPixmap(30,30);
	userlimitPixmap = new QPixmap(30,30);
	filenotPixmap = new QPixmap(30,30);
	invalidPixmap = new QPixmap(30,30);
	
	downloadPixmap->fill(QColor(59,144,255));
	userlimitPixmap->fill(QColor(222,255,101));
	filenotPixmap->fill(QColor(255,140,82));
	invalidPixmap->fill(QColor(255,77,12));

	
	resultSearchList = new QValueList<ResultSearch>;
	parser = 0;
	mainTabWidget->showPage(tab_6);
	idLineEdit->setFocus();
	connect(connectPBtn, SIGNAL(clicked()),this,SLOT(slotStartConnect()));
	connect(searchPBtn , SIGNAL(clicked()),this,SLOT(slotSearch()));
	connect(stopPBtn , SIGNAL(clicked()),this,SLOT(slotSearchStop()));

	connect(searchListBox,SIGNAL(selected(int)),this,
		SLOT(slotSearchListBoxSelected(int)));
	connect(searchListBox,SIGNAL(highlighted(int)),this,
		SLOT(slotSearchListBoxHighlighted(int)));

	QTimer *updateLabelTimer = new QTimer(this);
	connect(updateLabelTimer,SIGNAL(timeout()),
		this, SLOT(slotUpdateClientInfo()));
	updateLabelTimer->start(1000);

	initHeloBrower();
}
UzooMainNet::~UzooMainNet()
{
}
void
UzooMainNet::initHeloBrower()
{
	helpBrower->setText(kor(
		"소리우주 개발자 리스트\n"
		"Analysis/Design\n"
		"장혜식 perky@users.sourceforge.net\n"
		"Qt Developer\n"
		"이재일 sonegy@users.sourceforge.net\n\n"
		"도움을 주신분들\n"
		"박진철 exman@users.sourceforge.net\n"
		"남대현 imations@users.sourceforge.net\n"
		"류윤   ruyon@users.sourceforge.net\n"
		"류명환 ryu281@users.sourceforge.net\n"
		"최진철 taznux@users.sourceforge.net\n"
		"황장호 xrath@users.sourceforge.net\n"
	));
}
void
UzooMainNet::slotStartConnect()
{
	if ( idLineEdit->text().isEmpty() == true ||
		 passwdLineEdit->text().isEmpty() == true)
	{
		printLabel->setText("please input correct info");
		return;
	}
	_UserID = idLineEdit->text().local8Bit();
	_Passwd = passwdLineEdit->text().local8Bit();
	_Version= versionLineEdit->text().local8Bit();
	
	//게이트웨이를 얻어온다.
	QUrlOperator *gate = new QUrlOperator(
		"http://www.soribada.com/gateway.txt");
	connect(gate , SIGNAL(data(const QByteArray& ,QNetworkOperation*)),
		this , SLOT(slotGetGateWay(const QByteArray&)));
	gate->get();
	printLabel->setText("Connecting gateway");
}
void
UzooMainNet::slotGetGateWay(const QByteArray& byte)
{
	QString str(byte.data());
	// gateway의 정보를 분석해서 다시 asr접속을 시도한다.
    QString targetStr;
    int startIndex = str.find("http://");
    int endIndex = str.findRev(".phtml");
    targetStr = str.mid( startIndex , endIndex - startIndex+6);

    targetStr.append("?username=");
    targetStr.append(_UserID);
    targetStr.append("&password=");
    targetStr.append(_Passwd);
    targetStr.append("&version=");
    targetStr.append(_Version);

    QUrlOperator *asrlogin = new QUrlOperator( targetStr );
    connect( asrlogin , SIGNAL(data(const QByteArray&,QNetworkOperation*)) ,
            this , SLOT(slotGetServerInfo(const QByteArray&)));
    asrlogin->get();
    printLabel->setText("connecting ASR Url");
}
void
UzooMainNet::slotGetServerInfo(const QByteArray &byte)
{
	QString str(byte.data());
	if (str.left(17) == QString("Return Code : 101"))
	{
		printLabel->setText("Refuse from soribada");
		return;
	}
	// asr server에서 정보들을 긁어 모은다.
    QString ASR;
    int sIndex = str.find("ASR");
    int eIndex = str.find("ACH" , sIndex);
    _ASRUrl = str.mid(sIndex , eIndex-sIndex);
    _ASRUrl.remove(0,3);
    _ASRUrl = _ASRUrl.stripWhiteSpace();

    sIndex = str.find("MYIP");
    eIndex = str.find("PI" , sIndex);
    _Myip = str.mid(sIndex , eIndex- sIndex );
    _Myip.remove(0,4);
    _Myip = _Myip.stripWhiteSpace();

	_ASRUrl.append("?action=gimme&username=");
	_ASRUrl.append(_UserID);
	_ASRUrl.append("&password=");
	_ASRUrl.append(_Passwd);

	printLabel->setText("Succed to connect");
	mainTabWidget->showPage(tab );
	searchLineEdit->setFocus();
}
void
UzooMainNet::slotSearch()
{
	resultSearchList->clear();
	searchListBox->clear();
	if(parser !=0 ) {delete parser; parser=0;}
	UzooParser *_parser = new UzooParser( _ASRUrl , _Myip ,  searchLineEdit->text());
	parser = _parser;
	connect(_parser, SIGNAL(sendClientMessage(RecvMessage &)),
			this,   SLOT(slotAppendToSearchListView(RecvMessage &)));
	connect(_parser, SIGNAL(nowSendUDPClients(int)),
			progLCD,SLOT(display(int)));
	connect(_parser, SIGNAL(nowRecvUDPClients(int)),
			this , SLOT(slotPrintLabe1(int)));
}
void
UzooMainNet::slotSearchStop()
{
	parser->searchStop();
}
void
UzooMainNet::slotAppendToSearchListView(RecvMessage &message)
{
	ResultSearch result;
	result.address = message.address;
	QString target(message.message);

	int fIndex; 
	QString getString;

	fIndex = target.find("\n");
	getString = target.left(fIndex);
	target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
	// 첫번째 원하는 정보를 얻었다. getString
	result.userid = getString;
	
	fIndex = target.find("\n");
	getString = target.left(fIndex);
	target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
	result.port = getString.toInt();

	while(1)
	{
		// 패스가 아닌 쓰레기값을 지운다.
		while(1)
		{
			fIndex = 0;
			fIndex = target.find("\n");
			if (fIndex < 0 ) return;
			getString = target.left(fIndex);
			target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
			if(getString.lower().contains(".mp3") > 0 &&
				getString.lower().left(1) > "a" &&
				getString.lower().left(1) < "z" &&
				getString.mid(1,1) == ":") break;
		}
		result.path = getString;

		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
		result.filesize = getString.toLong();

		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
		result.filetime = getString;
		
		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
		result.bitrate = getString;
		
		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
		result.singer = getString;
		
		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
		result.title = getString;

		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // 첫번째 줄을 지운다.
		result.comment = getString;
		
		// 필요없는 문자열을 지웁니다.
		fIndex = 0;
		fIndex = target.find("\n\r");
		target.remove(0, fIndex + 2);
		
		// 리스트에 정보를 넣는다.
		ResultSearch appendResult;
		appendResult.address = result.address;
		appendResult.userid  = result.userid;
		appendResult.port    = result.port;
		appendResult.path	 = result.path;
		appendResult.filesize= result.filesize;
		appendResult.filetime= result.filetime;
		appendResult.bitrate = result.bitrate;
		appendResult.singer  = result.singer;
		appendResult.title   = result.title;
		appendResult.comment = result.comment;
		appendResult.downsize= 0;

		resultSearchList->append( appendResult );// 저장고에 저장한다.
			
		int pathFindLen = appendResult.path.length();
		int pathFindIndex = appendResult.path.findRev("\\");
		searchListBox->insertItem( 
			kor( appendResult.path.right(pathFindLen - pathFindIndex -1 ) ) );
		// listbox에 하나씩 넣어준다. 이때 인덱스는 resultSearchList의
		// 인덱스와 일치한다.

		//item->setText(2,kor( appendResult.title));
		//item->setText(3,kor( appendResult.singer));
		//item->setText(4,kor( appendResult.filesize));
		//item->setText(5,kor( appendResult.bitrate));
		//item->setText(6,kor( appendResult.filetime));
		//item->setText(7,kor( appendResult.userid ));
	
		if ( (target.lower()).contains(".mp3") <= 0 ){break;}
	}
}
void 
UzooMainNet::slotPrintLabe1(int num)
{
	int total = parser->getClientsInfoSize();
	message1Label->setText( 
		QString::number(num)+ " / " + QString::number(total));
}
void
UzooMainNet::slotSearchListBoxSelected(int num)
{
	//cout << "Num:"<< num << endl;
	QString *address_p 	= & (*resultSearchList)[num].address ;
	int 	port 		=  (*resultSearchList)[num].port;
	QString *path_p		= & (*resultSearchList)[num].path;
	long	filesize	=  (*resultSearchList)[num].filesize;

	//cout << "Address:"<< address_p->latin1() << endl;
	//cout << "port   :"<< port << endl;
	//cout << "paht   :"<< path_p->latin1() << endl;
	
	UzooSocket *download = new UzooSocket(*path_p , _UserID , this,"download");
	connect(download , SIGNAL(sendFileSize(int,int)),
		this , SLOT(slotSetDownLoadSize(int,int)));
	connect(download,SIGNAL(sendMessage(const QString&)),
		message2Label , SLOT(setText(const QString&)));
	download->setTotalFileSize(filesize);
	download->setListIndex( num );
	download->connectTo( *address_p , port);

	// 현재 리스트줄을 색을 넣는다. 다운로드임을 표시한다.
}
void
UzooMainNet::slotSearchListBoxHighlighted(int num)
{
	QString printFileSize;
	printFileSize.append( QString::number((*resultSearchList)[num].downsize) );
	printFileSize.append(" / ");
	printFileSize.append( QString::number((*resultSearchList)[num].filesize) );

	searchUser->setText( 	kor((*resultSearchList)[num].userid ));
	searchTitle->setText(	kor((*resultSearchList)[num].title ));
	searchSinger->setText(	kor((*resultSearchList)[num].singer ));
	searchSize->setText(	kor( printFileSize ) );
	searchTime->setText(	kor((*resultSearchList)[num].filetime ));
	searchQuality->setText( kor((*resultSearchList)[num].bitrate ));

	// 오른쪽 밑 라벨을 지운다.
	message2Label->setText("");
	searchDownLoad->setText("");
}
void
UzooMainNet::slotSetDownLoadSize(int index , int num)
{
	(*resultSearchList)[index].downsize = num;
	// index와 현재 하이라이트된 일치한다면 size라벨을 업데이트한다.
}
void
UzooMainNet::slotUpdateClientInfo()
{
	//현재 하이라이트된 인덱스의 downsize가 0이 아니며
	//filesize와 같지 않다면 다운중인 파일임을 알수 있다.
	int currentListIndex = searchListBox->currentItem();
	if (currentListIndex < 0 ) return;
	int downsize = (*resultSearchList)[currentListIndex].downsize;
	int filesize = (*resultSearchList)[currentListIndex].filesize;
	int count = (int)(((double)downsize/filesize)*100);
	if ( downsize !=0 )
	{
		// 현재 listbox의 인덱스를 이용해서 label을 업데이트
		searchSize->setText(
			QString::number(downsize)+" / "+QString::number(filesize));
		searchDownLoad->setText(QString::number( count)+"%" );
		message2Label->setText("DownLoading");
	}
}
