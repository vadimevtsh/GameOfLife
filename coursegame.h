#ifndef COURSEGAME_H
#define COURSEGAME_H

#include <QWidget>

class CourseGame : public QWidget
{
    Q_OBJECT

public:
    CourseGame(QWidget *parent = 0);
    ~CourseGame();


public slots:
    void grid(QPainter &brush);
    void space(QPainter &brush);
    void paintEvent(QPaintEvent *);

    void start_game();
    void stop_game();
    void clear();

    bool order_check(int x, int y);
    bool is_alive(int x, int y);

    bool cmp_world();
    void copy_world();
    bool dead_field();
    void next_generation();

    void glider();
    void random_fill();
    void next_step();

    void mousePressEvent(QMouseEvent *click);
    void mouseMoveEvent(QMouseEvent *move);

private:
    QTimer* timer;

    int universeSize;

    bool** current;
    bool** next;
};

#endif // COURSEGAME_H
