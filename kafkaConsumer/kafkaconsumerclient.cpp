#include "kafkaconsumerclient.h"
#include <QVector>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>


Kafkaconsumerclient::Kafkaconsumerclient(const QString &brokers, const QString &topics, QString groupid, qint32 nPartition=0, qint64 offset=0)
{
    m_strBrokers = brokers; // 代理
    m_strTopics = topics; // 主题
    m_strGroupid = groupid; // 消费者组id
    m_nPartition = nPartition; // 分区号
    m_nCurrentOffset = offset; // 偏移量

    com = new EB200Command(QHostAddress("192.168.2.200"), 5555); // 创建命令发送对象
}

Kafkaconsumerclient::~Kafkaconsumerclient(){
    Stop();
}

// 初始化
bool Kafkaconsumerclient::Init(){
    std::string errstr; // 错误信息

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL); // kafka配置
    if(!conf){
        qDebug()<<"RdKafka create global conf failed";
    }

    //设置broker list
    if(conf->set("metadata.broker.list", m_strBrokers.toStdString(), errstr) != RdKafka::Conf::CONF_OK){
        qDebug("Rdkafka conf set brokerlist failed::%s", errstr.c_str());
    }

    // 设置consummer group
    if(conf->set("group.id", m_strGroupid.toStdString(), errstr)!= RdKafka::Conf::CONF_OK){
        qDebug("RdKafka conf set group.id failed:%s", errstr.c_str());
    }
    QString strfetch_num = "10240000";
    // 每次从单个分区拉取消息的最大尺寸
    if(conf->set("max.partition.fetch.bytes", strfetch_num.toStdString(), errstr)!= RdKafka::Conf::CONF_OK){
        qDebug("RdKafka conf set max.partition failed:%s", errstr.c_str());
    }

    // 创建kafka消费者实例
    m_pKafkaConsumer = RdKafka::KafkaConsumer::create(conf, errstr);
    if(!m_pKafkaConsumer){
        qDebug()<<"failed to create consumer";
    }
    qDebug("% Created consumer %s", m_pKafkaConsumer->name());

    // 创建kafka topic的配置
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
    if(!tconf){
        qDebug()<<"RdKafka create topic conf failed";
        return false;
    }

//    if(tconf->set("auto.offset.reset", "latest", errstr)!=RdKafka::Conf::CONF_OK){
//        qDebug("Rdkafka conf set auto.offset.reset failed:", errstr.c_str());
//    }

    // 创建topic句柄
    m_pTopic = RdKafka::Topic::create(m_pKafkaConsumer, m_strTopics.toStdString(), tconf, errstr);
    if(!m_pTopic){
        qDebug("Rdkafka create topic failed:%s", errstr.c_str());
    }
    delete tconf;
    // 消费者订阅主题
    std::vector <std::string> topics;
    topics.push_back(m_strTopics.toStdString());
    RdKafka::ErrorCode resp = m_pKafkaConsumer->subscribe(topics);
    if(resp!=RdKafka::ERR_NO_ERROR){
        qDebug("failed to start consummer:%s", errstr.c_str());
    }


    return true;
}


void Kafkaconsumerclient::Msg_consume(RdKafka::Message *message, void *opaque){
    switch (message->err()){
        case RdKafka::ERR__TIMED_OUT:
            break;
    case RdKafka::ERR_NO_ERROR:
    {
        {
            QByteArray data = QByteArray((char*)message->payload()); // 从kafka端发来的命令
            qDebug()<<data;
            QJsonDocument doc(QJsonDocument::fromJson(data));

            QJsonObject obj = doc.object();

            // fscan->arr = QJsonArray(); // 清空json数组

            if(obj["cmd"].toString() == "fscan"){
                com->fscanSend(obj);
            }
            else if(obj["cmd"] == "dscan"){

            }
            else if(obj["cmd"] == "ifpan"){

            }
            else if(obj["cmd"] == "stop"){

            }
        }
        break;
    }
    case RdKafka::ERR__PARTITION_EOF:
        // qDebug("reachend the end of the queue, offset: %d", m_nLastOffset);
        break;
    }
}
void Kafkaconsumerclient::Start(int timeout_ms){
    RdKafka::Message *msg = NULL;
    m_bRun = true;
    while(m_bRun){
        msg = m_pKafkaConsumer->consume(timeout_ms);
        // qDebug()<<QByteArray((char*)msg->payload());
        Msg_consume(msg, NULL);
        delete msg;
        // m_pKafkaConsumer->poll(0);
    }
    m_pKafkaConsumer->close();
    // m_pKafkaConsumer->poll(1000);

    if(m_pTopic){
        delete m_pTopic;
        m_pTopic = NULL;
    }

    if(m_pKafkaConsumer){
        delete m_pKafkaConsumer;
        m_pKafkaConsumer = NULL;
    }
    // 销毁kafka实例
    RdKafka::wait_destroyed(5000);
}

// 停止kafka消费者客户端
void Kafkaconsumerclient::Stop(){
    m_bRun = false;
}













