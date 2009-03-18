#ifndef __INITIAL_H__
#define __INITIAL_H__

#include <QSqlDatabase>
#include <QSettings>

// place your code here
class InitialLR
{
public:
	InitialLR()			//check if the soft had initialed
	{
		readSetting();
		if( SqlInitial != "Yes" || SqlInitial.isEmpty() )
		{
			DatabaseInitial();
			SqlInitial = "Yes";
			saveSetting();
		}
	}
	QString SqlInitial;
	void DatabaseInitial();
	void saveSetting();
	void readSetting();
};

//----------save and read setting form the file of '~/.config/lazyword/lazyword.conf'----------
void InitialLR::saveSetting()
{
	QSettings settings("lazyword","lazyword");
 	settings.setValue("Config/SqlInitial",SqlInitial);
}
void InitialLR::readSetting()
{
	QSettings settings("lazyword","lazyword");
	SqlInitial = settings.value("Config/SqlInitial").toString();
}
//----------save and read setting form the file of '~/.config/lazyword/lazyword.conf'----------

void InitialLR::DatabaseInitial()
{	
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("data/Letter");
    db.open();
    QSqlQuery q;
	q.exec("CREATE TABLE AllTables(IDTable integer not null PRIMARY KEY AUTOINCREMENT,TableName VARCHAR(45) NOT NULL)");
	q.exec("CREATE TABLE LastConfig(ID integer Default 1 ,LetterID integer not null ,ShowTime Integer NOT NULL,IntervalTime INTEGER NOT NULL ,LibSelect Varchar(45) not null,Degree integer,Color Varchar(20))");
	q.exec("insert into LastConfig(LetterID,ShowTime,IntervalTime,LibSelect,Color) values(0,10,100,' ','#0000ff')");
	db.close();	
}

#endif // __INITIAL_H__
