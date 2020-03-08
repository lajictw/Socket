#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QtCore>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    void run();

    void setMessage(const QString &message);

    private:
        QString m_strMessage;

    signals:
        //自定义信号函数
        void sendMessage(const QString &message);

    public slots:
};

#endif // MYTHREAD_H
