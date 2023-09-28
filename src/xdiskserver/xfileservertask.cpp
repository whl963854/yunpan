#pragma warning (disable:4996)
#ifndef XFILE_SERVER_TASK_CPP
#define XFILE_SERVER_TASK_CPP

#include "xfileservertask.h"
#include "xtools.h"
#include <iostream>
using namespace std;

string XFileServerTask::m_curDir = "./";
std::mutex XFileServerTask::m_curDirMux;

//����Ŀ¼��ȡ����Ϣ������Ŀ¼�б�
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
    resmsg.size = dir.size()+1; // +1 ����\0
    resmsg.data = (char*)dir.c_str();
    write(&resmsg);
}

//����ͻ��˵��ϴ�����
void XFileServerTask::upload(const XMsg *msg)
{
    //1 ��ȡ�ļ������ļ���С
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

    //2 �򿪱����ļ�
    string filepath = getCurDir() + filename;
    ofs_.open(filepath, ios::out | ios::binary);
    if (!ofs_.is_open())
    {
        cout << "open file " << filepath << " failed!" << endl;
        return;
    }
    cout << "open file " << filepath << " success!" << endl;

    //3 �ظ�accept
    XMsg resmsg;
    resmsg.type = MSG_UPLOAD_ACCEPT;
    resmsg.size = 3; // +1����\0
    resmsg.data = (char*)"OK";
    write(&resmsg);

    //��������Ϣ����ʼ�����ļ�
    setIsRecvMsg(false);
    m_recvSize = 0;
}

//����ͻ��˵���������
void XFileServerTask::download(const XMsg *msg)
{
    if (!msg->data || !msg || msg->size <= 0)return;
    //���ļ�
    m_filePath = msg->data;
    if (m_filePath.empty())
        return;
    //��ȡ�ļ���
    ifs_.open(m_filePath.c_str(), ios::in | ios::binary | ios::ate);
    if (!ifs_.is_open())
    {
        cerr << "open file " << m_filePath << " failed!" << endl;
        return;
    }
    //2 ��ȡ�ļ����� �ļ���С  filename.zip,1024
    m_fileSize = ifs_.tellg();
    ifs_.seekg(0, ios::beg);
    cout << "open file " << m_filePath << " success!" << endl;

    //�ظ���Ϣ MSG_DOWNLOAD_ACCEPT
    char buf[32] = { 0 };
    //_CRT_SECURE_NO_WARNINGS
    sprintf(buf, "%d", m_fileSize);
    XMsg resmsg;
    resmsg.type = MSG_DOWNLOAD_ACCEPT;
    resmsg.size = strlen(buf)+1; // +1����\0
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
        cout << "ɾ���ɹ�" << endl;
        resmsg.type = MSG_DELETE_SUCCESS;
    }
    else
    {
        cout << "ɾ��ʧ��" << endl;
        resmsg.type = MSG_DELETE_FAILED;
    }
    char buf[32] = { 0 };
    sprintf(buf, "%d", m_fileSize);
    resmsg.size = strlen(buf) + 1; // +1����\0
    resmsg.data = buf;
    write(&resmsg);
}

//д�����ݻص�����
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

//���ر���Ϣ����ʱ�����ݽ����͵��˺�������ҵ��ģ������
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
        resmsg.size = 3; // +1����\0
        resmsg.data = (char*)"OK";
        write(&resmsg);
    }
}

bool XFileServerTask::readCB(const XMsg *msg)
{
    switch (msg->type)
    {
    case MSG_GETDIR:
        cout << "MSG_GETDIR  ��ȡ�ļ�Ŀ¼" << endl;
        getDir(msg);
        break;
    case MSG_UPLOAD_INFO:
        cout << "MSG_UPLOAD_INFO  ��ȡ�ϴ���Ϣ" << endl;
        upload(msg);
        break;
    case MSG_DOWNLOAD_INFO:
        cout << "MSG_DOWNLOAD_INFO  ��ȡ������Ϣ" << endl;
        download(msg);
        break;
    case MSG_DOWNLOAD_COMPLETE:
        cout << "MSG_DOWNLOAD_COMPLETE  �������" << endl;
        //����������Դ
        close();
        return false;
        break;
    case MSG_DELETE_INFO:
        cout << "����ɾ���ƶ��ļ�" << endl;
        deleteFile(msg);
        break;
    default:
        break;
    }
    return true;
}

#endif XFILE_SERVER_TASK_CPP