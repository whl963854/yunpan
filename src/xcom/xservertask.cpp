#ifndef XSERVER_TASK_CPP
#define XSERVER_TASK_CPP

#include "xservertask.h"
#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
#include <string.h>

using namespace  std;

static void SListenCB(struct evconnlistener* evc, evutil_socket_t client_socket, 
                        struct sockaddr* client_addr, int socklen, void* arg)
{
    cout << "新的连接：" << client_socket<< endl;
    auto task = (XServerTask*)arg;
    if (task->listenCB != nullptr)
    {
        //因为static函数没有this指针，无法调用成员函数，只能通过函数指针实现多态
        task->listenCB(client_socket, client_addr, socklen, arg);
    }
    else
    {
        cerr << "please set callback function listenCB" << endl;
    }
}

bool XServerTask::init()
{
    if (m_serverPort <= 0)
    {
        cerr << "XServerTask::Init failed! m_serverPort is not set" << endl;
        return false;
    }
    //监听端口
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_port = htons(m_serverPort);
    sin.sin_family = AF_INET;

    //事件监听器 设置回调函数 SListenCB表示当一个新的连接建立时需要调用的回调函数。
    /**
   Allocate a new evconnlistener object to listen for incoming TCP connections
   on a given address.
   @param base The event base to associate the listener with.
   @param cb A callback to be invoked when a new connection arrives. If the
      callback is NULL, the listener will be treated as disabled until the
      callback is set.
   @param ptr A user-supplied pointer to give to the callback.
   @param flags Any number of LEV_OPT_* flags
   @param backlog Passed to the listen() call to determine the length of the
      acceptable connection backlog.  Set to -1 for a reasonable default.
   @param addr The address to listen for connections on.
   @param socklen The length of the address.
 */
    auto evc = evconnlistener_new_bind(getBase(), SListenCB, this,
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
        10,  ///listen back
        (sockaddr*)&sin,
        sizeof(sin)
    );
    if (!evc)
    {
        cout << "listen port " << m_serverPort << " failed!" << endl;
        return false;
    }
    cout << "listen port " << m_serverPort << " success!" << endl;
    return true;
}

void XServerTask::setServerPort(int port)
{
    m_serverPort = port;
}


#endif // XSERVER_TASK_CPP
