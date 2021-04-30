#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qthread.h>
#include <qdebug.h>
#include <QThreadPool>
#include <jthread.h>
#include <QTimer>
#include <QMetaObject>
#include <jworker.h>
#include <QSemaphore>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>

const static int s_maxCount = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << __FUNCTION__ << QThread::currentThread();
    //    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::thOver() {
    static int overCount = 0;
    overCount++;
}

//QRunnable 使用
void MainWindow::on_pushButton_clicked()
{

    m_vec.clear();
    static QThreadPool tPool;
    tPool.setMaxThreadCount(3);

    for (int i = 0; i <s_maxCount; i++) {
        JRunnable *r = new JRunnable(this, i);
        m_vec.push_back(r);
        tPool.start(r);
        QThread::msleep(500);
    }

    qDebug() << __FUNCTION__;
}

//QThread 继承类，在run 函数内调用说明
void MainWindow::on_pushButton_qTread_clicked()
{
    m_vec.clear();
    for (int i = 0; i <s_maxCount; i++) {
        JThread *myThread = new JThread;
        connect(myThread, &JThread::started, this, [=](){
            qDebug() << "thread started";
        });
        connect(myThread, &JThread::finished, this, [=](){
            qDebug() << "thread finished ----";
        });
        myThread->start();

        //startMethod() 方法的运行也是在子线程里面运行的。
        QMetaObject::invokeMethod(myThread, &JThread::startMethod, Qt::QueuedConnection);
        m_vec.push_back(myThread);
    }
}


void MainWindow::on_pushButton_test_clicked()
{
    //    for (int i = 0; i <s_maxCount; i++) {

    //        //        QThread *_thread = new QThread();
    //        //        JWorker *_thread = new JWorker();
    //        int x = 3;   //定义int型变量x，内容为整数3
    //        int *_thread = &x;  //定义指向int型变量的指针px，内容为变量x的地址
    //        qDebug()<<"-------------------------------------------------------" << &_thread << _thread;
    //    }
    //        this->m_isFinished = true;
    //        qDebug() << "timer:" << m_i; }

}

//QThread moveToThread，在工作类异步调用说明
void MainWindow::on_moveToButton_clicked()
{
    //多线程 长时间运行后，手动释放结束
    //不能控制线程数量
    m_vec.clear();
    for (int i = 0; i <s_maxCount; i++) {
        JWorker *worker = new JWorker(); //工作类
        QThread *_thread = new QThread();

        m_vec.push_back(_thread);
        worker->moveToThread(_thread); //worker调用的方法都将是子线程方法
        connect(_thread, &QThread::finished, worker, &QObject::deleteLater);
        connect(worker, &JWorker::resultReady, _thread, [=](){
            _thread->quit();
            _thread->wait();

            QThread *_th = reinterpret_cast<QThread *>(this->m_vec[static_cast<unsigned int>(i)]);
            if(_th){
                //线程结束，销毁线程指针
                delete _th;
                _th = nullptr;
            }
        }, Qt::QueuedConnection);
        _thread->start();
        worker->doCustonWork(i);
    }
}

//QThread moveToThread + QSemaphore, 未成功
void MainWindow::on_semphoreButton_clicked()
{
    //多线程 长时间运行后，手动释放结束
    //能控制线程数量
    QSemaphore sem(1);
    m_vec.clear();
    for (int i = 0; i <s_maxCount; i++) {
        sem.acquire();
        qDebug() << "---- " << &sem;
        JWorker *worker = new JWorker();
        QThread *_thread = new QThread();

        m_vec.push_back(_thread);
        worker->moveToThread(_thread);
        connect(_thread, &QThread::finished, worker, &QObject::deleteLater);
        connect(worker, &JWorker::resultReady, _thread, [=, &sem](){
            qDebug() << &sem;
            sem.release();
            _thread->quit();
            _thread->wait();

            QThread *_th = reinterpret_cast<QThread *>(this->m_vec[static_cast<unsigned int>(i)]);
            if(_th){
                delete _th;
                _th = nullptr;
            }


        }, Qt::QueuedConnection);
        _thread->start();
        worker->doCustonWork(i);
        //        sem.release();

    }
}

//是单独模块，需导入 QT += concurrent
void MainWindow::on_pushButton_QTConcurrent_clicked()
{
    QVector<int> _vector;
    for (int i =0; i< 38; i++) {
        _vector.push_back(i);
    }

    std::function<void(int)> spin = [](int index) {
        //异步线程运行
        QThread::msleep(1500);
        qDebug() << "iteration" << index << "线程:" << QThread::currentThreadId();
    };
    //方式一：运行 map 循环
    QtConcurrent::map(_vector, spin);

    //方式一：运行lambda表达式
    QtConcurrent::run([=](){
        QThread::msleep(1500);
        qDebug() << "我运行的线程是" <<  QThread::currentThreadId();
    });
}
