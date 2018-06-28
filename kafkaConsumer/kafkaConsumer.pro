QT += core
QT -= gui

TARGET = kafkaConsumer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    kafkaconsumerclient.cpp

DISTFILES += \
    kafkaConsumer.pro.user

HEADERS += \
    kafkaconsumerclient.h

LIBS += -lrdkafka
LIBS += -lrdkafka++

