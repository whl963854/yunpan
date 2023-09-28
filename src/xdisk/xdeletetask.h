#ifndef XDELETE_TASK_H
#define XDELETE_TASK_H

#include "xcomtask.h"
#include <fstream>

typedef void(*DeleteCBFunc)();
class XDeleteTask : public XComTask
{
public:
    //接收到消息的回调
    virtual bool readCB(const XMsg* msg);

    //连接成功的消息回调
    virtual void connectedCB();

    DeleteCBFunc deleteSuccessCB = nullptr;

    DeleteCBFunc deleteFailedCB = nullptr;

    void setFilePath(std::string path);

private:

    //需要删除的文件相对路径
    std::string m_filePath;
};


#endif XDELETE_TASK_H

