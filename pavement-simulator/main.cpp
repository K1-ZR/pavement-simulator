
#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // added by keyvan
    QApplication::setStyle(QStyleFactory::create("Fusion"));
//    QApplication::setStyle(QStyleFactory::create("WindowsXP"));

    MainWindow w;
    w.show();

    return a.exec();
}
