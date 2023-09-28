#ifndef XDELETE_TASK_CPP
#define XDELETE_TASK_CPP


#include "xdeletetask.h"
#include <iostream>

using namespace std;

bool XDeleteTask::readCB(const XMsg* msg)
{
	cout << "XDeleteTask ReadBC" << endl;
	switch (msg->type)
	{
	case MSG_DELETE_SUCCESS:
		if (deleteSuccessCB)
			deleteSuccessCB();
		break;
	case MSG_DELETE_FAILED:
		if (deleteFailedCB)
			deleteFailedCB();
		break;
	default:
		break;
	}
	return false;
}

void XDeleteTask::connectedCB()
{
    // 发送删除文件请求
    XMsg msg;
    msg.type = MSG_DELETE_INFO;
    msg.data = (char*)m_filePath.c_str();
    msg.size = strlen(msg.data) + 1;
    write(&msg);
}

void XDeleteTask::setFilePath(std::string path)
{
	m_filePath = path;
}

#endif XDELETE_TASK_CPP