-- 1 人流量>30的地点&人流量
SELECT location_name,COUNT(loc_id) 'visitors'
FROM location,itinerary
WHERE location.id = loc_id 
GROUP BY loc_id
HAVING COUNT(*)>30
ORDER BY visitors DESC,location_name ASC;

-- 2 查询每个隔离地中正在进行隔离的人数，并按数量由多到少排序
SELECT location_name, COUNT(isol_loc_id) 'number'
FROM isolation_record,isolation_location
WHERE isolation_location.id = isol_loc_id AND state = 1
GROUP BY isol_loc_id
ORDER BY number DESC, location_name ASC;

-- 3 查询行程表中所有属于同一个人的接续行程信息
SELECT person.id,fullname,telephone,a.e_time 'reclosing_time',a.loc_id 'loc1',c.location_name 'address1',b.loc_id 'loc2',d.location_name 'address2'
FROM person,itinerary a,itinerary b,location c,location d
WHERE a.e_time = b.s_time AND a.p_id = b.p_id AND a.p_id = person.id 
	AND a.loc_id = c.id AND b.loc_id = d.id AND person.id > 30 
ORDER BY person.id,reclosing_time;

-- 4 查询充珉瑶和贾涵山的行程情况。查询结果包括：姓名、电话、到过什么地方（地名），何时到达，何时离开 。 列名原样列出即可，不必用别名。查询结果依人员编号降序排序。同一人员行程依行程开始时间顺序排列。
SELECT fullname,telephone,location_name,s_time,e_time
FROM person LEFT JOIN
(SELECT location_name, p_id, s_time, e_time
 FROM location, itinerary
 WHERE loc_id = location.id
 ) a
ON (person.id = a.p_id)
WHERE (person.fullname = '充珉瑶' OR person.fullname = '贾涵山')
ORDER BY person.id DESC, s_time;

-- 5 查询地名中带有‘店’字的地点编号和名称。查询结果按地点编号排序。
SELECT id,location_name
FROM location
WHERE location_name LIKE '%店%'
ORDER BY id;

***
-- 6 新发现一位确诊者，已知他在2021.2.2日20:05:40到21:25:40之间在“活动中心”逗留，凡在此间在同一地点逗留过的，视为接触者，请查询接触者的姓名和电话。查询结果按姓名排序。
SELECT fullname
FROM person, itinerary, location
WHERE person.id = itinerary.p_id AND itinerary.loc_id = location.id
    AND location_name = '活动中心'
    AND (itinerary.s_time < '2021-02-02 21:25:40')
	AND (itinerary.e_time > '2021-02-02 20:05:40')
ORDER BY fullname;

-- 7 查询仍在使用的隔离点名称。注意，隔离记录里如果只有隔离结束或确诊转院的记录，表明该隔离点已暂时停用，只要还有一个人在此处隔离，表明该隔离点仍在使用。查询结果按隔离点编号排序。
SELECT location_name 
FROM isolation_location, isolation_record
WHERE isol_loc_id = isolation_location.id
	AND isolation_record.state = 1
GROUP BY isol_loc_id
ORDER BY isol_loc_id;

-- 8 (带exists关键字)查询前30位有出行记录的人员姓名和电话。查询结果按照人员编号排序。
SELECT fullname,telephone
FROM person
WHERE EXISTS
    ( SELECT p_id
		FROM itinerary
		WHERE p_id = person.id
		ORDER BY p_id)
LIMIT 30;

-- 9 写一条带NOT EXISTS 子查询的SQL语句实现下述查询要求：查询人员表中没有去过地点“Today便利店”的人数。请给统计出的人数命名为number。
SELECT COUNT(id) number
FROM person
WHERE NOT EXISTS
 (SELECT *
  FROM itinerary,location
  WHERE p_id = person.id AND itinerary.loc_id = location.id AND location_name = 'Today便利店');

-- 10 (带not exists)查询人员表去过所有地点的人员姓名。查询结果依人员姓名顺序排序。
--    含义转换->不存在这样的地点y,人员x没有去过
SELECT fullname
FROM person
WHERE NOT EXISTS
(SELECT *
 FROM location
 WHERE NOT EXISTS
 (SELECT *
 FROM itinerary
 WHERE location.id = loc_id AND person.id = p_id
 ))
ORDER BY fullname;

-- 11 写一条SQL语句创建能反映所有隔离点现状的视图：isolation_location_status的创建
CREATE VIEW isolation_location_status (id, location_name, capacity, occupied)
AS
SELECT isolation_location.id,location_name,capacity,COUNT(case when state = 1 then 1 else null end) 'occupied'
FROM isolation_location LEFT JOIN
(SELECT *
 FROM isolation_record
 WHERE state = 1) a
ON (isolation_location.id = a.isol_loc_id)
GROUP BY isolation_location.id;

-- 12 从视图isolation_location_status中查询各隔离点的剩余空房间的数目。
SELECT location_name, capacity-occupied 'available_rooms'
FROM isolation_location_status
ORDER BY id;

-- 13 查询靳宛儿接触者的姓名和电话。与靳宛儿在同一地点逗留时间有交集的均为其接触者。查询结果按照人员姓名排序。
SELECT fullname, telephone
FROM itinerary a, person 
WHERE person.id = a.p_id
	AND a.loc_id IN (SELECT loc_id FROM itinerary b, person c WHERE c.fullname = '靳宛儿' AND c.id = b.p_id)
	AND a.s_time < (SELECT e_time FROM person p, itinerary i WHERE p.fullname = '靳宛儿' AND a.loc_id=i.loc_id AND i.p_id = p.id)
	AND a.e_time > (SELECT s_time FROM person p, itinerary i WHERE p.fullname = '靳宛儿' AND a.loc_id=i.loc_id AND i.p_id = p.id)
	AND person.fullname!='靳宛儿'
ORDER BY fullname;

-- 14 依据密切接触表的内容查询每个地点的密切接触者的数量，列出内容包括：地点名称，密接者人数。
SELECT location_name, COUNT(*) 'close_contact_number'
FROM close_contact, location
WHERE location.id = loc_id
GROUP BY loc_id
ORDER BY close_contact_number DESC, location_name;

-- 15 查询感染人数最多的人员编号，姓名，和被其感染的人数。
SELECT case_p_id, fullname, COUNT(*) 'infected_number'
FROM close_contact, person
WHERE person.id = case_p_id
GROUP BY case_p_id
ORDER BY infected_number DESC
LIMIT 1;

-- 16 查询2021-02-02 10:00:00到14:00:00期间，行程记录最频繁的三个人的姓名及行程记录条数。
SELECT fullname, COUNT(*) 'record_number'
FROM itinerary,person
WHERE p_id = person.id
	AND ((s_time >= '2021-02-02 10:00:00' AND s_time < '2021-02-02 14:00:00')
	OR (e_time > '2021-02-02 10:00:00' AND e_time <= '2021-02-02 14:00:00'))
GROUP BY p_id
ORDER BY record_number DESC, fullname ASC
LIMIT 3;

-- 17 从隔离点中，查询房间数(capacity)居第二多的隔离点名称及其房间数。
SELECT location_name, capacity
FROM isolation_location
WHERE capacity IN
(SELECT MAX(capacity)
 FROM isolation_location
 WHERE capacity NOT IN 
 (SELECT MAX(capacity)
	FROM isolation_location)
);
