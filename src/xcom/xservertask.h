#ifndef XSERVER_TASK_H
#define XSERVER_TASK_H

#include "xtask.h"

#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif 

typedef void(*ListenCBFunc)(int sock, struct sockaddr* addr, int socklen, void* arg);

class XCOM_API XServerTask :public XTask
{
public:

    virtual bool init();

    ListenCBFunc listenCB = 0;

    void setServerPort(int port);

private:

    int m_serverPort = 0;
};

#endif // XSERVER_TASK_H 