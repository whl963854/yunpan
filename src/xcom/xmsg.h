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
    MSG_GETDIR,             //请求目录     客户端请求
    MSG_DIRLIST,            //返回目录列表 服务端返回
    MSG_UPLOAD_INFO,        //请求上传文件 
    MSG_UPLOAD_ACCEPT,      //服务端准备好接收文件
    MSG_UPLOAD_COMPLETE,    //服务端接收文件结束
    MSG_DOWNLOAD_INFO,      //请求下载文件
    MSG_DOWNLOAD_ACCEPT,    //开始发送数据给客户端
    MSG_DOWNLOAD_COMPLETE,  //客户端下载成功
    MSG_DELETE_INFO,      //删除云端文件
    MSG_DELETE_SUCCESS,    //删除云端文件成功
    MSG_DELETE_FAILED,    //删除云端文件失败
    MSG_ERROR,              //消息类型错误
    MSG_MAX_TYPE,           //用来验证类型正确

};
//消息最大字节数
#define MSG_MAX_SIZE 1000000000

//消息头
struct XCOM_API XMsgHead
{
    MsgType type = MsgType::MSG_NONE;
    int size = 0;
};

//约定每个消息必须包含内容，没有内容使用OK
struct XCOM_API XMsg :public XMsgHead
{
    char* data = 0;     //存储消息内容
    int recved = 0;     //已经接收的消息字节数

};

#endif //XMSG_H 