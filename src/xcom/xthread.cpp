#ifndef XTHREAD_CPP
#define XTHREAD_CPP

#include "xthread.h"
#include <thread>
#include <iostream>
#include <event2/event.h>
#include "xtask.h"

using namespace std;

//激活线程任务的回调函数
static void notifyCB(int fd, short which, void *arg)
{
	XThread *t = (XThread *)arg;
	t->notify(fd, which);
}

void XThread::notify(int fd, short which)
{
	//水平触发 只要没有接受完成，会再次进来
	char buf[2] = { 0 };
	int re = recv(fd, buf, 1, 0);
	if (re <= 0)
		return;
	cout << m_id << " thread " << buf << endl;
	XTask *task = nullptr;
	//获取任务，并初始化任务
	m_tasksMux.lock();
	if (m_tasks.empty())
	{
		m_tasksMux.unlock();
		return;
	}
	task = m_tasks.front(); //先进先出
	m_tasks.pop_front();
	m_tasksMux.unlock();
	task->init();
}

void XThread::addTask(XTask *t)
{
	if (t==nullptr)return;
	t->setBase(this->m_base);
	m_tasksMux.lock();
	m_tasks.push_back(t);
	m_tasksMux.unlock();
}

//线程激活
void XThread::activate()
{
	int re = send(this->m_notifyFd, "c", 1, 0);
	if (re <= 0)
	{
		cerr << "XThread::Activate() failed!" << endl;
	}
}

//启动线程
void XThread::start()
{
	setUp();

	//启动线程
	thread th(&XThread::entry,this);

	//断开与主线程联系
	th.detach();
}

//安装线程，初始化event_base
bool XThread::setUp()
{
	//windows用配对socket 
	//创建一个socketpair 可以互相通信 fds[0] 读 fds[1]写 
	evutil_socket_t fds[2];
	if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0)
	{
		cout << "evutil_socketpair failed!" << endl;
		return false;
	}
	//设置成非阻塞
	evutil_make_socket_nonblocking(fds[0]);
	evutil_make_socket_nonblocking(fds[1]);


	//读取绑定到event事件中，写入要保存
	m_notifyFd = fds[1];

	//创建libevent上下文（无锁）
	event_config *ev_conf = event_config_new();
	event_config_set_flag(ev_conf, EVENT_BASE_FLAG_NOLOCK);
	this->m_base = event_base_new_with_config(ev_conf);
	event_config_free(ev_conf);
	if (!m_base)
	{
		cerr << "event_base_new_with_config failed in thread!" << endl;
		return false;
	}

	//添加管道监听事件，用于激活线程执行任务
	//EV_READ  只要网络缓冲中还有数据，回调函数就会被触发；
	//EV_PERSIST  不指定这个属性，回调函数被触发后事件会被删除；
	event *ev = event_new(m_base, fds[0], EV_READ | EV_PERSIST, notifyCB, this);
	event_add(ev, 0);

	return true;
}

//线程入口函数
void XThread::entry()
{
	cout << m_id << " XThread::Main() begin" << endl;
    if (!m_base)
    {
        cerr << "XThread::Main faield! m_base is null " << endl;
        cerr << "In windows set WSAStartup(MAKEWORD(2, 2), &wsa)" << endl;
        return;
    }
	//  This loop will run the event base until either there are no more pending or
	//	active, or until something calls event_base_loopbreak() or
	//	event_base_loopexit().
	event_base_dispatch(m_base);
	event_base_free(m_base);

	cout << m_id << " XThread::Main() end" << endl;
}

XThread::XThread()
{
}

XThread::~XThread()
{
}

int XThread::getId()
{
	return m_id;
}

void XThread::setId(int id)
{
	m_id = id;
}


#endif //XTHREAD_CPP