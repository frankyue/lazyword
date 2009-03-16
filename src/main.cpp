#include <QtGui>

#include "LazyWord.h"
#include "Initial.h"


int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(LazyWord);
	
	//QTranslator translator;
	//translator.load("translate/" + QLocale::system().name());
	
	QApplication app(argc, argv);
	//app.installTranslator(&translator);
    QApplication::setQuitOnLastWindowClosed(false);
	
	InitialLR intial;	
    LazyWord window;
    window.show();
    return app.exec();
}
