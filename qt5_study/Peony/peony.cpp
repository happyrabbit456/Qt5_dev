#include "peony.h"
#include <QtGlobal>

Peony::Peony() : m_timer(nullptr)
{
}

void Peony::setBloomDate(const QDateTime & date)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onBloomTime()));

    m_timer->setSingleShot(true);
    m_timer->start(static_cast<int>(QDateTime::currentDateTime().msecsTo(date)));
}

void Peony::onBloomTime()
{
    m_timer->disconnect(SIGNAL(timeout()), this);
    emit bloom();
}

