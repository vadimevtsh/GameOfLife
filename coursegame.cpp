#include "coursegame.h"
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

#define for1(i,n) for(int i = 1; i <= int(n); i++)

CourseGame::CourseGame(QWidget *parent) :   //Конструктор
    QWidget(parent),
    timer(new QTimer(this))
{
    universeSize = 50;  //размер вселенной
    timer->setInterval(100);

    connect(timer, SIGNAL(timeout()), this, SLOT(next_generation()));   //коннектит сигнал конца интервала таймера к следующему поколению

    current = new bool*[universeSize];  //динамическое выделение памяти на матрицу
    for1(i, universeSize)
        current[i] = new bool[universeSize];

    next = new bool*[universeSize];     //динамическое выделение памяти на матрицу
    for1(i, universeSize)
        next[i] = new bool[universeSize];

    for1(i, universeSize)               //Замена "мусора" в матрице на 0
        for1(j, universeSize)
            current[i][j] = false;

    for1(i, universeSize)               //Замена "мусора" в матрице на 0
        for1(j, universeSize)
            next[i][j] = false;
}

CourseGame::~CourseGame()   //Деструктор
{
    for1(i, universeSize) delete[] current[i];
        delete[] current;

    for1(i, universeSize) delete[] next[i];
        delete[] next;
}

void CourseGame::grid(QPainter &brush)
{
    QColor gridColor(1,1,1); //цвет
    brush.setPen(gridColor);

    float cell_width = (float)width() / universeSize; //ширина всего виджета, деленная на количество клеток в рядку

    for (float i = cell_width; i < width(); i += cell_width) //Вертикальные линии
        brush.drawLine(i, 0, i, height());

    float cell_height = (float)height() / universeSize; //высота всего виджета, деленная на количество клеток в столбце

    for (float i = cell_height; i < height(); i += cell_height) //Горизонтальная  линии
        brush.drawLine(0, i, width(), i);

    QRect limit(0, 0, width() - 1, height() - 1); //Сама граница
    brush.drawRect(limit); //Отрисовка границы, как прямоугольника
}


void CourseGame::space(QPainter &brush)
{
    float cell_width = (float)width() / universeSize;
    float cell_height = (float)height() / universeSize;

    QColor myColor(1,1,1);              //Черный цвет

    for1(i, universeSize)
    {
        for1(j, universeSize)
        {
            if (current[i][j] == true)      //Если клетка живая
            {
                float x = cell_width * j - cell_width;
                float y  = cell_height * i - cell_height;

                QRectF rectangle(x, y, cell_width, cell_height);     //Прямоугольник по координатам x y и размерностью cell_width && cell_height
                brush.fillRect(rectangle, QBrush(myColor)); //Заполяет этот прямоугольник черным цветом
            }
        }
    }
}

void CourseGame::paintEvent(QPaintEvent *) //Ивент на отрисовку поля, срабатывает при update()
{
    QPainter brush(this);

    grid(brush);
    space(brush);
}


void CourseGame::start_game()   //Запускает таймер
{
    timer->start();
}

void CourseGame::stop_game()    //останавливает таймер
{
    timer->stop();
}

void CourseGame::clear()    //Очищает поле, заполяя его нулямии
{
    for1(i, universeSize)
        for1(j, universeSize)
            current[i][j] = false;

    update();
}

bool CourseGame::order_check(int x, int y)  //Проверка на то, не выходит ли клетка по нужным коориднатам за границы карты, возвращает
                                            //значение клетки на нужном этапе
{
    if (x > universeSize || y > universeSize)
        return 0;

    if (x <= 0 || y <= 0)
        return 0;

    return current[x][y];
}

