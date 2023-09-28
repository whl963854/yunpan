#ifndef XDISK_CLIENT_CPP
#define XDISK_CLIENT_CPP

#include <iostream>
#include "xdiskclient.h"
#include "xdirtask.h"
#include "xcomtask.h"
#include "xtask.h"
#include "xthreadpool.h"
#include "xuploadtask.h"
#include "xdownloadtask.h"
#include "xdeletetask.h"
#include "xtools.h"

using namespace std;

bool XDiskClient::init()
{
    XThreadPool::Get()->init(10);
    return true;
}


static void dirCB(string dirs)
{
    cout << "目录列表如下：" << endl;
    auto dirsVec=getDirLists(dirs);
    for (auto dir : dirsVec)
    {
        cout << "# " << dir << endl;
    }
    XDiskClient::Get()->SDir(dirs);
}

static void uploadCB()
{
    cout << "uploadCB finish" << endl;
    XDiskClient::Get()->SUploadComplete();
}

static void deleteSuccessCB()
{
    cout << "deleteCB Success" << endl;
    XDiskClient::Get()->SDeleteSuccess();
}

static void deleteFailedCB()
{
    cout << "deleteCB Failed" << endl;
    XDiskClient::Get()->SDeleteFailed();
}

static void downloadCB()
{
    cout << "SDownloadComplete" << endl;
    XDiskClient::Get()->SDownloadComplete();
}


void XDiskClient::upload(std::string filepath)
{
    auto task = new XUploadTask();
    task->setServerIp(m_serverIp);
    task->setPort(m_serverPort);
    task->setFilePath(filepath);
    task->uploadCB = uploadCB;
    XThreadPool::Get()->dispatch(task);
}

void XDiskClient::download(std::string serverPath, std::string localDir)
{
    auto task = new XDownloadTask();
    task->setServerIp(m_serverIp);
    task->setPort(m_serverPort);
    task->setFilePath(serverPath);
    task->setLocalDir(localDir);
    task->downloadCB = downloadCB;
    XThreadPool::Get()->dispatch(task);
}

void XDiskClient::deleteFile(std::string serverPath)
{
    auto task = new XDeleteTask();
    task->setServerIp(m_serverIp);
    task->setPort(m_serverPort);
    task->setFilePath(serverPath);
    task->deleteSuccessCB = deleteSuccessCB;
    task->deleteFailedCB = deleteFailedCB;
    XThreadPool::Get()->dispatch(task);
}

void XDiskClient::getDir()
{
    cout << "getDir " << m_serverIp << ":" << m_serverPort << "/" << m_serverRoot << endl;
    auto task = new XDirTask();
    task->setServerIp(m_serverIp);
    task->setPort(m_serverPort);
    task->setServerRoot(m_serverRoot);
    task->dirCB = dirCB;
    //现在不能操作，task未初始化。task没有event_base
    XThreadPool::Get()->dispatch(task);
}


void XDiskClient::setServerIp(std::string ip)
{ 
	this->m_serverIp = ip; 
}

void XDiskClient::setPort(int port)
{ 
	this->m_serverPort = port; 
}

void XDiskClient::setServerRoot(std::string root)
{ 
	this->m_serverRoot = root; 
}

#endif //XDISK_CLIENT_H
