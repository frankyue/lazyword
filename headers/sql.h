#ifndef SQL_H
#define SQL_H

#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QtSql>

class SqlOperate
{
public:
	void connectdatabase();
};

void SqlOperate::connectdatabase()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setHostName("localhost");
    db.setDatabaseName("data/Letter");
    db.open();
}

#endif