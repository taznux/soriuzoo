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
#include <qdir.h>
#include <qlayout.h>
#include <qlistview.h>
#include <qcheckbox.h>
#include <qregexp.h>
#include <qcstring.h>

#include <iostream.h>
#include <stdlib.h>
#include <qbitmap.h>
#define kor(x) QString::fromLocal8Bit(x)

UzooMainNet::UzooMainNet(QWidget *parent,const char*name=0,int fl=0)
	: UzooMain(parent,name,fl)
{
	message0Label->setText(kor("환경설정합시다"));
	initStatusBar();
	initKorean();
	
	// 파서를 생성한다.
	parser = new UzooParser(this,"parser");
	connect(parser	,	SIGNAL(sendClientMessage(ResultSearch&)),
			this	,	SLOT(slotAppendToSearchListView(ResultSearch&)));
	connect(parser	,	SIGNAL(sendMessage(const QString& , int)),
		messageStatus,	SLOT(message(const QString& , int)));
	connect(parser	,	SIGNAL(nowRecvSendUDPClients(int,int)),
			this	,	SLOT(slotRecvSendUDPClients(int,int)));

	// configure Window
	genconfig = new UzooConfigImpl(this);
	this->info = genconfig->getInfo();
	genconfig->hide();
	connect(genconfig,SIGNAL(sendInfo(const UzooEnviroment&)) ,
		this, SLOT(slotEnviroment(const UzooEnviroment&)));
	
	// help Window
	help = new UzooHelpImpl(this);
	help->hide();
	connect(helpPBtn,SIGNAL(clicked()),this,SLOT(slotRunHelp()));
	
	// ID와 비번을 기입
	idLineEdit->setText(kor( info.userid ));
	passwdLineEdit->setText(kor( info.passwd));

	// 저장고를 생성하고, ListBox에도 넘겨준다.
	resultSearchList = new QValueList<ResultSearch>;
	searchListBox->setItems( resultSearchList);
	
	mainTabWidget->showPage(tab_4);
	idLineEdit->setFocus();
	connect(connectPBtn, SIGNAL(clicked()),this,SLOT(slotStartConnect()));
	connect(searchPBtn , SIGNAL(clicked()),this,SLOT(slotSearch()));
	connect(stopPBtn , SIGNAL(clicked()),this,SLOT(slotSearchStop()));

	// SearchListBox ===> this
	connect(searchListBox,	SIGNAL( selected(int) ),
			this	,		SLOT(	slotStartDownLoad(int) ));
	connect(searchListBox,	SIGNAL( highlighted(int) ),
			this	,		SLOT(	slotSearchListBoxHighlighted(int) ));
	connect(searchListBox,	SIGNAL( runMP3Player(ResultSearch&) ),
			this	,		SLOT(	slotAtOnceMP3Player(ResultSearch&) ));
	connect(searchListBox,	SIGNAL( startDownLoad(ResultSearch&) ),
			this	,		SLOT(	slotStartDownLoad(ResultSearch&) ));
	connect(searchListBox,	SIGNAL( stopDownLoad(ResultSearch&) ),
			this	,		SLOT(	slotStopDownLoad(ResultSearch&) ));

	connect(configPBtn,SIGNAL(clicked()),this,SLOT(slotRunConfig())),
	connect(appearanceConfigPBtn,	SIGNAL(clicked()),
			this	, 				SLOT(slotRunAppearanceConfig()));

	QTimer *updateLabelTimer = new QTimer(this);
	connect(updateLabelTimer,SIGNAL(timeout()),
		this, SLOT(slotUpdateClientInfo()));
	updateLabelTimer->start(100);

	if (info.autoLogin.lower() == QString("true"))
	{
		slotStartConnect();
	}
}
UzooMainNet::~UzooMainNet()
{
}
void
UzooMainNet::initStatusBar()
{
	messageStatus = new QStatusBar(this);
	UzooMainLayout->addWidget(messageStatus);
}
void
UzooMainNet::initKorean()
{
	this->setCaption(kor("소리우주(소리바다 for linux)"));
	this->searchPBtn->setText(kor("찾기"));
	this->stopPBtn->setText(kor("그만"));
	this->searchTitle->setText(kor("노래제목"));
	this->searchSinger->setText(kor("가수"));
	this->searchQuality->setText(kor("음질"));
	this->searchDownLoad->setText(kor("퍼센트"));
	this->searchSize->setText(kor("크기"));
	this->searchTime->setText(kor("시간"));
	this->searchUser->setText(kor("사용자"));
	this->mainTabWidget->changeTab(tab,kor("찾기"));

	this->TextLabel5->setText(kor("내려받기"));
	this->TextLabel6->setText(kor("올려주기"));
	this->mainTabWidget->changeTab(tab_2,kor("상태"));
	
	this->configPBtn->setText(kor("환경설정(&C)"));
	this->helpPBtn->setText(kor("도움말및 정보"));
	this->appearanceConfigPBtn->setText(kor("외형설정(&A)"));
	this->mainTabWidget->changeTab(tab_3,kor("설정"));

	this->TextLabel1->setText(kor("사용자ID"));
	this->TextLabel2_2->setText(kor("패스워드"));
	this->connectPBtn->setText(kor("접속"));
	this->mainTabWidget->changeTab(tab_4,kor("접속"));
	
}
void
UzooMainNet::slotEnviroment(const UzooEnviroment& info)
{
	this->info = info;
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
	info.userid = idLineEdit->text();
	info.passwd = passwdLineEdit->text();
	
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
    targetStr.append(kor(info.userid));
    targetStr.append("&password=");
    targetStr.append(kor(info.passwd));
    targetStr.append("&version=");
    targetStr.append(kor(info.version));

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
	_ASRUrl.append(kor(info.userid));
	_ASRUrl.append("&password=");
	_ASRUrl.append(kor(info.passwd));

	printLabel->setText("Succed to connect");
	mainTabWidget->showPage(tab );
	searchLineEdit->setFocus();
	searchPBtn->setEnabled(true);
	stopPBtn->setEnabled(true);
}
void
UzooMainNet::slotSearch()
{
	if (searchLineEdit->text().isEmpty() )
	{
		messageStatus->message("Please input string",2000);
		return;
	}
	messageStatus->message("Start ASR Parser",2000);
	resultSearchList->clear();
	searchListBox->clear();
	message1Label->setText("");

	// 파서를 시작한다.
	parser->setMyPort( info.userPort );
	parser->setRecvMaxNum( info.biggestSearch );
	parser->startParser( _ASRUrl , _Myip , searchLineEdit->text());
}
void
UzooMainNet::slotSearchStop()
{
	parser->searchStop();
}
void
UzooMainNet::slotAppendToSearchListView(ResultSearch &data)
{
	resultSearchList->append( data);
	searchListBox->insertItem(kor(data.filename));
}

