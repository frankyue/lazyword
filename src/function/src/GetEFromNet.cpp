#include "GetEFromNet.h"

// place your code here

GetEFromNet::GetEFromNet(int EID,QString letter,QString TN)
{
	TableName = TN;
	
	//if( EID == 3 )
	//{
		//getallexplain();
	//}
	//else
	//{
		ExplainID = EID;
		Letter = letter;
		
		if( ExplainID == 0)		//If the word has no explanation,first to get it from net then to store it!
		{
			StartBash();
		}
	//}
}

QString GetEFromNet::GetLastE()		//Get the explanation
{
	if( ExplainID == 1)
	{
		return GetFromDB();
	}
	else
	{
		return Getfromfile();	
	}
}

QString GetEFromNet::Getfromfile()			//get the explanation from the file which create by shell
{
	QString File = "data/bash/DownExp/Explain/chinese.txt";
	//how chinese.txt produce,just read the shell script GE.sh in 'data/bash/DownExp'

	//QString File = "src/bash/DownExp/Explain/chinese.txt";
	
	QFile file(File);
	file.open(QFile::ReadOnly);
	QTextStream Insertlib(&file);
	QSqlQuery q;
	QString Explain = Insertlib.readLine();

	//qDebug() << Explain;	
	QString UpdateEx = "update ";
	UpdateEx = UpdateEx + TableName + "set Explain ='" + Explain + "' where Letter= '" + Letter + "'";
	q.exec(UpdateEx);		//insert the explanation into the database
	
	QString UpdateEs = "update "; 
	UpdateEs = UpdateEs + TableName +" set ES = 1 where Letter = '" + Letter + "'";
	q.exec(UpdateEs);		//change the sign of explanation
	         
	return Explain;
}

void GetEFromNet::StartBash(QString letter)
{
	QString executable ="data/bash/DownExp/GE.sh";
	//the GE.sh accomplished to get the explanation's htm and get the explanation 
	
	//QString executable ="src/bash/DownExp/GE.sh";
	if( !letter.isNull() )
	{
		Letter = letter;
		//qDebug("not blank!");
    }
    
    //create a qt process to execute the shell 
	QProcess proc;
    QStringList arguments;
    arguments<<Letter;
    proc.start(executable, arguments);
    proc.closeWriteChannel();
    while (!proc.waitForFinished(20))
    {}

}

QString GetEFromNet::GetFromDB()		//If the EID = 1 which means the word's explanation is in the database!so get it!
{
	QSqlQueryModel * LibModel = new QSqlQueryModel;
	QString model = "select * from ";
	model = model + TableName + " where Letter = '" + Letter + "'";
	LibModel->setQuery(model);
	
	QSqlRecord TableModel_Record = LibModel->record(0);
	
	return TableModel_Record.value("Explain").toString();	
}

