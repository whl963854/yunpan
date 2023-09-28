#ifndef XDIRTASK_CPP
#define XDIRTASK_CPP

#include "xdirtask.h"
#include <iostream>
using namespace std;

//连接成功的消息回调
void XDirTask::connectedCB()
{
    XMsg msg;
    msg.type = MSG_GETDIR;
    msg.size = m_serverRoot.size() + 1;
    msg.data = (char*)m_serverRoot.c_str();
    write(&msg);
}

bool XDirTask::readCB(const XMsg* msg)
{
    //接收到服务端发送的目录
    switch (msg->type)
    {
    case MSG_DIRLIST: //服务器返回的目录列表
        cout << "GET MSG_DIRLIST SUCCEED" << endl;
        dirCB(msg->data);
        break;
    default:
        break;
    }
    return true;
}

void XDirTask::setServerRoot(std::string root)
{
    this->m_serverRoot = root;
}
#endif //XDIRTASK_CPP
