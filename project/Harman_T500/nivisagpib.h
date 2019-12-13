#ifndef NIVISAGPIB_H
#define NIVISAGPIB_H

#include <QObject>
#include <QDebug>
#include <QMap>

#include "visa.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class NIVisaGPIB : public QObject
{
    Q_OBJECT
public:
    explicit NIVisaGPIB(QObject *parent = nullptr);
    virtual ~NIVisaGPIB() override;

    ViStatus sample_viFindRsrc();
    ViStatus sample_getCurrent();

    ViStatus initGPIB();
    bool reset();
    bool autoZero(bool autoZero);
    bool getCurrent(string &value);

signals:

public slots:

public:
    QMap<string,ViSession> m_mapGPIB;

    ViUInt32 m_numInstrs;
    ViFindList m_findList;
    ViSession m_defaultRM;

    int m_nCurrGPIBIndex;
};

#endif // NIVISAGPIB_H
