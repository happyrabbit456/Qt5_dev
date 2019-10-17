#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opencv2/opencv.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Mat image = imread("D:\\opencv-3.4.7\\opencv\\sources\\doc\\opencv.jpg");  // 读入图片
    imshow("OpenCV Logo", image);              // 在窗口中展示图片
}

MainWindow::~MainWindow()
{
    delete ui;
}
