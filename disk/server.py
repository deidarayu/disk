#!/usr/bin/env python
# -*- coding: cp936 -*-

from socket import * 
from time import ctime
import os
import signal
import hashlib
import MySQLdb      #��ģ��ubuntu������'apt-get install python-mysqldb'��װ

HOST = ''           #�׽������ӵ�ַ
PORT = 8080         #�׽��ֶ˿�
BUFSIZE = 4096      #���ջ����С
ADDRESS = (HOST,PORT)   #��ַ���˿�
tcpSerSock = socket(AF_INET,SOCK_STREAM)  

def md5(src):  #��Ҫ���ڶԿͻ��˷��������ݽ��м��ܲ��������ݿ�
    src1 = src[0]
    m1 = hashlib.md5()
    m1.update(src1)
    print m1.hexdigest()    #������Ϣ...
    src2 = m1.hexdigest()[0:15]
    buf1 = src[1]
    src2 = src2+buf1
    print src2              #������Ϣ...
    m2 = hashlib.md5()
    m2.update(src2)
    conn = MySQLdb.connect(                         #�������ݿ�
	host='127.0.0.1',user='root'                #Ŀ�걾�����˺�root���ȿȣ�
	,passwd='bequiet',db='robber',port=3306)    #Ŀ�����ݿ⣺robber
    cur = conn.cursor()
    sql = 'insert into rob (userID,pass)values(%s,%s);' #�����������
    back = cur.execute(sql,(src[0],m2.hexdigest()))
    print back
    back = cur.execute('select * from rob')
    print back
    cur.close()
    conn.commit()   #�˴�ע�⣬һ��Ҫ��
    conn.close()
    print m2.hexdigest()

def signal_cirt(a,b):   #�˴��õ�Linux SIGCHLD�ź�����ֹ�����жϵ����׽��ֶ˿�ռ��
    tcpSerSock.close()
    os.exit(0)

#******************�ָ��ߣ�������************************
    
if __name__ == '__main__': #****int main(){}*****

    signal.signal(signal.SIGCHLD,signal_cirt)   #����signal����
    
    tcpSerSock.bind(ADDRESS)
    tcpSerSock.listen(20)           #���20�ͻ���

    while True:         #С������Ǹ��棬�˴�Ӧ���߳�
        print '+----------------------------+'
        tcpCliSock,addr = tcpSerSock.accept()
	BUF = []
        print 'Get!'

        while True:
            data = tcpCliSock.recv(BUFSIZE)
            if data == 'OK' or not data:    #��OK���ǲ��淶�ģ���'Thanks��\x0'���Ƕ�ذ
                tcpCliSock.send('Thanks.')
                break
            print 'Recv:',data      
	    BUF.append(data)
	md5(BUF)
	    
        tcpCliSock.close();
        print '+----------------------------+'
    
