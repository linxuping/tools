#-*-coding=utf-8 -*-
import os
import time

def listDir(fileDir):
     for eachFile in os.listdir(fileDir):
        if os.path.isfile(fileDir+"/"+eachFile):   #如果是文件，判断最后修改时间，符合条件进行删除
            ft = os.stat(fileDir+"/"+eachFile);
            ltime = int(ft.st_mtime); #获取文件最后修改时间
            #print "文件"+path+"/"+eachFile+"的最后修改时间为"+str(ltime);
            ntime = int(time.time())-3600*24; #获取现在时间减去3h
            if ltime<=ntime :         
                print "我要删除文件"+fileDir+"/"+eachFile;
                try:
                    os.remove(fileDir+"/"+eachFile);   
                except:
                    pass 

        elif os.path.isdir(fileDir+"/"+eachFile) :    #如果是文件夹，继续递归
            listDir(fileDir+"/"+eachFile);
    
if __name__ == '__main__':
    path = "D:\down\jailbreak";   #规定目录
    while True :    #持续
        listDir(path);
        print "3600s  wake up start.";
        time.sleep(600);   #减少资源利用率  600s秒一次


		
		