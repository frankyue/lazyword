#include "getallexp.h"

// place your code here

GetAllExp::GetAllExp(QString TN)//, QWidget * parent)  : QDialog(parent)
{
	TableName = TN;
	getallexplain();
}


int GetAllExp::getallexplain()
{	
	bool succe = true;
	
	GetEFromNet * GetE = new GetEFromNet(3,"a",TableName);		//see more about class GetEFromNet
	QSqlQueryModel LibTable;
    LibTable.setQuery("select * from "+ TableName +"");
    
    //create a progress to show the progress of getting the words' explanations
	QProgressDialog progress(tr("Get the words' explanation from the net..."),tr("cancel"),0,LibTable.rowCount(),this);
	progress.setWindowModality(Qt::WindowModal);
	
	
	for (int i = 0; i < LibTable.rowCount(); i++) 
	{
		progress.show();
		progress.setValue(i);
		qApp->processEvents();
		if( progress.wasCanceled() )
		{
			QMessageBox::information(0, tr("Error"),tr("You clicked the Cancel Button!"));
			succe = false;
			break;			
		}
			
		QSqlRecord LibTable_Record = LibTable.record(i);
		Letter = LibTable_Record.value("Letter").toString();
		GetE->StartBash(Letter);
		GetE->Getfromfile();
		succe = true;
	}	
	progress.setValue(LibTable.rowCount());
	
	if(succe)
	{
		QMessageBox::information(0, tr("Success"),tr("Successful!"));
	}
}
