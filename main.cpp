#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Start the application and show the window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
