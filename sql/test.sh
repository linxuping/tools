#mysql -uroot -e "show databases;"
mysql -uroot <<EOF
show databases;
use salmon;
#show tables;

drop table uclog;
drop table ucinfo;

create table `ucinfo` ( `id` int(11) NOT NULL AUTO_INCREMENT, `number` int(11) DEFAULT 0, PRIMARY KEY (`id`) );

create table `uclog` ( `id` int(11) NOT NULL AUTO_INCREMENT, `ucid` int(11) NOT NULL,`ip` char(48) DEFAULT 0, PRIMARY KEY (`id`), CONSTRAINT `ucid_1234` FOREIGN KEY (`ucid`) REFERENCES `ucinfo` (`id`) );

insert into ucinfo (number) values ('1234567'),('1234568'),('1234569');
insert into uclog (ucid,ip) values (1,"192.168.12.1"), (2,"192.168.12.2"), (2,"192.168.12.2"), (2,"192.168.12.3"), (3,"192.168.12.2"), (3,"192.168.12.4");

EOF

