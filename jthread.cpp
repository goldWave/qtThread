#include "jthread.h"
#include <QtDebug>
#include <QTimer>

JThread::JThread()
{
    //必须调用这个方法才能保证startMethod() 在子线程运行
    moveToThread(this);
}

JThread::~JThread() {
    qDebug() << __FUNCTION__;
}

//子线程
void JThread::run() {
    qDebug() << __FUNCTION__ << QThread::currentThread();
    //这里使用exec()方法，也可保证线程常驻，和上面例子的 while() 死循环的结果是一样的。
    //但是相比而言 更推荐使用while循环。
    this->exec();
}

//子线程
void JThread::startMethod() {

    qDebug() << __FUNCTION__ << QThread::currentThread();
    QThread::sleep(1);
    QTimer::singleShot(5000, this, [=] {qDebug() << "timer is complect:"; });
}
