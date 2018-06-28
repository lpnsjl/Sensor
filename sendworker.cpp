#include "sendworker.h"
#include "kafkaConsumer/kafkaconsumerclient.h"

SendWorker::SendWorker()
{

}


void SendWorker::run(){
    Kafkaconsumerclient *kafkaconsumer = new Kafkaconsumerclient("localhost:9092", "fscan", "1", 0, 0);
    kafkaconsumer->Init();
    kafkaconsumer->Start(500);
}
