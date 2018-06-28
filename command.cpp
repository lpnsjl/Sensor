#include "command.h"
#include <QString>
#include <QJsonArray>
#include <QHostAddress>

EB200Command::EB200Command(QHostAddress ip, quint16 port){
    tsock = new EBtcp(ip, port); // 创建tcp套接字接口
}

void EB200Command::fscanSend(QJsonObject jsonObj){

    /***先停止以前的命令***/
    tsock->sendSCPI("abort\n");
    tsock->sendSCPI("display:menu:default");

    /***发送命令***/
    QString command;
    // 清除接收机的设置
    command = QString("trace:udp:flag:off '%1', %2, 'opt', 'VOLTage:AC', 'FREQuency:RX', 'swap'\n").arg(jsonObj["ip"].toString()).arg(jsonObj["port"].toInt());
    tsock->sendSCPI(command);
    tsock->sendSCPI("*idn?\n");
    tsock->recv();
    // 设置频率为睡眠模式
    command = QString("frequency:mode %1\n").arg(jsonObj["mode"].toString());
    tsock->sendSCPI(command);
    //睡眠数量设置为10
    command = QString("sweep:count %1\n").arg(jsonObj["count"].toInt());
    tsock->sendSCPI(command);
    // 设置开始频率为118MHz
    command = QString("frequency:start %1\n").arg(jsonObj["startFre"].toString());
    tsock->sendSCPI(command);
    // 设置停止频率138MHz
    command = QString("frequency:stop %1\n").arg(jsonObj["stopFre"].toString());
    tsock->sendSCPI(command);
    // 设置频率步长25KHz
    command = QString("sweep:step %1\n").arg(jsonObj["step"].toString());
    tsock->sendSCPI(command);
    // 开启睡眠控制
    command = QString("sweep:control %1\n").arg(jsonObj["control"].toString());
    tsock->sendSCPI(command);
    // 设置停留时间为3秒
    command = QString("sweep:dwel %1\n").arg(jsonObj["dwell time"].toString());
    tsock->sendSCPI(command);
    // 设置保持时间1秒
    command = QString("sweep:hold:time %1\n").arg(jsonObj["hold time"].toString());
    tsock->sendSCPI(command);
    // 开启不间隔输出模式
    command = QString("output:squelch %1\n").arg(jsonObj["squelch"].toString());
    tsock->sendSCPI(command);
    // 设置门限10dbv
    command = QString("output:squelch:threshold %1\n").arg(jsonObj["threshold"].toString());
    tsock->sendSCPI(command);
    // 设置带宽9KHz
    command = QString("bandwidth %1\n").arg(jsonObj["bandwidth"].toString());
    tsock->sendSCPI(command);
    // 设置am解调模式
    command = QString("demodulation %1\n").arg(jsonObj["demodulation"].toString());
    tsock->sendSCPI(command);
    // 设置默认测量时间
    command = QString("measure:time %1\n").arg(jsonObj["measure time"].toString());
    tsock->sendSCPI(command);
    // 设置连续测量模式
    command = QString("measure:mode %1\n").arg(jsonObj["measure mode"].toString());
    tsock->sendSCPI(command);
    // 关闭自动频率控制
    command = QString("sense:frequency:afc %1\n").arg(jsonObj["afc"].toString());
    tsock->sendSCPI(command);
    // 设置自动生成控制
    command = QString("sense:gcontrol:mode %1\n").arg(jsonObj["gcontrol mode"].toString());
    tsock->sendSCPI("sense:gcontrol:mode agc\n");
    QJsonArray flag = jsonObj["flag"].toArray();
    // 设置标签
    command = QString("trace:udp:tag:on '%1', %2, %3\n").arg(jsonObj["ip"].toString()).arg(jsonObj["port"].toInt()).arg(jsonObj["tag"].toString());
    // qDebug()<<command;
    tsock->sendSCPI(command);
    // 设置标志
    command = QString("trace:udp:flag:on '%1', %2, ").arg(jsonObj["ip"].toString()).arg(jsonObj["port"].toInt());
    for(int i = 0; i<flag.size()-1; i++){
        command += QString("'%1',").arg(flag[i].toString());
    }
    command += QString("'%1'\n").arg(flag[flag.size()-1].toString());
    tsock->sendSCPI(command);

    tsock->sendSCPI("init\n");
}


