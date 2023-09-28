#ifndef XOWNLOAD_TASK_H
#define XOWNLOAD_TASK_H

#include "xcomtask.h"
#include <fstream>


typedef void(*DownloadCBFunc)();

class XDownloadTask :public XComTask
{
public:

    //当关闭消息接收时，数据将发送到此函数，由业务模块重载
    virtual void readCB(void* data, int size);

    //接收到消息的回调
    virtual bool readCB(const XMsg* msg);

    //连接成功的消息回调
    virtual void connectedCB();

    DownloadCBFunc downloadCB = nullptr;

    void setFilePath(std::string path) { this->m_filePath = path; }
    void setLocalDir(std::string localdir) { this->m_localDir = localdir; }

private:
    //文件大小
    int m_fileSize = 0;

    //需要下载的文件相对路径
    std::string m_filePath;

    //下载到本地的目录
    std::string m_localDir;

    //客户已经下载的大小
    int m_recvSize = 0;

    //写入接收的文件
    std::ofstream ofs_;
};



#endif XOWNLOAD_TASK_H