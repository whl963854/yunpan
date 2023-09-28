#ifndef XOWNLOAD_TASK_CPP
#define XOWNLOAD_TASK_CPP

#include"xdownloadtask.h"
#include <iostream>

using namespace std;

bool XDownloadTask::readCB(const XMsg* msg)
{
    switch (msg->type)
    {
    case MSG_DOWNLOAD_ACCEPT:
        //不接收消息，开始接收文件
        setIsRecvMsg(false);
        if (msg->data)
        {
            m_fileSize = atoi(msg->data);
        }
        else
        {
            close();
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}

//连接成功的消息回调
void XDownloadTask::connectedCB()
{
    if (m_filePath.empty())
    {
        close();
        return;
    }
    //3 发送下载文件请求
    string data = m_filePath;

    //获取文件名
    int pos = m_filePath.find_last_of('/');
    if (pos < 0)pos = 0;
    string filename = m_filePath.substr(pos, m_filePath.size() - pos);
    string path = m_localDir + filename;

    ofs_.open(path, ios::out | ios::binary);
    if (!ofs_.is_open())
    {
        cout << "open file " << path << " failed!" << endl;
        return;
    }
    cout << "open file " << path << " success!" << endl;

    XMsg msg;
    msg.type = MSG_DOWNLOAD_INFO;
    msg.data = (char*)data.c_str();
    msg.size = data.size() + 1;
    write(&msg);

}

//当关闭消息接收时，数据将发送到此函数，由业务模块重载
void XDownloadTask::readCB(void* data, int size)
{
    if (!data || size <= 0 || !ofs_.is_open())return;
    ofs_.write((char*)data, size);
    m_recvSize += size;
    if (m_recvSize == m_fileSize)
    {
        //下载成功
        if (downloadCB)
            downloadCB();
        cout << "file write end" << endl;
        ofs_.close();
        XMsg resmsg;
        resmsg.type = MSG_DOWNLOAD_COMPLETE;
        resmsg.size = 3; // +1发送\0
        resmsg.data = (char*)"OK";
        write(&resmsg);
    }
}

#endif XOWNLOAD_TASK_CPP