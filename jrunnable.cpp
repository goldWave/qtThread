#include "jrunnable.h"
#include <QDebug>
#include <qthread.h>
#include <QMetaObject>
#include <QTimer>

JRunnable::JRunnable(QObject *_obj, int i):m_i(i), m_obj(_obj)
{
}

JRunnable::~JRunnable() {
    qDebug() << __FUNCTION__<< QString::number(m_i);
}

void JRunnable::run(){
    //3秒后 m_isFinished 设置为true，代表可以退出下面循环。
    QTimer::singleShot(3000, m_obj, [=] {
        this->m_isFinished = true;
        qDebug() << "timer:" << m_i; }
    );

    //设置死循环的原因是，让 run() 方法不运行完成，不然run运行完成，代表线程结束
    while (true) {
        qDebug() << "m_isFinished = " << m_isFinished << QThread::currentThreadId();
        if (m_isFinished) {
            break;
        }
        QThread::msleep(1000);
    }
}
