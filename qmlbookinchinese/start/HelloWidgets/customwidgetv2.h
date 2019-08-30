#ifndef CUSTOMWIDGETV2_H
#define CUSTOMWIDGETV2_H

#include <QWidget>
#include <QGraphicsView>

class CustomWidgetV2 : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidgetV2(QWidget *parent = nullptr);

signals:

public slots:

private:
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
};

#endif // CUSTOMWIDGETV2_H
