/****************************************************************************
** Form interface generated from reading ui file 'configure.ui'
**
** Created: Sun Feb 17 10:29:03 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef UZOOCONFIG_H
#define UZOOCONFIG_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QButtonGroup;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QTabWidget;
class QTextView;
class QWidget;

class UzooConfig : public QDialog
{ 
    Q_OBJECT

public:
    UzooConfig( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~UzooConfig();

    QTabWidget* configureTabWidget;
    QWidget* tab;
    QGroupBox* GroupBox1;
    QLabel* TextLabel1_2;
    QSpinBox* myserver1SpinBox;
    QLabel* TextLabel2;
    QSpinBox* myserver2SpinBox;
    QLabel* TextLabel3;
    QSpinBox* userportSpinBox;
    QLabel* TextLabel4;
    QSpinBox* searchSpinBox;
    QGroupBox* GroupBox3;
    QPushButton* upFolderPBtn;
    QComboBox* upFolderComboBox;
    QPushButton* downFolderPBtn;
    QLineEdit* downFolderLineEdit;
    QGroupBox* GroupBox3_2;
    QLabel* TextLabel2_2;
    QLineEdit* passwdLineEdit;
    QLabel* TextLabel1_3;
    QCheckBox* autoLoginCheckBox;
    QLineEdit* useridLineEdit;
    QCheckBox* versionCheckBox;
    QLineEdit* versionLineEdit;
    QButtonGroup* ButtonGroup1;
    QLineEdit* playerLineEdit;
    QPushButton* findplayerPBtn;
    QCheckBox* startPlayerCheckBox;
    QLabel* TextLabel1;
    QSpinBox* laterPlayerSpinBox;
    QWidget* tab_2;
    QPushButton* helpPBtn;
    QTextView* licenseTextView;
    QTextView* developerTextView;
    QPushButton* applyPBtn;
    QPushButton* okPBtn;
    QPushButton* cancelPBtn;

public slots:
    virtual void slotApply();
    virtual void slotCancel();
    virtual void slotDownLoadFolder();
    virtual void slotFindPlayer();
    virtual void slotHelpBrowser();
    virtual void slotOk();

protected:
    QVBoxLayout* UzooConfigLayout;
    QGridLayout* tabLayout;
    QVBoxLayout* GroupBox1Layout;
    QHBoxLayout* Layout13;
    QHBoxLayout* Layout14;
    QHBoxLayout* Layout15;
    QHBoxLayout* Layout16;
    QVBoxLayout* GroupBox3Layout;
    QHBoxLayout* Layout7;
    QHBoxLayout* Layout17;
    QVBoxLayout* GroupBox3_2Layout;
    QGridLayout* Layout18;
    QHBoxLayout* Layout21;
    QVBoxLayout* ButtonGroup1Layout;
    QHBoxLayout* Layout10;
    QHBoxLayout* Layout11;
    QVBoxLayout* tabLayout_2;
    QHBoxLayout* Layout22;
};

#endif // UZOOCONFIG_H
