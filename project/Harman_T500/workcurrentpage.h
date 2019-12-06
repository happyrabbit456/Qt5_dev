#ifndef WORKCURRENTPAGE_H
#define WORKCURRENTPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>

class WorkCurrentPage : public QWizardPage
{
public:
    WorkCurrentPage(QWidget *parent = nullptr);

    bool validatePage() override;

private:
    QLabel *workLabel;

    void* currentForm;
};

#endif // WORKCURRENTPAGE_H
