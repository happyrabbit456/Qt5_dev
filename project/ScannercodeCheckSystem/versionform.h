#ifndef VERSIONFORM_H
#define VERSIONFORM_H

#include <QWidget>

namespace Ui {
class VersionForm;
}

class VersionForm : public QWidget
{
    Q_OBJECT

public:
    explicit VersionForm(QWidget *parent = nullptr);
    ~VersionForm();

private:
    Ui::VersionForm *ui;
};

#endif // VERSIONFORM_H
