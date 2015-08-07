#-- doc --
#alter table: http://blog.csdn.net/ws84643557/article/details/6939846
#end
#mysql -uroot -e "show databases;"
mysql -uroot <<EOF
show databases;
use salmon;
alter table product drop column count;
alter table product add  column count int(12) default 0;

drop trigger tg1;
create trigger tg1 
after insert on product 
for each row
begin
set @_count = '100';
end;
EOF

