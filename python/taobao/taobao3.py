#!/usr/bin/python
# -*- coding: UTF-8 -*-
import time
import winsound
from Tkinter import *           # 导入 Tkinter 库
import Tkinter as tk
from tkMessageBox import *
import traceback
root = Tk()                     # 创建窗口对象的背景色
root.title('淘宝采集助手')
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

f = open('cookies.txt')
cookies_str = f.read()
print "cookies: ",cookies_str
f.close()
cookies=""
  
#获取页面函数、  
def getHTMLText(url):  
    global cookies,cookies_str
    try:  
        headers = {'cookie':cookies_str}
        if not cookies:
            r=requests.get(url,timeout=3,headers=headers) 
        else:
            r=requests.get(url,timeout=3,cookies=cookies) 
        cookies = r.cookies		
        #print(cookies)
        r.raise_for_status()  
        r.encoding=r.apparent_encoding  
        return r.text  
    except:  
        print(sys.exc_info(),traceback.print_exc())


        
#对获取页面进行解析  
def parsePage(index,url):
    global _ins,cookies,text
    ilt = []
    for x in range(1):
        html=getHTMLText(url)  
        try:  
            #在爬取下来的网页中进行查找价格  
            #plt=re.findall(r'\"view_price\"\:\"[\d\.]*\"',html)  
            #在爬取下来的网页中查找物品  
            #tlt=re.findall(r'\"raw_title\"\:\".*?\"',html)  
            nids=re.findall(r'\"nid\"\:\".*?\"',html)  
            #print(html)
            for i in range(len(nids)):  
                #price=eval(plt[i].split(':')[1])  
                #title=eval(tlt[i].split(':')[1])
                price,title=0,''
                nid=eval(nids[i].split(':')[1])
                text.insert(tk.END, "爬取商品:%s \n"%nid)
                ilt.append([price,title,nid])
        except:  
            print sys.exc_info()
        if len(ilt) > 0:
            winsound.PlaySound('ALARM8', winsound.SND_ASYNC)
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

depth=50
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
        time.sleep(4)

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
        time.sleep(1.5)
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
    #winsound.Beep(300,1000)
    winsound.PlaySound('ALARM8', winsound.SND_ASYNC)
    winsound.PlaySound('ALARM8', winsound.SND_ASYNC)
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
fm1 = Frame(root)
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
    for i in xrange(1):
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

root.mainloop()                 # 进入消息循环
