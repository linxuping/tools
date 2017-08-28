'''
>>> import datetime
>>> str = '2012-11-19'
>>> date_time = datetime.datetime.strptime(str,'%Y-%m-%d')
>>> date_time
datetime.datetime(2012, 11, 19, 0, 0)
>>> date_time - datetime.timedelta(days=1)                   
datetime.datetime(2012, 11, 18, 0, 0)
>>> date_time.strftime('%Y-%m-%d')
'2012-11-19'
'''

def get_yesterday(date_str):
    import datetime
    date_time = datetime.datetime.strptime(date_str,'%Y-%m-%d')
    date_time = date_time - datetime.timedelta(days=1)                   
    return date_time.strftime('%Y-%m-%d')

print get_yesterday('2012-11-19')

