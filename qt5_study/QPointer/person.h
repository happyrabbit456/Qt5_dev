#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);

    Person(const QString &name, QObject *parent = nullptr);
    virtual ~Person();
    QString name() const;
    void setName(const QString &name);

signals:

public slots:

private:
    QString m_name;
};

#endif // PERSON_H
