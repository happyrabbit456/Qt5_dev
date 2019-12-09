#ifndef PARAMETERFORM_H
#define PARAMETERFORM_H

#include <QWidget>
#include <QSettings>

#include "nivisagpib.h"

namespace Ui {
class ParameterForm;
}

class ParameterForm : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterForm(QWidget *parent = nullptr);
    ~ParameterForm();

public:
    void ReadAppSettings();
    void WriteAppSettings();

    bool initComboGPIB();

private slots:
    void on_comboGPIBSelector_currentIndexChanged(int index);

    void on_btnLock_clicked();

    void on_btnUnlock_clicked();

private:
    Ui::ParameterForm *ui;

    QSettings *m_settings;
    void* currentForm;;
};

#endif // PARAMETERFORM_H
