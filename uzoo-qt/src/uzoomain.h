/****************************************************************************
** Form interface generated from reading ui file 'mainwindow.ui'
**
** Created: Wed Feb 20 14:30:23 2002
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
class ConditionListView;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class SearchListBox;

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
    QLabel* searchTitle;
    SearchListBox* searchListBox;
    QLabel* searchSinger;
    QLabel* searchQuality;
    QLabel* searchDownLoad;
    QLabel* searchSize;
    QLabel* searchUser;
    QLabel* searchTime;
    QWidget* tab_2;
    QLabel* TextLabel5;
    ConditionListView* downloadListView;
    QLabel* TextLabel6;
    ConditionListView* uploadListView;
    QWidget* tab_3;
    QPushButton* configPBtn;
    QPushButton* helpPBtn;
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
    QLabel* message0Label;
    QLabel* message1Label;
    QFrame* Line1;

protected:
    QVBoxLayout* UzooMainLayout;
    QVBoxLayout* tabLayout;
    QHBoxLayout* Layout14;
    QVBoxLayout* Layout9;
    QHBoxLayout* Layout9_2;
    QHBoxLayout* Layout10;
    QHBoxLayout* Layout11;
    QVBoxLayout* tabLayout_2;
    QVBoxLayout* tabLayout_3;
    QVBoxLayout* tabLayout_4;
    QHBoxLayout* Layout4;
    QHBoxLayout* Layout5;
    QHBoxLayout* Layout6;
    QHBoxLayout* Layout10_2;
};

#endif // UZOOMAIN_H
