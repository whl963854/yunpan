#ifndef XDISK_CLIENT_H
#define XDISK_CLIENT_H

#include <QObject>
#include <string>
class XDiskClient : public QObject
{
    Q_OBJECT

public:
    //����
    static XDiskClient* Get()
    {
        static XDiskClient xc;
        return &xc;
    }

    ///��ʼ���������̳߳�
    bool init();

    ////////////////////////////////////////////////////////////
    ///@brief ��ȡĿ¼�µ��ļ��б�ֻ��������Ϣ�������
    void getDir();

    ////////////////////////////////////////////////////////////
    ///@brief �ϴ��ļ�����
    ///@para filepath �����ļ�·��
    void upload(std::string filepath);

    ////////////////////////////////////////////////////////////
    ///@brief �ϴ��ļ�����
    ///@para serverpath Զ���ļ������·��
    ///@para localdir ���ش洢��Ŀ¼
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
    /// ������IP
    std::string m_serverIp = "";

    ///��������Ŀ¼
    std::string m_serverRoot = "";

    ///�������˿�
    int m_serverPort = 0;
    XDiskClient() {};
};

#endif //XDISK_CLIENT_H