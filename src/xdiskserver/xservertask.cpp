#pragma warning (disable:4996)

#include "xservertask.h"
#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
#include <string.h>
using namespace  std;

static void SListenCB(struct evconnlistener *evc, evutil_socket_t client_socket, struct sockaddr *client_addr, int socklen, void *arg)
{
    cout << "SListenCB" << endl;
    auto task = (XServerTask*)arg;
    if(task->listenCB)
        task->listenCB(client_socket, client_addr, socklen, arg);
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

    //设置回调函数
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



