#include <QtCore/QCoreApplication>

#include "../JSON/JSONManager.h"
#include "ComManager.h"



void customHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    qInstallMessageHandler(customHandler);

    JSONManager();

    /*--------------------------------------------*/
    ComManager Main;

    Main.Menu();

	a.exit();
    return 0;
}

void customHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "%s", msg.toUtf8().constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, "%s", msg.toLocal8Bit().constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s", msg.toLocal8Bit().constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "%s", msg.toLocal8Bit().constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal Message : %s", msg.toLocal8Bit().constData());
        break;
    }
}
