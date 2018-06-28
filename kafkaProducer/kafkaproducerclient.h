#ifndef KAFKAPRODUCERCLIENT_H
#define KAFKAPRODUCERCLIENT_H
#include <librdkafka/rdkafkacpp.h>
#include <QtDebug>
#include <QDebug>
#include <QByteArray>
#include <QString>

class KafkaProducerDeliveryReportCallBack: public RdKafka::DeliveryReportCb{
public:
    void dr_cb(RdKafka::Message &message){
        qDebug("Message delivery for %d bytes %s", message.len(), message.errstr().c_str());
        if(message.key()){
            qDebug("Key: %s", *(message.key()));
        }

    }
};

class Kafkaproducerclient
{
public:
    Kafkaproducerclient(const QString &brokers, const QString &topics, int npartition=0);
    virtual ~Kafkaproducerclient();
    bool Init();
    void Send(const QByteArray &msg);
    void Stop();

private:
    RdKafka::Producer *m_pProducer = NULL;
    RdKafka::Topic *m_pTopic = NULL;
    KafkaProducerDeliveryReportCallBack m_producerDeliveryReportCallBack;
    QString m_strTopics;
    QString m_strBrokers;
    bool m_bRun = false;
    int m_npartition = 0;
};

#endif // KAFKAPRODUCERCLIENT_H
