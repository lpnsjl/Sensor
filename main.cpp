#include <QCoreApplication>
#include "kafkaConsumer/kafkaconsumerclient.h"
#include "fscan.h"
#include "workhandle.h"
#include "sendworker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // 开启接收数据线程
    WorkHandle *handle = new WorkHandle();
    handle->start();
    /***开启消费者***/
    SendWorker *sender = new SendWorker();
    sender->start();

    return a.exec();
}

