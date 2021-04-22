#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qthread.h>
#include <qdebug.h>
#include <QThreadPool>
#include <jthread.h>
#include <QTimer>
#include <QMetaObject>
#include <jworker.h>

const static int s_maxCount = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << __FUNCTION__ << QThread::currentThread();
    on_pushButton_2_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::thOver() {
    static int overCount = 0;
    overCount++;
    //qDebug() << "complect count is " << overCount << QThread::currentThread();
    //    if (overCount >= s_maxCount) {
    //        for(auto thr : m_vec) {
    //            JThread *item_JThread = reinterpret_cast<JThread *>(thr);
    //            if(item_JThread) {
    //                item_JThread->deleteLater();
    //                item_JThread = nullptr;
    //                continue;
    //            }
    //            JRunnable *item_JRunnable = reinterpret_cast<JRunnable *>(thr);
    //            if(item_JRunnable) {
    //                item_JRunnable = nullptr;
    //                continue;
    //            }
    //        }
    //    }
}


void MainWindow::on_pushButton_clicked()
{
    m_vec.clear();
    QThreadPool tPool;
    tPool.setMaxThreadCount(4);


    for (int i = 0; i <s_maxCount; i++) {
        JRunnable *r = new JRunnable(this, i);
        m_vec.push_back(r);
        tPool.start(r);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    m_vec.clear();
    for (int i = 0; i <s_maxCount; i++) {
        JThread *myThread = new JThread;
        m_vec.push_back(myThread);

        connect(myThread, &JThread::started, this, [=](){
            qDebug() << "thread started";
        });
        connect(myThread, &JThread::finished, this, [=](){
            qDebug() << "thread finished ----";
            thOver();
        });

//        myThread->moveToThread(myThread);
        myThread->start();

        //        QMetaObject::invokeMethod(myThread, "startMethod", Qt::QueuedConnection);
        QMetaObject::invokeMethod(myThread, &JThread::startMethod, Qt::QueuedConnection);

        //        myThread->startMethod();
        m_vec.push_back(myThread);
    }


    //    QTimer::singleShot(10000, this, [=]{
    //      for(auto x : m_vec) {
    //          JThread *th = reinterpret_cast<JThread *>(x);
    //          if(th){
    //              qDebug() << "again";
    //               th->startThread();
    //          }
    //      }
    //    });
    //need delete thread
}

void MainWindow::on_pushButton_3_clicked()
{
    for (int i = 0; i <s_maxCount; i++) {

        //        QThread *_thread = new QThread();
        //        JWorker *_thread = new JWorker();
        int x = 3;   //定义int型变量x，内容为整数3
        int *_thread = &x;  //定义指向int型变量的指针px，内容为变量x的地址
        qDebug()<<"-------------------------------------------------------" << &_thread << _thread;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //多线程 长时间运行后，手动释放结束
    m_vec.clear();
    for (int i = 0; i <s_maxCount; i++) {
        JWorker *worker = new JWorker();
        QThread *_thread = new QThread();

        m_vec.push_back(_thread);
        worker->moveToThread(_thread);
        connect(_thread, &QThread::finished, worker, &QObject::deleteLater);
        connect(worker, &JWorker::resultReady, _thread, [=](){
            qDebug()<<"-------------------------------------------------------" << &_thread;
            qDebug() << "resultReady ---- over" << QThread::currentThread();
            _thread->quit();
            _thread->wait();

            QThread *_th = reinterpret_cast<QThread *>(this->m_vec[static_cast<unsigned int>(i)]);
            if(_th){
                delete _th;
                _th = nullptr;
            }
        }, Qt::QueuedConnection);
        _thread->start();
        qDebug() <<"-------------------------------------------------------"<<&_thread;
        worker->doCustonWork(i);
    }
}
