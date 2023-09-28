#ifndef XUPLOAD_TASK_CPP
#define XUPLOAD_TASK_CPP

#include "xuploadtask.h"
#include <iostream>

using namespace std;

//���յ���Ϣ�Ļص�
bool XUploadTask::readCB(const XMsg* msg)
{
    switch (msg->type)
    {
    case MSG_UPLOAD_ACCEPT:
        beginWrite();
        break;
    case MSG_UPLOAD_COMPLETE:
        //����ˢ��
        if (uploadCB)
            uploadCB();
        break;
    default:
        break;
    }
    return true;
}

///д�����ݻص�����
void XUploadTask::writeCB()
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

void XUploadTask::setFilePath(std::string path)
{
    this->m_filePath = path;
}

//���ӳɹ�����Ϣ�ص�
void XUploadTask::connectedCB()
{
    if (m_filePath.empty())
    {
        cerr << "XUploadTask connectedCB m_filePath is empty!" << endl;
        return;
    }

    //1 �򿪱����ļ�
    //��ת����β����ȡ�ļ���С
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
    string filename = "";
    int pos = m_filePath.find_last_of('/');
    if (pos < 0)pos = 0;
    filename = m_filePath.substr(pos, m_filePath.size() - pos);
    char data[1024] = { 0 };
    sprintf(data, "%s,%d", filename.c_str(), m_fileSize);

    //3 �����ϴ��ļ�����
    XMsg msg;
    msg.type = MSG_UPLOAD_INFO;
    msg.data = data;
    msg.size = strlen(data) + 1;
    write(&msg);
}

#endif XUPLOAD_TASK_CPP