#include "updatelib.h"
// place your code here

updatelib::updatelib(QString WordLib, QWidget * parent) : QDialog(parent)
{
	//constructed function just produce the UI
	wordlib = WordLib;
	LibFile = new QLabel(tr("Lib FileName"));
	LibFile_Box = new QLineEdit();
	SubmitButton = new QPushButton(tr("Submit"));
	CancelButton = new QPushButton(tr("Cancel"));
	BrowseButton = new QPushButton(tr("Browse"));	
	
	connect(BrowseButton, SIGNAL(clicked()), this, SLOT(browse()));
	connect(SubmitButton, SIGNAL(clicked()), this, SLOT(libsubmit()));
	connect(CancelButton, SIGNAL(clicked()), this, SLOT(Cancel()));
    QGridLayout *gridlayout = new QGridLayout;
	QHBoxLayout *hboxlayout = new QHBoxLayout;
    QVBoxLayout *vboxlayout = new QVBoxLayout;
	
	gridlayout->addWidget(LibFile,0,0,1,1);
	gridlayout->addWidget(LibFile_Box,0,2,1,6);
	gridlayout->addWidget(BrowseButton,0,9,1,1);
		
	hboxlayout->addWidget(SubmitButton);
	hboxlayout->addWidget(CancelButton);
	
	vboxlayout->addLayout(gridlayout);
	vboxlayout->addLayout(hboxlayout);
	
	setLayout(vboxlayout);
	
}


void updatelib::browse()		//function like the name browse the file
{
	QString Filename = QFileDialog::getOpenFileName (this,
                                tr("Find File"), QDir::currentPath());
    if (!Filename.isEmpty()) 
    {
    	LibFile_Box->setText(Filename);
    }
}

void updatelib::libsubmit()
{
	QSqlQuery q;
		
	if(LibFile_Box->text().isEmpty())
	{
		QMessageBox::critical(0,QObject::tr("show_Error"),QObject::tr("show_Error1 = Please Fill them all!"),QMessageBox::Cancel);
	}
	else
	{
		//bool NoErr;
  		QString InsertWord;
		QFile file(LibFile_Box->text());
		file.open(QFile::ReadOnly);
    	QTextStream Insertlib(&file);
    	//The insertlib get the file's point
    	
		for(int i = 0; !Insertlib.atEnd(); i++)		//if not at the end of file,go on
    	{    
    		InsertWord = Insertlib.readLine();
    		q.exec("select * from " + wordlib +" where Letter = '" +InsertWord +"'");
    		bool d = q.next();					
			if(!d)											//if the word not exist in the old wordlib,insert it!
			{
				q.exec("insert into "+ wordlib +"(Letter) values('"+InsertWord+"')");
			}
		}
		QDialog::accept();
	}
}

//-----------------------above slot---------------------	