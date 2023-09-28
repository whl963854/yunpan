#ifndef XCOM_TASK_H
#define XCOM_TASK_H

#include <string>
#include "xtask.h"
#include"xmsg.h"

//通信
class XCOM_API XComTask : public XTask
{
public:

    ///初始化bufferevent，客户端建立连接
    virtual bool init() override;

    virtual void close();

    ///事件回调函数
    virtual void eventCB(short what);

    ///读取数据回调函数
    virtual void readCB();

    //激活写入回调
    virtual void beginWrite();

    //发送消息
    virtual bool write(const XMsg* msg);

    virtual bool write(const void* data, int size);

    void setIsRecvMsg(bool isrecv);

    void setServerIp(std::string ip);

    void setPort(int port);

    bool getIsRecvMsg();

    std::string getServerIp();

    int getPort();

    
public:
    // ***由业务类重载的函数***
    //连接成功的消息回调
    virtual void connectedCB() {};

    //当关闭消息接收时，数据将发送到此函数,写入文件
    virtual void readCB(void* data, int size) {};

    //接收到消息的回调
    //返回true正常，返回false退出当前的消息处理,不处理下一条消息
    virtual bool readCB(const XMsg* msg) = 0;

    ///写入数据回调函数
    virtual void writeCB() {};

protected:

    //读取缓存
    char m_readBuf[4096] = { 0 };

private:

    /// 服务器IP
    std::string m_serverIp = "";

    ///服务器端口
    int m_serverPort = 0;

    struct bufferevent* m_bev = 0;

    //数据包缓存
    XMsg m_msg;

    //是否接收消息
    //接收的消息会调用 void readCB(const XMsg *msg)
    //不接收消息调用 void readCB(void *data, int size)
    bool m_isRecvMsg = true;

};

#endif // XCOM_TASK_H 