#ifndef XMSG_H
#define XMSG_H

#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif 

enum MsgType
{
    MSG_NONE = 0,
    MSG_GETDIR,             //����Ŀ¼     �ͻ�������
    MSG_DIRLIST,            //����Ŀ¼�б� ����˷���
    MSG_UPLOAD_INFO,        //�����ϴ��ļ� 
    MSG_UPLOAD_ACCEPT,      //�����׼���ý����ļ�
    MSG_UPLOAD_COMPLETE,    //����˽����ļ�����
    MSG_DOWNLOAD_INFO,      //���������ļ�
    MSG_DOWNLOAD_ACCEPT,    //��ʼ�������ݸ��ͻ���
    MSG_DOWNLOAD_COMPLETE,  //�ͻ������سɹ�
    MSG_DELETE_INFO,      //ɾ���ƶ��ļ�
    MSG_DELETE_SUCCESS,    //ɾ���ƶ��ļ��ɹ�
    MSG_DELETE_FAILED,    //ɾ���ƶ��ļ�ʧ��
    MSG_ERROR,              //��Ϣ���ʹ���
    MSG_MAX_TYPE,           //������֤������ȷ

};
//��Ϣ����ֽ���
#define MSG_MAX_SIZE 1000000000

//��Ϣͷ
struct XCOM_API XMsgHead
{
    MsgType type = MsgType::MSG_NONE;
    int size = 0;
};

//Լ��ÿ����Ϣ����������ݣ�û������ʹ��OK
struct XCOM_API XMsg :public XMsgHead
{
    char* data = 0;     //�洢��Ϣ����
    int recved = 0;     //�Ѿ����յ���Ϣ�ֽ���

};

#endif //XMSG_H 