#ifndef VOLTAGEFORM_H
#define VOLTAGEFORM_H

#include <QWidget>

namespace Ui {
class VoltageForm;
}

class VoltageForm : public QWidget
{
    Q_OBJECT

public:
    explicit VoltageForm(QWidget *parent = nullptr);
    ~VoltageForm();

private:
    Ui::VoltageForm *ui;
};

#endif // VOLTAGEFORM_H
