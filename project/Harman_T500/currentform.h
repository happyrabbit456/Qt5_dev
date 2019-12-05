#ifndef CURRENTFORM_H
#define CURRENTFORM_H

#include <QWidget>
#include <QDebug>

#include "nivisagpib.h"

namespace Ui {
class CurrentForm;
}

class CurrentForm : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentForm(QWidget *parent = nullptr);
    ~CurrentForm();

public:
    bool initComboGPIB();

public:
    NIVisaGPIB m_niVisaGPIB;

private slots:
    void on_comboGPIBSelector_currentIndexChanged(int index);

private:
    Ui::CurrentForm *ui;
};

#endif // CURRENTFORM_H
