#include <QtGui>
#include <QPainter>


#include "LazyWord.h"
#include "sql.h"
#include "GetSelect.h"
#include "explain.h"
#include "updatelib.h"
#include "getallexp.h"

int LazyWord::Invertime = 10;
LazyWord::LazyWord( QWidget * parent ) : QDialog(parent) ,LID(0),CheckEnd(0),GetTheSlot(0)
{
	SqlOperate a;
	a.connectdatabase();
	RestoreConfig_color();
	RestoreConfigall();
    ConfigureUI();
    createActions();
    IconMenu();
	ShowIcon();
	
	connect(ActionRestore, SIGNAL(triggered()), this, SLOT(ShowNormal()));
	
	connect(UpdateLibButton, SIGNAL(clicked()), this, SLOT(updateLib()));
	connect(InsertLibButton, SIGNAL(clicked()), this, SLOT(InsertLib()));    
    connect(ShowTestButton, SIGNAL(clicked()), this, SLOT(ShowMessage()));
    connect(OkButton,SIGNAL(clicked()),this,SLOT(OkSubmit()));
    connect(AboutButton,SIGNAL(clicked()),this,SLOT(about()));
    connect(GetAllExplainButton,SIGNAL(clicked()),this,SLOT(getAllExplain()));
    connect(ChangeColorButton,SIGNAL(clicked()),this,SLOT(setshowcolor()));
	connect(ItimeBox,SIGNAL(valueChanged(int)),this,SLOT(changeItime(int)));
   
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(LetterClicked()));
     
    connect(show_AllBox, SIGNAL(toggled(bool)),this, SLOT(setBoxVisible(bool)));
    connect(show_StrangeBox, SIGNAL(toggled(bool)),this, SLOT(setBoxVisibleSingle()));
    connect(show_UnderstandBox, SIGNAL(toggled(bool)),this, SLOT(setBoxVisibleSingle()));
    connect(show_MasterBox, SIGNAL(toggled(bool)),this, SLOT(setBoxVisibleSingle()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ConfigureBox);
    setLayout(mainLayout);

    
    trayIcon->show();
    
    setWindowTitle(tr("LazyWord"));
    setGeometry(QRect(400, 200, 449, 407));
    resize(400, 300);
    
}

//----------------------------SLOT----------------------------
void LazyWord::changeItime(int i)
{
	Invertime = i;
}

void LazyWord::setshowcolor()
{
	QColor lor(colorselect);
	QColor color = QColorDialog::getColor( lor, this);
	if (color.isValid())
		{
			QSqlQuery q;
			q.exec("update LastConfig set Color = '"+color.name()+"' where ID = 1");
		}
	RestoreConfig_color();
}

void LazyWord::setBoxVisible(bool visible)
{
	show_StrangeBox->setChecked(false);
    show_UnderstandBox->setChecked(false);
	show_MasterBox->setChecked(false);
	
	show_StrangeBox->setEnabled(!visible);
	show_UnderstandBox->setEnabled(!visible);
	show_MasterBox->setEnabled(!visible);
}

void LazyWord::setBoxVisibleSingle()
{
	show_AllBox->setChecked(false);
	if( show_StrangeBox->isChecked() && show_UnderstandBox->isChecked() && show_MasterBox->isChecked() )
	{
		show_StrangeBox->setChecked(false);
    	show_UnderstandBox->setChecked(false);
		show_MasterBox->setChecked(false);
		
		show_AllBox->setChecked(true);
	}
}

void LazyWord::CloseDialogWindow(QCloseEvent *event)
{
    if (trayIcon->isVisible()) 
    {
        hide();
        event->ignore();
    }
}

void LazyWord::ShowIcon()
{
	QIcon icon;
    icon.addPixmap(QPixmap("data/images/tux.png"), QIcon::Normal, QIcon::Off);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
}

