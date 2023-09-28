#ifndef XDIRTASK_H
#define XDIRTASK_H

#include "xcomtask.h"


typedef void(*DirCBFunc)(std::string dirs);

class XDirTask :public XComTask
{
public:

    //���յ���Ϣ�Ļص�
    virtual bool readCB(const XMsg* msg)override;

    //���ӳɹ�����Ϣ�ص�
    virtual void connectedCB()override;

    //��ȡĿ¼����õĻص�
    DirCBFunc dirCB = nullptr;

    void setServerRoot(std::string root);

private:

    //��������Ŀ¼
    std::string m_serverRoot = "";

};


#endif XDIRTASK_H
