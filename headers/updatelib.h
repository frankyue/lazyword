#ifndef __UPDATELIB_H__
#define __UPDATELIB_H__

// place your code here
#include <QDialog>
#include <QtGui>
#include <QtSql>

class updatelib : public QDialog
{
        Q_OBJECT
public:
        QString FileName() const;
        QString NewLibName() const;
        updatelib(QString WordLib, QWidget * parent = 0);
private slots:
        void Cancel(){ reject();}
        void browse();
        void libsubmit();
private:

	QLabel *LibFile;
	QLineEdit *LibFile_Box;
	QPushButton *SubmitButton;
	QPushButton *CancelButton;
	QPushButton *BrowseButton;
	
	QString wordlib;
};


#endif // __UPDATELIB_H__
