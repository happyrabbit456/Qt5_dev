#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Logo图片显示
//    ui->labelLogo->setPixmap(QPixmap(":/res/images/MINAMI_logo.jpg"));
//    ui->labelLogo->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

