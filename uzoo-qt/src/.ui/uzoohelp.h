/****************************************************************************
** Form interface generated from reading ui file 'help.ui'
**
** Created: Wed Feb 20 14:24:06 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef UZOOHELP_H
#define UZOOHELP_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QComboBox;
class QLabel;
class QTabWidget;
class QTextView;
class QWidget;

class UzooHelp : public QDialog
{ 
    Q_OBJECT

public:
    UzooHelp( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~UzooHelp();

    QTabWidget* helpTabWidget;
    QWidget* helpTab;
    QLabel* TextLabel1;
    QComboBox* helpBrowserComboBox;
    QLabel* helpLabel;
    QWidget* aboutTab;
    QLabel* aboutLabel;
    QWidget* developersTab;
    QTextView* develBrowser;
    QWidget* licenseTab;
    QTextView* licenseBrowser;

protected:
    QVBoxLayout* UzooHelpLayout;
    QVBoxLayout* helpTabLayout;
    QHBoxLayout* Layout1;
    QVBoxLayout* aboutTabLayout;
    QVBoxLayout* developersTabLayout;
    QVBoxLayout* licenseTabLayout;
};

#endif // UZOOHELP_H
