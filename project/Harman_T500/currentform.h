﻿#ifndef CURRENTFORM_H
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

protected:
    void resetTestHandle();

public:
    bool initComboGPIB();

public:
    NIVisaGPIB m_niVisaGPIB;

private slots:
    void on_comboGPIBSelector_currentIndexChanged(int index);

    void on_btnReset_clicked();

    void on_btnTest_clicked();

private:
    Ui::CurrentForm *ui;
};

#endif // CURRENTFORM_H
