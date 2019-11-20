#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    QImage image;
    image.load(":/res/images/None.jpg");
    ui->labelStatusImage->clear();
//    QImage fixedImage=ConvertImageToTransparent(image);
//    ui->labelStatusImage->setPixmap(QPixmap::fromImage(fixedImage));
    ui->labelStatusImage->setPixmap(QPixmap::fromImage(image));
    ui->labelStatusImage->setScaledContents(true);
    ui->labelStatusImage->show();
}

TestForm::~TestForm()
{
    delete ui;    
}

///将指定图片的指定颜色扣成透明颜色的方法
QImage TestForm::ConvertImageToTransparent(QImage image/*QPixmap qPixmap*/)
{
        image = image.convertToFormat(QImage::Format_ARGB32);
        union myrgb
        {
            uint rgba;
            uchar rgba_bits[4];
        };
        myrgb* mybits =(myrgb*)image.bits();
        int len = image.width()*image.height();
        while(len --> 0)
        {
            mybits->rgba_bits[3] = (mybits->rgba== 0xFF000000)?0:255;
            mybits++;
        }
        return image;
}


//将背景为白色的图片改为透明色
void TestForm::ConvertImageToTransparent(QPixmap qPixmap)
{
    QImage image = qPixmap.toImage();
    image = image.convertToFormat(QImage::Format_ARGB32);
    union myrgb
    {
        uint rgba;
        uchar rgba_bits[4];
    };
    myrgb* mybits =(myrgb*) image.bits();
    int len = image.width()*image.height();
    while(len --> 0)
    {
        mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:255;
        mybits++;
    }
}



