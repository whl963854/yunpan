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

	//�����߳�
	void start();

	//�߳���ں���
	void entry();

	//��װ�̣߳���ʼ��event_base�͹ܵ������¼����ڼ���
	bool setUp();

	//�յ����̷߳����ļ�����Ϣ���̳߳صķַ���
	void notify(int fd, short which);

	//�̼߳���
	void activate();

	//��Ӵ��������һ���߳�ͬʱ���Դ��������񣬹���һ��event_base
	void addTask(XTask *t);

	XThread();

	~XThread();


private:
	//�̱߳��
	int m_id = 0;

	int m_notifyFd = 0;

	struct event_base *m_base = 0;

	//�����б�
	std::list<XTask*> m_tasks;

	//�̰߳�ȫ ����
	std::mutex m_tasksMux;

};

#endif