bool CourseGame::is_alive(int x, int y)      //Проверка на то, станет ли "живой" клетка на опреденной координате
{
    int counter = 0;

    if (order_check(x, y + 1)) counter++;
    if (order_check(x, y - 1)) counter++;

    if (order_check(x - 1, y - 1)) counter++;
    if (order_check(x - 1, y)) counter++;
    if (order_check(x - 1, y + 1)) counter++;

    if (order_check(x + 1, y - 1)) counter++;
    if (order_check(x + 1, y)) counter++;
    if (order_check(x + 1, y + 1)) counter++;    //Окол Мура (считаются 8 соседей)

    if (counter == 3)                       //Если 3 живых соседа, то клетка оживает, либо остается живой
        return true;
    if (current[x][y] == true && counter == 2)  //Если клетка живая и имеет 2 живых соседа, то остается живой
        return true;

    return false;           //Во всех иных случаях умирает
}

bool CourseGame::cmp_world()    //Проверка на то, совпадает ли следующее поколение с нынешним
{
    for1(i, universeSize)
        for1(j, universeSize)
            if (current[i][j] != next[i][j])
                return false;       //не совпадает

    return true;       //совпадает, значит конечная конфигурация
}

void CourseGame::copy_world()       //копирует мир, можно сказать перенося значения переменной next на current
{
    for1(i, universeSize)
        for1(j, universeSize)
            current[i][j] = next[i][j];
}

bool CourseGame::dead_field()       //Провека на то, есть ли живые клетки на поле
{
    int counter = 0;

    for1(i, universeSize)
        for1(j, universeSize)
            if (current[i][j] == 1) counter++;

    if (counter == 0) return false;     //живых клеток нет
    return true;                        //живые клетки есть
}

void CourseGame::next_generation()
{

    if (!dead_field())                      //Если нет живых клеток, игра останавливается
    {
        QMessageBox::information(this, tr("Игра остановилась"), tr("Все клетки мертвы"), QMessageBox::Ok);
        stop_game();

        return;
    }

    for1(i, universeSize)
        for1(j, universeSize)
            next[i][j] = is_alive(i, j);    //Заполнение следующего поколения

    if (cmp_world())                        //Если текующая конфигурация совпадает со следующей, то игра останавливается
    {
        QMessageBox::information(this, tr("Игра остановилась"), tr("Конечная конфигурация"), QMessageBox::Ok);
        stop_game();

        return;
    }

    copy_world();                           //Перенос мира с next на current

    update();                               //Обновление поля
}

void CourseGame::glider()                   //Устанавливает глайдер в верхнем левом углу
{
    current[3][1] = 1;
    current[3][2] = 1;
    current[3][3] = 1;
    current[2][3] = 1;
    current[1][2] = 1;
    update();
}

void CourseGame::random_fill()              //Случайно заполняет поля, склоняясь ближе к количеству нулей
{
    for1(i, universeSize)
        for1(j, universeSize)
            current[i][j] = rand() % 100 < 25;
    update();
}

void CourseGame::next_step()        //Просто запускает следующее поколение, работает пошагово
{
    timer->stop();
    next_generation();
}


void CourseGame::mousePressEvent(QMouseEvent *click) //Ивент на нажатие кнопок мыши
{
    double cellWidth = (double)width() / universeSize;
    double cellHeight = (double)height() / universeSize;

    int x = click->y()/cellHeight + 1;
    int y = click->x()/cellWidth + 1;

    if (click->button() == Qt::LeftButton)      //Если нажата левая кнопка мыши, то делает клетку живой
        current[x][y] = 1;

    if (click->button() == Qt::RightButton)     //Если нажата правая кнопка мыши, то делает клетку мертвой
        current[x][y] = 0;

    update();               //Обновляет поле
}

void CourseGame::mouseMoveEvent(QMouseEvent *move)          //Ивент на зажатие кнопок мыши
{
    double cellWidth = (double)width() / universeSize;
    double cellHeight = (double)height() / universeSize;

    int x = move->y()/cellHeight + 1;
    int y = move->x()/cellWidth + 1;

    if (x > universeSize || y > universeSize)               //Не выходит ли нажатие за границы
        return;
    if (x <= 0 || y <= 0)
        return;

    if (move->buttons() == Qt::LeftButton) //Если зажата левая кнопка мыши, то делает клетку живой
        current[x][y] = 1;

    if (move->buttons() == Qt::RightButton) //Если зажата левая кнопка мыши, то делает клетку живой
        current[x][y] = 0;

    update();   //обновляет поле
}
