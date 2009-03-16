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
		if( ExplainID == 0)
		{
			StartBash();
		}
	//}
}

QString GetEFromNet::GetLastE()
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

QString GetEFromNet::Getfromfile()
{
	QString File = "data/bash/DownExp/Explain/chinese.txt";

	//QString File = "src/bash/DownExp/Explain/chinese.txt";
	
	QFile file(File);
	file.open(QFile::ReadOnly);
	QTextStream Insertlib(&file);
	QSqlQuery q;
	QString Explain = Insertlib.readLine();

	//qDebug() << Explain;	
	QString UpdateEx = "update ";
	UpdateEx = UpdateEx + TableName + "set Explain ='" + Explain + "' where Letter= '" + Letter + "'";
	q.exec(UpdateEx);
	QString UpdateEs = "update "; 
	UpdateEs = UpdateEs + TableName +" set ES = 1 where Letter = '" + Letter + "'";
	q.exec(UpdateEs);
	         
	return Explain;
}

void GetEFromNet::StartBash(QString letter)
{
	QString executable ="data/bash/DownExp/GE.sh";
	//QString executable ="src/bash/DownExp/GE.sh";
	if( !letter.isNull() )
	{
		Letter = letter;
		//qDebug("not blank!");
        }
	QProcess proc;
    QStringList arguments;
    arguments<<Letter;
    proc.start(executable, arguments);
    proc.closeWriteChannel();
    while (!proc.waitForFinished(20))
    {}

}

QString GetEFromNet::GetFromDB()
{
	QSqlQueryModel * LibModel = new QSqlQueryModel;
	QString model = "select * from ";
	model = model + TableName + " where Letter = '" + Letter + "'";
	LibModel->setQuery(model);
	
	QSqlRecord TableModel_Record = LibModel->record(0);
	
	return TableModel_Record.value("Explain").toString();	
}

