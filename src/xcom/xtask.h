#ifndef XTASK_H
#define XTASK_H

#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif

class XCOM_API XTask
{
public:

    //初始化任务
    virtual bool init() = 0;

    int getThreadId() { return m_threadId; }

    void setThreadId(int getThreadId) { m_threadId = getThreadId; }

    int getSock() { return m_sock; }

    void setSock(int sock) { this->m_sock = sock; }

    struct event_base* getBase() { return m_base; }

    void setBase(struct event_base* getBase) { this->m_base = getBase; }

private:

    struct event_base* m_base = 0;

    int m_sock = 0;

    int m_threadId = 0;

};

#endif

