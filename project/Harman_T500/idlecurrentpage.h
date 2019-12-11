#ifndef IDLECURRENTPAGE_H
#define IDLECURRENTPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>

class IdleCurrentPage : public QWizardPage
{
    Q_OBJECT

public:
    IdleCurrentPage(QWidget *parent = nullptr);

    bool validatePage() override;

private:
    QLabel *idleLabel;

    void* currentForm;
};

#endif // IDLECURRENTPAGE_H
