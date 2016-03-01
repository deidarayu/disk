#!/usr/bin/env python
# -*- coding: cp936 -*-

from socket import * 
from time import ctime
import os
import signal
import hashlib
import MySQLdb      #此模块ubuntu下命令'apt-get install python-mysqldb'安装

HOST = ''           #套接字链接地址
PORT = 8080         #套接字端口
BUFSIZE = 4096      #接收缓冲大小
ADDRESS = (HOST,PORT)   #地址，端口
tcpSerSock = socket(AF_INET,SOCK_STREAM)  

def md5(src):  #主要用于对客户端发来的数据进行加密并存入数据库
    src1 = src[0]
    m1 = hashlib.md5()
    m1.update(src1)
    print m1.hexdigest()    #调试信息...
    src2 = m1.hexdigest()[0:15]
    buf1 = src[1]
    src2 = src2+buf1
    print src2              #调试信息...
    m2 = hashlib.md5()
    m2.update(src2)
    conn = MySQLdb.connect(                         #连接数据库
	host='127.0.0.1',user='root'                #目标本机，账号root（咳咳）
	,passwd='bequiet',db='robber',port=3306)    #目标数据库：robber
    cur = conn.cursor()
    sql = 'insert into rob (userID,pass)values(%s,%s);' #插入数据语句
    back = cur.execute(sql,(src[0],m2.hexdigest()))
    print back
    back = cur.execute('select * from rob')
    print back
    cur.close()
    conn.commit()   #此处注意，一定要加
    conn.close()
    print m2.hexdigest()

def signal_cirt(a,b):   #此处用到Linux SIGCHLD信号量防止调试中断导致套接字端口占用
    tcpSerSock.close()
    os.exit(0)

#******************分割线，看你妹************************
    
if __name__ == '__main__': #****int main(){}*****

    signal.signal(signal.SIGCHLD,signal_cirt)   #调用signal函数
    
    tcpSerSock.bind(ADDRESS)
    tcpSerSock.listen(20)           #最多20客户端

    while True:         #小程序就是个玩，此处应另开线程
        print '+----------------------------+'
        tcpCliSock,addr = tcpSerSock.accept()
	BUF = []
        print 'Get!'

        while True:
            data = tcpCliSock.recv(BUFSIZE)
            if data == 'OK' or not data:    #‘OK’是不规范的！，'Thanks！\x0'更是逗匕
                tcpCliSock.send('Thanks.')
                break
            print 'Recv:',data      
	    BUF.append(data)
	md5(BUF)
	    
        tcpCliSock.close();
        print '+----------------------------+'
    
