#ifndef CURRENTFORM_H
#define CURRENTFORM_H

#include <QWidget>

namespace Ui {
class CurrentForm;
}

class CurrentForm : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentForm(QWidget *parent = nullptr);
    ~CurrentForm();

private:
    Ui::CurrentForm *ui;
};

#endif // CURRENTFORM_H
