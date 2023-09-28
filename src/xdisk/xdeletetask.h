#ifndef XDELETE_TASK_H
#define XDELETE_TASK_H

#include "xcomtask.h"
#include <fstream>

typedef void(*DeleteCBFunc)();
class XDeleteTask : public XComTask
{
public:
    //���յ���Ϣ�Ļص�
    virtual bool readCB(const XMsg* msg);

    //���ӳɹ�����Ϣ�ص�
    virtual void connectedCB();

    DeleteCBFunc deleteSuccessCB = nullptr;

    DeleteCBFunc deleteFailedCB = nullptr;

    void setFilePath(std::string path);

private:

    //��Ҫɾ�����ļ����·��
    std::string m_filePath;
};


#endif XDELETE_TASK_H

