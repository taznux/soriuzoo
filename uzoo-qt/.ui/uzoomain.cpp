/****************************************************************************
** Form implementation generated from reading ui file 'mainwindow.ui'
**
** Created: Sun Feb 10 21:00:30 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uzoomain.h"

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlcdnumber.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a UzooMain which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
UzooMain::UzooMain( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "UzooMain" );
    resize( 285, 362 ); 
    setCaption( tr( "Sori Uzoo" ) );
    UzooMainLayout = new QVBoxLayout( this ); 
    UzooMainLayout->setSpacing( 0 );
    UzooMainLayout->setMargin( 0 );

    mainTabWidget = new QTabWidget( this, "mainTabWidget" );
    mainTabWidget->setTabPosition( QTabWidget::Top );

    tab = new QWidget( mainTabWidget, "tab" );
    tabLayout = new QVBoxLayout( tab ); 
    tabLayout->setSpacing( 5 );
    tabLayout->setMargin( 5 );

    Layout14 = new QHBoxLayout; 
    Layout14->setSpacing( 6 );
    Layout14->setMargin( 0 );

    searchLineEdit = new QLineEdit( tab, "searchLineEdit" );
    Layout14->addWidget( searchLineEdit );

    searchPBtn = new QPushButton( tab, "searchPBtn" );
    searchPBtn->setText( tr( "Search" ) );
    Layout14->addWidget( searchPBtn );

    stopPBtn = new QPushButton( tab, "stopPBtn" );
    stopPBtn->setText( tr( "Stop" ) );
    Layout14->addWidget( stopPBtn );
    tabLayout->addLayout( Layout14 );

    searchListBox = new QListBox( tab, "searchListBox" );
    tabLayout->addWidget( searchListBox );

    searchTitle = new QLabel( tab, "searchTitle" );
    searchTitle->setMaximumSize( QSize( 32767, 20 ) );
    searchTitle->setFrameShape( QLabel::Box );
    searchTitle->setFrameShadow( QLabel::Raised );
    searchTitle->setText( tr( "title" ) );
    tabLayout->addWidget( searchTitle );

    Layout17 = new QHBoxLayout; 
    Layout17->setSpacing( 0 );
    Layout17->setMargin( 0 );

    Layout16 = new QVBoxLayout; 
    Layout16->setSpacing( 0 );
    Layout16->setMargin( 0 );

    searchSinger = new QLabel( tab, "searchSinger" );
    searchSinger->setMaximumSize( QSize( 32767, 20 ) );
    searchSinger->setFrameShape( QLabel::Box );
    searchSinger->setFrameShadow( QLabel::Raised );
    searchSinger->setText( tr( "singer" ) );
    Layout16->addWidget( searchSinger );

    searchQuality = new QLabel( tab, "searchQuality" );
    searchQuality->setMaximumSize( QSize( 32767, 20 ) );
    searchQuality->setFrameShape( QLabel::Box );
    searchQuality->setFrameShadow( QLabel::Raised );
    searchQuality->setText( tr( "quality" ) );
    Layout16->addWidget( searchQuality );

    searchDownLoad = new QLabel( tab, "searchDownLoad" );
    searchDownLoad->setMaximumSize( QSize( 32767, 20 ) );
    searchDownLoad->setFrameShape( QLabel::Box );
    searchDownLoad->setFrameShadow( QLabel::Raised );
    searchDownLoad->setText( tr( "percent" ) );
    Layout16->addWidget( searchDownLoad );
    Layout17->addLayout( Layout16 );

    Layout21 = new QVBoxLayout; 
    Layout21->setSpacing( 0 );
    Layout21->setMargin( 0 );

    searchSize = new QLabel( tab, "searchSize" );
    searchSize->setMaximumSize( QSize( 32767, 20 ) );
    searchSize->setFrameShape( QLabel::Box );
    searchSize->setFrameShadow( QLabel::Raised );
    searchSize->setText( tr( "size" ) );
    Layout21->addWidget( searchSize );

    searchTime = new QLabel( tab, "searchTime" );
    searchTime->setMaximumSize( QSize( 32767, 20 ) );
    searchTime->setFrameShape( QLabel::Box );
    searchTime->setFrameShadow( QLabel::Raised );
    searchTime->setText( tr( "time" ) );
    Layout21->addWidget( searchTime );

    searchUser = new QLabel( tab, "searchUser" );
    searchUser->setMaximumSize( QSize( 32767, 20 ) );
    searchUser->setFrameShape( QLabel::Box );
    searchUser->setFrameShadow( QLabel::Raised );
    searchUser->setText( tr( "user" ) );
    Layout21->addWidget( searchUser );
    Layout17->addLayout( Layout21 );
    tabLayout->addLayout( Layout17 );
    mainTabWidget->insertTab( tab, tr( "Search" ) );

    tab_2 = new QWidget( mainTabWidget, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2 ); 
    tabLayout_2->setSpacing( 5 );
    tabLayout_2->setMargin( 5 );

    TextLabel5 = new QLabel( tab_2, "TextLabel5" );
    TextLabel5->setMaximumSize( QSize( 32767, 25 ) );
    TextLabel5->setFrameShape( QLabel::Box );
    TextLabel5->setFrameShadow( QLabel::Raised );
    TextLabel5->setText( tr( "DownLoad" ) );
    tabLayout_2->addWidget( TextLabel5 );

    downloadListView = new QListView( tab_2, "downloadListView" );
    downloadListView->addColumn( tr( "file name" ) );
    downloadListView->addColumn( tr( "titile" ) );
    downloadListView->addColumn( tr( "singer" ) );
    downloadListView->addColumn( tr( "size" ) );
    downloadListView->addColumn( tr( "qualitty" ) );
    downloadListView->addColumn( tr( "time" ) );
    downloadListView->addColumn( tr( "user" ) );
    downloadListView->addColumn( tr( "speed" ) );
    downloadListView->setSelectionMode( QListView::Extended );
    downloadListView->setAllColumnsShowFocus( TRUE );
    tabLayout_2->addWidget( downloadListView );

    TextLabel6 = new QLabel( tab_2, "TextLabel6" );
    TextLabel6->setMaximumSize( QSize( 32767, 25 ) );
    TextLabel6->setFrameShape( QLabel::Box );
    TextLabel6->setFrameShadow( QLabel::Raised );
    TextLabel6->setText( tr( "UpLoad" ) );
    tabLayout_2->addWidget( TextLabel6 );

    uploadListView = new QListView( tab_2, "uploadListView" );
    uploadListView->addColumn( tr( "file name" ) );
    uploadListView->addColumn( tr( "titile" ) );
    uploadListView->addColumn( tr( "singer" ) );
    uploadListView->addColumn( tr( "size" ) );
    uploadListView->addColumn( tr( "qualitty" ) );
    uploadListView->addColumn( tr( "time" ) );
    uploadListView->addColumn( tr( "user" ) );
    uploadListView->addColumn( tr( "speed" ) );
    uploadListView->setSelectionMode( QListView::Extended );
    uploadListView->setAllColumnsShowFocus( TRUE );
    tabLayout_2->addWidget( uploadListView );
    mainTabWidget->insertTab( tab_2, tr( "DownUp" ) );

    tab_3 = new QWidget( mainTabWidget, "tab_3" );
    tabLayout_3 = new QVBoxLayout( tab_3 ); 
    tabLayout_3->setSpacing( 5 );
    tabLayout_3->setMargin( 5 );

    Layout7 = new QHBoxLayout; 
    Layout7->setSpacing( 6 );
    Layout7->setMargin( 0 );

    upFolderPBtn = new QPushButton( tab_3, "upFolderPBtn" );
    upFolderPBtn->setText( tr( "UpLoad Folder" ) );
    Layout7->addWidget( upFolderPBtn );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout7->addItem( spacer );
    tabLayout_3->addLayout( Layout7 );

    upFolderComboBox = new QComboBox( FALSE, tab_3, "upFolderComboBox" );
    upFolderComboBox->setEditable( FALSE );
    tabLayout_3->addWidget( upFolderComboBox );

    Layout8 = new QHBoxLayout; 
    Layout8->setSpacing( 6 );
    Layout8->setMargin( 0 );

    downFolderLineEdit = new QLineEdit( tab_3, "downFolderLineEdit" );
    Layout8->addWidget( downFolderLineEdit );

    downFolderPBtn = new QPushButton( tab_3, "downFolderPBtn" );
    downFolderPBtn->setText( tr( "DownLoad Folder" ) );
    Layout8->addWidget( downFolderPBtn );
    tabLayout_3->addLayout( Layout8 );

    privateTabWidget = new QTabWidget( tab_3, "privateTabWidget" );

    tab_4 = new QWidget( privateTabWidget, "tab_4" );
    tabLayout_4 = new QVBoxLayout( tab_4 ); 
    tabLayout_4->setSpacing( 6 );
    tabLayout_4->setMargin( 11 );

    Layout13 = new QHBoxLayout; 
    Layout13->setSpacing( 6 );
    Layout13->setMargin( 0 );

    TextLabel1_2 = new QLabel( tab_4, "TextLabel1_2" );
    TextLabel1_2->setText( tr( "Biggest connect by One Client" ) );
    Layout13->addWidget( TextLabel1_2 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout13->addItem( spacer_2 );

    myserver1SpinBox = new QSpinBox( tab_4, "myserver1SpinBox" );
    Layout13->addWidget( myserver1SpinBox );
    tabLayout_4->addLayout( Layout13 );

    Layout14_2 = new QHBoxLayout; 
    Layout14_2->setSpacing( 6 );
    Layout14_2->setMargin( 0 );

    TextLabel2 = new QLabel( tab_4, "TextLabel2" );
    TextLabel2->setText( tr( "Biggest connect of Every" ) );
    Layout14_2->addWidget( TextLabel2 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout14_2->addItem( spacer_3 );

    myserver2SpinBox = new QSpinBox( tab_4, "myserver2SpinBox" );
    Layout14_2->addWidget( myserver2SpinBox );
    tabLayout_4->addLayout( Layout14_2 );

    Layout15 = new QHBoxLayout; 
    Layout15->setSpacing( 6 );
    Layout15->setMargin( 0 );

    TextLabel3 = new QLabel( tab_4, "TextLabel3" );
    TextLabel3->setText( tr( "User Port" ) );
    Layout15->addWidget( TextLabel3 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout15->addItem( spacer_4 );

    userportSpinBox = new QSpinBox( tab_4, "userportSpinBox" );
    Layout15->addWidget( userportSpinBox );
    tabLayout_4->addLayout( Layout15 );

    Layout16_2 = new QHBoxLayout; 
    Layout16_2->setSpacing( 6 );
    Layout16_2->setMargin( 0 );

    TextLabel4 = new QLabel( tab_4, "TextLabel4" );
    TextLabel4->setText( tr( "Biggest search" ) );
    Layout16_2->addWidget( TextLabel4 );
    QSpacerItem* spacer_5 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout16_2->addItem( spacer_5 );

    searchSpinBox = new QSpinBox( tab_4, "searchSpinBox" );
    Layout16_2->addWidget( searchSpinBox );
    tabLayout_4->addLayout( Layout16_2 );
    privateTabWidget->insertTab( tab_4, tr( "MyServer" ) );

    tab_5 = new QWidget( privateTabWidget, "tab_5" );
    tabLayout_5 = new QVBoxLayout( tab_5 ); 
    tabLayout_5->setSpacing( 6 );
    tabLayout_5->setMargin( 11 );

    Layout15_2 = new QHBoxLayout; 
    Layout15_2->setSpacing( 6 );
    Layout15_2->setMargin( 0 );
    QSpacerItem* spacer_6 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout15_2->addItem( spacer_6 );

    TextLabel1_3 = new QLabel( tab_5, "TextLabel1_3" );
    TextLabel1_3->setText( tr( "Version" ) );
    Layout15_2->addWidget( TextLabel1_3 );

    versionLineEdit = new QLineEdit( tab_5, "versionLineEdit" );
    versionLineEdit->setMaximumSize( QSize( 40, 32767 ) );
    versionLineEdit->setText( tr( "1.94" ) );
    Layout15_2->addWidget( versionLineEdit );
    tabLayout_5->addLayout( Layout15_2 );

    helpBrower = new QTextBrowser( tab_5, "helpBrower" );
    helpBrower->setText( tr( "" ) );
    tabLayout_5->addWidget( helpBrower );
    privateTabWidget->insertTab( tab_5, tr( "Etc" ) );
    tabLayout_3->addWidget( privateTabWidget );
    mainTabWidget->insertTab( tab_3, tr( "Etc" ) );

    tab_6 = new QWidget( mainTabWidget, "tab_6" );
    tabLayout_6 = new QVBoxLayout( tab_6 ); 
    tabLayout_6->setSpacing( 0 );
    tabLayout_6->setMargin( 20 );

    printLabel = new QLabel( tab_6, "printLabel" );
    printLabel->setMaximumSize( QSize( 32767, 50 ) );
    printLabel->setFrameShape( QLabel::Box );
    printLabel->setFrameShadow( QLabel::Raised );
    printLabel->setText( tr( "Hello?" ) );
    printLabel->setAlignment( int( QLabel::AlignCenter ) );
    tabLayout_6->addWidget( printLabel );

    Layout4 = new QHBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );

    TextLabel1 = new QLabel( tab_6, "TextLabel1" );
    TextLabel1->setText( tr( "UserID" ) );
    Layout4->addWidget( TextLabel1 );
    QSpacerItem* spacer_7 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout4->addItem( spacer_7 );

    idLineEdit = new QLineEdit( tab_6, "idLineEdit" );
    Layout4->addWidget( idLineEdit );
    tabLayout_6->addLayout( Layout4 );

    Layout5 = new QHBoxLayout; 
    Layout5->setSpacing( 6 );
    Layout5->setMargin( 0 );

    TextLabel2_2 = new QLabel( tab_6, "TextLabel2_2" );
    TextLabel2_2->setText( tr( "PassWord" ) );
    Layout5->addWidget( TextLabel2_2 );
    QSpacerItem* spacer_8 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout5->addItem( spacer_8 );

    passwdLineEdit = new QLineEdit( tab_6, "passwdLineEdit" );
    passwdLineEdit->setEchoMode( QLineEdit::Password );
    Layout5->addWidget( passwdLineEdit );
    tabLayout_6->addLayout( Layout5 );

    Layout6 = new QHBoxLayout; 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );

    infoSaveCheckBox = new QCheckBox( tab_6, "infoSaveCheckBox" );
    infoSaveCheckBox->setText( tr( "memo" ) );
    Layout6->addWidget( infoSaveCheckBox );

    connectPBtn = new QPushButton( tab_6, "connectPBtn" );
    connectPBtn->setText( tr( "connect" ) );
    Layout6->addWidget( connectPBtn );
    tabLayout_6->addLayout( Layout6 );

    Line7 = new QFrame( tab_6, "Line7" );
    Line7->setFrameStyle( QFrame::HLine | QFrame::Sunken );
    tabLayout_6->addWidget( Line7 );

    UzooPixmap = new QLabel( tab_6, "UzooPixmap" );
    UzooPixmap->setScaledContents( TRUE );
    tabLayout_6->addWidget( UzooPixmap );
    mainTabWidget->insertTab( tab_6, tr( "Connect" ) );
    UzooMainLayout->addWidget( mainTabWidget );

    Line1 = new QFrame( this, "Line1" );
    Line1->setFrameStyle( QFrame::HLine | QFrame::Sunken );
    UzooMainLayout->addWidget( Line1 );

    Layout1 = new QHBoxLayout; 
    Layout1->setSpacing( 6 );
    Layout1->setMargin( 0 );

    progLCD = new QLCDNumber( this, "progLCD" );
    Layout1->addWidget( progLCD );

    message1Label = new QLabel( this, "message1Label" );
    message1Label->setMaximumSize( QSize( 32767, 25 ) );
    message1Label->setFrameShape( QLabel::Box );
    message1Label->setFrameShadow( QLabel::Raised );
    message1Label->setText( tr( "" ) );
    Layout1->addWidget( message1Label );

    message2Label = new QLabel( this, "message2Label" );
    message2Label->setMaximumSize( QSize( 32767, 25 ) );
    message2Label->setFrameShape( QLabel::Box );
    message2Label->setFrameShadow( QLabel::Raised );
    message2Label->setText( tr( "" ) );
    Layout1->addWidget( message2Label );
    UzooMainLayout->addLayout( Layout1 );

    // tab order
    setTabOrder( idLineEdit, passwdLineEdit );
    setTabOrder( passwdLineEdit, connectPBtn );
    setTabOrder( connectPBtn, infoSaveCheckBox );
    setTabOrder( infoSaveCheckBox, mainTabWidget );
    setTabOrder( mainTabWidget, searchLineEdit );
    setTabOrder( searchLineEdit, searchPBtn );
    setTabOrder( searchPBtn, downloadListView );
    setTabOrder( downloadListView, uploadListView );
    setTabOrder( uploadListView, upFolderPBtn );
    setTabOrder( upFolderPBtn, upFolderComboBox );
    setTabOrder( upFolderComboBox, downFolderLineEdit );
    setTabOrder( downFolderLineEdit, downFolderPBtn );
    setTabOrder( downFolderPBtn, privateTabWidget );
    setTabOrder( privateTabWidget, myserver1SpinBox );
    setTabOrder( myserver1SpinBox, myserver2SpinBox );
    setTabOrder( myserver2SpinBox, userportSpinBox );
    setTabOrder( userportSpinBox, searchSpinBox );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UzooMain::~UzooMain()
{
    // no need to delete child widgets, Qt does it all for us
}

