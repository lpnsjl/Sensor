#include "ebtcp.h"

EBtcp::EBtcp(QHostAddress ip, quint16 port, QObject *parent) : QObject(parent)
{
    tsock = new QTcpSocket(this);
    tsock->connectToHost(ip, port);

    connect(tsock, &QTcpSocket::readyRead, this, &EBtcp::recv);
}

void EBtcp::recv(){
    QString data = tsock->readAll();
    qDebug()<<data;
}


void EBtcp::sendSCPI(QString command){
    tsock->write(command.toUtf8());
    tsock->waitForBytesWritten();
}
