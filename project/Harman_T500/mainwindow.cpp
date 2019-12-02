#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <exception>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GPIB gpib;
    gpib.sample();

    double value = 0.0;
    gpib.DMM_ReadCurrent(value);
}

MainWindow::~MainWindow()
{
    delete ui;
}

