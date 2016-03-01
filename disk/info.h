#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

#define INFO_BUFFER_SIZE 32767

int gethost(char *buf);
void getMac(char * mac);

typedef struct _ASTAT_
{
    ADAPTER_STATUS adapt;
    NAME_BUFFER NameBuff [30];
} ASTAT, *PASTAT;

#endif // INFO_H_INCLUDED
