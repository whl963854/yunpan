#include "xdisk.h"
#include <QtWidgets/QApplication>
#include <WinSock2.h>
#include <iostream>

int main(int argc, char *argv[])
{
    //��ʼ��socket��
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    QApplication a(argc, argv);
    XDisk w;
    w.show();
    //�����źŲ�
    return a.exec();
}
