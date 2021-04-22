#ifndef JTHREAD_H
#define JTHREAD_H

#include <QObject>
#include <QThread>

class JThread : public QThread
{
    Q_OBJECT
public:
    JThread();
    ~JThread() override;

    QThread *m_nowThread = nullptr;
  public slots:
    void startMethod();
protected:
    void run() override;

};

#endif // JTHREAD_H
