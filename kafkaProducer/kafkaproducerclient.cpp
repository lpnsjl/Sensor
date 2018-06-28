#include "kafkaproducerclient.h"

Kafkaproducerclient::Kafkaproducerclient(const QString &brokers, const QString &topics, int npartition)
{
    m_bRun = true;
    m_strBrokers = brokers;
    m_strTopics = topics;
    m_npartition = npartition;
}

Kafkaproducerclient::~Kafkaproducerclient(){
    Stop();
}

bool Kafkaproducerclient::Init(){
    std::string errstr = ""; // 错误接收对象
    // 创建配置对象
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    // 设置borkerlist
    if(conf->set("metadata.broker.list", m_strBrokers.toStdString(), errstr) != RdKafka::Conf::CONF_OK){
        qDebug("RdKafka conf set brokerkist failed: %s", errstr.c_str());
    }

    // 设置发送消息回调函数
    conf->set("dr_cb", &m_producerDeliveryReportCallBack, errstr);

    // 创建生产者
    m_pProducer = RdKafka::Producer::create(conf, errstr);
    if(!m_pProducer){
        qDebug("Failed to create producer: ", errstr.c_str());
        return false;
    }

    qDebug("% Create producer ", m_pProducer->name());

    // 创建主题,由服务器配置主题
    m_pTopic = RdKafka::Topic::create(m_pProducer, m_strTopics.toStdString(), tconf, errstr);
    if(!m_pTopic){
        qDebug("Failed to create topic: ", errstr.c_str());
        return false;
    }

    return true;

}

// 生产者发送消息
void Kafkaproducerclient::Send(const QByteArray &msg){
    if(!m_bRun)
        return;

    // 生产消息
    RdKafka::ErrorCode resp = m_pProducer->produce(m_pTopic, m_npartition, RdKafka::Producer::RK_MSG_COPY, (char*)msg.data(), msg.size(), NULL, NULL);
    if(resp != RdKafka::ERR_NO_ERROR)
        qDebug("Producer failed: %s", RdKafka::err2str(resp));
    else
        qDebug("Produced message ( %d bytes)", msg.size());

    m_pProducer->poll(0);
    // 等待消息发送
    while(m_bRun && m_pProducer->outq_len()>0){
        qDebug("Waiting for %d", m_pProducer->outq_len());
        m_pProducer->poll(100);
    }
}


void Kafkaproducerclient::Stop(){
    delete m_pProducer;
    delete m_pTopic;
}


/*
 * 生产者客户端处理流程
 * 创建顶级配置conf // conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL)
 * 设置顶级配置    // conf->set("metadata.broker.list", m_strBrokers.toStdString(), errstr)
 * 设置生产消息回调函数  // conf->set("dr_cb", &m_producerDeliveryReportCallBack, errstr);
 * 创建主题配置tconf // tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC)
 * 设置主题配置  // tconf->set("auto.offset.reset", "smallest", errstr)
 * 创建主题  // m_pTopic = RdKafka::Topic::create(m_pKafkaConsumer, m_strTopics.toStdString(), tconf, errstr)
 * 创建生产者 // m_pKafkaConsumer = RdKafka::Consumer::create(conf, errstr);
 * 生产消息 // m_pProducer->produce(m_pTopic, m_npartition, RdKafka::Producer::RK_MSG_COPY, (char*)msg.data(), msg.size(), NULL, NULL)
 * 停止生产，销毁生产者,主题  // delete m_pProducer;  delete m_pTopic;
*/





















