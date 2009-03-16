#include "showmessage.h"

showmessage::showmessage(QString wordget,QString Explainget,QString color,QWidget * parent) : QWidget(parent,Qt::FramelessWindowHint)
{
	this->setAttribute(Qt::WA_NoSystemBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
    Word = wordget;
    Explain = Explainget;
    Color = color;
    this->resize(1000,150);
    this->setGeometry(100,1000,1000,150);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(close()));
		
	timer->start(5 * 1000);
}

void showmessage::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QFont a;//,b;
    a.setPointSize(35);
    //b.setPointSize(35);
    painter.setPen(QColor(Color));
    painter.setFont(a);
    painter.drawText(30, 50,Word);
    //painter.setFont(b);
    painter.drawText(150, 120,Explain);
    painter.end();
}

void showmessage::mouseDoubleClickEvent( QMouseEvent * event )
{
	close();
}
