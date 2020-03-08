#ifndef SENDOBJECT_H
#define SENDOBJECT_H
#include <QtCore>


class SendObject: public QObject
{
    Q_OBJECT
    public:
        explicit SendObject(QObject *parent = 0);
        void setMessage(const QString &message);

    private:
        QString m_strMessage;

    signals:
        //自定义信号函数
        void sendMessage(const QString &message);

    public slots:
};

#endif // SENDOBJECT_H
