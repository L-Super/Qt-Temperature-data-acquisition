#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //代表运行的项目
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
