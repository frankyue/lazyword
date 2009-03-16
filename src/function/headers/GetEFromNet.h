#ifndef __GETEFROMNET_H__
#define __GETEFROMNET_H__

//#include "GetEFromNet.h"
#include <QFile>
#include <QtSql>
#include <QProcess>
#include <QSqlQueryModel>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDialog>
#include <QtGui>
#include <QProgressDialog>
// place your code here

class GetEFromNet
{
public:
	GetEFromNet(int EID,QString letter,QString TN);
	QString GetLastE();
	QString Getfromfile();
	void StartBash(QString letter = 0);
	QString GetFromDB();	
	
	//void getallexplain();
private:
	int ExplainID;
	int LetterID;
	QString TableName;
	QString Letter;
};
#endif // __GETEFROMNET_H__
