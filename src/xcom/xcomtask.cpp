#ifndef XCOM_TASK_CPP
#define XCOM_TASK_CPP

#include "xcomtask.h"
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <iostream>
#include <string.h>

using namespace std;

static void SReadCB(struct bufferevent* bev, void* ctx)
{
    auto task = (XComTask*)ctx;
    task->readCB();
}

static void SWriteCB(struct bufferevent* bev, void* ctx)
{
    auto task = (XComTask*)ctx;
    task->writeCB();
}

static void SEventCB(struct bufferevent* bev, short what, void* ctx)
{
    auto task = (XComTask*)ctx;
    task->eventCB(what);
}

bool  XComTask::write(const void* data, int size)
{
    if (!m_bev || !data || size <= 0)return false;
    int re = bufferevent_write(m_bev, data, size);
    if (re != 0)return false;
    return true;
}

bool XComTask::write(const XMsg* msg)
{
    if (!m_bev || !msg || !msg->data || msg->size <= 0)return false;
    //1 д����Ϣͷ
    int re = bufferevent_write(m_bev, msg, sizeof(XMsgHead));
    if (re != 0)return false;
    //2 д����Ϣ����
    re = bufferevent_write(m_bev, msg->data, msg->size);
    if (re != 0)return false;
    return true;
}

//����д��ص�,����д�¼�������bufferevent������Գ���д������
void XComTask::beginWrite()
{
    if (!m_bev)return;
    bufferevent_trigger(m_bev, EV_WRITE, 0);
}

void XComTask::readCB()
{
    for (;;)//ȷ����Ե�������ܶ�ȡ��������
    {
        if (!m_isRecvMsg)
        {
            int len = bufferevent_read(m_bev, m_readBuf, sizeof(m_readBuf));
            if (len <= 0)return;
            readCB(m_readBuf, len);
            continue;
        }

        //1 ����ͷ����Ϣ
        if (!m_msg.data)
        {
            int headsize = sizeof(XMsgHead);
            int len = bufferevent_read(m_bev, &m_msg, headsize);
            if (len <= 0)return;
            if (len != headsize)
            {
                cerr << "msg head recv error" << endl;
                return;
            }
            //��֤��Ϣͷ����Ч��
            if (m_msg.type >= MSG_MAX_TYPE || m_msg.size <= 0 || m_msg.size > MSG_MAX_SIZE)
            {
                cerr << "msg head is error" << endl;
                return;
            }
            m_msg.data = new char[m_msg.size];
        }
        int readsize = m_msg.size - m_msg.recved;
        if (readsize <= 0)
        {
            delete m_msg.data;
            memset(&m_msg, 0, sizeof(m_msg));
            return;
        }
        int len = bufferevent_read(m_bev, m_msg.data + m_msg.recved, readsize);
        if (len <= 0)
            return;
        m_msg.recved += len;
        if (m_msg.recved == m_msg.size)
        {
            //������Ϣ
            cout << "recieve msg size:" << m_msg.size << endl;
            //���������������bev_��������
            if (!readCB(&m_msg))
            {
                return;
            }
            delete m_msg.data;
            memset(&m_msg, 0, sizeof(m_msg));
        }
    }
}
bool XComTask::init()
{
    //���ַ���˻��ǿͻ���
    int comsock = this->getSock();
    if (comsock <= 0)
        comsock = -1;

    ///��bufferevent �������� 
    /// ����bufferevent������ -1�Զ�����socket
    m_bev = bufferevent_socket_new(getBase(), comsock, BEV_OPT_CLOSE_ON_FREE);
    if (!m_bev)
    {
        cerr << "bufferevent_socket_new failed!" << endl;
        return false;
    }

    //���ûص�����
    /*The read callback is triggered when new data arrives in the input
        bufferand the amount of readable data exceed the low watermark
        which is 0 by default.

        The write callback is triggered if the write buffer has been
        exhausted or fell below its low watermark.
    */
    bufferevent_setcb(m_bev, SReadCB, SWriteCB, SEventCB, this);
    bufferevent_enable(m_bev, EV_READ | EV_WRITE);

    timeval tv = { 10,10 };
    bufferevent_set_timeouts(m_bev, &tv, &tv);

    //���ӷ�����
    if (m_serverIp.empty())
    {
        return true;
    }
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_serverPort);

    //��һ�� IPv4 �� IPv6 ��ַ���ı���ʾ��ʽת��Ϊ��������ʽ
    evutil_inet_pton(AF_INET, m_serverIp.c_str(), &sin.sin_addr.s_addr);
    //���ӵ�������
    int re = bufferevent_socket_connect(m_bev, (sockaddr*)&sin, sizeof(sin));
    if (re != 0)
        return false;
    return true;
}

void XComTask::eventCB(short what)
{
    cout << "eventCB :" << getPort() << endl;
    if (what & BEV_EVENT_CONNECTED)
    {
        cout << "BEV_EVENT_CONNECTED" << endl;
        //֪ͨ���ӳɹ�
        connectedCB();
    }

    ///�˳�Ҫ����������
    if (what & BEV_EVENT_ERROR)
    {
        cout << "BEV_EVENT_ERROR " << endl;
        close();
    }
    if (what & BEV_EVENT_TIMEOUT)
    {
        cout << "BEV_EVENT_TIMEOUT " << endl;
        close();
    }
    if (what & BEV_EVENT_EOF)
    {
        cout << "BEV_EVENT_EOF" << endl;
        close();
    }
}


void XComTask::close()
{
    if (m_bev)
        bufferevent_free(m_bev);
    m_bev = nullptr;
    if (m_msg.data)
        delete m_msg.data;
    memset(&m_msg, 0, sizeof(m_msg));
    delete this;
}

void XComTask::setIsRecvMsg(bool isrecv)
{ 
    this->m_isRecvMsg = isrecv; 
}

void XComTask::setServerIp(std::string ip)
{ 
    this->m_serverIp = ip; 
}

void XComTask::setPort(int port)
{ 
    this->m_serverPort = port; 
}

bool XComTask::getIsRecvMsg()
{ 
    return this->m_isRecvMsg; 
}

std::string XComTask::getServerIp()
{ 
    return this->m_serverIp; 
}

int XComTask::getPort()
{ 
    return this->m_serverPort; 
}

#endif //XCOM_TASK_CPP