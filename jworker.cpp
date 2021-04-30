#include "jworker.h"
#include <qdebug.h>
#include <QTimer>
#include <stdlib.h>
#include <windows.h>

JWorker::JWorker(QObject *parent) : QObject(parent)
{

}

static int _total = 0;
void JWorker::doCustonWork(int i)
{
    //子线程工作，随机时间到了，后直接发消息结束线程。

    int randTime = rand()%4000 + 1000;
    QTimer::singleShot(randTime, this, [=]{
        _total++;
        emit resultReady();
        qDebug() << "i:" << i << "   _total:" << _total;
    });
}

JWorker::~JWorker()
{}
