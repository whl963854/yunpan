#ifndef XUPLOAD_TASK_H
#define XUPLOAD_TASK_H

#include "xcomtask.h"
#include <fstream>

typedef void(*UploadCBFunc)();

class XUploadTask :public XComTask
{
public:

    //���յ���Ϣ�Ļص�
    virtual bool readCB(const XMsg* msg);

    //���ӳɹ�����Ϣ�ص�
    virtual void connectedCB();

    ///д�����ݻص�����
    virtual void writeCB();

    void setFilePath(std::string path);

    //�ϴ��ɹ���Ļص�����
    UploadCBFunc uploadCB = nullptr;

private:
    //��Ҫ�ϴ����ļ�·��
    std::string m_filePath = "";

    //��ʱ��֧�ִ���2G�ļ�
    int m_fileSize = 0;

    //��ȡ�ļ�
    std::ifstream ifs_;

};

#endif XUPLOAD_TASK_H
