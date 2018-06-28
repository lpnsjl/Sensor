#include "fscan.h"
#include <QtEndian>
#include <QDateTime>
#include <strings.h>
#include <kafkaProducer/kafkaproducerclient.h>

Queue *queue = new Queue; // 存放接收数据的队列
Fscan::Fscan(QHostAddress ip, quint16 port, QObject *parent) : QObject(parent)
{
    buf.resize(0x80000);

    usock = new QUdpSocket(this);
    bool b = usock->bind(ip, port);

    WorkerThread *workthread = new WorkerThread(); // 工作线程，发送数据
    workthread->start(); // 开启线程，发送数据

    connect(usock, &QUdpSocket::readyRead, this, &Fscan::recv);
}

void Fscan::recv(){
    // qDebug()<<"enter recv handle!";
    int maxsize = usock->pendingDatagramSize();
    char *p = buf.data();
    bzero(p, buf.size()); // 将缓冲区置零
    usock->readDatagram(p, maxsize);
    // qDebug()<<buf;

    QDateTime time = QDateTime::currentDateTime();
    QString nowtime = time.toString("yyyy-MM-dd hh:mm::ss.zzz");

    EB200Header *eb200header = (EB200Header*)p;
    unsigned short length = qFromBigEndian(eb200header->length) + 20; // 包的总长度
    unsigned short traceNum = qFromBigEndian(eb200header->traceNum); // 跟踪项目的数目
    fscanHeader *fscan = (fscanHeader*)(p + EB200_HEADER);
    int step = qFromBigEndian(fscan->step); // 步长
    int start = EB200_HEADER + FSCAN_HEADER;
    for(int i=0; i<traceNum; i++){
        traceHeader *data1 = (traceHeader*)(p + start + i*2);
        short level = qFromBigEndian(data1->level); // 电平
        traceHeader *data2 = (traceHeader*)(p + start + traceNum*2 + (i-1)*4);
        int fre = qFromBigEndian(data2->frequency); // 频率
        qDebug("fre: %d\tlevel: %d", fre, level);
        if(level == 2000){
            time = QDateTime::currentDateTime();
            nowtime = time.toString("yyyy-MM-dd hh:mm::ss.zzz");
            QJsonDocument doc;
            doc.setArray(arr);
            QByteArray sendData = doc.toBinaryData();
            arr = QJsonArray(); // 清空json数组

            queue->total->acquire();
            queue->queue.append(sendData); // 将接收的一帧数据放入队列中
            queue->available->release();
        }
        /***将数据构造成json对象***/
        obj.insert("level", level);
        obj.insert("fre", fre);
        obj.insert("step", step);
        obj.insert("time", nowtime);
        arr.append(obj);
    }
}

// 发送数据的线程
void WorkerThread::run(){
    // 初始化生产者
    Kafkaproducerclient *kafkaClient = new Kafkaproducerclient("localhost:9092", "fscanData", 0);
    kafkaClient->Init();
    // 轮循发送数据
    while(1){
        queue->available->acquire(); // 当队列没有数据会阻塞
        QByteArray data = queue->queue.dequeue();
        kafkaClient->Send(data);
        queue->total->release(); // 当队列数据达到最大容量1000时会阻塞
    }
}


