import json
import commands
import time
import datetime
import os
#os.system("C:\\auto_crack\\crack\\start.cmd")

#status,output = commands.getstatusoutput("taskkill /f /im IPACrackGen.exe")
def get_qlen(qname):
    output = os.popen("curl -i -u teiron:teiron http://queue.local:5673/api/queues/%2f/"+qname).read()
    if "messages" not in output:
        print output
    else:
        data = '{'+output.split("{",1)[1]
        jobj = json.loads(data)
        del_get = 0
        try:
            del_get = jobj['message_stats']['deliver_get']
        except:
            pass
        qlen = jobj['messages']
        return qlen,del_get
    return 0,0

init = True
qlen,gsize = 0,0
count = 0
while True:
    asize,bsize = get_qlen('jb_down_PC216')
    if init:
        qlen,gsize = asize,bsize
        init = False
    #print asize,bsize,gsize
    if asize == 0:
        gsize = bsize
        count  = 0
    elif bsize == gsize:
        count = count+1
        if count >= 500:
            print "restart ... ",datetime.datetime.now()
            count = 0
            os.system("taskkill /f /im IPACrackGen.exe")
            os.system("C:\\auto_crack\\crack\\startcrack.cmd")
    else:
        gsize = bsize
        count = 0
    time.sleep(3)

import time
time.sleep(3000)

