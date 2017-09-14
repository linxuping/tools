import redis
r = redis.Redis(host='127.0.0.1', port=6379, db=1)
for i in r.hscan_iter(match="*circle*"):
    print i
