#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

struct ID{
    char name[200];
    char NO;
}id;

int Send_Sock(char *address,void *buf,int len,void *recvbuf, int reclen);

#endif // SOCKET_H_INCLUDED
