#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "coursegame.h"

namespace Ui
{
class CourseGameWindow;
}

class CourseGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    CourseGameWindow(QWidget *parent = 0);
    ~CourseGameWindow();

private:
    Ui::CourseGameWindow *ui;
    CourseGame *gameLife;
};

#endif // MAINWINDOW_H
