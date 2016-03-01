#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define AIM_PORT 8080

using namespace std;

int Send_Sock(char *address,void *buf,int len,void *recvbuf, int reclen){
    unsigned long ip;
    char **point = (char**)buf;
    int bytes;
    if((ip = inet_addr(address))<0){
        MessageBox(NULL,TEXT("invalid address!"),\
                   TEXT("Error"),MB_OK|MB_ICONERROR);
        return -1;
    }
    short port = AIM_PORT;
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        MessageBox(NULL,TEXT("invalid port!"),\
                   TEXT("Error"),MB_OK|MB_ICONERROR);
        return -1;
    }
    SOCKET sock;
    if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
        MessageBox(NULL,TEXT("invalid socket!"),\
                   TEXT("Error"),MB_OK|MB_ICONERROR);
        return -1;
    }
    struct sockaddr_in serverAddress;
    memset(&serverAddress,0,sizeof(sockaddr_in));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.S_un.S_addr = ip;
    serverAddress.sin_port = htons(port);
    //建立和服务器的连接
    if(connect(sock,(sockaddr*)&serverAddress,sizeof(serverAddress))==SOCKET_ERROR){
        MessageBox(NULL,TEXT("Connect disable!"),\
                   TEXT("Error"),MB_OK|MB_ICONERROR);
        return -1;
    }
    for(int i=0;i<len;i++){
        if(send(sock,(char*)point[i],strlen(point[i]),0) == SOCKET_ERROR){
            MessageBox(NULL,TEXT("SEND ERROR"),\
                       TEXT("Error"),MB_OK|MB_ICONERROR);
            return -1;
        }
        Sleep(500);
    }
    if((bytes = recv(sock,(char*)recvbuf,reclen,0)) == SOCKET_ERROR){
        MessageBox(NULL,TEXT("RECV ERROR"),\
                   TEXT("Error"),MB_OK|MB_ICONERROR);
        return -1;
    }
    ((char*)recvbuf)[bytes] = 0;
    MessageBoxA(NULL,(char*)recvbuf,"sssss",MB_OK);
    if(strcmp((char*)recvbuf,"Thanks.")==0){
        closesocket(sock);
        WSACleanup();
    }
    return 0;
}
