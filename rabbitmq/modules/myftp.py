#!/usr/bin/env python 
# -*- coding: utf-8 -*-
#http://www.linuxidc.com/Linux/2012-10/71527.htm
import os
import sys
import socket
import traceback
import mylog as mo
from ftplib import FTP 
 
def ftp_up(filenames,hostname,port,uname,passwd,cwd,handler_fetchname):
    socket.setdefaulttimeout(6*60*60)    #超时FTP时间设置为60秒
    try:
        ftp=FTP() 
        ftp.set_debuglevel(0)#打开调试级别2，显示详细信息;0为关闭调试信息 
        ftp.connect(hostname,port,100)#连接 
        ftp.login(uname,passwd)#登录，如果匿名登录则用空串代替即可 
        #print ftp.getwelcome()#显示ftp服务器欢迎信息 
        tmps = cwd.split("/")
        tmpcwd = ""
        for tmp in tmps:
            tmpcwd += tmp + "/"
            try:
                ftp.mkd(tmpcwd)
            except:
                pass
        ftp.cwd(cwd) #选择操作目录'xxx/xxx/' 
        bufsize = 1024#设置缓冲块大小 
        for filename in filenames:
            file_handler = open(filename,'rb')#以读模式在本地打开文件 		
            if handler_fetchname != None:
                filename = handler_fetchname(filename)
            ftp.storbinary('STOR %s' % os.path.basename(filename),file_handler,bufsize)#上传文件 
            ftp.set_debuglevel(0) 
            file_handler.close() 
            mo.logger.info("FTP fin: %s"%filename)
        ftp.quit()
    except:
        mo.logger.info("FTP failed: %s"%str(str(sys.exc_info()) + "; " + str(traceback.format_exc())) )
        return False,sys.exc_info()
    return True,None
'''
ret = ftp_up("myftp.py","localhost",'21',"tei","123456")
print ret
'''

