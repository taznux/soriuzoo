/****************************************************************************
** Form interface generated from reading ui file 'mainwindow.ui'
**
** Created: Sun Feb 10 21:00:29 2002
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
class QCheckBox;
class QComboBox;
class QFrame;
class QLCDNumber;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QListView;
class QListViewItem;
class QPushButton;
class QSpinBox;
class QTabWidget;
class QTextBrowser;

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
    QPushButton* upFolderPBtn;
    QComboBox* upFolderComboBox;
    QLineEdit* downFolderLineEdit;
    QPushButton* downFolderPBtn;
    QTabWidget* privateTabWidget;
    QWidget* tab_4;
    QLabel* TextLabel1_2;
    QSpinBox* myserver1SpinBox;
    QLabel* TextLabel2;
    QSpinBox* myserver2SpinBox;
    QLabel* TextLabel3;
    QSpinBox* userportSpinBox;
    QLabel* TextLabel4;
    QSpinBox* searchSpinBox;
    QWidget* tab_5;
    QLabel* TextLabel1_3;
    QLineEdit* versionLineEdit;
    QTextBrowser* helpBrower;
    QWidget* tab_6;
    QLabel* printLabel;
    QLabel* TextLabel1;
    QLineEdit* idLineEdit;
    QLabel* TextLabel2_2;
    QLineEdit* passwdLineEdit;
    QCheckBox* infoSaveCheckBox;
    QPushButton* connectPBtn;
    QFrame* Line7;
    QLabel* UzooPixmap;
    QFrame* Line1;
    QLCDNumber* progLCD;
    QLabel* message1Label;
    QLabel* message2Label;

protected:
    QVBoxLayout* UzooMainLayout;
    QVBoxLayout* tabLayout;
    QHBoxLayout* Layout14;
    QHBoxLayout* Layout17;
    QVBoxLayout* Layout16;
    QVBoxLayout* Layout21;
    QVBoxLayout* tabLayout_2;
    QVBoxLayout* tabLayout_3;
    QHBoxLayout* Layout7;
    QHBoxLayout* Layout8;
    QVBoxLayout* tabLayout_4;
    QHBoxLayout* Layout13;
    QHBoxLayout* Layout14_2;
    QHBoxLayout* Layout15;
    QHBoxLayout* Layout16_2;
    QVBoxLayout* tabLayout_5;
    QHBoxLayout* Layout15_2;
    QVBoxLayout* tabLayout_6;
    QHBoxLayout* Layout4;
    QHBoxLayout* Layout5;
    QHBoxLayout* Layout6;
    QHBoxLayout* Layout1;
};

#endif // UZOOMAIN_H
