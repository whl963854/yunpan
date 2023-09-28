#ifndef XTHREAD_H
#define XTHREAD_H

#include <list>
#include <mutex>

#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif 

class XTask;
class XCOM_API XThread
{
public:

	int getId();

	void setId(int id);

	//启动线程
	void start();

	//线程入口函数
	void entry();

	//安装线程，初始化event_base和管道监听事件用于激活
	bool setUp();

	//收到主线程发出的激活消息（线程池的分发）
	void notify(int fd, short which);

	//线程激活
	void activate();

	//添加处理的任务，一个线程同时可以处理多个任务，共用一个event_base
	void addTask(XTask *t);

	XThread();

	~XThread();


private:
	//线程编号
	int m_id = 0;

	int m_notifyFd = 0;

	struct event_base *m_base = 0;

	//任务列表
	std::list<XTask*> m_tasks;

	//线程安全 互斥
	std::mutex m_tasksMux;

};

#endif
