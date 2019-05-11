#!/usr/bin/env python
#coding:utf-8

#https://www.cnblogs.com/wangyongsong/p/6750454.html
import time
class Date:
    def __init__(self,year,month,day):
        self.year=year
        self.month=month
        self.day=day
    @staticmethod
    def now1():
        t=time.localtime()
        return Date(t.tm_year,t.tm_mon,t.tm_mday)

    @classmethod #改成类方法
    def now2(cls):
        t=time.localtime()
        return cls(t.tm_year,t.tm_mon,t.tm_mday) #哪个类来调用,即用哪个类cls来实例化

class EuroDate(Date):
    def __str__(self):
        return 'year:%s month:%s day:%s' %(self.year,self.month,self.day)

#如果要把一个类的实例变成 str，就需要实现特殊方法__str__()：
e=EuroDate.now1()
print(e)
e=EuroDate.now2()
print(e)

#-------------- 加了self的属性就是类实例的属性，不加就是类的属性 ----------------
class Car1:
    wheel = 4 

class Car2:
    def __init__(self):
        self.wheel = 4

print "来看下__dict__的差别吧："
c1 = Car1()
c2 = Car2()
print dir(c1), c1.__dict__
print dir(c2), c2.__dict__

