#ifndef JWORKER_H
#define JWORKER_H

#include <QObject>
#include <QThread>

class JWorker : public QObject
{
    Q_OBJECT
public:
    explicit JWorker(QObject *parent = nullptr);
    void doCustonWork(int i =0);
    ~JWorker();
signals:
    //发消息给MainWindow，代表子线程数据处理完成，可以销毁
    void resultReady();

public slots:
};

#endif // JWORKER_H
