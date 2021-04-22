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
//    qDebug() << __FUNCTION__ << QThread::currentThread();
    QThread::msleep(1000);
    auto x =  QMetaObject::invokeMethod(m_obj, "thOver", Qt::DirectConnection);
    QTimer::singleShot(5000, m_obj, [=] {qDebug() << "timer:" << m_i; });
}
