import MySQLdb
import copy
import time
import sys 
import traceback 
import modules as mo
g_conn = None
#lock


def db_init():
		global g_conn
		ret = None
		for i in range(3):
				try:
						mo.logger.info( "[conn]%s_%s_%s_%s %d."%("192.168.12.19","caiji","()zk4DW{","resource",i) )
						g_conn=MySQLdb.connect(host="192.168.12.19",user="caiji",passwd="()zk4DW{",db="resource",port=3306,charset='utf8')
						return True,None
				except:
						ret = str(sys.exc_info()) + "; " + str(traceback.format_exc()) 
						mo.logger.error( ret )
						#time.sleep(1)
		return False,ret


class DBOperation:
	default = "default"
	select = "select"
	insert = "insert"


#@mo.time_calc
def db_exec(_sql, op=DBOperation.default):
		global g_conn
		starttime = time.time()
		count,rets = -1,None
		ret = None
		is_w = (_sql.find("select ")!=0 or _sql.find("6s_trace")!=0 or _sql.find("6s_wx_msg")!=0)
		for i in range(2):
				_cur = None
				try:
						_cur = g_conn.cursor()
						count=_cur.execute(_sql) 
						rets = _cur.fetchall()
						break
				except:
						rets = "[sql error] retry.%d, %s, %s. [%s]"%(i,str(sys.exc_info()),str(traceback.format_exc()),_sql  )
						mo.logger.error( rets )
						db_init()
				finally:
						if _cur != None:
								ret = _cur.lastrowid
								_cur.close()
								g_conn.commit()
		#mo.logger.info("[sql] %s %d %s. "%(_sql,count,str(rets) ))
		endtime = time.time()
		if not " 6s_trace" in _sql and not " 6s_wx_msg" in _sql:
			if is_w:
				mo.logger.info("[sql_w] %s, count:%d, time:%.03f."%(_sql,count,float(endtime - starttime) ))
			else:
				mo.logger.info("[sql_r] %s, count:%d, time:%.03f."%(_sql,count,float(endtime - starttime) ))
		if op == DBOperation.insert:
			return count,rets,ret
		return count,rets


db_init()


