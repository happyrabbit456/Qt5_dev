#ifndef SNPAGE_H
#define SNPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>

class SNPage : public QWizardPage
{
public:
    SNPage(QWidget *parent = nullptr);

    bool validatePage() override;

private:
    QLabel *snLabel;
    QLineEdit *snLineEdit;

    void* currentForm;
};

#endif // SNPAGE_H
