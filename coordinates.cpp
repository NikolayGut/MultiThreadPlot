#include "coordinates.h"
#include <QThread>

void Coordinates::makeCoordinates()
{
    forever {
        if (requestedClear) {
            MyThread::currentThread()->requestInterruption();
            emit finishThread();
            return;
        }
        if (requestedStop) {
            pauseManager.wait(&mtx);
        }
        else {
            qDebug() << MyThread::currentThreadId();
            double x = QRandomGenerator::global()->bounded(0, 100);
            double y = QRandomGenerator::global()->bounded(0, 100);
            emit dataReady(x, y);
            MyThread::msleep(1500);
        }
    }
}


