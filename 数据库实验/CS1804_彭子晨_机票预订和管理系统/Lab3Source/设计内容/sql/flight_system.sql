/**
*
*
*/

-- 表1 航班信息表(flight) 记录航班信息
-- 航班号flight_id，公司名company_name，飞机类型plane_type
-- 出发城市departure_city，到达城市arrival_city
DROP TABLE IF EXISTS flight;
CREATE TABLE flight  (
    flight_id varchar(20) NOT NULL PRIMARY KEY, 
    company_name varchar(20) NOT NULL,
    plane_type varchar(20) NOT NULL,    
    departure_city varchar(20) NOT NULL,
    arrival_city varchar(10) NOT NULL
);


-- 表2 班次信息表(class) 记录班次信息
-- 航班号id，航班名name，起飞时间departure_time，到达时间arrival_time
-- 起飞地点departure_airport，到达地点arrival_airport
-- 座位数a_number,b_number, 票价a_price，b_price
DROP TABLE IF EXISTS classes;
CREATE TABLE classes (
    class_id varchar(20) NOT NULL PRIMARY KEY,
    departure_time datetime NOT NULL,
    departure_airport varchar(20) NOT NULL,
    arrival_time datetime NOT NULL,
    arrival_airport varchar(20) NOT NULL,
    a_number int(11) NOT NULL,
    b_number int(11) NOT NULL,
    a_price int(11) NULL,
    b_price int(11) NULL,
    flight_id varchar(20) NULL,
    constraint classes_flight_fid_fk FOREIGN KEY (flight_id)
      references flight(flight_id)
      on delete cascade on update cascade
);


-- 表3 用户信息表(users)记录用户信息
-- 账号account, 密码password，用户姓名name，性别sex
-- 年龄age，电话tel
DROP TABLE IF EXISTS users;
CREATE TABLE users (
  account varchar(20) NOT NULL PRIMARY KEY,
  password varchar(20) NOT NULL,
  name varchar(20) NOT NULL,
  sex varchar(10) null,
  age int null,
  tel varchar(20) null
);


-- 表4 旅客订票信息表
-- 序号order_id, 身份证号id, 座位号seat, 舱位degree
DROP TABLE IF EXISTS passengers;
CREATE TABLE passengers (
  order_id int NOT NULL PRIMARY KEY,
  name varchar(20) NOT NULL,
  account varchar(20) NOT NULL,
  id varchar(20) NOT NULL,
  order_time datetime NOT NULL,
  seat varchar(5) NOT NULL,
  degree varchar(2) NOT NULL,
  class_id varchar(20) NOT NULL,
  constraint passengers_classes_cid_fk FOREIGN KEY (class_id) 
    references classes(class_id)
    on delete cascade on update cascade,
  constraint passengers_users_account_fk FOREIGN KEY (account)
    references users(account)
    on delete cascade on update cascade
);

