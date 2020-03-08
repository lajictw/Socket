#include "sendobject.h"

SendObject::SendObject(QObject *parent) : QObject(parent)
{

}

void SendObject::setMessage(const QString &message)
{
    m_strMessage = message;
    //发送消息
    emit sendMessage(message);
}
