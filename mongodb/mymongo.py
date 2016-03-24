from pymongo import *  
#from pymongo.objectid import ObjectId  
from gridfs import *
from pprint import pprint  
#doc: http://blog.csdn.net/w13770269691/article/details/7187657
  
conn = MongoClient("192.168.29.163", 27017)
db = conn.test  
print db
db = conn.collections  
print db
gfs = GridFS(db)
print gfs

print "+ write in"
with open("/etc/rc.local", "r") as file:  
	id = gfs.put(file.read(), filename = "/xxx/yyy/a.txt", upload = "q.yuhen", abc = 123)  
	print id 
print gfs.list()

print "+ read out"
with open("/tmp/rc.local", "w") as file:  
	out = gfs.get_last_version("/xxx/yyy/a.txt")  
	file.write(out.read())  
	print out.name, out.length 

print gfs.list()



