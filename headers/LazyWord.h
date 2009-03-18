#ifndef LAZYWORD_H
#define LAZYWORD_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QSqlQueryModel>
#include "GetEFromNet.h"
#include "showmessage.h"
#include "ui_lazywordhelp.h"

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;

QT_END_NAMESPACE

#include "inslib.h"




class LazyWord : public QDialog
{
    Q_OBJECT
public:
    LazyWord(QWidget * parent = 0);
protected:
    void CloseDialogWindow(QCloseEvent *event);
private slots:
    void ShowIcon();
    void ShowMessage();
    void LetterClicked();
    void InsertLib();
    void OkSubmit();
    void StartToLazy();    
    void ShowNormal();
    void setBoxVisible(bool visible);
    void setBoxVisibleSingle();
    void updateLib();
    void getAllExplain();
    void about();
    void storequit();
    void changetime();
    void setshowcolor();
    void changeItime(int i);
    
    void remind();
private:
    void ConfigureUI();
    void createActions();
    void IconMenu();
    int warring();
    void RestoreConfig_color();
    void RestoreConfigall();
    
    QComboBox * WordLib();
    QSqlQueryModel * GetLibModel();
   	
    QCheckBox *showIconCheckBox;
    QCheckBox *show_StrangeBox;
    QCheckBox *show_UnderstandBox;
    QCheckBox *show_MasterBox;
    QCheckBox *show_AllBox;
    QGroupBox *ConfigureBox;
    QLabel *LibSelectLabel;
    QLabel *StimeLabel;
    QLabel *ItimeLabel;
    QLabel *DselectLabel;
    
    QComboBox * WordLibBox;    
    QSpinBox *StimeBox;
    QSpinBox *ItimeBox;
    
    QPushButton *InsertLibButton;
    QPushButton *OkButton;
    QPushButton *ShowTestButton;
    QPushButton *AboutButton;
    QPushButton *UpdateLibButton;
    QPushButton *GetAllExplainButton;
    QPushButton *ChangeColorButton;

    QAction *ActionRestore;
    QAction *ActionQuit;

    QSystemTrayIcon *trayIcon;
    QMenu *MenuIcon;
    
    QTimer *timer;
    QTimer *T;
//-----------------------Test-------------------
	QLabel *show1;
	QLabel *show2;
	QLabel *show3;
	QLabel *show4;
	QLineEdit *show5;
//-----------------------Test-------------------

	static int Invertime;
	int Shtime;
    int ES;
    int LID;
    int CheckEnd;					//The last LID
    QString ChenkTableName;			//Get The TableID
    int GetTheSlot;					//The variable to control the word whether start to show on not
    QString LetterToShow;

    QString colorselect;
	QString lastlib;    
	
	Ui_Form ui;
    
};


#endif
