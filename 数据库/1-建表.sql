drop database if exists course;
create database course;
use course;

set FOREIGN_KEY_CHECKS = 0;

drop table if exists student;
create table student(
	Sno char(9) primary key,
	Sname char(20),
	Ssex char(2),
	Sage smallint,
	Sdept char(20)
);

insert into student values
	(201215121, '李勇', '男', 20, 'CS'),
	(201215122, '刘晨', '女', 19, 'CS'),
	(201215123, '王敏', '女', 18, 'MA'),
	(201215125, '张立', '男', 19, 'IS')
;

drop table if exists course;
create table course(
	Cno char (4) primary key,
	Cname char(40) not null,
	Cpno char(4),
	Ccredit smallint,
	foreign key (Cpno) references course(Cno)
);

insert into course values
	('1','数据库','5', 4),
	('2','数学',null, 4),
	('3','信息系统','1', 4),
	('4','操作系统','6', 3),
	('5','数据结构','7', 4),
	('6','数据处理',null, 2),
	('7','PASCAL语言','6', 4)
;

drop table if exists SC;
create table SC(
	Sno char(9),
	Cno char(4),
	Grade smallint,
	primary key (Sno,Cno),
	foreign key (Sno) references student(Sno),
	foreign key (Cno) references course(Cno)
);

insert into SC values
	('201215121', '1', 92),
	('201215121', '2', 85),
	('201215121', '3', 88),
	('201215122', '2', 90),
	('201215122', '3', 80)
;

set FOREIGN_KEY_CHECKS = 1;

select * from student;
select * from course;
select * from SC;



