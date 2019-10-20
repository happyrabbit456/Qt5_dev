#include "mainwindow.h"
#include "workerthread.h"

#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_workerThread = new WorkerThread(this);

    qDebug() << "Main Thread : " << QThread::currentThreadId();

    // 创建开始按钮、进度条
    QPushButton *pStartButton = new QPushButton(this);
    QPushButton *pStopButton = new QPushButton(this);
    m_pProgressBar = new QProgressBar(this);

    //设置文本、进度条取值范围
//    pStartButton->setText(QString::fromLocal8Bit("开始"));//乱码
    pStartButton->setText(QStringLiteral("开始"));
    pStopButton->setText((QStringLiteral("停止")));

    m_pProgressBar->setFixedHeight(25);
    m_pProgressBar->setRange(0, 100);
    m_pProgressBar->setValue(0);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pStartButton, 0, Qt::AlignHCenter);
    pLayout->addWidget(pStopButton, 0, Qt::AlignHCenter);
    pLayout->addWidget(m_pProgressBar);
    pLayout->setSpacing(50);
    pLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(pLayout);

    // 连接信号槽
    connect(pStartButton, SIGNAL(clicked(bool)), this, SLOT(startThread()));
    connect(pStopButton, SIGNAL(clicked(bool)), this, SLOT(stopThread()));
}

MainWindow::~MainWindow()
{
    delete m_workerThread;
    m_workerThread=nullptr;
}

