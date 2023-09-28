#ifndef XFILE_SERVER_TASK_H
#define XFILE_SERVER_TASK_H

#include "xcomtask.h"
#include <fstream>
#include <mutex>
class XFileServerTask :public XComTask
{
public:
    //���յ���Ϣ�Ļص�
    virtual bool readCB(const XMsg *msg);

    //���ر���Ϣ����ʱ�����ݽ����͵��˺�������ҵ��ģ������
    virtual void readCB(void *data, int size);

    ///д�����ݻص�����
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

    //����Ŀ¼��ȡ����Ϣ������Ŀ¼�б�
    void getDir(const XMsg *msg);

    //����ͻ��˵��ϴ�����
    void upload(const XMsg *msg);

    //����ͻ��˵���������
    void download(const XMsg *msg);

    void deleteFile(const XMsg* msg);

    //�ļ���С
    int m_fileSize = 0;

    //�ͻ��Ѿ��ϴ��Ĵ�С
    int m_recvSize = 0;

    ///��ǰ·��
    static std::string m_curDir;

    static std::mutex m_curDirMux;

    //д����յ��ļ�
    std::ofstream ofs_;

    //��ȡ�ļ�
    std::ifstream ifs_;

    std::string m_filePath;
    

};

#endif