#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CourseGameWindow w;
    w.setWindowTitle("CourseGame");
    w.show();
    return a.exec();
}
