#include "workhandle.h"
#include "fscan.h"
#include "udp.h"



void WorkHandle::run(){
    // Udp *u = new Udp();
    Fscan *fscan = new Fscan(QHostAddress("192.168.2.5"), 9000);
    exec();
}
