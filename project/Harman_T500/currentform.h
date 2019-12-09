#ifndef CURRENTFORM_H
#define CURRENTFORM_H

#include <QWidget>
#include <QDebug>

#include <QtWidgets>

#include "parameterform.h"
#include "testform.h"

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

    TestForm *m_pTestForm;
    ParameterForm *m_pParameterForm;

private:
    Ui::CurrentForm *ui;
};

#endif // CURRENTFORM_H
