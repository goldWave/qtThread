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
    void resultReady();

public slots:
};

#endif // JWORKER_H
