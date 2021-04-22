#include "jworker.h"
#include <qdebug.h>
#include <QTimer>
#include <stdlib.h>

JWorker::JWorker(QObject *parent) : QObject(parent)
{

}

void JWorker::doCustonWork(int i)
{
    int in_c = rand()%4000 + 1000;
    qDebug() << in_c << i;
    QTimer::singleShot(in_c, this, [=]{
        qDebug() << QThread::currentThread() << "---------" << i;
        emit resultReady();
    });
}

JWorker::~JWorker()
{
    qDebug() << __FUNCTION__;
}
