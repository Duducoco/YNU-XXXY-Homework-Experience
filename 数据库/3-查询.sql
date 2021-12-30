use course;

select Sno, Sname from Student;
select Sno, Sno, Sdept from student;
select * from student;
select Sname, 2014-Sage from student;
select Sname, 'Year of Birth:', 2014-Sage, lower(Sdept) from student;
select Sname as Name, 'Year of Birth:' as BIRTH, 2014-Sage as Birthday, LOWER(Sdept) as DEPARTMENT from Student;
select Sno from sc;
select distinct Sno from sc;
select ALL Sno from sc;
select Sname from Student where Sdept='CS';
select Sname, Sage from student where Sage < 20;
select distinct Sno from sc where Grade < 60;
select Sname, Sdept, Sage from Student where Sage between 20 and 30;
select Sname, Sdept, Sage from student where Sage not between 20 and 30;
select Sname,Ssex from student where Sdept in ('CS', 'MA', 'IS');
select Sname,Ssex from student where Sdept not in ('CS', 'MA', 'IS');
select * from student where Sno like '201215121';
select Sname, Sno, Ssex from student where Sname like '刘%';
select Sname from student where Sname like '欧阳_';
select Sname, Sno, Ssex from student where Sname not like '刘%';
select Cno, Ccredit from Course where Cname like 'DB\_Design' escape '\\';
select * from course where Cname like 'DB\_%i__' escape '\\';
select Sno, Cno from SC where Grade is null;
--
select Sname from student where Sdept='CS' and Sage < 20;
select Sname,Ssex from student where Sdept = 'CS' or Sdept = 'MA' or Sdept = 'IS';
select Sno, Grade from sc where Cno='3' order by Grade desc;
select * from student order by Sdept,Sage desc;
select count(*) from student;
select count(distinct Sno) from sc;
select avg(Grade) from sc where Cno='1';
select max(Grade) from sc where Cno='1';
select sum(Ccredit) from sc, course where Sno = '201215012' and SC.Cno=Course.Cno;
select Cno, COUNT(Sno) from SC group by Cno;
select Sno from SC group by Sno having count(*) > 3;
select Sno, avg(Grade) from sc group by Sno having avg(grade) >= 90;
select student.*, sc.* from student, sc where student.Sno=sc.sno;
select student.sno, Sname, Ssex, Sage, Sdept, Cno, Grade from Student,sc where student.sno = sc.sno;
select student.sno, sname from student,sc where student.sno=sc.sno and sc.cno='2' and sc.grade>90;
select first.cno, second.cpno from course as first, course as second where first.cpno=second.cno;
select student.sno, sname,ssex, sage,sdept,cno,grade from student left join sc on (student.sno = sc.sno);
select student.sno, Sname,Cname,Grade from student,sc,course where student.sno = sc.sno and sc.cno = course.cno;
select sname from student where Sno in
	(select Sno from sc where Cno='2');

select Sno, Sname, Sdept from student where Sdept in
	(select sdept from student where Sname='刘晨');

select sno,sname from student where sno in 
	(select sno from sc where cno in
		(select cno from course where Cname='信息系统')
    );
    
select student.sno,sname from student,sc,course where student.sno=sc.sno and sc.cno=course.cno and course.cname='信息系统';
select sno,sname,sdept from student where sdept=(
	select sdept from student where sname='刘晨'
);
select sno,cno from sc as x where grade >= (
	select avg(grade) from sc as y where y.sno=x.sno
);
select sname,sage from student where 
	sage < any ( select sage from student where sdept='cs') and 
	sdept <> 'cs';

select sname,sage from student where 
	sage < (select max(sage) from student where sdept ='cs') and
	sdept <> 'cs';

select sname,sage from student where 
	sage < all(select sage from student where sdept='cs') and
	sdept <> 'cs';

select sname,sage from student where
	sage < (select min(sage) from student where sdept='cs')and
	sdept <> 'cs';
    
select sname from student where 
	exists (select * from sc where sno=Student.sno and cno='1');
    
select sname from student where
	not exists (select * from sc where sno=Student.sno and cno='1');
    
select sname from student where 
	not exists (select * from course where (
			not exists(select * from sc where sno=student.sno and cno = course.cno)
		)
    );
    
select distinct sno from sc as scx where
	not exists (
		select * from sc as scy where 
			scy.sno='201215122' and 
			not exists(
				select * from sc as scz where
					scz.sno = scx.sno and 
                    scz.cno=scy.cno
            )
    );

select * from student where sdept='cs'
union
select * from student where sage < 19;

select sno from sc where cno='1' 
	union 
select sno from sc where cno='2';

-- 例3.66
-- mysql没有INTERSECT，采用内连接
select f.* from student as f 
	inner join student as s
	on f.sno=s.sno and f.sage<=19 and s.sdept='cs';

select f.sno from sc as f inner join sc as s on
	f.sno = s.sno and f.cno='1' && s.cno='2';
	
-- mysql没有except
    
select * from student where sdept='cs' and sage > 19;

-- 派生表
select sno,cno from sc, (select sno,avg(grade) from sc group by sno) as Avg_sc(avg_sno,avg_grade)
	where sc.sno=Avg_sc.avg_sno and sc.grade >= avg_sc.avg_grade;
    
select sname from student, (select sno from sc where cno='1') as sc1
	where student.sno=sc1.sno;
    






