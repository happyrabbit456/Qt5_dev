#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr);
    ~TestForm();

    QImage ConvertImageToTransparent(QImage image/*QPixmap qPixmap*/);
    void ConvertImageToTransparent(QPixmap qPixmap);

private:
    Ui::TestForm *ui;    
};

#endif // TESTFORM_H
