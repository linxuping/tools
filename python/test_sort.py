class Car:
  m = 0
  def __init__(self,m):
    self.m = m

lis = [ Car(4),Car(3),Car(5) ]
for item in lis:
  print item.m

lis2 = sorted(lis, key=lambda d:d.m)
print type(lis2)
for item in lis2:
  print item.m

lis2 = sorted(lis, key=lambda d:d.m, reverse=True)
for item in lis2:
  print item.m

lis2 = sorted([], key=lambda d:d.m, reverse=True)
for item in lis2:
  print item.m
