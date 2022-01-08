drop database if exists Course2;
create database Course2;

use Course2;

set FOREIGN_KEY_CHECKS = 0;

-- 完整性约束子句
drop table if exists Student;
CREATE TABLE Student(
	Sno NUMERIC(20)
    CONSTRAINT C1 CHECK (Sno BETWEEN 90000 AND 99999),
    Sname CHAR(20),
    CONSTRAINT C2 CHECK ( Sname IS NOT NULL),
    Sage NUMERIC(3),
    CONSTRAINT C3 CHECK (Sage < 30),
    Ssex CHAR(2),
    CONSTRAINT C4 CHECK (Ssex IN ( '男','女')),
    CONSTRAINT StudentKey PRIMARY KEY(Sno)
);

-- insert into student values
-- 	(201215121, '李勇', '男', 20, 'CS'),
--  (201215122, '刘晨', '女', 19, 'CS'),
-- 	(201215123, '王敏', '女', 18, 'MA'),
-- 	(201215125, '张立', '男', 19, 'IS')
-- ;


drop table if exists course;
create table course(
	Cno char (4) primary key,
	Cname char(40) not null,
	Cpno char(4),
	Ccredit smallint,
	foreign key (Cpno) references course(Cno)
);

drop table if exists SC;
create table SC(
	Sno NUMERIC(20) not null,
	Cno char(4) not null,
	Grade smallint,
	primary key (Sno,Cno)
	-- foreign key (Sno) references student(Sno),
	-- foreign key (Cno) references course(Cno)
);

drop table if exists dept;
CREATE TABLE DEPT(
 	Deptno  NUMERIC(2),
 	Dname  CHAR(9)  UNIQUE,/*要求Dname列值唯一*/
 	Location  CHAR(10),
 	PRIMARY KEY (Deptno)
 );


drop table if exists TEACHER;
CREATE TABLE TEACHER(
	Eno NUMERIC(4) PRIMARY KEY,
    Ename CHAR(10),
    Job CHAR(8),
    Sal NUMERIC(7,2),
    Deduct NUMERIC(7,2),
    Deptno NUMERIC(2),
    CONSTRAINT TEACHERKey FOREIGN KEY (Deptno) REFERENCES DEPT(Deptno),
    CONSTRAINT C5 CHECK (Sal+Deduct >= 3000)
    -- 这里用C1会报constraint重复的错误，
);

alter table student
	drop constraint c1;
    
alter table student
	add constraint c1 check (sno between 900000 and 999999);

alter table student
	drop constraint c3;
    
alter table student
	add constraint c3 check (sage<40);

DELIMITER |
drop trigger if exists sc_t;
create trigger sc_t
after update on sc for each row
begin
	if(NEW.grade >= 1.1 * OLD.grade) then
		insert into sc_u values (OLD.sno, OLD.cno, OLD.grade,NEW.grade);
	end if;
end |



CREATE TABLE StudentInsertLog (
	Numbers int
)
DELIMITER |
drop trigger if exists Student_Count;
create trigger Student_Count
after insert on student for each row
	INSERT INTO StudentInsertLog (Numbers) SELECT count(NEW.Sno) from Student



DELIMITER |
drop trigger if exists Insert_sal;

create trigger Insert_sal
before insert on Teacher for each row
begin 
	if ( (NEW.job='教授') and (NEW.sal < 4000) ) then
		set NEW.sal := 4000;
	end if;
end |


DELIMITER |
drop trigger if exists Update_sal;
create trigger Update_sal
before update on Teacher for each row
begin 
	if ( (NEW.job='教授') and (NEW.sal < 4000) ) then
		set NEW.sal := 4000;
	end if;
end |





CREATE TABLE SC_U(
	Sno NUMERIC(20),
	Cno char(4),
	oldGrade smallint,
	newGrade smallint
)



set FOREIGN_KEY_CHECKS = 1;

insert into sc values(2,'2',80);
update sc (2,'2',90) where sno=2;

