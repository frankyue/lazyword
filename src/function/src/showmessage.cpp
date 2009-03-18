#include "showmessage.h"

//show the explanation like the word is written on the screen
showmessage::showmessage(QString wordget,QString Explainget,QString color,int fontsize,int time ,QWidget * parent) : QWidget(parent,Qt::FramelessWindowHint)
//the variable:word , explanation , color , fontsize , time to show and QWidget
{
	this->setAttribute(Qt::WA_NoSystemBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
 	//set the QDialog that show with a transparent background
    
    sizefont = fontsize;
    Word = wordget;
    Explain = Explainget;
    Color = color;
    
    this->resize(1000,150);
    this->setGeometry(100,1000,1000,150);
    
    //Follow:set the time of explanation's showing
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(close()));
	timer->start(time * 1000);
}

void showmessage::paintEvent(QPaintEvent * event)		//draw the explanation on the screen
{
    QPainter painter(this);
    QFont a;//,b;
    a.setPointSize(sizefont);
    //b.setPointSize(35);
    painter.setPen(QColor(Color));
    painter.setFont(a);
    painter.drawText(30, 50,Word);
    //painter.setFont(b);
    painter.drawText(150, 120,Explain);
    painter.end();
}

void showmessage::mouseDoubleClickEvent( QMouseEvent * event )  //doubleclick to close the qdialog
{
	close();
}
