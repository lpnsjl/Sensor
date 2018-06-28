QT += core
QT -= gui

TARGET = kafkaProducer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    kafkaproducerclient.cpp

HEADERS += \
    kafkaproducerclient.h


LIBS += -lrdkafka
LIBS += -lrdkafka++
