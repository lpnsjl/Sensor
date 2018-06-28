#ifndef SENDWORKER_H
#define SENDWORKER_H
#include <QThread>

class SendWorker:public QThread
{
public:
    virtual void run();
    SendWorker();
};

#endif // SENDWORKER_H
