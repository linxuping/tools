#mysql -uroot -e "show databases;"
mysql -uroot <<EOF
show databases;
use salmon;
#show tables;

drop table uclog;
drop table ucinfo;

create table `ucinfo` ( `id` int(11) NOT NULL AUTO_INCREMENT, `number` int(11) DEFAULT 0, PRIMARY KEY (`id`) );

create table `uclog` ( `id` int(11) NOT NULL AUTO_INCREMENT, `ucid` int(11) NOT NULL,`number` int(11) DEFAULT 0, PRIMARY KEY (`id`), CONSTRAINT `ucid_1234` FOREIGN KEY (`ucid`) REFERENCES `ucinfo` (`id`) );

EOF