void EB200Command::dscanSend(QJsonObject jsonObj){
    // tsock->connect_recevier(QHostAddress("192.168.2.200"), 5555);

    /***先停止以前的命令***/
    tsock->sendSCPI("abort\n");
    tsock->sendSCPI("display:menu:default");

    /***发送命令***/
    QString command;
    command = QString("trace:udp:flag:off '%1', %2, 'opt', 'VOLTage:AC', 'FREQuency:RX', 'swap'\n").arg(jsonObj["ip"].toString()).arg(jsonObj["port"].toInt());
    tsock->sendSCPI(command);
    tsock->sendSCPI("*idn?\n");
    tsock->recv();
    // 设置频率为dscan模式
    command = QString("frequency:mode %1\n").arg(jsonObj["mode"].toString());
    tsock->sendSCPI(command);
    //睡眠数量设置为
    command = QString("dscan:count %1\n").arg(jsonObj["count"].toInt());
    tsock->sendSCPI(command);
    // 设置为高速获取数据
    command = QString("frequency:dscan:speed %1\n").arg(jsonObj["speed"].toString());
    tsock->sendSCPI(command);
    // 设置开始频率为
    command = QString("frequency:dscan:start %1\n").arg(jsonObj["startFre"].toString());
    tsock->sendSCPI(command);
    // 设置停止频率
    command = QString("frequency:dscan:stop %1\n").arg(jsonObj["stopFre"].toString());
    tsock->sendSCPI(command);
    // 设置光标频率
    command = QString("frequency:dscan:marker %1\n").arg(jsonObj["marker"].toString());
    tsock->sendSCPI(command);
    // 设置参考电平
    command = QString("voltage:ac:range %1\n").arg(jsonObj["range"].toInt());
    tsock->sendSCPI(command);
    // 设置频率步长25KHz
    command = QString("frequency:dscan:step %1\n").arg(jsonObj["step"].toString());
    tsock->sendSCPI(command);
    // 开启不间隔输出模式
    command = QString("output:squelch %1\n").arg(jsonObj["squelch"].toString());
    tsock->sendSCPI(command);
    // 设置门限10dbv
    command = QString("output:squelch:threshold %1\n").arg(jsonObj["threshold"].toString());
    tsock->sendSCPI(command);
    // 设置am解调模式
    command = QString("demodulation %1\n").arg(jsonObj["demodulation"].toString());
    tsock->sendSCPI(command);
    // 设置带宽
    command = QString("bandwidth %1\n").arg(jsonObj["bandwidth"].toString());
    tsock->sendSCPI(command);
    // 设置默认测量时间
    command = QString("measure:time %1\n").arg(jsonObj["measure time"].toString());
    tsock->sendSCPI(command);
    // 设置连续测量模式
    command = QString("measure:mode %1\n").arg(jsonObj["measure mode"].toString());
    tsock->sendSCPI(command);
    // 关闭自动频率控制
    command = QString("sense:frequency:afc %1\n").arg(jsonObj["afc"].toString());
    tsock->sendSCPI(command);
    // 设置自动生成控制
    command = QString("sense:gcontrol:mode %1\n").arg(jsonObj["gcontrol mode"].toString());
    tsock->sendSCPI("sense:gcontrol:mode agc\n");
    QJsonArray flag = jsonObj["flag"].toArray();
    // 设置标签
    command = QString("trace:udp:tag:on '%1', %2, %3\n").arg(jsonObj["ip"].toString()).arg(jsonObj["port"].toInt()).arg(jsonObj["tag"].toString());
    tsock->sendSCPI(command);
    // 设置标志
    command = QString("trace:udp:flag:on '%1', %2, ").arg(jsonObj["ip"].toString()).arg(jsonObj["port"].toInt());
    for(int i = 0; i<flag.size()-1; i++){
        command += QString("'%1',").arg(flag[i].toString());
    }
    command += QString("'%1'\n").arg(flag[flag.size()-1].toString());
    tsock->sendSCPI(command);

    // 开始扫描
    tsock->sendSCPI("init\n");
}

void EB200Command::ifpanSend(QJsonObject jsonObj){


}


void EB200Command::stop(){
    /***停止接收机***/
    tsock->sendSCPI("abort\n");
    tsock->sendSCPI("display:menu:default");
}
















