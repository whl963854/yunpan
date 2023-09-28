#ifndef XTHREAD_POOL_CPP
#define XTHREAD_POOL_CPP


#include "xthreadpool.h"
#include "xthread.h"
#include <thread>
#include <iostream>
#include "xtask.h"

using namespace std;

//分发线程
void XThreadPool::dispatch(XTask* task)
{
	//轮询
	if (task==nullptr)return;
	int tid = (m_lastThread + 1) % m_threadCount;
	m_lastThread = tid;
	XThread* t = m_threads[tid];
	t->addTask(task);
	//激活线程
	t->activate();
}

//初始化所有线程并启动线程
void XThreadPool::init(int threadCount)
{
	this->m_threadCount = threadCount;
	this->m_lastThread = -1;
	for (int i = 0; i < threadCount; i++)
	{
		XThread* t = new XThread();
		t->setId(i + 1);
		cout << "Create thread " << i << endl;
		//启动线程
		t->start();
		m_threads.push_back(t);
		this_thread::sleep_for(10ms);
	}
}


#endif //XTHREAD_POOL_CPP
