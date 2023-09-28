#ifndef XTHREAD_POOL_CPP
#define XTHREAD_POOL_CPP


#include "xthreadpool.h"
#include "xthread.h"
#include <thread>
#include <iostream>
#include "xtask.h"

using namespace std;

//�ַ��߳�
void XThreadPool::dispatch(XTask* task)
{
	//��ѯ
	if (task==nullptr)return;
	int tid = (m_lastThread + 1) % m_threadCount;
	m_lastThread = tid;
	XThread* t = m_threads[tid];
	t->addTask(task);
	//�����߳�
	t->activate();
}

//��ʼ�������̲߳������߳�
void XThreadPool::init(int threadCount)
{
	this->m_threadCount = threadCount;
	this->m_lastThread = -1;
	for (int i = 0; i < threadCount; i++)
	{
		XThread* t = new XThread();
		t->setId(i + 1);
		cout << "Create thread " << i << endl;
		//�����߳�
		t->start();
		m_threads.push_back(t);
		this_thread::sleep_for(10ms);
	}
}


#endif //XTHREAD_POOL_CPP
