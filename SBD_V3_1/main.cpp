#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    //QApplication::setQuitOnLastWindowClosed(0);


    return a.exec();
}
