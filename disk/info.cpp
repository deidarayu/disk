#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "info.h"

using namespace std;

#define INFO_BUFFER_SIZE 32767

int gethost(char *buf){
  CHAR  infoBuf[INFO_BUFFER_SIZE];
  DWORD  bufCharCount = INFO_BUFFER_SIZE;
  int i=0;

  if( GetComputerName( infoBuf, &bufCharCount ) ){
    if(strlen(infoBuf)>=5){
        infoBuf[5] = 0;
    }else if(strlen(infoBuf)<5){
        for(i = strlen(infoBuf);i<5;i++){
            infoBuf[i] = 'X';
        }
        infoBuf[5] = 0;
    }
    strncpy(buf,infoBuf,5);
  }
    return strlen(buf);
}


void getMac(char * mac)
{
    ASTAT Adapter;
    NCB Ncb;
    UCHAR uRetCode;
    LANA_ENUM lenum;
    int i = 0;

    memset(&Ncb, 0, sizeof(Ncb));
    Ncb.ncb_command = NCBENUM;
    Ncb.ncb_buffer = (UCHAR *)&lenum;
    Ncb.ncb_length = sizeof(lenum);

    uRetCode = Netbios( &Ncb );
    //printf( "The NCBENUM return adapter number is: %d \n ", lenum.length);
    for(i=0; i < lenum.length ; i++)
    {
        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lenum.lana[i];
        uRetCode = Netbios( &Ncb );

        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lenum.lana[i];
        strcpy((char *)Ncb.ncb_callname, "* ");
        Ncb.ncb_buffer = (unsigned char *) &Adapter;
        Ncb.ncb_length = sizeof(Adapter);
        uRetCode = Netbios( &Ncb );

        if (uRetCode == 0)
        {
            //sprintf(mac, "%02x-%02x-%02x-%02x-%02x-%02x ",
            sprintf(mac, "%02X%02X%02X%02X%02X%02X",
                    Adapter.adapt.adapter_address[0],
                    Adapter.adapt.adapter_address[1],
                    Adapter.adapt.adapter_address[2],
                    Adapter.adapt.adapter_address[3],
                    Adapter.adapt.adapter_address[4],
                    Adapter.adapt.adapter_address[5]
                   );
            //printf( "The Ethernet Number on LANA %d is: %s\n ", lenum.lana[i], mac);
        }
    }
}
