drop user if exists 'U1'@'localhost';
drop user if exists 'U2'@'localhost';
drop user if exists 'U3'@'localhost';
drop user if exists 'U4'@'localhost';
drop user if exists 'U5'@'localhost';
drop user if exists 'U6'@'localhost';
drop user if exists 'U7'@'localhost';
create user 'U1'@'localhost' identified by 'U1';
create user 'U2'@'localhost' identified by 'U2';
create user 'U3'@'localhost' identified by 'U3';
create user 'U4'@'localhost' identified by 'U4';
create user 'U5'@'localhost' identified by 'U5';
create user 'U6'@'localhost' identified by 'U6';
create user 'U7'@'localhost' identified by 'U7';

use course;


grant select on table student to U1@localhost;
grant all privileges on table student to U2@localhost, U3@localhost;
grant all privileges on table course to U2@localhost, U3@localhost;

grant update(Sno),select on table student to U4@localhost;
grant insert on table sc to U5@localhost with grant option;

-- U5执行
grant insert on table sc to U6@localhost with grant option;

-- U6执行
grant insert on table sc to U7@localhost;


revoke select on table student from U1@localhost;
revoke update(Sno) on table student from U4@localhost;

revoke insert on table sc from U5@localhost; -- 不能使用cascade

create role R1;
grant select, update, insert on table student to R1;
grant R1 to U1@localhost, U2@localhost, U3@localhost;

revoke R1 from U1@localhost;

grant delete on table student to R1;

revoke select on table student from R1;


create view cs_student as select * from student where sdept='cs';		-- 创建视图
grant select on cs_student to U1@localhost;
grant all privileges on cs_student to U2@localhost;



