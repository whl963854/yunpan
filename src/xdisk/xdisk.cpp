#ifndef XDISK_CPP
#define XDISK_CPP

#include "xdisk.h"
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include "xdiskclient.h"
#include <iostream>
#include<QScrollBar>
#include<QMessageBox>

using namespace std;
XDisk::XDisk(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    XDiskClient::Get()->init();

    //ע���ź�֧�ֵ�����
    qRegisterMetaType<std::string>("std::string");

    //��Ŀ¼��ȡ���ź�
    QObject::connect(XDiskClient::Get(), SIGNAL(SDir(std::string)),
        this, SLOT(updateDir(std::string)));

    QObject::connect(XDiskClient::Get(), SIGNAL(SUploadComplete()),
        this, SLOT(refresh()));

    QObject::connect(XDiskClient::Get(), SIGNAL(SDownloadComplete()),
        this, SLOT(downloadComplete()));

    QObject::connect(XDiskClient::Get(), SIGNAL(SDeleteSuccess()),
        this, SLOT(refresh()));


    init();

    refresh();
}

void XDisk::downloadComplete()
{
    QMessageBox::information(this, "", "download complete");
}


void XDisk::deleteSuccess()
{
    QMessageBox::information(this, "", "delete Success");
}

void XDisk::deleteFailed()
{
    QMessageBox::information(this, "", "delete Failed");
}

void XDisk::refresh()
{
    updateServerInfo();
    XDiskClient::Get()->getDir();
}

void XDisk::init()
{
    beautify();
}

void XDisk::updateDir(std::string dirs)
{
    QString str = dirs.c_str();
    str = str.trimmed();
    if (str.isEmpty())
    {
        for (int row = ui.fileListWidget->rowCount() - 1; row >= 0; row--)
        {
            ui.fileListWidget->removeRow(row);
        }
        return;
    }
       
    QStringList filestr = str.split(';');
    ui.fileListWidget->setRowCount(filestr.size());
    for (int i = 0; i < filestr.size(); i++)
    {
        QStringList fileinfo = filestr[i].split(',');
        if (fileinfo.size() != 2) continue;
        //���뵽�б�
        ui.fileListWidget->setItem(i, 0, new QTableWidgetItem(fileinfo[0]));
        ui.fileListWidget->setItem(i, 1, new QTableWidgetItem(tr("%1Byte").arg(fileinfo[1])));
    }

}

void XDisk::updateServerInfo()
{
    //������·�� ������IP �������˿�
    string ip = ui.ipEdit->text().toStdString();
    string root = ui.pathEdit->text().toStdString();
    int port = ui.portBox->value();
    XDiskClient::Get()->setPort(port);
    XDiskClient::Get()->setServerIp(ip);
    XDiskClient::Get()->setServerRoot(root);
}

void XDisk::deleteFile()
{
    updateServerInfo();
    int row = ui.fileListWidget->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "", QString::fromLocal8Bit("��ѡ��Ҫɾ�����ļ�"));
        return;
    }
    //��ȡҪɾ���ļ����ļ���
    auto item = ui.fileListWidget->item(row, 0);
    string filename = item->text().toStdString();
    string filepath = ui.pathEdit->text().toStdString();
    filepath += "/";
    filepath += filename;
    int ret = QMessageBox::information(this, "fight", "are you sure delete it?", QMessageBox::No, QMessageBox::Yes);
    if (ret == QMessageBox::Yes)
    {
        std::cout << "delete " << filename << std::endl;
        XDiskClient::Get()->deleteFile(filepath);
    }
}

void XDisk::download()
{
    //�û�ѡ�������ļ���·��
    updateServerInfo();
    int row = ui.fileListWidget->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "", QString::fromLocal8Bit("��ѡ�������ļ�"));
        return;
    }
    //��ȡѡ����ļ���
    auto item = ui.fileListWidget->item(row, 0);
    string filename = item->text().toStdString();
    //��ȡ����·��
    QString localpath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("��ѡ������·��"));
    if (localpath.isEmpty())
        return;
    string filepath = ui.pathEdit->text().toStdString();
    filepath += "/";
    filepath += filename;
    XDiskClient::Get()->download(filepath, localpath.toStdString());

}


void XDisk::upload()
{
    //�û�ѡ��һ���ļ�
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ���ϴ��ļ�"));
    if (filename.isEmpty())
        return;

    updateServerInfo();
    XDiskClient::Get()->upload(filename.toStdString());
}

XDisk::~XDisk()
{}

void XDisk::beautify()
{
    ui.fileListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.fileListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.fileListWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

#endif //XDISK_CPP