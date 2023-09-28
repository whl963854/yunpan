#ifndef XTHREAD_CPP
#define XTHREAD_CPP

#include "xthread.h"
#include <thread>
#include <iostream>
#include <event2/event.h>
#include "xtask.h"

using namespace std;

//�����߳�����Ļص�����
static void notifyCB(int fd, short which, void *arg)
{
	XThread *t = (XThread *)arg;
	t->notify(fd, which);
}

void XThread::notify(int fd, short which)
{
	//ˮƽ���� ֻҪû�н�����ɣ����ٴν���
	char buf[2] = { 0 };
	int re = recv(fd, buf, 1, 0);
	if (re <= 0)
		return;
	cout << m_id << " thread " << buf << endl;
	XTask *task = nullptr;
	//��ȡ���񣬲���ʼ������
	m_tasksMux.lock();
	if (m_tasks.empty())
	{
		m_tasksMux.unlock();
		return;
	}
	task = m_tasks.front(); //�Ƚ��ȳ�
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

//�̼߳���
void XThread::activate()
{
	int re = send(this->m_notifyFd, "c", 1, 0);
	if (re <= 0)
	{
		cerr << "XThread::Activate() failed!" << endl;
	}
}

//�����߳�
void XThread::start()
{
	setUp();

	//�����߳�
	thread th(&XThread::entry,this);

	//�Ͽ������߳���ϵ
	th.detach();
}

//��װ�̣߳���ʼ��event_base
bool XThread::setUp()
{
	//windows�����socket 
	//����һ��socketpair ���Ի���ͨ�� fds[0] �� fds[1]д 
	evutil_socket_t fds[2];
	if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0)
	{
		cout << "evutil_socketpair failed!" << endl;
		return false;
	}
	//���óɷ�����
	evutil_make_socket_nonblocking(fds[0]);
	evutil_make_socket_nonblocking(fds[1]);


	//��ȡ�󶨵�event�¼��У�д��Ҫ����
	m_notifyFd = fds[1];

	//����libevent�����ģ�������
	event_config *ev_conf = event_config_new();
	event_config_set_flag(ev_conf, EVENT_BASE_FLAG_NOLOCK);
	this->m_base = event_base_new_with_config(ev_conf);
	event_config_free(ev_conf);
	if (!m_base)
	{
		cerr << "event_base_new_with_config failed in thread!" << endl;
		return false;
	}

	//��ӹܵ������¼������ڼ����߳�ִ������
	//EV_READ  ֻҪ���绺���л������ݣ��ص������ͻᱻ������
	//EV_PERSIST  ��ָ��������ԣ��ص��������������¼��ᱻɾ����
	event *ev = event_new(m_base, fds[0], EV_READ | EV_PERSIST, notifyCB, this);
	event_add(ev, 0);

	return true;
}

//�߳���ں���
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