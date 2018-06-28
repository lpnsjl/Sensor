#ifndef EBTCP_H
#define EBTCP_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class EBtcp : public QObject
{
    Q_OBJECT
public:
    explicit EBtcp(QHostAddress ip, quint16 port, QObject *parent = 0);
    void sendSCPI(QString command);
private:
    QTcpSocket *tsock;
signals:

public slots:
    void recv(); // 接收数据
};

#endif // EBTCP_H
