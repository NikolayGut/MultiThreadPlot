#ifndef COORDINATES_H
#define COORDINATES_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QRandomGenerator>
#include <QDebug>
#include <mythread.h>


class Coordinates : public QObject
{
    Q_OBJECT
public:
    Coordinates() {}
    bool requestedStop = false;
    bool requestedClear = false;
    QMutex mtx;
    QWaitCondition pauseManager;

public slots:
    void makeCoordinates();

signals:
    void dataReady(const double &x, const double &y);
    void finishThread();
};

#endif // COORDINATES_H
