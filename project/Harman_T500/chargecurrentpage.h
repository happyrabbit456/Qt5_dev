#ifndef CHARGECURRENTPAGE_H
#define CHARGECURRENTPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>

class ChargeCurrentPage : public QWizardPage
{
    Q_OBJECT

public:
    ChargeCurrentPage(QWidget *parent = nullptr);

    bool validatePage() override;

private:
    QLabel *chargeLabel;

    void* currentForm;
};

#endif // CHARGECURRENTPAGE_H
