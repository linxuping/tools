start=`date`
for((i=0;i<100;i++))
do
echo "start user "$i
python simple_test_send_priority.py 10000 &
done
echo "from "$start" to "`date`
