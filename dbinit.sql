#! /bin/bash

user="john_feng"
password="SmartAll1"
host="rm-2ze845t4xp15d2umrao.mysql.rds.aliyuncs.com"
port="3306"
db_name="smartall"    #数据库
db_table="retaillabel"    #数据表

mysql -u$user -h$host -P$port -p$password<<EOF
#drop database if exists $db_name    #如果数据库存在，删除数据库
#create database $db_name

use $db_name
drop table if exists $db_table

# 建立表格
#create  table $db_table
#(
#retailLabel_id int(11) not null auto_increment primary key ,
#retailLabel_name text not null ,
#label int(8) not null 
#)engine=Innodb default charset=utf8 ;
#

# 插入数据
insert into $db_name.$db_table(retailLabel_name,label) values("background",0);
insert into $db_name.$db_table(retailLabel_name,label) values("king_jia",1);
insert into $db_name.$db_table(retailLabel_name,label) values("red_wang",2);
insert into $db_name.$db_table(retailLabel_name,label) values("red_jia",3);


