#ifndef XDISK_CLIENT_H
#define XDISK_CLIENT_H

#include <QObject>
#include <string>
class XDiskClient : public QObject
{
    Q_OBJECT

public:
    //单件
    static XDiskClient* Get()
    {
        static XDiskClient xc;
        return &xc;
    }

    ///初始化，包括线程池
    bool init();

    ////////////////////////////////////////////////////////////
    ///@brief 获取目录下的文件列表，只是请求消息到服务端
    void getDir();

    ////////////////////////////////////////////////////////////
    ///@brief 上传文件请求
    ///@para filepath 本地文件路径
    void upload(std::string filepath);

    ////////////////////////////////////////////////////////////
    ///@brief 上传文件请求
    ///@para serverpath 远端文件的相对路径
    ///@para localdir 本地存储的目录
    void download(std::string serverPath, std::string localDir);

    void deleteFile(std::string serverPath);

    void setServerIp(std::string ip);
    void setPort(int port);
    void setServerRoot(std::string root);

signals:
    void SDir(std::string dirs);

    void SUploadComplete();

    void SDownloadComplete();

    void SDeleteSuccess();

    void SDeleteFailed();

private:
    /// 服务器IP
    std::string m_serverIp = "";

    ///服务器的目录
    std::string m_serverRoot = "";

    ///服务器端口
    int m_serverPort = 0;
    XDiskClient() {};
};

#endif //XDISK_CLIENT_H