#include "jthread.h"
#include <QtDebug>
#include <QTimer>

JThread::JThread()
{
    moveToThread(this);
}

JThread::~JThread() {
    qDebug() << __FUNCTION__;
}

void JThread::run() {
    qDebug() << __FUNCTION__ << QThread::currentThread();
//m_nowThread = QThread::currentThread();
this->exec();

}


void JThread::startMethod() {

    qDebug() << __FUNCTION__ << QThread::currentThread();
    QThread::sleep(1);
    QTimer::singleShot(5000, this, [=] {qDebug() << "timer is complect:"; });
}
