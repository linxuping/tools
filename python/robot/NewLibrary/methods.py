# encoding=utf8
import sys

reload(sys)
sys.setdefaultencoding('utf8')

class MyClass(object):
    def __init__(self):
        pass

    def printMsg(self,msg):
        import os
        os.system('mkdir /tmp/lxp.log')
        print "hello "+msg

    def writetbLog(self,type,title,quanter,integer,decimal,sale_count,img,code):
        #print "args: ",title,quanter,integer,decimal,sale_count,img,code
        title,quanter,integer,decimal,sale_count,code = str(title),str(quanter),str(integer),str(decimal),str(sale_count),str(code)
        img = str(img)[:-14]+"_400x400"
        file = r'/tmp/tb_%s.log'%type
        file_key = r'/tmp/tb_%s_key.log'%type
        if int(quanter) < 5:
                return
        with open(file, 'a+') as f:
                f.write('"%s","%s","%s.%s","%s","%s","%s","%s"\n'%(title,quanter,integer,decimal,sale_count,img,code,type))
        with open(file_key, 'a+') as f:
                f.write('%s_'%(title))
        #import os
        #os.system('mkdir /tmp/lxp.log')
        #print "hello "+msg

    def writeGood(self,fpath,line):
        head_len = len("J_Itemlist_Pic_")
        gid = line[head_len:]
        with open(fpath, 'a+') as f:
            f.write('https://detail.tmall.com/item.htm?id=%s\n'%(gid))
        #import os

    def voicePage(self):
        import winsound
        winsound.PlaySound('ALARM8', winsound.SND_ASYNC)

    def voiceEnd(self):
        import winsound
        winsound.Beep(300, 2000)
