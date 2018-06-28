#include "udp.h"
#include <strings.h>

Udp::Udp(QObject *parent) : QObject(parent)
{
    buf.resize(1000);
    usock = new QUdpSocket(this);
    bool b = usock->bind(QHostAddress("192.168.2.5"), 9000);
    connect(usock, &QUdpSocket::readyRead, this, &Udp::recv);
}


void Udp::recv(){
    int maxsize = usock->pendingDatagramSize();
    bzero(buf.data(), buf.size());
    usock->readDatagram(buf.data(), maxsize);
    qDebug()<<buf.left(maxsize);
}