void LazyWord::ShowMessage()
{
	if( LID >= CheckEnd || ChenkTableName != WordLibBox->currentText())
	{
		LID = 0;
	}
	
	QSqlQueryModel * TableModel = GetLibModel();
	QSqlRecord TableModel_Record = TableModel->record(LID);
	
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(1);
	
   	ChenkTableName = WordLibBox->currentText();
	
	ES = TableModel_Record.value("ES").toInt();
	LetterToShow = TableModel_Record.value("Letter").toString();
	trayIcon->showMessage("", LetterToShow, icon,
                          StimeBox->value() * 1000);
    LID ++ ;

}

void LazyWord::LetterClicked()
{	
	GetEFromNet * GetE = new GetEFromNet(ES,LetterToShow,WordLibBox->currentText());
	QString ExplainShow = GetE->GetLastE();
        //QString Show;
        //Show = LetterToShow + ":\n\t" + ExplainShow ;
        //    QMessageBox::information(0, tr("Explain"),Show);

    showmessage * showWE = new showmessage(LetterToShow,ExplainShow,colorselect,0);
    showWE->show();
}

void LazyWord::getAllExplain()
{
	if( WordLibBox->currentText().isEmpty())
	{
		QMessageBox::critical(0,QObject::tr("Error!"),QObject::tr("Please choose a wordLib!"),QMessageBox::Cancel);
	}
	int check = warring();
	if( check == 1 ) 
	{
		GetAllExp * getall = new GetAllExp(WordLibBox->currentText());
	}
}

void LazyWord::updateLib()
{	
	if( WordLibBox->currentText().isEmpty())
	{
		QMessageBox::critical(0,QObject::tr("Error!"),QObject::tr("Please choose a wordLib!"),QMessageBox::Cancel);
	}
	else
	{
		updatelib * ul = new updatelib(WordLibBox->currentText());
		int accepted = ul->exec();
		if( accepted == 1)
		{
			QMessageBox::information(0, tr("Success"),
                             tr("Succeed to Update the WordLib!"));
		}
	}
}

void LazyWord::InsertLib()
{
	Inslib *avb = new Inslib(this);
	int accepted = avb->exec();
	if( accepted == 1)
	{
		QMessageBox::information(0, tr("Success"),
                             tr("Succeed to import the WordLib!"));
                             
		QString NewLib = avb->newlib();
		WordLibBox->addItem(NewLib);
	}
}

void LazyWord::OkSubmit()    //store the configure ,close the mainwindow and start to run the soft 
{
	if( WordLibBox->currentText().isEmpty())
	{
		QMessageBox::critical(0,QObject::tr("Error!"),QObject::tr("Please choose a wordLib!"),QMessageBox::Cancel);
	}
	else
	{
		if(!show_StrangeBox->isChecked() && !show_UnderstandBox->isChecked() && !show_MasterBox->isChecked() && !show_AllBox->isChecked())
		{
			QMessageBox::critical(0,QObject::tr("Error!"),QObject::tr("Please choose the Degree!"),QMessageBox::Cancel);
		}
		else
		{
			timer = new QTimer(this);
			timer->start(Invertime * 1000);
			GetTheSlot = 1;
			connect(timer,SIGNAL(timeout()),this,SLOT(StartToLazy()));
			reject();
		}
	}
}

void LazyWord::StartToLazy() //Good Function name
{
	//qDebug("%d",Invertime);
	if( GetTheSlot == 1 )
	{
		ShowMessage();
	}
}

void LazyWord::ShowNormal()
{
	GetTheSlot = 0;
	showNormal();
}

