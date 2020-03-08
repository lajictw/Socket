#include "mythread.h"
#include <QtCore>
#include <QDebug>
#include<winsock2.h>
using namespace std;
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>
#include<thread>
#include <sendobject.h>

void gettype(char *url, char *type);
char *readfile(char *filepath, char *str);
void multitest(SOCKET servSock, SOCKET clntSock);
string get_real_url(string s1,string s2);


extern SOCKET servSock;
extern QString FakeMenu;


MyThread::MyThread()
{

}

void MyThread::run()
{
    qDebug()<<"Running";
    int i=0;
    while(true)
    {
        int nSize = sizeof(SOCKADDR);
        struct sockaddr_in clntAddr;
        SOCKET clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &nSize); //应zl老铁提议移动到此
        if(clntSock!=-1)
        {
            char tips[200];
            sprintf(tips,"client socket success! socket = %d, IP = %s \n", clntSock, inet_ntoa(clntAddr.sin_addr));
            QString message(tips);
            emit sendMessage(message);
            qDebug()<<"message "<<message<<endl;
            cout<<"emitted successful"<<endl;
            class thread th(multitest,servSock,clntSock);
            th.detach();
            i++;
        }

//        int i=0;
        cout<<i<<" times"<<endl;

    }

}

void gettype(char *url, char *type) //获取文件格式
{
    int i;
    i = strlen(url);
    printf("%d", i);
    int j = 0;
    while (true)
    {
        if (url[i] == '.')
            break;
        type[j] = url[i];
        j++;
        i--;
    }
    type[j] = 0;
    printf("%s\n", type);
    j--;
    i = 0;
    char h;
    while (i <= j)
    {
        h = type[j];
        type[j] = type[i];
        type[i] = h;
        i++;
        j--;
    }
}

char *readfile(char *filepath, char *str) //读取文件内容
{
    char haha[200] = "C:/Users/ccttww/Desktop/VSCode/CPP/socket";
    // filepath="/a.png";
    strcat(haha, filepath);
    cout << haha << endl;
    FILE *file = fopen(haha, "rb");
    char *gg;
    if(file==NULL)
    {
        file=fopen("C:/Users/ccttww/Desktop/VSCode/CPP/socket/test.html","rb");
        int size = filelength(fileno(file));
        cout << size << endl;
        itoa(size, str, 10);
        gg = (char *)malloc((size + 1) * sizeof(char));
        fread(gg, 1, size + 1, file);
        gg[size + 1] = 0;

        //   printf("%s",gg);
        fclose(file);
        // cout << gg << endl;
        // cout << "read compeleted!" << endl;
        return gg;
    }

    printf("filetest\n");
    if (file != NULL)
    {
        int size = filelength(fileno(file));
        cout << size << endl;
        itoa(size, str, 10);
        gg = (char *)malloc((size + 1) * sizeof(char));
        fread(gg, 1, size + 1, file);
        gg[size + 1] = 0;

        //   printf("%s",gg);
        fclose(file);
        // cout << gg << endl;
        // cout << "read compeleted!" << endl;
        return gg;
    }
}

string get_real_url(string s1,string s2)
{

    int s1_len = s1.size();
    int Com;
    Com = s2.compare(0, s1_len, s1);
    cout << "Com" << Com << endl;
    if (Com == 0)
    {
        cout << "s2:" << s2 << endl;
        s2.erase(0, s1_len);
        cout << "s2:" << s2 << endl;
    }
    else
    {
        printf("not submenu");
    }
    return s2;
}

void multitest(SOCKET servSock,SOCKET clntSock)
{
        //int nSize = sizeof(SOCKADDR);
        //struct sockaddr_in clntAddr;
        char _recvBuf[1024] = {};
        char method[20] = {};
        char Furl[200]={};
        char url[200] = {};
        const char *constUrl;
        char type[10] = {};
        char version[100] = {};
        char sending[] = "HTTP/1.1 200 OK\r\n";
        char *file_read;
        char server_info[] = "Server: Tiny Web Server\r\n";
        char enter[] = "\r\n";
        char length_info[50] = "Content-length: ";
        char type_info[40] = "Content-type: ";
        char length[25];
        char connection[] = "Connection: Close\r\n"; //尝试加入connection字段以解决网页多媒体传输问题
        string FMenu=FakeMenu.toStdString();
        //SOCKET clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &nSize); //应zl老铁提议移动到此

//        if (clntSock == -1)
//        {
//            perror("client socket error!");
//        }
//        else
//        {
//            printf("client socket success! socket = %d, IP = %s \n", clntSock, inet_ntoa(clntAddr.sin_addr));

//        }

        int file_length; //int型文档长度
        int nLen = recv(clntSock, _recvBuf, 1024, 0);
        cout << _recvBuf << endl;

        // if (nLen <= 0)
        // {
        //     printf("client has quit!\n");
        //     break;
        // }

        //测试用输出，用于确定是否由于上述if导致退出
        printf("loop break test\n");

        sscanf(_recvBuf, "%s %s %s", method, Furl, version);
        string Aurl(Furl,Furl+strlen(Furl));
        Aurl=get_real_url(FMenu,Aurl);
        constUrl=Aurl.c_str();
        strcpy(url,constUrl);

        gettype(url, type);

        //测试用输出，用于检查包含多媒体文件的网页的第二个包的type是否正常
        cout << "url is" << url << " type is" << type << endl;

        // strcat(version, sending);
        file_read = readfile(url, length);
        char back_type[20] = {};
        if (strstr(type, "htm") != NULL)
        {
            strcpy(back_type, "text/html");
        }
        else if (strstr(type, "jpg") != NULL)
        {
            strcpy(back_type, "image/jpg");
        }

        //测试用输出，用于检查包含多媒体文件的网页的第二个包的back_type是否正常
        cout << "url is" << url << " back type is" << back_type << endl;

        strcat(length_info, length);
        // cout << "length info1" << length_info << endl; //测试用输出
        strcat(length_info, enter);
        // cout << "length info2" << length_info << endl; //测试用输出
        strcat(type_info, back_type);
        // cout << "type info1" << type_info << endl; //测试用输出
        strcat(type_info, enter);
        // cout << "type info2" << type_info << endl; //测试用输出
        strcat(type_info, enter);
        // cout << "type info2" << type_info << endl; //测试用输出

        //测试用输出
        cout << "output test" << endl;
        cout << sending << server_info << length_info << type_info << file_read;
        int s, si, li, ti;
        s = sizeof(sending) + 1;
        si = sizeof(server_info) + 1;
        li = sizeof(length_info) + 1;
        ti = sizeof(type_info) + 1;
        cout << "s is" << s << "si is" << si << "li is" << li << "ti is" << ti << endl;

        send(clntSock, sending, strlen(sending), 0); //长度+1,发送的是http/*.*,200,ok

        send(clntSock, server_info, strlen(server_info), 0); //发送的是服务器信息
        send(clntSock, length_info, strlen(length_info), 0); //发送的是文件长度信息
        send(clntSock, connection, strlen(connection), 0);   //发送的是连接信息
        send(clntSock, type_info, strlen(type_info), 0);     //长度+1,发送的是文件格式信息

        // char *filepath;
        // filepath=url;
        // FILE *file = fopen(filepath, "rb");
        // if (file)
        // {
        //     int size = filelength(fileno(file));
        //     // cout << size << endl;
        //     // fclose(file);

        // }

        file_length = atoi(length);
        send(clntSock, file_read, file_length + 1, 0); //长度+1，将结尾符一并发送过去,发送的是请求的二进制文件

        closesocket(clntSock); //应zl老铁提议移动至此
}



