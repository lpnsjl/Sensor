#include <QCoreApplication>
#include <QByteArray>
#include <QFile>

#include "kafkaproducerclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // 读取json配置文件内容
    QFile jsonFile("../project/radio/dscan.json");
    if(!jsonFile.open(QIODevice::ReadOnly)){
        qDebug()<<"can't open file fscan.json";
        return -1;
    }
    QByteArray data = jsonFile.readAll();


    Kafkaproducerclient *kafkaproducer = new Kafkaproducerclient("localhost:9092", "dscan", 3);
    kafkaproducer->Init();
    kafkaproducer->Send(data);
    return a.exec();
}

