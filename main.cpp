#include <QtPrintSupport/QPrinter>
//#include <QGuiApplication>
#include<QApplication>
#include <QQmlApplicationEngine>

#include "qwtquick2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);

    qmlRegisterType<QwtQuick2Plot>("QwtQuick2", 1, 0, "QwtQuick2Plot");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return a.exec();
}
