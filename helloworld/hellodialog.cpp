#include "hellodialog.h"
#include "ui_hellodialog.h"
#include"mythread.h"
#include <QMessageBox>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>
#include<thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib") //加载 ws2_32.dll
#define _cSock , clntSock;
MyThread mThread;
QString FakeMenu;
SOCKET servSock;

hellodialog::hellodialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::hellodialog)
{
    ui->setupUi(this);
//    while(1)
    {
        bool test_signal;

        //信号与槽链接在一起
        test_signal=connect(&mThread, SIGNAL(sendMessage(const QString &)), this, SLOT(getMessage(const QString &)));
        if(test_signal==true)
            qDebug()<<"got connected";
        else if(test_signal==false)
            qDebug()<<"failed";
    }

}

hellodialog::~hellodialog()
{
    delete ui;
}


void hellodialog::on_startbtn_clicked()
{
//    ui->ConPrint->append("sdasa");
    QString ip=ui->ipLine->text();
    QString Port=ui->portLine->text();
    FakeMenu=ui->AddrLine->text();
    QByteArray ipip=ip.toLatin1();
    QByteArray popo=Port.toLatin1();
    char *ip_addr=ipip.data();
    char *port=popo.data();
    int input_port=atoi(port);
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
       //创建套接字
    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
       //绑定套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));            //每个字节都用0填充
    sockAddr.sin_family = PF_INET;                     //使用IPv4地址
       sockAddr.sin_addr.s_addr = inet_addr(ip_addr); //具体的IP地址
       sockAddr.sin_port = htons(input_port);                   //端口
       bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));
       //进入监听状态
       listen(servSock, 20);

       listen(servSock, 20);
       //接收客户端请求
       // SOCKADDR clntAddr;
       struct sockaddr_in clntAddr;
       int nSize = sizeof(SOCKADDR);
       mThread.start();
       printf("client server connection closed\n"); //测试用输出，观察何时结束socket链接

        //closesocket(servSock);
           //终止 DLL 的使用
        //WSACleanup();

}

void hellodialog::on_endbtn_clicked()
{
    //qDebug()<<"before wait";
    mThread.terminate();
    mThread.wait();
    //qDebug()<<"afterwait";

}

void hellodialog::getMessage(const QString &message)
{
     ui->ConPrint->append("message");
     ui->ConPrint->append(message);

//    cout<<"got emit"<<endl;
}
