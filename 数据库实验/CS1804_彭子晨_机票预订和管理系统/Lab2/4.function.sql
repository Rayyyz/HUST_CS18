-- 1. 用create function语句创建符合以下要求的函数：
-- 依据人员编号计算其到达所有地点的次数(即行程表中的记录数)。
-- 函数名为：Count_Records。函数的参数名可以自己命名
DELIMITER ;;
CREATE FUNCTION Count_Records(tmp_id INT)
RETURNS INT
BEGIN
	RETURN (SELECT COUNT(*) FROM itinerary WHERE p_id = tmp_id);
END;;
DELIMITER ;

-- 利用创建的函数，仅用一条SQL语句查询在行程表中至少有3条行程记录的人员信息，查询结果依人员编号排序
SELECT person.id 'id', fullname, telephone
FROM person, itinerary
WHERE person.id = p_id AND Count_Records(person.id)>=3
GROUP BY person.id
ORDER BY person.id ASC;