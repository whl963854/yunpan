#pragma warning (disable:4996)
#ifndef XFILE_SERVER_TASK_CPP
#define XFILE_SERVER_TASK_CPP

#include "xfileservertask.h"
#include "xtools.h"
#include <iostream>
using namespace std;

string XFileServerTask::m_curDir = "./";
std::mutex XFileServerTask::m_curDirMux;

//处理目录获取的消息，返回目录列表
void XFileServerTask::getDir(const XMsg *msg)
{
    if (!msg->data)return;
    string root = msg->data;
    if (root.empty())
    {
        root = "./";
    }
    setCurDir(root);
    string dir = getDirData(root);
    XMsg resmsg;
    resmsg.type = MSG_DIRLIST;
    resmsg.size = dir.size()+1; // +1 发送\0
    resmsg.data = (char*)dir.c_str();
    write(&resmsg);
}

//处理客户端的上传请求
void XFileServerTask::upload(const XMsg *msg)
{
    //1 获取文件名和文件大小
    if (!msg->data || !msg || msg->size <= 0)return;
    string str = msg->data;
    if (str.empty())return;
    int pos = str.find_last_of(',');
    if (pos <= 0)return;
    string filename = str.substr(0, pos);
    int sizepos = pos + 1;
    if (sizepos >= str.size())
        return;
    string tmp = str.substr(sizepos, str.size() - sizepos);
    cout << filename << ":" << tmp << endl;
    m_fileSize = atoi(tmp.c_str());
    if (m_fileSize <= 0)
        return;

    //2 打开本地文件
    string filepath = getCurDir() + filename;
    ofs_.open(filepath, ios::out | ios::binary);
    if (!ofs_.is_open())
    {
        cout << "open file " << filepath << " failed!" << endl;
        return;
    }
    cout << "open file " << filepath << " success!" << endl;

    //3 回复accept
    XMsg resmsg;
    resmsg.type = MSG_UPLOAD_ACCEPT;
    resmsg.size = 3; // +1发送\0
    resmsg.data = (char*)"OK";
    write(&resmsg);

    //不接受消息，开始接收文件
    setIsRecvMsg(false);
    m_recvSize = 0;
}

//处理客户端的下载请求
void XFileServerTask::download(const XMsg *msg)
{
    if (!msg->data || !msg || msg->size <= 0)return;
    //打开文件
    m_filePath = msg->data;
    if (m_filePath.empty())
        return;
    //获取文件名
    ifs_.open(m_filePath.c_str(), ios::in | ios::binary | ios::ate);
    if (!ifs_.is_open())
    {
        cerr << "open file " << m_filePath << " failed!" << endl;
        return;
    }
    //2 获取文件名称 文件大小  filename.zip,1024
    m_fileSize = ifs_.tellg();
    ifs_.seekg(0, ios::beg);
    cout << "open file " << m_filePath << " success!" << endl;

    //回复消息 MSG_DOWNLOAD_ACCEPT
    char buf[32] = { 0 };
    //_CRT_SECURE_NO_WARNINGS
    sprintf(buf, "%d", m_fileSize);
    XMsg resmsg;
    resmsg.type = MSG_DOWNLOAD_ACCEPT;
    resmsg.size = strlen(buf)+1; // +1发送\0
    resmsg.data = buf;
    write(&resmsg);

}

void XFileServerTask::deleteFile(const XMsg* msg)
{
    if (!msg->data || !msg || msg->size <= 0)return;
    string filePath = msg->data;
    int pos = filePath.find_last_of('/');
    if (pos <= 0)return;
    string filename = filePath.substr(pos+1);
    XMsg resmsg;
    if (remove(filePath.c_str()) == 0)
    {
        cout << "删除成功" << endl;
        resmsg.type = MSG_DELETE_SUCCESS;
    }
    else
    {
        cout << "删除失败" << endl;
        resmsg.type = MSG_DELETE_FAILED;
    }
    char buf[32] = { 0 };
    sprintf(buf, "%d", m_fileSize);
    resmsg.size = strlen(buf) + 1; // +1发送\0
    resmsg.data = buf;
    write(&resmsg);
}

//写入数据回调函数
void XFileServerTask::writeCB()
{
    if (!ifs_.is_open())return;
    ifs_.read(m_readBuf, sizeof(m_readBuf));
    int len = ifs_.gcount();
    if (len <= 0)
    {
        ifs_.close();
        return;
    }
    write(m_readBuf, len);
    if (ifs_.eof())
    {
        ifs_.close();
    }
}

//当关闭消息接收时，数据将发送到此函数，由业务模块重载
void XFileServerTask::readCB(void *data, int size)
{
    if (!data || size <= 0||!ofs_.is_open())return;
    ofs_.write((char*)data, size);
    m_recvSize += size;
    if (m_recvSize == m_fileSize)
    {
        cout << "file write end" << endl;
        ofs_.close();
        XMsg resmsg;
        resmsg.type = MSG_UPLOAD_COMPLETE;
        resmsg.size = 3; // +1发送\0
        resmsg.data = (char*)"OK";
        write(&resmsg);
    }
}

bool XFileServerTask::readCB(const XMsg *msg)
{
    switch (msg->type)
    {
    case MSG_GETDIR:
        cout << "MSG_GETDIR  获取文件目录" << endl;
        getDir(msg);
        break;
    case MSG_UPLOAD_INFO:
        cout << "MSG_UPLOAD_INFO  获取上传信息" << endl;
        upload(msg);
        break;
    case MSG_DOWNLOAD_INFO:
        cout << "MSG_DOWNLOAD_INFO  获取下载信息" << endl;
        download(msg);
        break;
    case MSG_DOWNLOAD_COMPLETE:
        cout << "MSG_DOWNLOAD_COMPLETE  下载完成" << endl;
        //清理网络资源
        close();
        return false;
        break;
    case MSG_DELETE_INFO:
        cout << "请求删除云端文件" << endl;
        deleteFile(msg);
        break;
    default:
        break;
    }
    return true;
}

#endif XFILE_SERVER_TASK_CPP