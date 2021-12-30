DROP DATABASE IF EXISTS HOMEWORK;
CREATE DATABASE HOMEWORK;
USE HOMEWORK;

DROP TABLE IF EXISTS Workers;
-- 职工表
CREATE TABLE Workers (
    WNo char(20),               -- 工号 
    WName char(20) UNIQUE,      -- 姓名
    Age smallint,               -- 年龄
    Job char(20),               -- 职务
    Sal numeric,                -- 工资
    DeptNo smallint UNIQUE,     -- 部门号
    PRIMARY KEY (WNo)  
);


DROP TABLE IF EXISTS Dept;
CREATE TABLE Dept (
    Dno smallint,               -- 部门号
    Dname char (20) NOT NULL,   -- 部门名称
    Manager char (20),          -- 经理
    Addr char (20),             -- 地址
    Phone char (11),            -- 手机
    PRIMARY KEY (Dno)
);


drop user if exists '王明'@'localhost';
drop user if exists '李勇'@'localhost';
drop user if exists '刘星'@'localhost';
drop user if exists '张新'@'localhost';
drop user if exists '周平'@'localhost';
drop user if exists '杨兰'@'localhost';
create user '王明'@'localhost' identified by 'wangming';
create user '李勇'@'localhost' identified by 'liyong';
create user '刘星'@'localhost' identified by 'liuxing';
create user '张新'@'localhost' identified by 'zhangxin';
create user '周平'@'localhost' identified by 'zhouping';
create user '杨兰'@'localhost' identified by 'yanglan';

-- (1) 用户王明对两个表有select权限
GRANT SELECT ON TABLE Workers TO 王明@localhost;
GRANT SELECT ON TABLE Dept TO 王明@localhost;
-- (2) 用户李勇对两个表有insert和delete权限
GRANT INSERT, DELETE ON TABLE Workers TO 李勇@localhost;
GRANT INSERT, DELETE ON TABLE Dept TO '李勇'@'localhost';
-- (3) 每个职工只对自己有select的权限
-- 创建视图
drop view if exists worker;
create view worker as select * from Workers where concat(WName,'@localhost') = user();
GRANT SELECT ON homework.worker TO 王明@localhost, 李勇@localhost,刘星@localhost,张新@localhost,周平@localhost,杨兰@localhost;

-- (4) 用户刘星对职工表有select权限，对工资字段具有更新权限
GRANT SELECT ON Workers TO 刘星@localhost;
GRANT UPDATE(Sal) ON Workers TO 刘星@localhost;

-- (5) 用户张新具有修改这两个表的结构的权限
GRANT ALTER ON Workers TO 张新@localhost;
GRANT ALTER ON Dept TO 张新@localhost;

-- (6) 用户周平具有对两个表的所有权限，并具有给其他用户授权的权限
GRANT ALL ON TABLE Workers TO 周平@localhost with grant option;
GRANT ALL ON TABLE Dept TO 周平@localhost with grant option;
-- (7) 用户杨兰具有从每个部门职工中select最高工资、最低工资、平均工资的权限，她不能查看每个人的工资
-- 创建部门工资视图
drop view if exists deptSal;
create view deptSal as select AVG(Sal) as avsSal, MAX(Sal) as maxSal,MIN(Sal) as minSal from Workers group by DeptNo;
GRANT SELECT on homework.deptsal TO 杨兰@localhost;


-- 回收权限
-- (1) 回收用户王明对两个表的select权限
REVOKE SELECT ON TABLE Workers FROM 王明@localhost;
REVOKE SELECT ON TABLE Dept FROM 王明@localhost;
-- (2) 回收用户李勇对两个表的insert和delete权限
REVOKE INSERT, DELETE ON TABLE Workers FROM 李勇@localhost;
REVOKE INSERT, DELETE ON TABLE Dept FROM 李勇@localhost;

-- (3) 回收每个职工对自己的select的权限
REVOKE SELECT ON homework.worker FROM 王明@localhost, 李勇@localhost,刘星@localhost,张新@localhost,周平@localhost,杨兰@localhost;

-- (4) 回收刘星对职工表的select权限，对工资字段的更新权限
REVOKE SELECT, UPDATE(Sal) ON TABLE Workers FROM 刘星@localhost;

-- (5) 回收用户张新的修改这两个表的结构的权限
REVOKE ALTER ON TABLE Workers FROM 张新@localhost;
REVOKE ALTER ON TABLE Dept FROM 张新@localhost;
-- (6) 回收用户周平具有的对两个表的所有权限，以及给其他用户授权的权限
REVOKE ALL ON TABLE Workers FROM 周平@localhost;
REVOKE ALL ON TABLE Dept FROM 周平@localhost;

-- (7) 祸首用户杨兰的从每个部门职工中select最高工资、最低工资、平均工资的权限
REVOKE SELECT on homework.deptsal FROM 杨兰@localhost;













