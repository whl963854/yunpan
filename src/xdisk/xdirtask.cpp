#ifndef XDIRTASK_CPP
#define XDIRTASK_CPP

#include "xdirtask.h"
#include <iostream>
using namespace std;

//���ӳɹ�����Ϣ�ص�
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
    //���յ�����˷��͵�Ŀ¼
    switch (msg->type)
    {
    case MSG_DIRLIST: //���������ص�Ŀ¼�б�
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
