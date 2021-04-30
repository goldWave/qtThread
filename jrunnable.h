#ifndef JRUNNABLE_H
#define JRUNNABLE_H

#include <QObject>
#include <QRunnable>


class JRunnable : public QRunnable
{
public:
    explicit JRunnable(QObject *_obj, int i =-1);
    ~JRunnable() override;
    void run() override;
    int m_i = -1;
    QObject *m_obj{nullptr};

    //设置标志位，代表线程可以退出，
    bool m_isFinished{false};
};

#endif // JRUNNABLE_H
