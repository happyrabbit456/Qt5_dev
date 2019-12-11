#ifndef CONCLUSIONPAGE_H
#define CONCLUSIONPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = nullptr);

    bool validatePage() override;

private:
    QLabel *conclusionLabel;

    void* currentForm;
};

#endif // CONCLUSIONPAGE_H
