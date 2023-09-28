#ifndef XFILE_SERVER_TASK_H
#define XFILE_SERVER_TASK_H

#include "xcomtask.h"
#include <fstream>
#include <mutex>
class XFileServerTask :public XComTask
{
public:
    //接收到消息的回调
    virtual bool readCB(const XMsg *msg);

    //当关闭消息接收时，数据将发送到此函数，由业务模块重载
    virtual void readCB(void *data, int size);

    ///写入数据回调函数
    virtual void writeCB();

    static void setCurDir(std::string dir)
    {
        m_curDirMux.lock();
        m_curDir = dir;
        m_curDirMux.unlock();
    }

    static std::string getCurDir()
    {
        m_curDirMux.lock();
        std::string dir = m_curDir;
        m_curDirMux.unlock();
        return dir;
    }

private:

    //处理目录获取的消息，返回目录列表
    void getDir(const XMsg *msg);

    //处理客户端的上传请求
    void upload(const XMsg *msg);

    //处理客户端的下载请求
    void download(const XMsg *msg);

    void deleteFile(const XMsg* msg);

    //文件大小
    int m_fileSize = 0;

    //客户已经上传的大小
    int m_recvSize = 0;

    ///当前路径
    static std::string m_curDir;

    static std::mutex m_curDirMux;

    //写入接收的文件
    std::ofstream ofs_;

    //读取文件
    std::ifstream ifs_;

    std::string m_filePath;
    

};

#endif