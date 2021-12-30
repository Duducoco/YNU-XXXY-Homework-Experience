USE homework;
SET FOREIGN_KEY_CHECKS = 0;
SET FOREIGN_KEY_CHECKS = 1;

DROP TABLE IF EXISTS Workers;
CREATE TABLE Workers (
    WNo char(20),               -- 工号 
    WName char(20) NOT NULL,    -- 姓名
    Age smallint,               -- 年龄
    CONSTRAINT CA CHECK(Age <= 60),
    Job char(20),               -- 职务
    Sal numeric,                -- 工资
    DeptNo smallint UNIQUE,     -- 部门号
    PRIMARY KEY (WNo)   
);
-- DROP INDEX IDX_WNo ON Workers;
-- CREATE UNIQUE INDEX IDX_Wno ON Workers (Wno);   --建立索引
DROP INDEX IDX_WName ON Workers;
CREATE UNIQUE INDEX IDX_WName on Workers (Wname);


DROP TABLE IF EXISTS Dept;
CREATE TABLE Dept (
    Dno smallint,               -- 部门号
    Dname char (20) NOT NULL,   -- 部门名称
    Manager char (20) not null, -- 经理名
    Phone char (11),            -- 电话
    PRIMARY KEY (Dno)
);

-- DROP INDEX IDX_Dept ON Dept;
-- CREATE UNIQUE INDEX IDX_Dept ON Dept (Dno);     --建立索引
DROP INDEX IDX_Man on Dept;
CREATE UNIQUE INDEX IDX_Man ON Dept (Manager);     --建立索引

-- 添加外键 部门号来自Dept表中的部门号
alter table Workers add CONSTRAINT FK_DNO foreign key(DeptNo) REFERENCES Dept(Dno);

-- 添加外键 经理名来自员工名字
alter table Dept add CONSTRAINT FK_Man foreign key(Manager) REFERENCES Workers(Wname);


INSERT INTO workers values (1, '王明',23,'工作1',3000,1);
INSERT INTO workers values (2, '李勇',24,'工作2',3230,2);
INSERT INTO workers values (3, '刘星',25,'工作3',4300,3);
INSERT INTO workers values (4, '张新',26,'工作4',4500,4);
INSERT INTO workers values (5, '周平',27,'工作5',4600,5);
INSERT INTO workers values (6, '杨兰',29,'工作6',3498,6);


INSERT INTO dept VALUES (1,'部门1','王明','123123123');

INSERT INTO dept VALUES (2,'部门2','李勇','789789678');

INSERT INTO dept VALUES (3,'部门3','刘星','2345345354');

INSERT INTO dept VALUES (4,'部门4','张新','567567567');

INSERT INTO dept VALUES (5,'部门5','周平','234234234');

INSERT INTO dept VALUES (6,'部门6','杨兰','345345235');

select * from workers;

INSERT INTO dept VALUES (7,'部门7','李四','234453423');
DELETE FROM DEPT WHERE DNO=7;


INSERT INTO workers values (7, '张三',61,'工作6',3498,6);