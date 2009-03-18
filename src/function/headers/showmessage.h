#ifndef SHOWMESSAGE_H
#define SHOWMESSAGE_H

#include <QtGui>

// place your code here
class showmessage: public QWidget
{
        Q_OBJECT
public:
        showmessage(QString wordget,QString Explainget,QString color,int fontsize = 35,int time = 5,QWidget *parent = 0);
protected:
        void paintEvent(QPaintEvent *event);
        void mouseDoubleClickEvent( QMouseEvent * event );
private:
        QString Word;
        QString Explain;
        QString Color;
        int sizefont;
};


#endif // SHOWMESSAGE_H
