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

#include <iostream.h>
#include <stdlib.h>
#undef DEBUG_UZOO
#define kor(x) QString::fromLocal8Bit(x)

UzooMainNet::UzooMainNet(QWidget *parent,const char*name=0,int fl=0)
	: UzooMain(parent,name,fl)
{
	message0Label->setText(kor("ȯ�漳���սô�"));
	initStatusBar();
	initKorean();
	
	// �ļ��� �����Ѵ�.
	parser = new UzooParser(this,"parser");
	connect(parser, SIGNAL(sendClientMessage(RecvMessage &)),
			this,   SLOT(slotAppendToSearchListView(RecvMessage &)));
	connect(parser, SIGNAL(nowRecvSendUDPClients(int, int)),
			this , SLOT(slotPrintLabel(int , int)));
	connect(parser,SIGNAL(sendMessage(const QString& , int)),
			messageStatus,SLOT(message(const QString& , int)));

	// configure Window
	genconfig = new UzooConfigImpl(this);
	this->info = genconfig->getInfo();
	genconfig->hide();
	connect(genconfig,SIGNAL(sendInfo(const UzooEnviroment&)) ,
		this, SLOT(slotEnviroment(const UzooEnviroment&)));
	
	// ID�� ����� ����
	idLineEdit->setText(kor( info.userid ));
	passwdLineEdit->setText(kor( info.passwd));

	// ����Ʈ �ڽ��� �� ��
	downloadPixmap = new QPixmap(30,30);
	userlimitPixmap = new QPixmap(30,30);
	filenotPixmap = new QPixmap(30,30);
	invalidPixmap = new QPixmap(30,30);
	downloadPixmap->fill(QColor(59,144,255));
	userlimitPixmap->fill(QColor(222,255,101));
	filenotPixmap->fill(QColor(255,140,82));
	invalidPixmap->fill(QColor(255,77,12));
	
	resultSearchList = new QValueList<ResultSearch>;
	mainTabWidget->showPage(tab_4);
	idLineEdit->setFocus();
	connect(connectPBtn, SIGNAL(clicked()),this,SLOT(slotStartConnect()));
	connect(searchPBtn , SIGNAL(clicked()),this,SLOT(slotSearch()));
	connect(stopPBtn , SIGNAL(clicked()),this,SLOT(slotSearchStop()));

	connect(searchListBox,SIGNAL(selected(int)),this,
		SLOT(slotSearchListBoxSelected(int)));
	connect(searchListBox,SIGNAL(highlighted(int)),this,
		SLOT(slotSearchListBoxHighlighted(int)));

	connect(configPBtn,SIGNAL(clicked()),this,SLOT(slotRunConfig())),
	connect(appearanceConfigPBtn,SIGNAL(clicked()),
		this, SLOT(slotRunAppearanceConfig()));

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
	this->setCaption(kor("�Ҹ�����(�Ҹ��ٴ� for linux)"));
	this->searchPBtn->setText(kor("ã��"));
	this->stopPBtn->setText(kor("�׸�"));
	this->searchTitle->setText(kor("�뷡����"));
	this->searchSinger->setText(kor("����"));
	this->searchQuality->setText(kor("����"));
	this->searchDownLoad->setText(kor("�ۼ�Ʈ"));
	this->searchSize->setText(kor("ũ��"));
	this->searchTime->setText(kor("�ð�"));
	this->searchUser->setText(kor("�����"));
	this->mainTabWidget->changeTab(tab,kor("ã��"));

	this->TextLabel5->setText(kor("�����ޱ�"));
	this->downloadListView->setColumnText(0,kor("�����̸�"));
	this->downloadListView->setColumnText(1,kor("����"));
	this->downloadListView->setColumnText(2,kor("����"));
	this->downloadListView->setColumnText(3,kor("ũ��"));
	this->downloadListView->setColumnText(4,kor("����"));
	this->downloadListView->setColumnText(5,kor("�ð�"));
	this->downloadListView->setColumnText(6,kor("�����"));
	this->downloadListView->setColumnText(7,kor("�ӵ�"));
	this->TextLabel6->setText(kor("�÷��ֱ�"));
	this->uploadListView->setColumnText(0,kor("�����̸�"));
	this->uploadListView->setColumnText(1,kor("����"));
	this->uploadListView->setColumnText(2,kor("����"));
	this->uploadListView->setColumnText(3,kor("ũ��"));
	this->uploadListView->setColumnText(4,kor("����"));
	this->uploadListView->setColumnText(5,kor("�ð�"));
	this->uploadListView->setColumnText(6,kor("�����"));
	this->uploadListView->setColumnText(7,kor("�ӵ�"));
	this->mainTabWidget->changeTab(tab_2,kor("����"));
	
	this->configPBtn->setText(kor("�Ϲݼ���(&C)"));
	this->appearanceConfigPBtn->setText(kor("��������(&A)"));
	this->mainTabWidget->changeTab(tab_3,kor("����"));

	this->TextLabel1->setText(kor("�����ID"));
	this->TextLabel2_2->setText(kor("�н�����"));
	this->connectPBtn->setText(kor("����"));
	this->mainTabWidget->changeTab(tab_4,kor("����"));
	
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
	
	//����Ʈ���̸� ���´�.
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
	// gateway�� ������ �м��ؼ� �ٽ� asr������ �õ��Ѵ�.
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
	// asr server���� �������� �ܾ� ������.
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

	// �ļ��� �����Ѵ�.
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
UzooMainNet::slotAppendToSearchListView(RecvMessage &message)
{
	ResultSearch result;
	result.address = message.address;
	QString target(message.message);

	int fIndex; 
	QString getString;

	fIndex = target.find("\n");
	getString = target.left(fIndex);
	target.remove(0,fIndex+1); // ù��° ���� �����.
	// ù��° ���ϴ� ������ �����. getString
	result.userid = getString;
	
	fIndex = target.find("\n");
	getString = target.left(fIndex);
	target.remove(0,fIndex+1); // ù��° ���� �����.
	result.port = getString.toInt();

	while(1)
	{
		// �н��� �ƴ� �����Ⱚ�� �����.
		while(1)
		{
			fIndex = 0;
			fIndex = target.find("\n");
			if (fIndex < 0 ) return;
			getString = target.left(fIndex);
			target.remove(0,fIndex+1); // ù��° ���� �����.
			if(getString.lower().contains(".mp3") > 0 &&
				getString.lower().left(1) > "a" &&
				getString.lower().left(1) < "z" &&
				getString.mid(1,1) == ":") break;
		}
		result.path = getString;

		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // ù��° ���� �����.
		result.filesize = getString.toLong();

		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // ù��° ���� �����.
		result.filetime = getString;
		
		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // ù��° ���� �����.
		result.bitrate = getString;
		
		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // ù��° ���� �����.
		result.singer = getString;
		
		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // ù��° ���� �����.
		result.title = getString;

		fIndex = 0;
		fIndex = target.find("\n");
		getString = target.left(fIndex);
		target.remove(0,fIndex+1); // ù��° ���� �����.
		result.comment = getString;
		
		// �ʿ���� ���ڿ��� ����ϴ�.
		fIndex = 0;
		fIndex = target.find("\n\r");
		target.remove(0, fIndex + 2);
		
		// ����Ʈ�� ������ �ִ´�.
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
		appendResult.state 	 = 0;

		resultSearchList->append( appendResult );// ����� �����Ѵ�.
			
		int pathFindLen = appendResult.path.length();
		int pathFindIndex = appendResult.path.findRev("\\");
		searchListBox->insertItem( 
			kor( appendResult.path.right(pathFindLen - pathFindIndex -1 ) ) );
		// listbox�� �ϳ��� �־��ش�. �̶� �ε����� resultSearchList��
		// �ε����� ��ġ�Ѵ�.

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
UzooMainNet::slotPrintLabel(int num , int num2)
{
//	int total = parser->getClientsInfoSize();
	message1Label->setText( 
		QString::number(num)+ " / " + QString::number(num2));
}
void
UzooMainNet::slotSearchListBoxSelected(int num)
{
	//cout << "Num:"<< num << endl;
	//QString *address_p 	= & (*resultSearchList)[num].address ;
	//int 	port 		=  (*resultSearchList)[num].port;
	//QString *path_p		= & (*resultSearchList)[num].path;
	//long	filesize	=  (*resultSearchList)[num].filesize;

	//cout << "Address:"<< address_p->latin1() << endl;
	//cout << "port   :"<< port << endl;
	//cout << "paht   :"<< path_p->latin1() << endl;
	
	UzooSocket *download = new UzooSocket(this,"download" , 
			(*resultSearchList)[num] , num , info.userid );
	download->setDownLoadPath( info.downloadPath );

	connect(download , SIGNAL(sendFileSize(int,int)),
		this , SLOT(slotSetDownLoadSize(int,int)));
	connect(download , SIGNAL(sendState(int,char)),
		this , SLOT(slotSetSocketState(int,char)));
	connect(download , SIGNAL(start(UzooSocket*)),
		this , SLOT(slotStartDownLoad(UzooSocket*)));
	connect(download , SIGNAL(end(UzooSocket*)),
		this , SLOT(slotEndDownLoad(UzooSocket*)));
	// ���� ����Ʈ���� ���� �ִ´�. �ٿ�ε����� ǥ���Ѵ�.
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

	// ������ �� ���� �����.
	searchDownLoad->setText("");
}
void
UzooMainNet::slotSetDownLoadSize(int index , int num)
{
	(*resultSearchList)[index].downsize = num;
	// index�� ���� ���̶���Ʈ�� ��ġ�Ѵٸ� size���� ������Ʈ�Ѵ�.
}
void
UzooMainNet::slotSetSocketState(int index , char state)
{
	(*resultSearchList)[index].state = state;
}
void
UzooMainNet::slotUpdateClientInfo()
{
	int currentListIndex = searchListBox->currentItem();
	if (currentListIndex < 0 ) return;

	int downsize = (*resultSearchList)[currentListIndex].downsize;
	int filesize = (*resultSearchList)[currentListIndex].filesize;
	int count = (int)(((double)downsize/filesize)*100);
	// ���� listbox�� �ε����� �̿��ؼ� label�� ������Ʈ
	searchSize->setText(
		QString::number(downsize)+" / "+QString::number(filesize));
	searchDownLoad->setText(QString::number( count)+"%" );

	int state = (*resultSearchList)[currentListIndex].state;
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
UzooMainNet::slotRunConfig()
{
	genconfig->show();
}
void
UzooMainNet::slotRunAppearanceConfig()
{
}
void
UzooMainNet::slotStartDownLoad(UzooSocket *downloader)
{
	QString downloadFileName(downloader->getDownLoadFileName());
	downloadFileName.prepend("\\");
	downloadFileName.replace( QRegExp(" ") , "\\ ");
#ifdef DEBUG_UZOO
	cout << "Start Download\n";
#endif
	if ( info.playerEnable.lower() == "true")
	{
		this->mp3player = info.defaultPlayerPath +" "+ downloadFileName + "&";
		QTimer::singleShot(
			info.playerStartTime*1000 , this , SLOT(slotRunMP3Player()));
	}
}
void
UzooMainNet::slotRunMP3Player()
{
#ifdef DEBUG_UZOO
	cout << mp3player.local8Bit().data() << "\n";
#endif
	system( mp3player.local8Bit().data() );
}
void
UzooMainNet::slotEndDownLoad(UzooSocket *downloader)
{
#ifdef DEBUG_UZOO
	cout << "End DownLoad\n";
#endif
}
