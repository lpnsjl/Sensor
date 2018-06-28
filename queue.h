#ifndef QUEUE_H
#define QUEUE_H

#include <QObject>
#include <QSemaphore>
#include <QQueue>


class Queue : public QObject
{
    Q_OBJECT
public:
    QQueue <QByteArray> queue;
    QSemaphore *total;
    QSemaphore *available;
    explicit Queue(QObject *parent = 0);

signals:

public slots:
};

#endif // QUEUE_H