void LazyWord::about()
{
	QMessageBox msgBox;
	msgBox.setText(tr("\tLazyWord is based on the stardict at present(not all),which can help Lazy man like me to remember the word where you store inthe stardict and import them into LazyWord's Databases! \n"
                             "\tNow enjoy yourself!Enjoy Lazing!\n"
                                "\tCopyright © 2009-2010 frankyue\n"
                                "\tE-mail:frankyue1019@gmail.com"
                                ));
	msgBox.setDetailedText(tr("website: http://github.com/frankyue/lazyword/tree/master"));
	msgBox.setStandardButtons(QMessageBox::Ok );
	QPushButton *diag = msgBox.addButton(tr("Help"), QMessageBox::HelpRole);
	msgBox.exec();
	if (msgBox.clickedButton() == diag) 
		{
			QWidget *uiwidget= new QWidget(0,Qt::Dialog);
			ui.setupUi(uiwidget);
			//uiwidget->setGeometry(100,1000,1000,150);
			uiwidget->show();			
		}	
}

void LazyWord::storequit()				//store the confiugration and quit
{
	QSqlQuery q;
	q.prepare("UPDATE LastConfig SET LetterID = ? , ShowTime = ? , IntervalTime = ? , LibSelect = ? where ID = 1");
	q.bindValue(0,QVariant(LID));
	q.bindValue(1,QVariant(StimeBox->value()));
	q.bindValue(2,QVariant(ItimeBox->value()));
	q.bindValue(3,WordLibBox->currentText());
	q.exec();	
	QCoreApplication::quit();
}

void LazyWord::changetime()				//change the show time and Interval
{
	Invertime = ItimeBox->value();
}


//----------------Above slots---------------------

//----------------Flow UI -----------------------

void LazyWord::ConfigureUI()
{
	ConfigureBox = new QGroupBox(tr("Configure"));

    LibSelectLabel = new QLabel(tr("LibSelect:"));
	//WordLibBox = new QComboBox;	
	WordLibBox = WordLib();

    StimeLabel = new QLabel(tr("Showtime:"));
    ItimeLabel = new QLabel(tr("Invertaltime:"));

    StimeBox = new QSpinBox;
    StimeBox->setRange(5, 60);
    StimeBox->setSuffix(" s");
    StimeBox->setValue(Shtime);
    
    ItimeBox = new QSpinBox;
    ItimeBox->setRange(5, 180);
    ItimeBox->setSuffix(" s");
    ItimeBox->setValue(Invertime);
    
    DselectLabel = new QLabel(tr("Degree Select:"));
    show_StrangeBox = new QCheckBox(tr("Strange"));
    show_UnderstandBox = new QCheckBox(tr("Understand"));
	show_MasterBox = new QCheckBox(tr("Master"));
    show_AllBox = new QCheckBox(tr("All"));
    ShowTestButton = new QPushButton(tr("Test"));
    AboutButton = new QPushButton(tr("About"));
    InsertLibButton = new QPushButton(tr("Insert Lib"));
    OkButton = new QPushButton(tr("Start Lazy"));
    UpdateLibButton = new QPushButton(tr("Update Lib"));
    GetAllExplainButton = new QPushButton(tr("Get All Explain"));
    ChangeColorButton = new QPushButton(tr("Change Color"));
    //ShowTestButton->setDefault(true);

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(LibSelectLabel, 0, 0);
    messageLayout->addWidget(WordLibBox, 0, 1, 1, 2);
    messageLayout->addWidget(StimeLabel, 1, 0);
    messageLayout->addWidget(StimeBox, 1, 1);
    messageLayout->addWidget(ItimeLabel, 1, 3);
    messageLayout->addWidget(ItimeBox, 1, 4);
    messageLayout->addWidget(DselectLabel, 2, 0);
	messageLayout->addWidget(show_StrangeBox, 3, 1,1,1);
	messageLayout->addWidget(show_UnderstandBox, 3, 2,1,1);
	messageLayout->addWidget(show_MasterBox, 3, 3,1,1);
	messageLayout->addWidget(show_AllBox, 3, 4,1,1);
	messageLayout->addWidget(UpdateLibButton, 4, 1);
    messageLayout->addWidget(InsertLibButton, 4, 2);
    messageLayout->addWidget(OkButton, 4, 3);
    messageLayout->addWidget(ShowTestButton, 4, 4);
    messageLayout->addWidget(GetAllExplainButton,5,2);
    messageLayout->addWidget(AboutButton,5,0);
	messageLayout->addWidget(ChangeColorButton,5,1);
    
    messageLayout->setRowStretch(4, 1);

    
    ConfigureBox->setLayout(messageLayout);
}

