#ifndef XTHREAD_POOL_H
#define XTHREAD_POOL_H

#include <vector>

#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif

class XThread;
class XTask;
class XCOM_API XThreadPool
{
public:

	static XThreadPool* Get()
	{
		static XThreadPool p;
		return &p;
	}

	void init(int threadCount);

	void dispatch(XTask* task);

	XThreadPool() {};

private:

	///�߳�����
	int m_threadCount = 0;

	///��һ�ηַ��õ��̣߳�������ѯ
	int m_lastThread = -1;

	///�̳߳��̶߳���
	std::vector<XThread*>m_threads;


};

#endif //XTHREAD_POOL_H