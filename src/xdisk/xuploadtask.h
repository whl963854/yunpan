#ifndef XUPLOAD_TASK_H
#define XUPLOAD_TASK_H

#include "xcomtask.h"
#include <fstream>

typedef void(*UploadCBFunc)();

class XUploadTask :public XComTask
{
public:

    //接收到消息的回调
    virtual bool readCB(const XMsg* msg);

    //连接成功的消息回调
    virtual void connectedCB();

    ///写入数据回调函数
    virtual void writeCB();

    void setFilePath(std::string path);

    //上传成功后的回调函数
    UploadCBFunc uploadCB = nullptr;

private:
    //需要上传的文件路径
    std::string m_filePath = "";

    //暂时不支持大于2G文件
    int m_fileSize = 0;

    //读取文件
    std::ifstream ifs_;

};

#endif XUPLOAD_TASK_H
