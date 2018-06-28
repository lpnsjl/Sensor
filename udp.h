#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>

class Udp : public QObject
{
    Q_OBJECT
public:
    void recv();
    QByteArray buf;
    explicit Udp(QObject *parent = 0);
private:
    QUdpSocket *usock;
signals:

public slots:
};

#endif // UDP_H
