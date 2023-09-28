#include "xdisk.h"
#include <QtWidgets/QApplication>
#include <WinSock2.h>
#include <iostream>

int main(int argc, char *argv[])
{
    //初始化socket库
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    QApplication a(argc, argv);
    XDisk w;
    w.show();
    //处理信号槽
    return a.exec();
}
