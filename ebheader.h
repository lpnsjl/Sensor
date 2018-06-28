#ifndef EBHEADER
#define EBHEADER
// eb200的通用头
struct EB200Header{
    unsigned int magicNum; // 接收机品牌信息
    unsigned short versionMinor; // 接收机次要版本号
    unsigned short versionMajor; // 接收机主要版本号
    unsigned short sequenceNum; // 数据包的序号
    char reserved[6]; // 保留字节数
    unsigned short tag; // 接收机扫描方式的标签
    unsigned short length; // 属性长度 = 数据包总长度 - 20(tag以上所有的字节长度,包含tag)
    unsigned short traceNum; // 跟踪数据的数目
    char reserved2; // 保留字节
    unsigned char optHeaderLength; // 可选头的字节数
    unsigned int traceSelecterFlag; // 跟踪选择标志
};
#define EB200_HEADER sizeof(EB200Header)

// fscan的头部
struct fscanHeader{
    short cycleCount; // 测量周期数
    short holdTime; // 保持时间
    short dwellTime; // 停留时间
    short direcation; // 扫描方式,up|down(1|0)
    short stopSingle;// 停止信号
    short unknown; // 暂时不知道
    unsigned int startFre; // 开始频率
    unsigned int stopFre; // 停止频率
    unsigned int step; // 步长
};
#define FSCAN_HEADER sizeof(fscanHeader)

// dscan的头部
struct dscanHeader{
    unsigned int startFre; // 开始频率
    unsigned int stopFre; // 停止频率
    unsigned int stepFre; // 带宽/2
    unsigned int markerFre; // 光标频率
    short bandZoom; // 带宽展开
    short rng; // 参考电平
    short reserved; // 保留字节
};
#define DSCAN_HEADER sizeof(dscanHeader)

// ifpan的头部
struct ifpanHeader{
    unsigned int frequency; // 中心频率
    unsigned int span; // 扫描范围
    short reserved; // 保留字节
    short flag; // 计算标志
    unsigned int time; // 测量时间(单位 微秒)
};
#define IFPAN_HEADER sizeof(ifpanHeader)

// 数据项结构
struct traceHeader{
    short level; // 电平
    unsigned int frequency; // 频率
};
#define TRACE_HRADER sizeof(traceHeader)

#endif // EBHEADER

