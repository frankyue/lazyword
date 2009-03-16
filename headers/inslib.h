#ifndef INSLIB_H
#define INSLIB_H


#include <QDialog>
#include <QtGui>
#include <QtSql>
QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
class QGridLayout;
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QHoverEvent>
QT_END_NAMESPACE


class Inslib : public QDialog
{
        Q_OBJECT
public:
        QString FileName() const;
        QString NewLibName() const;
        Inslib( QWidget * parent = 0);
        QString newlib();
private slots:
        void Cancel(){ reject();}
        void browse();
        void libsubmit();
        void test();
private:

	QLabel *LibFile;
	QLabel *LibNewName;
	QLineEdit *LibFile_Box;
	QLineEdit *LibNewName_Edit;
	QPushButton *SubmitButton;
	QPushButton *CancelButton;
	QPushButton *BrowseButton;
};

#endif