void
UzooMainNet::slotSearchListBoxHighlighted(int num)
{
	searchUser->setText( 	kor((*resultSearchList)[num].userid ));
	searchTitle->setText(	kor((*resultSearchList)[num].title ));
	searchSinger->setText(	kor((*resultSearchList)[num].singer ));
	searchTime->setText(	kor((*resultSearchList)[num].filetime ));
	searchQuality->setText( kor((*resultSearchList)[num].bitrate ));

	// 오른쪽 밑 라벨을 지운다.
	searchDownLoad->setText("");

	int state = (*resultSearchList)[searchListBox->currentItem()].state;
	if ( state == 0)
		messageStatus->message("Please download me!",2000);
	else if(state ==1)
		messageStatus->message("Start download" , 2000);
	else if(state ==2)
		messageStatus->message("Downloading" , 2000);
	else if(state ==3)
		messageStatus->message("Finished download" , 2000);
	else if(state ==4)
		messageStatus->message("Wating", 2000);
	else if(state ==5)
		messageStatus->message("Error",2000);
	else if(state ==6)
		messageStatus->message("User Limit",2000);
	else if(state ==7)
		messageStatus->message("File Not Found",2000);
	else if(state ==8)
		messageStatus->message("Invaild Command",2000);
	else if(state ==9)
		messageStatus->message("File Exist",2000);
	else if(state ==10)
		messageStatus->message("Connection Closed",2000);
	else if(state ==11)
		messageStatus->message("Delayed Close Finished",2000);
}
void
UzooMainNet::slotUpdateClientInfo()
{
	int currentListIndex = searchListBox->currentItem();
	if (currentListIndex < 0 ) return;

	int downsize = (*resultSearchList)[currentListIndex].downsize;
	int filesize = (*resultSearchList)[currentListIndex].filesize;
	double count = (double)(((double)downsize/(double)filesize)*100);
	// 현재 listbox의 인덱스를 이용해서 label을 업데이트
	QCString downsizeString;
	QCString filesizeString;
	downsizeString.sprintf("%.2f", (double)(downsize/1024)/1024);
	filesizeString.sprintf("%.2f", (double)(filesize/1024)/1024);
	searchSize->setText(downsizeString+" / "+ filesizeString + "M");
	searchDownLoad->setText(QString::number( count)+"%" );
}
void
UzooMainNet::slotRecvSendUDPClients(int left,int right)
{
	QString leftString;
	leftString.sprintf("%d" , left);
	QString rightString;
	rightString.sprintf("%d" , right);
	message1Label->setText( leftString + " / "+ rightString);
}
void
UzooMainNet::slotRunConfig()
{
	genconfig->show();
}
void
UzooMainNet::slotRunHelp()
{
	help->show();
}
void
UzooMainNet::slotRunAppearanceConfig()
{
}
/*****************************************************************************
 * MP3 Player Function
 */
