#!/usr/bin/env python 
# -*- coding: utf-8 -*-
#http://www.linuxidc.com/Linux/2012-10/71527.htm
import os
import sys
from ftplib import FTP 
 
def ftp_up(filename = "20120904.rar"):
    try:
        ftp=FTP() 
        ftp.set_debuglevel(0)#打开调试级别2，显示详细信息;0为关闭调试信息 
        ftp.connect('localhost','21')#连接 
        ftp.login('teiron','123456')#登录，如果匿名登录则用空串代替即可 
        #print ftp.getwelcome()#显示ftp服务器欢迎信息 
        #ftp.cwd('xxx/xxx/') #选择操作目录 
        bufsize = 1024#设置缓冲块大小 
        file_handler = open(filename,'rb')#以读模式在本地打开文件 
        ftp.storbinary('STOR %s' % os.path.basename(filename),file_handler,bufsize)#上传文件 
        ftp.set_debuglevel(0) 
        file_handler.close() 
        ftp.quit()
    except:
        print sys.exc_info()
        return False
    return True

ret = ftp_up("bb.jpg")


