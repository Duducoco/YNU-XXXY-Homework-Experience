drop database if exists chapter8;
create database chapter8;
use chapter8;
drop table if exists account;
create table account
(
    accountnum char (4) primary key,
    total float
);
insert into account values  ('0001', 200), 
                            ('0002', 300);


drop procedure if exists p_transfer;
DELIMITER |
create procedure p_transfer
(   
    inAccount char(4), 
    outAccount char(4), 
    amount float, 
    out info varchar(10)
)
begin
    declare totalDepositOut float;
    declare totalDepositIn float;
    declare inNum char(4);
    declare outNum char(4);

    select accountnum into inNum from account where accountnum = inAccount;

    if (inNum is null) then
        set info = '转入账号有错';
    else
        select accountnum, total into outNum, totalDepositOut
        from account where accountnum = outAccount;
		if (outNum is null) then
			set info = '转出账号有错';
		else
			if (totalDepositOut < amount) then
				set info = '转出余额不足';
			else
            update account set total = total - amount where accountnum = outAccount;
				update account set total = total  + amount where accountnum = inAccount;
				set info = '转账成功！';
			end if;
		end if; 
    end if; 
select info;
end |


call p_transfer('0002','0001',50, @info);
SELECT @info AS 结果;
 
select * from account;



set foreign_key_checks =0;

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
	('7','PASCAL语言','6', 4),
    ('8','离散数学',null, 4)
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
	('201215121', '8', 68),
	('201215122', '1', 80),
    ('201215122', '2', 90),
	('201215122', '3', 80),
    ('201215122', '8', 73),
	('201215123', '1', 80),
    ('201215123', '2', 90),
	('201215123', '3', 92),
    ('201215123', '8', 85),
	('201215125', '1', 84),
    ('201215125', '2', 73),
    ('201215125', '3', 59),
    ('201215125', '8', 88)
;

set foreign_key_checks =1;


-- (1) 统计离散数学的成绩分布情况
drop table if exists lisan_seg;
create table lisan_seg 
(
    Cname char(20),
    less_than_60 int,
    between_60_69 int,
    between_70_79 int,
    between_80_89 int,
    between_90_100 int
);


drop procedure if exists p_lisan;
DELIMITER |
create procedure p_lisan(
    courseName varchar(20),
    out info varchar(20)
)
begin
    declare less_than_60 int;
    declare between_60_69 int;
    declare between_70_79 int;
    declare between_80_89 int;
    declare between_90_100 int;
    declare courseNo char(4);

    select Cno into courseNo from course where Cname = courseName;

    select count(*) into less_than_60 from SC where Cno=courseNo and Grade < 60;
    select count(*) into between_60_69 from SC where Cno=courseNo and Grade between 60 and 69;
    select count(*) into between_70_79 from SC where Cno=courseNo and Grade between 70 and 79;
    select count(*) into between_80_89 from SC where Cno=courseNo and Grade between 80 and 89;
    select count(*) into between_90_100 from SC where Cno=courseNo and Grade between 90 and 100;

    insert into lisan_seg values
        (courseName,less_than_60, between_60_69, between_70_79, between_80_89, between_90_100);
    set info='成功';
select info;
end |

call p_lisan('离散数学',@info);
SELECT @info AS 结果;

select * from lisan_seg;

-- (2)统计任意一门课的平均成绩
drop table if exists avg_grade;
create table avg_grade
(
    Cname char(20),
    avg_grade float
);

drop procedure if exists p_avg;
DELIMITER |
create procedure p_avg(
    CourseName varchar(20),
    out info varchar(20)
)
begin
    declare course_number int;  -- 课程数量
    declare avg_grade float;    -- 平均成绩
    declare courseNo char(4);   -- 课程号
    declare done_num int;    -- 完成数量

    select Cno into courseNo from course where Cname=CourseName;
    select AVG(Grade) into avg_grade from SC where Cno=courseNo;

    insert into avg_grade(Cname, avg_grade) values(CourseName, avg_grade);
    set info='成功';
select info;
end

call p_avg('离散数学',@info);
select * from avg_grade;

-- (3)将学生选课成绩从百分制改为等级制（A,B,C,D,E)
alter table SC add column grade_rank char(20);

drop procedure if exists p_grade;
DELIMITER |
create procedure p_grade(
    out info varchar(20)
)
begin
    update SC set grade_rank = 'A' where Grade >= 90;
    update SC set grade_rank = 'B' where Grade between 80 and 89;
    update SC set grade_rank = 'C' where Grade between 70 and 79;
    update SC set grade_rank = 'D' where Grade between 60 and 69;
    update SC set grade_rank = 'E' where Grade < 60;

    set info='成功';
select info;
end

call p_grade(@info);
select @info AS 结果;
select Sno, Cno, grade_rank from SC;





