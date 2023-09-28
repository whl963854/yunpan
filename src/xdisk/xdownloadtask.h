#ifndef XOWNLOAD_TASK_H
#define XOWNLOAD_TASK_H

#include "xcomtask.h"
#include <fstream>


typedef void(*DownloadCBFunc)();

class XDownloadTask :public XComTask
{
public:

    //���ر���Ϣ����ʱ�����ݽ����͵��˺�������ҵ��ģ������
    virtual void readCB(void* data, int size);

    //���յ���Ϣ�Ļص�
    virtual bool readCB(const XMsg* msg);

    //���ӳɹ�����Ϣ�ص�
    virtual void connectedCB();

    DownloadCBFunc downloadCB = nullptr;

    void setFilePath(std::string path) { this->m_filePath = path; }
    void setLocalDir(std::string localdir) { this->m_localDir = localdir; }

private:
    //�ļ���С
    int m_fileSize = 0;

    //��Ҫ���ص��ļ����·��
    std::string m_filePath;

    //���ص����ص�Ŀ¼
    std::string m_localDir;

    //�ͻ��Ѿ����صĴ�С
    int m_recvSize = 0;

    //д����յ��ļ�
    std::ofstream ofs_;
};



#endif XOWNLOAD_TASK_H