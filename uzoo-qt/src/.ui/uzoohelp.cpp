/****************************************************************************
** Form implementation generated from reading ui file 'help.ui'
**
** Created: Wed Feb 20 14:24:06 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uzoohelp.h"

#include <qcombobox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qtextview.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a UzooHelp which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
UzooHelp::UzooHelp( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "UzooHelp" );
    resize( 470, 322 ); 
    setCaption( tr( "Help Window" ) );
    UzooHelpLayout = new QVBoxLayout( this ); 
    UzooHelpLayout->setSpacing( 6 );
    UzooHelpLayout->setMargin( 11 );

    helpTabWidget = new QTabWidget( this, "helpTabWidget" );

    helpTab = new QWidget( helpTabWidget, "helpTab" );
    helpTabLayout = new QVBoxLayout( helpTab ); 
    helpTabLayout->setSpacing( 6 );
    helpTabLayout->setMargin( 11 );

    Layout1 = new QHBoxLayout; 
    Layout1->setSpacing( 6 );
    Layout1->setMargin( 0 );

    TextLabel1 = new QLabel( helpTab, "TextLabel1" );
    TextLabel1->setText( tr( "GoTo HomePage" ) );
    Layout1->addWidget( TextLabel1 );

    helpBrowserComboBox = new QComboBox( FALSE, helpTab, "helpBrowserComboBox" );
    helpBrowserComboBox->insertItem( tr( "http://sf.net/projects/soriuzoo" ) );
    helpBrowserComboBox->insertItem( tr( "http://sonegy.home.uos.ac.kr/soriuzoo" ) );
    helpBrowserComboBox->insertItem( tr( "http://soribada.kldp.org" ) );
    helpBrowserComboBox->insertItem( tr( "http://www.soribada.com" ) );
    Layout1->addWidget( helpBrowserComboBox );
    helpTabLayout->addLayout( Layout1 );

    helpLabel = new QLabel( helpTab, "helpLabel" );
    helpLabel->setFrameShape( QLabel::Box );
    helpLabel->setFrameShadow( QLabel::Raised );
    helpLabel->setText( tr( "TextLabel2" ) );
    helpTabLayout->addWidget( helpLabel );
    helpTabWidget->insertTab( helpTab, tr( "Help" ) );

    aboutTab = new QWidget( helpTabWidget, "aboutTab" );
    aboutTabLayout = new QVBoxLayout( aboutTab ); 
    aboutTabLayout->setSpacing( 6 );
    aboutTabLayout->setMargin( 11 );

    aboutLabel = new QLabel( aboutTab, "aboutLabel" );
    aboutLabel->setFrameShape( QLabel::Box );
    aboutLabel->setFrameShadow( QLabel::Raised );
    aboutLabel->setText( tr( "TextLabel1" ) );
    aboutTabLayout->addWidget( aboutLabel );
    helpTabWidget->insertTab( aboutTab, tr( "About this" ) );

    developersTab = new QWidget( helpTabWidget, "developersTab" );
    developersTabLayout = new QVBoxLayout( developersTab ); 
    developersTabLayout->setSpacing( 6 );
    developersTabLayout->setMargin( 11 );

    develBrowser = new QTextView( developersTab, "develBrowser" );
    developersTabLayout->addWidget( develBrowser );
    helpTabWidget->insertTab( developersTab, tr( "Developers" ) );

    licenseTab = new QWidget( helpTabWidget, "licenseTab" );
    licenseTabLayout = new QVBoxLayout( licenseTab ); 
    licenseTabLayout->setSpacing( 6 );
    licenseTabLayout->setMargin( 11 );

    licenseBrowser = new QTextView( licenseTab, "licenseBrowser" );
    licenseTabLayout->addWidget( licenseBrowser );
    helpTabWidget->insertTab( licenseTab, tr( "License" ) );
    UzooHelpLayout->addWidget( helpTabWidget );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UzooHelp::~UzooHelp()
{
    // no need to delete child widgets, Qt does it all for us
}

