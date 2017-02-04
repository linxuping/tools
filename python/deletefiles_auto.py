#-*-coding=utf-8 -*-
import os
import time

def listDir(fileDir):
  try:
     for eachFile in os.listdir(fileDir):
        if os.path.isfile(fileDir+"/"+eachFile):   
            ft = os.stat(fileDir+"/"+eachFile);
            ltime = int(ft.st_mtime); 
            ntime = int(time.time())-3600*2; 
            if ltime<=ntime :         
                #print "del "+fileDir+"/"+eachFile;
                try:
                    os.remove(fileDir+"/"+eachFile);   
                except:
                    pass 

        elif os.path.isdir(fileDir+"/"+eachFile) :   
            listDir(fileDir+"/"+eachFile);
  except:
    pass
    
if __name__ == '__main__':
    path = "D:\down\jailbreak"; 
    while True :    
        listDir("C:\\ipa\\Fail");
        listDir("C:\ipa\\\InstallErr");
        listDir("C:\\ipa\\TestFail");
        listDir("C:\\ipa\\wait");
        listDir("C:\\ipa\\wait");
        listDir(u"D:\\ipa\\InstallErr");
        listDir(u"D:\\ipa\\TestFail");
        print "1800s wake up start.";
        time.sleep(1800);   
