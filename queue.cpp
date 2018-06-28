#include "queue.h"

Queue::Queue(QObject *parent) : QObject(parent)
{
    // queue = new QQueue;
    total = new QSemaphore(1000);
    available = new QSemaphore();
    // total->release(1000);
}

