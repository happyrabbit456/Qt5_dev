#include "glwidget.h"

const GLfloat PI = 3.1415926536f;

GLWidget::GLWidget(QGLWidget *parent) : QGLWidget (parent)
{
    setMinimumSize(320,240);
    resize(640,480);
    setWindowTitle(tr("Hello OpenGL"));
    short angle = 18;
    for(short i=0; i<5; i++) {
        Point[i][0] = cos(angle * PI/180);
        Point[i][1] = sin(angle * PI/180);
        Point[i][2] = 0.0;
        angle += 72;
    }
}

GLWidget::~GLWidget()
{
}
void GLWidget::initializeGL()
{
    // 初始化函数
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}
void GLWidget::paintGL()
{
    //清除之前图形并将背景设置为 blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef( -1.5,  0.0, -6.0 );

    glBegin( GL_QUADS );
    glVertex3f(  -1.0,  1.0,  0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glEnd();

    glTranslatef(  3.0,  0.0,  0.0 );

    glBegin( GL_TRIANGLES );
    glVertex3f(  0.0,  1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glEnd();

}
void GLWidget::resizeGL(int width, int height)
{
    // 窗口大小变化时 调整大小
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLdouble fovy=45.0;
    GLdouble glWidth=static_cast<GLdouble>(width);
    GLdouble glHeight=static_cast<GLdouble>(height);
    GLdouble aspect=glWidth/glHeight;
    GLdouble zNear=0.1;
    GLdouble zFar=100.0;
    gluPerspective(fovy,aspect,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void GLWidget::mouseDoubleClickEvent( QMouseEvent *event )
{
    Q_UNUSED(event);

    if(windowState() &  Qt::WindowFullScreen)
        showNormal();
    else
        showFullScreen();
}
void GLWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
}

