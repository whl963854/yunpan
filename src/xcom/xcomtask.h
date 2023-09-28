#ifndef XCOM_TASK_H
#define XCOM_TASK_H

#include <string>
#include "xtask.h"
#include"xmsg.h"

//ͨ��
class XCOM_API XComTask : public XTask
{
public:

    ///��ʼ��bufferevent���ͻ��˽�������
    virtual bool init() override;

    virtual void close();

    ///�¼��ص�����
    virtual void eventCB(short what);

    ///��ȡ���ݻص�����
    virtual void readCB();

    //����д��ص�
    virtual void beginWrite();

    //������Ϣ
    virtual bool write(const XMsg* msg);

    virtual bool write(const void* data, int size);

    void setIsRecvMsg(bool isrecv);

    void setServerIp(std::string ip);

    void setPort(int port);

    bool getIsRecvMsg();

    std::string getServerIp();

    int getPort();

    
public:
    // ***��ҵ�������صĺ���***
    //���ӳɹ�����Ϣ�ص�
    virtual void connectedCB() {};

    //���ر���Ϣ����ʱ�����ݽ����͵��˺���,д���ļ�
    virtual void readCB(void* data, int size) {};

    //���յ���Ϣ�Ļص�
    //����true����������false�˳���ǰ����Ϣ����,��������һ����Ϣ
    virtual bool readCB(const XMsg* msg) = 0;

    ///д�����ݻص�����
    virtual void writeCB() {};

protected:

    //��ȡ����
    char m_readBuf[4096] = { 0 };

private:

    /// ������IP
    std::string m_serverIp = "";

    ///�������˿�
    int m_serverPort = 0;

    struct bufferevent* m_bev = 0;

    //���ݰ�����
    XMsg m_msg;

    //�Ƿ������Ϣ
    //���յ���Ϣ����� void readCB(const XMsg *msg)
    //��������Ϣ���� void readCB(void *data, int size)
    bool m_isRecvMsg = true;

};

#endif // XCOM_TASK_H 