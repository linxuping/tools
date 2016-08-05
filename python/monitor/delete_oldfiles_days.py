#coding=utf-8  
import os  
import datetime  
import time  
#获得当前日期  
today = datetime.date.today()  
#获得历史日期，本例中为14天之前  
twoweek= datetime.timedelta(days=-5)    
leastday = today + twoweek  
print(today)  
print(leastday)  
dir = "D:\\down\\jailbreak"  
  
def deleteFile():  
    files = os.listdir(dir)  
    for f in files:  
        destfile = os.path.join(dir,f);  
        if (os.path.isfile(destfile)):  
            name = os.path.splitext(f)[0]  
            postfix = os.path.splitext(f)[1]  
            #获得文件后缀，只是针对.zip文件  
            if (postfix == ".ipa"):  
                print(name)  
                #获得该文件的创建日期，modifytime为元组  
                modifytime = time.localtime((os.path.getmtime(destfile)))  
                year = modifytime[0]  
                month = modifytime[1]  
                day = modifytime[2]  
                #将日期初始化为date对象  
                filedate = datetime.date(year, month, day)  
                #比较日期，删除较早的文件  
                if (leastday > filedate):  
                    print("delete old file")  
                    os.remove(destfile)  
              
if __name__ == '__main__':  
    deleteFile()  
