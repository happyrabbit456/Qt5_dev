#include "person.h"

#include <QDebug>

Person::Person(QObject *parent) : QObject(parent)
{

}

Person::Person(const QString &name, QObject *parent) : QObject(parent)
{
    m_name = name;
    qDebug() << "create a person: " << m_name;
}


Person::~Person()
{
    qDebug() << "delete a person: " << m_name;
}

QString Person::name() const
{
    return m_name;
}

void Person::setName(const QString &name)
{
    m_name = name;
}

