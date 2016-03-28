#!/usr/bin/env python
# -*- coding: utf-8 -*-
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

db.places.insert({
"loc": {"type": "Point", "coordinates": [ -73.97, 40.77 ] },
"name": "Central Park",
"category" : "Parks"
   }
)
db.places.insert({
      "loc" : { "type": "Point", "coordinates": [ -73.88, 40.78 ] },
      "name": "La Guardia Airport",
      "category" : "Airport"
   }
)
#建立索引
#print type(db.places),dir(db.places)
'''
['_BaseObject__codec_options', '_BaseObject__read_concern', '_BaseObject__read_preference', '_BaseObject__write_concern', '_Collection__create', '_Collection__create_index', '_Collection__database', '_Collection__find_and_modify', '_Collection__full_name', '_Collection__name', '__call__', '__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattr__', '__getattribute__', '__getitem__', '__hash__', '__init__', '__iter__', '__module__', '__ne__', '__new__', '__next__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_command', '_count', '_delete', '_insert', '_insert_one', '_legacy_write', '_socket_for_primary_reads', '_socket_for_reads', '_socket_for_writes', '_update', 'aggregate', 'bulk_write', 'codec_options', 'count', 'create_index', 'create_indexes', 'database', 'delete_many', 'delete_one', 'distinct', 'drop', 'drop_index', 'drop_indexes', 'ensure_index', 'find', 'find_and_modify', 'find_one', 'find_one_and_delete', 'find_one_and_replace', 'find_one_and_update', 'full_name', 'group', 'index_information', 'initialize_ordered_bulk_op', 'initialize_unordered_bulk_op', 'inline_map_reduce', 'insert', 'insert_many', 'insert_one', 'list_indexes', 'map_reduce', 'name', 'next', 'options', 'parallel_scan', 'read_concern', 'read_preference', 'reindex', 'remove', 'rename', 'replace_one', 'save', 'update', 'update_many', 'update_one', 'with_options', 'write_concern']`
'''
db.places.create_index( [("loc","2dsphere")] )
#参数不是1或-1，为2dsphere。还可以建立组合索引。
#db.places.createIndex( { "loc" : "2dsphere" , "category" : -1, "name": 1 } )
print db.places.find
print db.places.list_indexes()

