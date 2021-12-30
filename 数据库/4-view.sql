use course;

drop view if exists is_student;
create view is_student as 
	select Sno, Sname, Sage from student where Sdept='is'
    with check option;
    
drop view if exists is_s1;
create view is_s1(Sno,Sname,Grade) as
	select Student.Sno, Sname,Grade from Student,SC where 
		Sdept='is' and 
        Student.Sno = SC.Sno and 
        SC.Cno = '1';


drop view if exists is_s2;
create view is_s2 as select Sno,Sname,Grade from is_s1 where Grade > 90;

drop view if exists BT_S;
create view BT_S(Sno,Sname,Sbirth) as 
	select Sno,Sname,2021-Sage from student;

drop view if exists S_G;
create view S_G(Sno,Savg) as 
	select Sno,avg(Grade) from SC group by Sno;
    
drop view if exists F_student;
create view F_Student (F_sno, name, sex, age, Sdept) as
	select * from student where Ssex = '女';
    
select Sno,Sage from is_student where Sage < 20;

select is_student.sno, sname from is_student,sc where is_student.sno=sc.sno and sc.cno='1';

select Sno, avg(Grade) from sc group by sno having avg(grade) >= 90;
    
select * from 
	(select Sno, avg(Grade) from sc group by Sno) 
    as S_G(Sno,Gavg) where Gavg>=90;
    
update is_student set Sname='刘辰' where Sno='201215122';

-- insert into is_student values ('201215129','赵新',20);  报错，mysql不支持这么做



