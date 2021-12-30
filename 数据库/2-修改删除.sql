use course;
show tables;
SET SQL_SAFE_UPDATES = 0;
SET FOREIGN_KEY_CHECKS = 0;

insert into student (Sno, Sname, Ssex, Sdept, Sage) values ('201215128', '陈冬','男','IS', 18);
insert into student values('201215126', '张成民', '男',18,'CS');

insert into SC (Sno, Cno) values ('201215128', '1');

drop table if exists Dept_age;
create table Dept_age(
	Sdept char(15),
    Avg_age smallint
);

insert into Dept_age(Sdept, Avg_age) 
	select Sdept,AVG(Sage) 
	from Student 
	group by Sdept;

select * from Dept_age;

update student set Sage = 22 where Sno = '201215121';

update student set Sage = Sage + 1;

update SC set Grade = 0 where Sno in (
	select Sno from student where Sdept = 'CS'
);
select * from SC;

delete from Student where Sno = '201215128';

-- 这里没有写删除多个元组的删除语句

delete from sc where Sno in(
	select Sno from student where Sdept='CS'
);

insert into sc (Sno, Cno, Grade) values ('201215126', '1', null);
-- insert into sc (Sno, Cno) values ('201215126', 1);
update student set Sdept=null where Sno = '201215200';

select * from student where Sname is null or Ssex = null or Sage = null or Sdept = null;

select * from sc where Grade < 60 and Cno = '1';

select Sno from SC where Grade < 60 and Cno = '1'
union
select Sno from SC where Grade is null and Cno = '1';

select Sno from sc where Cno = '1' and (Grade < 60 or Grade is null);

SET FOREIGN_KEY_CHECKS = 1;
SET SQL_SAFE_UPDATES = 1;

select * from sc;

