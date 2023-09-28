#ifndef XDIRTASK_H
#define XDIRTASK_H

#include "xcomtask.h"


typedef void(*DirCBFunc)(std::string dirs);

class XDirTask :public XComTask
{
public:

    //接收到消息的回调
    virtual bool readCB(const XMsg* msg)override;

    //连接成功的消息回调
    virtual void connectedCB()override;

    //获取目录后调用的回调
    DirCBFunc dirCB = nullptr;

    void setServerRoot(std::string root);

private:

    //服务器的目录
    std::string m_serverRoot = "";

};


#endif XDIRTASK_H
