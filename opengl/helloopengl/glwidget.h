#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QtOpenGL>
#include <QtOpenGL/qgl.h>

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QTime>
#include <QVector>
#include <QPushButton>
#include <QOpenGLFunctions>

#include <gl/GL.h>
#include <gl/GLU.h>

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QGLWidget *parent = nullptr);

    ~GLWidget();

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *e);

private:
    GLfloat Point[5][3];
};

#endif // GLWIDGET_H
