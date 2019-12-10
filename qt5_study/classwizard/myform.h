#ifndef MYFORM_H
#define MYFORM_H

#include <QWidget>
#include <QWizard>
#include <QWizardPage>

namespace Ui {
class MyForm;
}

class MyForm : public QWizardPage
{
    Q_OBJECT

public:
    explicit MyForm(QWizardPage *parent = nullptr);
    ~MyForm();

private:
    Ui::MyForm *ui;
};

#endif // MYFORM_H