void LazyWord::createActions()
{
    ActionRestore = new QAction(tr("&Restore"), this);
    connect(ActionRestore, SIGNAL(triggered()), this, SLOT(ShowNormal()));
    	
    ActionQuit = new QAction(tr("&Quit"), this);
    connect(ActionQuit, SIGNAL(triggered()), this, SLOT(storequit()));
}

void LazyWord::IconMenu()
{
    MenuIcon = new QMenu(this);
	MenuIcon->addAction(ActionRestore);
    MenuIcon->addSeparator();
    MenuIcon->addAction(ActionQuit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(MenuIcon);
}
//----------------Above UI -----------------------

//----------------Flow Function-------------------
int LazyWord::warring()
{
	QMessageBox msgBox;
	msgBox.setText("warring!");
	msgBox.setInformativeText("It may be take a long time and be sure you are connect to Internet!will you go on?");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	int ret = msgBox.exec();
	int check = 0;	 
	switch (ret) 
	{
		case QMessageBox::Ok:
       		check = 1;
	    	break;
    	case QMessageBox::Cancel:
       		check = 0;
	    	break;
	 }	
	return check;
}

QComboBox * LazyWord::WordLib()
{
	QComboBox *TablesComboBox = new QComboBox;
	QSqlQueryModel AllTable;
    AllTable.setQuery("select * from AllTables;");
    
    TablesComboBox->addItem(lastlib);
    QString Item = lastlib;
    
	for (int i = 0; i < AllTable.rowCount(); i++) 
	{
		QSqlRecord AllTable_Record = AllTable.record(i);
				
		if(lastlib != AllTable_Record.value("TableName"))
		{
			TablesComboBox->addItem(AllTable_Record.value("TableName").toString());
		}
	}

   	return TablesComboBox;   	
}

QSqlQueryModel * LazyWord::GetLibModel()			//Get the Date whic the user want to show
{
	GetSelect GS;
	int FS = GS.Select(show_StrangeBox->isChecked(),show_UnderstandBox->isChecked(),show_MasterBox->isChecked()
	,show_AllBox->isChecked());	
	//qDebug("FO = %d,IO = %d",FS,IO);
	QSqlQueryModel * LibModel = new QSqlQueryModel;
	QString model = "select * from ";	 

   	if( FS-4<=0 )
   	{
   		if( FS-4!=0)
   		{
   			model = model + WordLibBox->currentText() + " where Familiar =" + QString::number(FS);
  		}
  		else
  		{
  			model = model + WordLibBox->currentText();
 		}
  	}
  	else
  	{
		model = model + WordLibBox->currentText() + " where Familiar !=" + QString::number(FS-4);
 	}
 	LibModel->setQuery(model);
 	
 	CheckEnd = LibModel->rowCount();
 	
 	return LibModel; 	
}

void LazyWord::RestoreConfig_color()
{
	QSqlQueryModel GetTheLastconfig;
	GetTheLastconfig.setQuery("select * from LastConfig;");
	
    QSqlRecord Lastconfig_Record = GetTheLastconfig.record(0);
    colorselect = Lastconfig_Record.value("Color").toString();
}

void LazyWord::RestoreConfigall()
{
	QSqlQueryModel GetTheLastconfig;
	GetTheLastconfig.setQuery("select * from LastConfig;");
	
    QSqlRecord Lastconfig_Record = GetTheLastconfig.record(0);
    lastlib = Lastconfig_Record.value("LibSelect").toString();
    Shtime = Lastconfig_Record.value("ShowTime").toInt();
    Invertime = Lastconfig_Record.value("IntervalTime").toInt();
}
