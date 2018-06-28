QT += core
QT -= gui
QT += network

TARGET = Sensor
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    fscan.cpp \
    queue.cpp \
    kafkaProducer/kafkaproducerclient.cpp \
    kafkaConsumer/kafkaconsumerclient.cpp \
    ebtcp.cpp \
    command.cpp \
    workhandle.cpp \
    udp.cpp \
    sendworker.cpp

HEADERS += \
    fscan.h \
    queue.h \
    kafkaProducer/kafkaproducerclient.h \
    kafkaConsumer/kafkaconsumerclient.h \
    ebtcp.h \
    command.h \
    workhandle.h \
    udp.h \
    sendworker.h

LIBS += -lrdkafka
LIBS += -lrdkafka++

INCLUDEPATH += $$PWD/KafkaConsumer/
INCLUDEPATH += $$PWD/KafkaProducer/


