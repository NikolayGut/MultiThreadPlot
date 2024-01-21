#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QObject>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread();
};

#endif // MYTHREAD_H
