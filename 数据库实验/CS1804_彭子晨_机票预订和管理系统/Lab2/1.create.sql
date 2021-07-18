create database if not exists covid19mon;
use covid19mon;

-- 请在以下适当的空白位置填写SQL语句完成任务书的要求。空白位置不够的话，可以通过回车换行增加。
-- 表1 人员表(person)
create table person(
id INT,
fullname CHAR(20) NOT NULL,
telephone CHAR(11) NOT NULL,
CONSTRAINT pk_person PRIMARY KEY(id));
-- 表2 地点表(location)
create table location(
id int,
location_name char(20) not null,
constraint pk_location primary key(id));
-- 表3 行程表（itinerary）
create table itinerary(
id int,
p_id int,
loc_id int,
s_time datetime,
e_time datetime,
constraint pk_itinerary primary key(id),
constraint fk_itinerary_pid foreign key(p_id)
references person(id),
constraint fk_itinerary_lid foreign key(loc_id)
references location(id));
-- 表4 诊断表（diagnose_record）
create table diagnose_record(
id int,
p_id int,
diagnose_date datetime,
result int,
constraint pk_diagnose_record primary key(id),
constraint fk_diagnose_pid foreign key(p_id)
references person(id));
-- 表5 密切接触者表（close_contact）
create table close_contact(
id INT,
p_id INT,
contact_date datetime,
loc_id INT,
case_p_id INT,
CONSTRAINT pk_close_contact PRIMARY KEY(id),
CONSTRAINT fk_contact_pid FOREIGN KEY(p_id)
REFERENCES person(id),
CONSTRAINT fk_contact_lid FOREIGN KEY(loc_id)
REFERENCES location(id),
CONSTRAINT fk_contact_caseid FOREIGN KEY(case_p_id)
REFERENCES person(id));
-- 表6 隔离地点表（isolation_location）
create table isolation_location(
id INT,
location_name CHAR(20),
capacity INT,
CONSTRAINT pk_isolation_loc PRIMARY KEY(id));
-- 表7 隔离表（isolation_record）
create table isolation_record(
id INT,
p_id INT,
s_date datetime,
e_date datetime,
isol_loc_id INT,
state INT,
CONSTRAINT pk_isolation PRIMARY KEY(id),
CONSTRAINT fk_isolation_pid FOREIGN KEY(p_id)
REFERENCES person(id),
CONSTRAINT fk_isolation_lid FOREIGN KEY(isol_loc_id)
REFERENCES isolation_location(id));
-- 代码结束
/* *********************************************************** */
