#!/usr/bin/python
# -*- coding: UTF-8 -*-
import os
import time
import hashlib
import datetime
import base64
from Tkinter import *           # 导入 Tkinter 库
import Tkinter as tk
from tkMessageBox import *
fpath = "c1.conf"
fdomain = "c2.conf"

#common BEGIN
#en\decode
def code_prefix():
    str = datetime.date.today().strftime('%Y-%m-%d')
    m1 = hashlib.md5()
    m1.update(str.encode("utf-8"))
    token = m1.hexdigest()
    return base64.b64encode(str)[:8]+token[:20]
def encrypt(key):
	return code_prefix()+base64.b64encode(key)
def decrypt(value):
	value = value[28:]
	try:
		return base64.b64decode(value)
	except:
		pass
	return None
print encrypt('hello')
print decrypt(encrypt('hello'))

def get_mac():
    import uuid
    mac=uuid.UUID(int = uuid.getnode()).hex[-12:].upper()
    return '%s:%s:%s:%s:%s:%s' % (mac[0:2],mac[2:4],mac[4:6],mac[6:8],mac[8:10],mac[10:])
	
def get_domain():
	if os.path.exists(fdomain):
		f = open(fdomain,'r')
		tmp = f.read()
		f.close()
		return decrypt(tmp)
	return 'test.66boy.cn'

def auth(username,passwd):
	import urllib2
	import json
	mac = get_mac()
	encryptData = encrypt(str(username)+str(passwd)+mac)
	data = {
		'field1': username,
		'field2': passwd,
		'field3': encrypt(mac),
		'field4': encryptData
	}
	headers = {'Content-Type': 'application/json'}
	request = urllib2.Request(url='http://%s/api/circle/login/xtb'%get_domain(), headers=headers, data=json.dumps(data))
	resp = json.loads(urllib2.urlopen(request).read())
	data = resp['data']
	if data['domain']:
		f = open(fdomain, 'w')
		f.write(encrypt(data['domain']))
		f.close()
	return data
#auth('lucky01','123456')
#common END

root = Tk()                     # 创建窗口对象的背景色
root.title('淘宝采集助手')
def center_window(root, width, height):
    screenwidth = root.winfo_screenwidth()
    screenheight = root.winfo_screenheight()
    size = '%dx%d+%d+%d' % (width, height, (screenwidth - width)/2, (screenheight - height)/2)
    print(size)
    root.geometry(size)
center_window(root,600,360)
                                # 创建两个列表
li     = ['C','python','php','html','SQL','java']
movie  = ['CSS','jQuery','Bootstrap']
button = Button(root)
listb  = Listbox(root)          #  创建两个列表组件
listb2 = Listbox(root)
for item in li:                 # 第一个小部件插入数据
    listb.insert(0,item)

for item in movie:              # 第二个小部件插入数据
    listb2.insert(0,item)

#listb.pack()                    # 将小部件放置到主窗口中
#listb2.pack()

import thread
import threading
lock = threading.Lock()
tasks = 0

import requests  
import re
import sys
from os.path import join,abspath
requests.utils.DEFAULT_CA_BUNDLE_PATH = 'cacert.pem'
  
#获取页面函数、  
def getHTMLText(url):  
    try:  
        r=requests.get(url,timeout=30)  
        r.raise_for_status()  
        r.encoding=r.apparent_encoding  
        return r.text  
    except:  
        print(sys.exc_info())


        
#对获取页面进行解析  
def parsePage(index,url):
    global _ins
    ilt = []
    for x in range(2):
        html=getHTMLText(url)  
        try:  
            #在爬取下来的网页中进行查找价格  
            #plt=re.findall(r'\"view_price\"\:\"[\d\.]*\"',html)  
            #在爬取下来的网页中查找物品  
            #tlt=re.findall(r'\"raw_title\"\:\".*?\"',html)  
            nids=re.findall(r'\"nid\"\:\".*?\"',html)  
            for i in range(len(nids)):  
                #price=eval(plt[i].split(':')[1])  
                #title=eval(tlt[i].split(':')[1])
                price,title=0,''
                nid=eval(nids[i].split(':')[1])
                ilt.append([price,title,nid])
        except:  
            print sys.exc_info()
        if len(ilt) > 0:
            break
    _ins[index] = ilt


#进行打印  
def printGoodsList(ilt):  
    tplt = "{:4}\t{:8}\t{:16}\t{:24}"  
    print(tplt.format("序号", "价格", "商品名称", "nid"))  
    count = 0  
    for g in ilt:  
        count = count + 1  
        #print(tplt.format(count, g[0], g[1], g[2]))  
        #print(g[2])
        _f.write("https://detail.tmall.com/item.htm?id="+g[2].strip(' \r\n')+"\n")

depth=100
_in = 0
_out = 0
_ins = {}


def _run(start_url):
    global _in,_out
    while _in < depth:
        try:
            i = 0
            lock.acquire()
            i = _in
            _in += 1
            #print i,start_url+'&s='+str(44*i)
            lock.release()
            parsePage( i,start_url+'&s='+str(44*i) )
        except:
            try:
                lock.release()
            except:
                pass
            print sys.exc_info()
        lock.acquire()
        _out += 1
        print _out
        lock.release()

