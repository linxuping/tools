kill -2 `cat master.pid`
while [[ `ps aux | grep proxymaster | grep -v 'tail -f proxymaster' | grep -v grep  | wc -l` -gt 0 ]]
do
   echo "kill proxymaster in process ... left:"`ps aux | grep proxymaster | grep -v 'tail -f proxymaster' | grep -v grep  | wc -l`
   sleep 1
done
