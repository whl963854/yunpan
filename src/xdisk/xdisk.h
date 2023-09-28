#ifndef XDISK_H
#define XDISK_H

#include <QtWidgets/QMainWindow>
#include "ui_xdisk.h"

class XDisk : public QMainWindow
{
    Q_OBJECT

public:
    XDisk(QWidget *parent = nullptr);
    ~XDisk();
    void updateServerInfo();
    void init();

public slots:
    void refresh();
    void updateDir(std::string dirs);
    void upload();
    void download();
    void downloadComplete();
    void deleteFile();
    void deleteSuccess();
    void deleteFailed();

private:

    Ui::XDiskClass ui;

    void XDisk::beautify();
};


#endif XDISK_H 


