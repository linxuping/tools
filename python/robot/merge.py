import os
f = open('merge.csv','w+')
f.write('type,titles\n')
for _file in os.listdir('./'):
    if not '_key.log' in _file:
        continue
    _key = _file.split('_')[1]
    f2 = open(_file,'r')
    content = f2.read().replace(',',' ')
    f.write('%s,%s\n'%(_key,content))
f.close()
