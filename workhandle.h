#ifndef WORKHANDLE_H
#define WORKHANDLE_H

#include <QObject>
#include <QThread>

class WorkHandle : public QThread
{
public:
    virtual void run();
    // explicit WorkHandle(QObject *parent = 0);

};

#endif // WORKHANDLE_H
