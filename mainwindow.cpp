#include "mainwindow.h"
#include "ui_mainwindow.h"

CourseGameWindow::CourseGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CourseGameWindow),
    gameLife(new CourseGame(this))
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), gameLife,SLOT(stop_game()));
    connect(ui->pushButton_2, SIGNAL(clicked()), gameLife,SLOT(clear()));
    connect(ui->pushButton_3, SIGNAL(clicked()), gameLife,SLOT(start_game()));
    connect(ui->pushButton_4, SIGNAL(clicked()), gameLife,SLOT(glider()));
    connect(ui->pushButton_5, SIGNAL(clicked()), gameLife,SLOT(random_fill()));
    connect(ui->pushButton_7, SIGNAL(clicked()), gameLife,SLOT(next_step()));

    ui->verticalLayout->addWidget(gameLife);
}

CourseGameWindow::~CourseGameWindow()
{
    delete ui;
}


