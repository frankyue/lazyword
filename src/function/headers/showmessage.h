#ifndef SHOWMESSAGE_H
#define SHOWMESSAGE_H

#include <QtGui>

// place your code here
class showmessage: public QWidget
{
        Q_OBJECT
public:
        showmessage(QString wordget,QString Explainget,QString color,QWidget *parent = 0);
protected:
        void paintEvent(QPaintEvent *event);
        void mouseDoubleClickEvent( QMouseEvent * event );
private:
        QString Word;
        QString Explain;
        QString Color;
};


#endif // SHOWMESSAGE_H
