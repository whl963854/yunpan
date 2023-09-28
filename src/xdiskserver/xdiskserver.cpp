#ifndef XSERVER_TASK_CPP
#define XSERVER_TASK_CPP

#include <iostream>
#include <windows.h>
#include "xthreadpool.h"
#include "xservertask.h"
#include "xfileservertask.h"
#include <thread>

using namespace std;
static void listenCB(int sock, struct sockaddr* addr, int socklen, void* arg)
{
    auto task = new XFileServerTask();
    task->setSock(sock);
    XThreadPool::Get()->dispatch(task);
    cout << "listenCB in main  sock=" << sock << endl;
}

int main(int argc, char* argv[])
{
    //初始化socket库
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    //获取端口和线程池线程数量
    int server_port = 21002;
    int thread_count = 10;


    //初始化主线程池
    XThreadPool::Get()->init(thread_count);

    XThreadPool serverPool;
    serverPool.init(1);
    auto task = new XServerTask();
    task->setServerPort(server_port);
    task->listenCB = listenCB;
    serverPool.dispatch(task);

    for (;;)
    {
        this_thread::sleep_for(1s);
    }

    return 0;
}

#endif XSERVER_TASK_CPP
