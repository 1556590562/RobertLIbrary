#include "mainwindow.h"
#include "maintablewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainTableWindow w;
    w.setWindowTitle("综合测评统计计算系统");
    w.show();

    return a.exec();
}
