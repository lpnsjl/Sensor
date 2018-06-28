#include <QCoreApplication>
#include <kafkaconsumerclient.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Kafkaconsumerclient *kafkaconsumer = new Kafkaconsumerclient("localhost:9092", "google", "1", 0, RdKafka::Topic::OFFSET_BEGINNING);
    if (!kafkaconsumer->Init())
        {
            fprintf(stderr, "kafka server initialize error\n");
            return -1;
        }

        kafkaconsumer->Start(1000);

        return 0;

    return a.exec();
}