void /* Not slot function */
UzooMainNet::runMP3Player(ResultSearch &data)
{
	QString downloadFilePath(data.downpath);
	downloadFilePath.replace( QRegExp(" ") , "\\ ");
	downloadFilePath.replace( QRegExp("(") , "\\(");
	downloadFilePath.replace( QRegExp(")") , "\\)");
	downloadFilePath.replace( QRegExp("[") , "\\[");
	downloadFilePath.replace( QRegExp("]") , "\\]");
	downloadFilePath.replace( QRegExp("&") , "\\&");

	#ifdef DEBUG_UZOO
	cout << "Start Download\n";
	#endif
	if ( info.playerEnable.lower() == "true")
	{
		this->mp3player = info.defaultPlayerPath+ " " + downloadFilePath + "&";
		QTimer::singleShot(
			info.playerStartTime*1000 , this , SLOT(slotRunMP3Player()));
	}
}
void
UzooMainNet::runMP3Player(int listIndex)
{
	ResultSearch *data = &(*resultSearchList)[listIndex];
	runMP3Player( *data);
}
void // 내부 slot으로만 사용
UzooMainNet::slotRunMP3Player()
{
	#ifdef DEBUG_UZOO
	cout << mp3player.local8Bit().data() << "\n";
	#endif
	system( mp3player.local8Bit().data() );
}
void
UzooMainNet::slotAtOnceMP3Player(ResultSearch& data)
{
	QString downloadFilePath(data.downpath);
	downloadFilePath.replace( QRegExp(" ") , "\\ ");
	downloadFilePath.replace( QRegExp("(") , "\\(");
	downloadFilePath.replace( QRegExp(")") , "\\)");
	downloadFilePath.replace( QRegExp("[") , "\\[");
	downloadFilePath.replace( QRegExp("]") , "\\]");
	downloadFilePath.replace( QRegExp("&") , "\\&");

	QString mp3( info.defaultPlayerPath + " "  + downloadFilePath + "&" );
	system( mp3.local8Bit().data() );
}
void
UzooMainNet::slotAtOnceMP3Player(int index)
{
	slotAtOnceMP3Player( (*resultSearchList)[index] );
}
/* End MP3 Player Function */
/****************************************************************************/

/****************************************************************************
 ****************************************************************************
 * DownLoad oder Function
 */
void
UzooMainNet::slotStartDownLoad(int num)
{
	
	UzooSocket *download = new UzooSocket(this,"download" , 
							(*resultSearchList)[num] , info.userid );
	download->setDownLoadPath( info.downloadPath );
	connect(download ,	SIGNAL(sendMessage(const QString& , int)),
		messageStatus , SLOT(message(const QString&,int)));
	/* 다운로드가 성공적으로 시작하면 정해진 함수를 가동 */
	connect(download ,	SIGNAL(start(ResultSearch&)),
			this , 		SLOT(slotSucceedStartDownLoad(ResultSearch&)));
	/* 다운로드가 성공적으로 종료하면 정해진 함수를 가동 */
	connect(download , 	SIGNAL(end(ResultSearch&)),
			this , 		SLOT(slotSucceedEndDownLoad(ResultSearch&)));
	/* 다양한 상태를 SearchListBox에 전달한다 */
	connect(download , 	SIGNAL(state(ResultSearch&)),
		searchListBox,	SLOT(slotStateItem(ResultSearch&)));
}
void
UzooMainNet::slotStartDownLoad(ResultSearch &data)
{
	slotStartDownLoad( findIndex(data) );
}
void
UzooMainNet::slotSucceedStartDownLoad(ResultSearch &data)
{
	// runMP3Player를 작동시킨다.
	runMP3Player(data);
	// dowloadListView에 저장한다.
	downloadListView->addResultSearch(data);
}
void
UzooMainNet::slotSucceedEndDownLoad(ResultSearch &data)
{
	// downloadListView에 아이템을 제거한다.
	downloadListView->removeResultSearch(data);
}
void
UzooMainNet::slotStopDownLoad(ResultSearch& data)
{
	// Not Implements
}
void
UzooMainNet::slotStopDownLoad(int index)
{
	// Not Implements
}
/* 다운로드 상태를 리스트박스에 아이콘으로 넣는다. */
/*void
UzooMainNet::slotStateDownLoad(ResultSearch &data)
{
}
void
UzooMainNet::slotStateDownLoad(int index)
{
}*/
/* End DownLoad Oder Function */
/****************************************************************************
 ***************************************************************************/

/* private function */
int
UzooMainNet::findIndex(ResultSearch& data)
{
	for(int i=0 ; i <(int)resultSearchList->count() ;i++)
	{
		ResultSearch *src = &(*resultSearchList)[i];
		if (src == &data ) // address compare
			return i; 
	}
	return -1;
}
