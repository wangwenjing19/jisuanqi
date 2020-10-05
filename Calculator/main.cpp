#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *mainWnd = new MainWindow;
    mainWnd->show();

    return a.exec();
}
