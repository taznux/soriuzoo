/****************************************************************************
** Form implementation generated from reading ui file 'configure.ui'
**
** Created: Wed Feb 20 14:24:06 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uzooconfig.h"

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a UzooConfig which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
UzooConfig::UzooConfig( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "UzooConfig" );
    resize( 358, 281 ); 
    setCaption( tr( "Enviroment Configration" ) );
    UzooConfigLayout = new QVBoxLayout( this ); 
    UzooConfigLayout->setSpacing( 6 );
    UzooConfigLayout->setMargin( 11 );

    configureTabWidget = new QTabWidget( this, "configureTabWidget" );

    tab = new QWidget( configureTabWidget, "tab" );
    tabLayout = new QVBoxLayout( tab ); 
    tabLayout->setSpacing( 6 );
    tabLayout->setMargin( 11 );

    GroupBox1 = new QGroupBox( tab, "GroupBox1" );
    GroupBox1->setTitle( tr( "MyServer" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QVBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 11 );

    Layout13 = new QHBoxLayout; 
    Layout13->setSpacing( 6 );
    Layout13->setMargin( 0 );

    TextLabel1_2 = new QLabel( GroupBox1, "TextLabel1_2" );
    TextLabel1_2->setText( tr( "Biggest connect by One Client" ) );
    Layout13->addWidget( TextLabel1_2 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout13->addItem( spacer );

    myserver1SpinBox = new QSpinBox( GroupBox1, "myserver1SpinBox" );
    myserver1SpinBox->setEnabled( FALSE );
    myserver1SpinBox->setValue( 3 );
    Layout13->addWidget( myserver1SpinBox );
    GroupBox1Layout->addLayout( Layout13 );

    Layout14 = new QHBoxLayout; 
    Layout14->setSpacing( 6 );
    Layout14->setMargin( 0 );

    TextLabel2 = new QLabel( GroupBox1, "TextLabel2" );
    TextLabel2->setText( tr( "Biggest connect of Every" ) );
    Layout14->addWidget( TextLabel2 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout14->addItem( spacer_2 );

    myserver2SpinBox = new QSpinBox( GroupBox1, "myserver2SpinBox" );
    myserver2SpinBox->setEnabled( FALSE );
    myserver2SpinBox->setValue( 6 );
    Layout14->addWidget( myserver2SpinBox );
    GroupBox1Layout->addLayout( Layout14 );

    Layout15 = new QHBoxLayout; 
    Layout15->setSpacing( 6 );
    Layout15->setMargin( 0 );

    TextLabel3 = new QLabel( GroupBox1, "TextLabel3" );
    TextLabel3->setText( tr( "User Port" ) );
    Layout15->addWidget( TextLabel3 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout15->addItem( spacer_3 );

    userportSpinBox = new QSpinBox( GroupBox1, "userportSpinBox" );
    userportSpinBox->setMaxValue( 9999 );
    userportSpinBox->setMinValue( 9001 );
    Layout15->addWidget( userportSpinBox );
    GroupBox1Layout->addLayout( Layout15 );

    Layout16 = new QHBoxLayout; 
    Layout16->setSpacing( 6 );
    Layout16->setMargin( 0 );

    TextLabel4 = new QLabel( GroupBox1, "TextLabel4" );
    TextLabel4->setText( tr( "Biggest search" ) );
    Layout16->addWidget( TextLabel4 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout16->addItem( spacer_4 );

    searchSpinBox = new QSpinBox( GroupBox1, "searchSpinBox" );
    searchSpinBox->setMaxValue( 1000 );
    searchSpinBox->setMinValue( 100 );
    searchSpinBox->setLineStep( 10 );
    searchSpinBox->setValue( 500 );
    Layout16->addWidget( searchSpinBox );
    GroupBox1Layout->addLayout( Layout16 );
    tabLayout->addWidget( GroupBox1 );
    configureTabWidget->insertTab( tab, tr( "MyServer" ) );

    tab_2 = new QWidget( configureTabWidget, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2 ); 
    tabLayout_2->setSpacing( 6 );
    tabLayout_2->setMargin( 11 );

    GroupBox3 = new QGroupBox( tab_2, "GroupBox3" );
    GroupBox3->setTitle( tr( "Path" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QVBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 11 );

    Layout7_2 = new QHBoxLayout; 
    Layout7_2->setSpacing( 6 );
    Layout7_2->setMargin( 0 );

    upFolderPBtn = new QPushButton( GroupBox3, "upFolderPBtn" );
    upFolderPBtn->setEnabled( FALSE );
    upFolderPBtn->setText( tr( "UpLoad Folder" ) );
    Layout7_2->addWidget( upFolderPBtn );
    QSpacerItem* spacer_5 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout7_2->addItem( spacer_5 );
    GroupBox3Layout->addLayout( Layout7_2 );

    upFolderComboBox = new QComboBox( FALSE, GroupBox3, "upFolderComboBox" );
    upFolderComboBox->setEnabled( FALSE );
    upFolderComboBox->setEditable( FALSE );
    GroupBox3Layout->addWidget( upFolderComboBox );

    Layout17_2 = new QHBoxLayout; 
    Layout17_2->setSpacing( 6 );
    Layout17_2->setMargin( 0 );

    downFolderPBtn = new QPushButton( GroupBox3, "downFolderPBtn" );
    downFolderPBtn->setText( tr( "DownLoad Folder" ) );
    Layout17_2->addWidget( downFolderPBtn );
    QSpacerItem* spacer_6 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout17_2->addItem( spacer_6 );
    GroupBox3Layout->addLayout( Layout17_2 );

    downFolderLineEdit = new QLineEdit( GroupBox3, "downFolderLineEdit" );
    GroupBox3Layout->addWidget( downFolderLineEdit );
    tabLayout_2->addWidget( GroupBox3 );
    configureTabWidget->insertTab( tab_2, tr( "Path" ) );

    tab_3 = new QWidget( configureTabWidget, "tab_3" );
    tabLayout_3 = new QVBoxLayout( tab_3 ); 
    tabLayout_3->setSpacing( 6 );
    tabLayout_3->setMargin( 11 );

    ButtonGroup1 = new QButtonGroup( tab_3, "ButtonGroup1" );
    ButtonGroup1->setTitle( tr( "Default MP3 Player" ) );
    ButtonGroup1->setColumnLayout(0, Qt::Vertical );
    ButtonGroup1->layout()->setSpacing( 0 );
    ButtonGroup1->layout()->setMargin( 0 );
    ButtonGroup1Layout = new QVBoxLayout( ButtonGroup1->layout() );
    ButtonGroup1Layout->setAlignment( Qt::AlignTop );
    ButtonGroup1Layout->setSpacing( 6 );
    ButtonGroup1Layout->setMargin( 11 );

    Layout10_2 = new QHBoxLayout; 
    Layout10_2->setSpacing( 6 );
    Layout10_2->setMargin( 0 );

    playerLineEdit = new QLineEdit( ButtonGroup1, "playerLineEdit" );
    playerLineEdit->setText( tr( "xmms" ) );
    Layout10_2->addWidget( playerLineEdit );

    findplayerPBtn = new QPushButton( ButtonGroup1, "findplayerPBtn" );
    findplayerPBtn->setText( tr( "Find Player" ) );
    Layout10_2->addWidget( findplayerPBtn );
    ButtonGroup1Layout->addLayout( Layout10_2 );

    Layout11_2 = new QHBoxLayout; 
    Layout11_2->setSpacing( 6 );
    Layout11_2->setMargin( 0 );

    startPlayerCheckBox = new QCheckBox( ButtonGroup1, "startPlayerCheckBox" );
    startPlayerCheckBox->setText( tr( "As soon as run" ) );
    startPlayerCheckBox->setChecked( TRUE );
    Layout11_2->addWidget( startPlayerCheckBox );
    QSpacerItem* spacer_7 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout11_2->addItem( spacer_7 );

    TextLabel1_4 = new QLabel( ButtonGroup1, "TextLabel1_4" );
    TextLabel1_4->setText( tr( "seconds later" ) );
    Layout11_2->addWidget( TextLabel1_4 );

    laterPlayerSpinBox = new QSpinBox( ButtonGroup1, "laterPlayerSpinBox" );
    Layout11_2->addWidget( laterPlayerSpinBox );
    ButtonGroup1Layout->addLayout( Layout11_2 );
    tabLayout_3->addWidget( ButtonGroup1 );
    configureTabWidget->insertTab( tab_3, tr( "Default Player" ) );

    tab_4 = new QWidget( configureTabWidget, "tab_4" );
    tabLayout_4 = new QVBoxLayout( tab_4 ); 
    tabLayout_4->setSpacing( 6 );
    tabLayout_4->setMargin( 11 );

    GroupBox3_2 = new QGroupBox( tab_4, "GroupBox3_2" );
    GroupBox3_2->setTitle( tr( "User Infomation" ) );
    GroupBox3_2->setColumnLayout(0, Qt::Vertical );
    GroupBox3_2->layout()->setSpacing( 0 );
    GroupBox3_2->layout()->setMargin( 0 );
    GroupBox3_2Layout = new QVBoxLayout( GroupBox3_2->layout() );
    GroupBox3_2Layout->setAlignment( Qt::AlignTop );
    GroupBox3_2Layout->setSpacing( 6 );
    GroupBox3_2Layout->setMargin( 11 );

    Layout18_2 = new QGridLayout; 
    Layout18_2->setSpacing( 6 );
    Layout18_2->setMargin( 0 );

    TextLabel2_2_2 = new QLabel( GroupBox3_2, "TextLabel2_2_2" );
    TextLabel2_2_2->setText( tr( "PassWd" ) );

    Layout18_2->addWidget( TextLabel2_2_2, 1, 1 );

    passwdLineEdit = new QLineEdit( GroupBox3_2, "passwdLineEdit" );
    passwdLineEdit->setEnabled( TRUE );

    Layout18_2->addWidget( passwdLineEdit, 1, 2 );
    QSpacerItem* spacer_8 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout18_2->addItem( spacer_8, 1, 0 );

    TextLabel1_3_2 = new QLabel( GroupBox3_2, "TextLabel1_3_2" );
    TextLabel1_3_2->setText( tr( "UserID" ) );

    Layout18_2->addWidget( TextLabel1_3_2, 0, 1 );

    autoLoginCheckBox = new QCheckBox( GroupBox3_2, "autoLoginCheckBox" );
    autoLoginCheckBox->setText( tr( "Auto Login" ) );

    Layout18_2->addWidget( autoLoginCheckBox, 0, 0 );

    useridLineEdit = new QLineEdit( GroupBox3_2, "useridLineEdit" );

    Layout18_2->addWidget( useridLineEdit, 0, 2 );
    GroupBox3_2Layout->addLayout( Layout18_2 );

    Layout21_2 = new QHBoxLayout; 
    Layout21_2->setSpacing( 6 );
    Layout21_2->setMargin( 0 );

    versionCheckBox = new QCheckBox( GroupBox3_2, "versionCheckBox" );
    versionCheckBox->setText( tr( "version enable" ) );
    Layout21_2->addWidget( versionCheckBox );
    QSpacerItem* spacer_9 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout21_2->addItem( spacer_9 );

    versionLineEdit = new QLineEdit( GroupBox3_2, "versionLineEdit" );
    versionLineEdit->setEnabled( FALSE );
    versionLineEdit->setText( tr( "1.94" ) );
    Layout21_2->addWidget( versionLineEdit );
    GroupBox3_2Layout->addLayout( Layout21_2 );
    tabLayout_4->addWidget( GroupBox3_2 );
    configureTabWidget->insertTab( tab_4, tr( "User Info" ) );
    UzooConfigLayout->addWidget( configureTabWidget );

    Layout22 = new QHBoxLayout; 
    Layout22->setSpacing( 6 );
    Layout22->setMargin( 0 );
    QSpacerItem* spacer_10 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout22->addItem( spacer_10 );

    applyPBtn = new QPushButton( this, "applyPBtn" );
    applyPBtn->setText( tr( "&Apply" ) );
    Layout22->addWidget( applyPBtn );

    okPBtn = new QPushButton( this, "okPBtn" );
    okPBtn->setText( tr( "&Ok" ) );
    Layout22->addWidget( okPBtn );

    cancelPBtn = new QPushButton( this, "cancelPBtn" );
    cancelPBtn->setText( tr( "&Cancel" ) );
    Layout22->addWidget( cancelPBtn );
    UzooConfigLayout->addLayout( Layout22 );

    // signals and slots connections
    connect( applyPBtn, SIGNAL( clicked() ), this, SLOT( slotApply() ) );
    connect( okPBtn, SIGNAL( clicked() ), this, SLOT( slotOk() ) );
    connect( cancelPBtn, SIGNAL( clicked() ), this, SLOT( slotCancel() ) );

    // tab order
    setTabOrder( configureTabWidget, myserver1SpinBox );
    setTabOrder( myserver1SpinBox, myserver2SpinBox );
    setTabOrder( myserver2SpinBox, userportSpinBox );
    setTabOrder( userportSpinBox, searchSpinBox );
    setTabOrder( searchSpinBox, applyPBtn );
    setTabOrder( applyPBtn, okPBtn );
    setTabOrder( okPBtn, cancelPBtn );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UzooConfig::~UzooConfig()
{
    // no need to delete child widgets, Qt does it all for us
}

void UzooConfig::slotApply()
{
    qWarning( "UzooConfig::slotApply(): Not implemented yet!" );
}

void UzooConfig::slotCancel()
{
    qWarning( "UzooConfig::slotCancel(): Not implemented yet!" );
}

void UzooConfig::slotDownLoadFolder()
{
    qWarning( "UzooConfig::slotDownLoadFolder(): Not implemented yet!" );
}

void UzooConfig::slotFindPlayer()
{
    qWarning( "UzooConfig::slotFindPlayer(): Not implemented yet!" );
}

void UzooConfig::slotOk()
{
    qWarning( "UzooConfig::slotOk(): Not implemented yet!" );
}

