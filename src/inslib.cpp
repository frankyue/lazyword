#include "inslib.h"

Inslib::Inslib(QWidget * parent) : QDialog(parent)
{
	//the constructed function just produce the UI
	LibFile = new QLabel("FileName");
	LibNewName = new QLabel("NewName");
	LibFile_Box = new QLineEdit();
	LibNewName_Edit = new QLineEdit();
	SubmitButton = new QPushButton("Submit");
	CancelButton = new QPushButton("Cancel");
	BrowseButton = new QPushButton("Browse");	
	
	connect(BrowseButton, SIGNAL(clicked()), this, SLOT(browse()));
	connect(SubmitButton, SIGNAL(clicked()), this, SLOT(libsubmit()));
	connect(CancelButton, SIGNAL(clicked()), this, SLOT(Cancel()));
    QGridLayout *gridlayout = new QGridLayout;
	QHBoxLayout *hboxlayout = new QHBoxLayout;
    QVBoxLayout *vboxlayout = new QVBoxLayout;
	
	gridlayout->addWidget(LibFile,0,0,1,1);
	gridlayout->addWidget(LibFile_Box,0,2,1,6);
	gridlayout->addWidget(BrowseButton,0,9,1,1);
	gridlayout->addWidget(LibNewName,1,0,1,1);
	gridlayout->addWidget(LibNewName_Edit,1,2,1,3);
	
	hboxlayout->addWidget(SubmitButton);
	hboxlayout->addWidget(CancelButton);
	
	vboxlayout->addLayout(gridlayout);
	vboxlayout->addLayout(hboxlayout);
	
	setLayout(vboxlayout);
	
}


void Inslib::browse()		//function like the name browse the file
{
	QString Filename = QFileDialog::getOpenFileName (this,
                                tr("FindFile"), QDir::currentPath());
    if (!Filename.isEmpty()) 
    {
    	LibFile_Box->setText(Filename);
    	//LibFile_Box->setCurrentIndex(LibFile_Box->currentIndex() + 1);
    }
}

void Inslib::libsubmit()
{
	QSqlQuery q;
		
	if(LibNewName_Edit->text().isEmpty() || LibFile_Box->text().isEmpty())
	{
		QMessageBox::critical(0,QObject::tr("Error"),QObject::tr("Please Fill them all!"),QMessageBox::Cancel);
	}
	else
	{
		bool NoErr;
		
    	QString createtable = "CREATE TABLE ";
    	QString createpart = " (IDLetter integer not null PRIMARY KEY AUTOINCREMENT,Letter VARCHAR(45) NOT NULL,Familiar INTEGER NOT NULL DEFAULT 1,Explain VARCHAR(45),ES INTEGER NOT NULL DEFAULT 0);";
   		createtable += LibNewName_Edit->text();
		createtable += createpart;
		//insert new wordlib's sql language
			
		NoErr = q.exec(createtable);
		
		if(NoErr)
		{		
			//if no err start to insert the word from the file
			QString InsertWord;
			QFile file(LibFile_Box->text());
			file.open(QFile::ReadOnly);
    		QTextStream Insertlib(&file);
    		
			for(int i = 0; !Insertlib.atEnd(); i++)
    		{    
    			InsertWord = Insertlib.readLine();
    			q.exec("select * from " +LibNewName_Edit->text()+" where Letter = '" +InsertWord +"'");
    			bool d = q.next();					
				if(!d)											//Check if the word exist!
				{
					q.exec("insert into "+LibNewName_Edit->text()+"(Letter,Explain) values('"+InsertWord+"','No Explanation')");
				}
			}
			QString Tablename = "insert into AllTables(TableName) values('";
			Tablename = Tablename + LibNewName_Edit->text() + " ')" ;
			q.exec(Tablename);
			
			QDialog::accept();
		}
		else
		{
			QMessageBox::critical(0,QObject::tr("Error"),QObject::tr("The Name is exist!"),QMessageBox::Cancel);
			LibNewName_Edit->clear();
		}
	}
}

QString Inslib::newlib()
{
	return LibNewName_Edit->text();
}



//-----------------just test at first by author-------------------
void Inslib::test()
{
	bool ab;
	QSqlQuery q;
	ab = q.exec(" create table aaa(id integer)");
	if(!ab)
	{
		qDebug("wrong!");
	}
}


//-----------------------above slot---------------------	
