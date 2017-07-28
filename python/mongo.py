import redis
import copy
import datetime
import sys 
import traceback 
#import skills.settings as settings
#import modules as mo

import pymongo
client = pymongo.MongoClient('localhost', 27017)
mdb = client.airlib
#mdb.book.create_index([('corrd','2dsphere')])
#mdb.book.insert_one({"corrd":[114,50],"streat":"***","name":"new book","create_time":datetime.datetime.now()})
#mdb.book.insert_one({"corrd":[114,60],"streat":"***","name":"new book2","create_time":datetime.datetime.now()})
#mdb.book.insert_one({"corrd":[184,50],"streat":"***","name":"new book3","create_time":datetime.datetime.now()})
#cursor = mdb.book.find({"corrd": {'$geoWithin':{'$centerSphere':[[114,49],1000] }} })
cursor = mdb.book.find({"corrd": {'$near':{'$geometry':{'type':'Point','coordinates':[114,49]}} } }).limit(2).skip(0)
for doc in cursor:
	print doc
