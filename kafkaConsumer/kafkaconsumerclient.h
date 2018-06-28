#ifndef KAFKACONSUMERCLIENT_H
#define KAFKACONSUMERCLIENT_H
#include <QString>
#include <librdkafka/rdkafkacpp.h>
#include "command.h"


class Kafkaconsumerclient
{
public:
    EB200Command *com;
    Kafkaconsumerclient(const QString &brokers, const QString &topics, QString groupid, qint32 nPartition, qint64 offset);
    virtual ~Kafkaconsumerclient();
    // 初始化
    bool Init();
    // 开始获取消息
    void Start(int timeout_ms);
    // 停止
    void Stop();
private:
    // 消费消息
    void Msg_consume(RdKafka::Message* message, void* opaque);
    QString m_strBrokers;
    QString m_strTopics;
    QString m_strGroupid;
    qint64 m_nLastOffset = 0;
    RdKafka::KafkaConsumer *m_pKafkaConsumer = NULL;
    RdKafka::Topic *m_pTopic = NULL;
    qint64 m_nCurrentOffset = RdKafka::Topic::OFFSET_BEGINNING;
    qint32 m_nPartition = 0;
    bool m_bRun = false;
};

#endif // KAFKACONSUMERCLIENT_H
