#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void setupUI();

protected slots:
    void onSubmit();

private:
    QComboBox ** m_scores;
    int m_nQuestionCount;
};
#endif // WIDGET_H
