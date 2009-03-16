#ifndef __EXPLAIN_H__
#define __EXPLAIN_H__

// place your code here
#include <QtGui>
#include <QDialog>

class ExplainDialog : public QDialog
{
	Q_OBJECT
public:
	ExplainDialog( QWidget * parent = 0);
	void CreateSaveDegreeBox();
private:
	QGroupBox *SaveDegreeBox;
    QRadioButton *StrangeRadioButton;
    QRadioButton *UnderstandRadioButton;
    QRadioButton *MasterRadioButton;
    QPushButton *SaveButton;
    QPushButton *CancelButton;
};

#endif // __EXPLAIN_H__
