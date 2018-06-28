#ifndef COMMAND_H
#define COMMAND_H
#include "ebtcp.h"
#include <QJsonObject>
#include <QHostAddress>

// 处理eb200设备的命令发送
class EB200Command
{
public:
    EBtcp *tsock; // tcp套接字接口
    EB200Command(QHostAddress ip, quint16 port);
    void fscanSend(QJsonObject jsonObj); // 发送fscan命令
    void dscanSend(QJsonObject jsonObj); // 发送dscan命令
    void ifpanSend(QJsonObject jsonObj); // 发送ifpan命令
    void stop(); // 停止接收机
};

#endif // COMMAND_H
