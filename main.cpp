#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    srand( (unsigned)time(NULL) );
    w.startGrid();
    w.showWindow();
    //w.gameFlow(&w);
    //w.endCheck(&w);
    return a.exec();
}