_num = 0
def wait_result():
    infoList=[]
    global _in,_out,depth,_ins,text,_num
    while True:
        _num += 1
        print _out
        #label['text'] = "进行中... %d/%d"%(_out,depth)
        #label.config(text="进行中... %d/%d"%(_out,depth))
        #label.pack()
        #root.update_idletasks()
        text.delete(1.0,tk.END)
        text.insert(tk.END, "正在爬取最新商品信息：%d/%% %s\n"%(_out,'.'*(_num%6)))
        time.sleep(0.5)
        if _out < depth:
            continue
        break
    for k,v in _ins.items():
        print k,len(v)
        infoList.extend(v)
    print 'result: ',len(infoList)
    printGoodsList(infoList)
    #label['text'] = "生成完毕！"
    text.insert(tk.END, "生成完毕！\r\n")
    _in = 0
    _out = 0
    _ins = {}
    _f.close()



def helloButton():
    if _in > 0:
        showwarning('Yes', '有任务正在执行！')
        return
    if not entry.get():
        showwarning('Yes', '请输入搜索词！')
        return
    print _in
    #time.sleep(1)
    label['text'] = "正在生成中，请稍候后。。。"
    time.sleep(1)
    gen(entry.get())

_f = None
fm1,entry,text,label = None,None,None,None
def showMain():
	global fm1,entry,text,label
	fm1 = Frame(root)
	label = Label(fm1, text="请输入商品关键字：")
	label.pack(side=LEFT)
	entry = Entry(fm1)
	entry.pack(side=LEFT)
	Button(fm1, text='生成', command=helloButton).pack(side=LEFT, padx=10)
	fm1.pack(side=TOP)

	text = tk.Text(root)
	text.pack()
	label = Label(root,text = '0%')
	#label.pack()

  
def gen(goods):
    global tasks,_out,label
    #goods='书包'
    global _f
    _f = open(goods+'.txt', 'w+')
    #depth=10
    start_url='https://s.taobao.com/search?q='+goods  
    infoList=[]  
    #for i in range(depth):
    #    print i
    #    try:  
    #        #str函数的作用是将其中的内容转换为字符串  
    #        url=start_url+'&s='+str(44*i)  
    #        print url
    #        #html=getHTMLText(url)  
    #        #parsePage(infoList , html)
    #        thread.start_new_thread( parsePage, (infoList, url, ) )
    #    except:  
    #        print sys.exc_info()
    for i in xrange(8):
        thread.start_new_thread( _run, (start_url, ) )
    thread.start_new_thread(wait_result,())
    return
    infoList=[]
    global _out,depth,_ins
    while True:
        print _out
        label['text'] = "进行中... %d/%d"%(_out,depth)
        #label.config(text="进行中... %d/%d"%(_out,depth))
        #label.pack()
        #root.update_idletasks()
        
        text.insert(0, "正在爬取最新商品信息... %d/%d"%(_out,depth))
        time.sleep(2)
        if _out < depth:
            continue
        break
    for k,v in _ins.items():
        print k,len(v)
        infoList.extend(v)
    print 'result: ',len(infoList)
    printGoodsList(infoList)
    label['text'] = "生成完毕！"
    _f.close()

class LoginPage(Frame,object):
    def __init__(self):
        super(LoginPage,self).__init__()
        self.username = StringVar()
        self.password = StringVar()
        self.pack()
        self.createForm()
 
    def createForm(self):
        Label(self).grid(row=0, stick=W, pady=10)
        Label(self, text = '账户: ').grid(row=1, stick=W, pady=10)
        Entry(self, textvariable=self.username).grid(row=1, column=1, stick=E)
        Label(self, text = '密码: ').grid(row=2, stick=W, pady=10)
        Entry(self, textvariable=self.password, show='*').grid(row=2, column=1, stick=E)
        Button(self, text='登陆', command=self.loginCheck).grid(row=3, stick=W, pady=10)
        Button(self, text='退出', command=self.quit).grid(row=3, column=1, stick=E)
 
    def loginCheck(self):
        name = self.username.get()
        secret = self.password.get()
        data = None
        for i in range(3):
            try:
                data = auth(name,secret)
                break
            except:
                time.sleep(i)
        if not data:
            return showinfo(title='错误', message='服务器忙！请联系技术人员处理')
        print data
        if data['status']:
            self.destroy()
            showMain()
            f = open(fpath,'w')
            f.write(encrypt(get_mac()))
            f.close()
        else:
            showinfo(title='错误', message=data['reason'])
            # print('账号或密码错误！')
'''  
root = Tk()
root.title('小程序')
width = 280
height = 200
screenwidth = root.winfo_screenwidth()  
screenheight = root.winfo_screenheight() 
alignstr = '%dx%d+%d+%d' % (width, height, (screenwidth-width)/2, (screenheight-height)/2)
root.geometry(alignstr)    # 居中对齐
'''

if os.path.exists(fpath):
	f = open(fpath,'r')
	tmp = f.read()
	f.close()
	if decrypt(tmp) == get_mac():
		showMain()
	else:
		LoginPage()
else:
	LoginPage()

root.mainloop()                 # 进入消息循环


