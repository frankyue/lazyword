#include "explain.h"

ExplainDialog::ExplainDialog(QWidget * parent) : QDialog(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	//QComboBox * CreateExplainBox();
	//QComboBox * CreateSaveDegreeBox();
	CreateSaveDegreeBox();
	mainLayout->addWidget(SaveDegreeBox);
    setLayout(mainLayout);

    setWindowTitle(tr("show_SoftName"));
    resize(400, 300);
//	resize()			
}

//----------------------Flow UI Create---------------------
//QGroupBox * ExplainDialog::CreateExplainBox()
//{
	//
//}

void ExplainDialog::CreateSaveDegreeBox()
{
	SaveDegreeBox = new QGroupBox(this);
    //SaveDegreeBox->setGeometry(QRect(10, 80, 351, 61));
    StrangeRadioButton = new QRadioButton(SaveDegreeBox);
    StrangeRadioButton->setText(tr("StrangeRadioButton"));
    //StrangeRadioButton->setGeometry(QRect(10, 10, 99, 21));
    UnderstandRadioButton = new QRadioButton(SaveDegreeBox);
    UnderstandRadioButton->setText(tr("UnderstandRadioButton"));
    //UnderstandRadioButton->setGeometry(QRect(120, 10, 99, 21));
    MasterRadioButton = new QRadioButton(SaveDegreeBox);
    MasterRadioButton->setText(tr("MasterRadioButton"));
    //MasterRadioButton->setGeometry(QRect(240, 10, 99, 21));
    SaveButton = new QPushButton(SaveDegreeBox);
    SaveButton->setText(tr("SaveButton"));
    //SaveButton->setGeometry(QRect(40, 30, 102, 26));
    CancelButton = new QPushButton(SaveDegreeBox);
    CancelButton->setText(tr("CancelButton"));
    //CancelButton->setGeometry(QRect(210, 30, 102, 26));
}
//----------------------Above UI Create---------------------
// place your code here
