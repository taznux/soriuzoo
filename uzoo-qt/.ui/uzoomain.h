/****************************************************************************
** Form interface generated from reading ui file 'mainwindow.ui'
**
** Created: Sun Feb 17 10:29:02 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef UZOOMAIN_H
#define UZOOMAIN_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QFrame;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QListView;
class QListViewItem;
class QPushButton;
class QTabWidget;

class UzooMain : public QWidget
{ 
    Q_OBJECT

public:
    UzooMain( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~UzooMain();

    QTabWidget* mainTabWidget;
    QWidget* tab;
    QLineEdit* searchLineEdit;
    QPushButton* searchPBtn;
    QPushButton* stopPBtn;
    QListBox* searchListBox;
    QLabel* searchTitle;
    QLabel* searchSinger;
    QLabel* searchQuality;
    QLabel* searchDownLoad;
    QLabel* searchSize;
    QLabel* searchTime;
    QLabel* searchUser;
    QWidget* tab_2;
    QLabel* TextLabel5;
    QListView* downloadListView;
    QLabel* TextLabel6;
    QListView* uploadListView;
    QWidget* tab_3;
    QPushButton* configPBtn;
    QPushButton* appearanceConfigPBtn;
    QWidget* tab_4;
    QLabel* printLabel;
    QLabel* TextLabel1;
    QLineEdit* idLineEdit;
    QLabel* TextLabel2_2;
    QLineEdit* passwdLineEdit;
    QPushButton* connectPBtn;
    QFrame* Line7;
    QLabel* UzooPixmap;
    QFrame* Line1;
    QLabel* message0Label;
    QLabel* message1Label;

protected:
    QVBoxLayout* UzooMainLayout;
    QVBoxLayout* tabLayout;
    QHBoxLayout* Layout14;
    QHBoxLayout* Layout17;
    QVBoxLayout* Layout16;
    QVBoxLayout* Layout21;
    QVBoxLayout* tabLayout_2;
    QVBoxLayout* tabLayout_3;
    QVBoxLayout* tabLayout_4;
    QHBoxLayout* Layout4;
    QHBoxLayout* Layout5;
    QHBoxLayout* Layout6;
    QHBoxLayout* Layout10;
};

#endif // UZOOMAIN_H
