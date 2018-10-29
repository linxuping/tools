import random
#------- CET-4 -------
f4=open('cet4.txt','r')
lines4 = f4.readlines()
f4.close()
random.shuffle(lines4)
print len(lines4)
f4_2=open('cet4_2.txt','w+')
for line in lines4:
  if len(line.strip('\n')) <= 2:
    print '4',line
    continue
  f4_2.write(line)
f4_2.close()

#------- CET-6 -------
f6=open('cet6.txt','r')
lines6 = f6.readlines()
f6.close()
random.shuffle(lines6)
print len(lines6)
f6_2=open('cet6_2.txt','w+')
for line in lines6:
  if len(line.strip('\n')) <= 2:
    print '6',line
    continue
  f6_2.write(line)
f6_2.close()
