from sqlalchemy import *   
from sqlalchemy.sql import *   
from sqlalchemy.orm import sessionmaker,mapper  
import datetime  
from models import *
  
engine = create_engine('mysql://cdb:Zzm8709+cdb@localhost/cdb2?charset=utf8') 
Session = sessionmaker(bind=engine)
session = Session()
query = session.query(User)
print query.filter(User.create_time>'20010622').limit(3).all()
print query.first().phone,query.first().id
print query.filter(User.id == 19).first().phone
print query.filter(User.id == 19).scalar().phone
print query.count()

print  session.query(LiveTicket).count()
print  "liveticket id: ",session.query(LiveTicket, User).outerjoin(User, LiveTicket.user_id == User.id).first().LiveTicket.id
print  session.query(LiveTicket, User).outerjoin(User, LiveTicket.user_id == User.id).filter(User.id==137).first()
#print  session.query(LiveTicket, User).outerjoin(User, LiveTicket.user_id == User.id).filter(User.id==137).one()
obj = session.query(LiveTicket, User).outerjoin(User, LiveTicket.user_id == User.id).filter(LiveTicket.id==10).scalar()
print obj.create_time
print (datetime.datetime.now() - obj.create_time).total_seconds()

'''
print "-- wk --"
ret = session.query(LiveTicket.id,LiveTicket.live_id).outerjoin(User, LiveTicket.user_id == User.id).outerjoin(Live, LiveTicket.live_id == Live.id).filter(LiveTicket.id==10).scalar()
ret = session.query(LiveTicket.id,LiveTicket.live_id).outerjoin(User, LiveTicket.user_id == User.id).outerjoin(Live, LiveTicket.live_id == Live.id).filter(LiveTicket.id==1000).scalar()
print ret,not ret
print session.query(LiveTicket.id,LiveTicket.live_id).outerjoin(User, LiveTicket.user_id == User.id).outerjoin(Live, LiveTicket.live_id == Live.id).filter(LiveTicket.id==10).first()
print session.query(LiveTicket,Live.id,User.id).outerjoin(User, LiveTicket.user_id == User.id).outerjoin(Live, LiveTicket.live_id == Live.id).filter(LiveTicket.id==10).first()
#print session.query(CircleUser).outerjoin(Circle, and_(CircleUser.circle_id==Circle.id,CircleUser.user_id==290)).first().__dict__
#print session.query(Circle.id, Circle.id==2).all()
print session.query(CircleUser).all()
cuobj = CircleUser(user_id=282, circle_id=2)
print cuobj.__dict__
session.add(cuobj)
session.flush()
ret = session.query(Circle.name,Circle.head_portrait,User.nickname).outerjoin(User, Circle.user_id==User.id).all()
for a,b,c in ret:
    print a,b,c
print "---end---"
import datetime
#user__2 = User(id=10000001,nickname="user__2",login_time=datetime.datetime.now())
#print user__2.__dict__
#session.add(user__2)
#print user__2.id
#print session.query(Circle).outerjoin(CircleUser, CircleUser.circle_id==Circle.id).filter(or_(CircleUser.user_id==290,Circle.user_id==290)).filter(Circle.status==1).order_by(Circle.create_time.desc()).all()
print session.query(Circle.create_time).first()[0].strftime("%Y-%m-%d") 
'''

'''
itemobjs = session.query(CircleTopic.id,CircleTopic.content,CircleTopic.create_time,User.portrait,User.nickname,CircleReply.content).\
                    outerjoin(Circle, and_(CircleTopic.circle_id==Circle.id,Circle.user_id==290)).\
                    outerjoin(User, CircleTopic.user_id==User.id).\
                    outerjoin(CircleReply, and_(CircleTopic.id==CircleReply.topic_id,CircleReply.type==3)).\
                    order_by(CircleTopic.create_time.desc()).offset(0).limit(10).all()
itemids = [ x[0] for x in itemobjs ]
from sqlalchemy.orm import aliased
cra = aliased(CircleReply)
ua = aliased(User)
ura = aliased(User)
query = session.query(cra.id,cra.topic_id,cra.img,cra.content,\
                    cra.create_time,cra.type,\
                    ua.id,ura.id,ua.nickname,ura.nickname).\
            outerjoin(ua,cra.user_id==ua.id).\
            outerjoin(ura,cra.user_id_reply==ura.id).\
            filter(cra.id.in_(itemids)).order_by(cra.create_time.asc())
replies = {}
for id,itemid,img,content,ctime,type,nname,nname_rep,uid,urid in query.all():
    if itemid not in replies:
        replies[itemid] = []
    replies[itemid].append( {'id':id,'topic_id':itemid,'img':img,'content':content,\
                            'time':ctime.strftime("%Y-%m-%d"),'type':type,\
                            'user_reply':{'id':urid,'name':nname_rep},\
                            'user':{'id':uid,'name':nname} })
print replies
items = []
for id,cont,ctime,portrait,nname,cont_reply in itemobjs:
    items.append( {'id':id,'content':cont,'content_reply':cont_reply,\
                    'portrait':portrait,'time':ctime.strftime("%Y-%m-%d"),\
                    'nickname':nname,'replies':replies[id]} )    


cia = aliased(CircleTopic)
cra = aliased(CircleReply)
ua = aliased(User)
ura = aliased(User)
query = session.query(cia.id,cia.content,cia.create_time,\
              User.portrait,User.nickname,cra.content).\
            outerjoin(Circle, cia.circle_id==Circle.id).\
            outerjoin(User, cia.user_id==User.id).outerjoin(cra,\
              and_(cia.id==cra.topic_id,cra.type==3)).\
            order_by(cia.create_time.desc()).filter(Circle.user_id==290)

itemobjs = query.all()
itemids = [ x[0] for x in itemobjs ]
query = session.query(cra.id,cra.topic_id,cra.img,cra.content,\
                    cra.create_time,cra.type,\
                    ua.id,ura.id,ua.nickname,ura.nickname).\
            outerjoin(ua,cra.user_id==ua.id).\
            outerjoin(ura,cra.user_id_reply==ura.id).\
            filter(cra.id.in_(itemids)).order_by(cra.create_time.asc())
replies = {}
for id,itemid,img,content,ctime,type,nname,nname_rep,uid,urid in query.all():
    if itemid not in replies:
        replies[itemid] = []
    replies[itemid].append( {'id':id,'topic_id':itemid,'img':img,'content':content,\
                            'time':ctime.strftime("%Y-%m-%d"),'type':type,\
                            'user_reply':{'id':urid,'name':nname_rep},\
                            'user':{'id':uid,'name':nname} })
items = []
for id,cont,ctime,portrait,nname,cont_reply in itemobjs:
    items.append( {'id':id,'content':cont,'content_reply':cont_reply,\
                    'portrait':portrait,'time':ctime.strftime("%Y-%m-%d"),\
                    'nickname':nname,'replies':replies[id]} )
print items
'''
'''
args = [getattr(CircleTopic,'id'),getattr(CircleTopic,'user_id')]
ret = session.query(*args).filter(CircleTopic.circle_id==1)
print ret.first()
'''


'''
metaitemobjs = MetaData(engine)
users = Table('user', metaitemobjs, autoload=True)
class user(object):
    pass
usermapper = mapper(user, users)
print users.__dict__
class TableA(Base):
    __tablename__ = "tablea"
    id = Column(Integer, primary_key=True)
    name = Column(String)

    tableB = relationship("TableB", secondary = TableC.__table__)

class TableB(Base):
    __tablename__ = "tableb"
    id = Column(Integer, primary_key=True)
    name = Column(String)
'''



