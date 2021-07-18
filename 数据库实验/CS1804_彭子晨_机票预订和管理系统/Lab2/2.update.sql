-- 插入三条数据
INSERT INTO person(id,fullname,telephone)
VALUES(1,"张小敏","13907110001"),(2,"李大锤","18907110002"),(3,"孙二娘","13307100003");

-- 删除2
DELETE FROM person WHERE id = 2

-- 更改电话
UPDATE person SET telephone = "13607176668" WHERE id = 1

-- 触发器
-- SQL Server一次可以定义多个事件(insert,delete,upate三者的任意组合)驱动的触发器，但MySQL一次只能定义一个事件(insert,delte,update三选一)驱动的触发器。这意味着，如果你希望多个事件均触发完整性检查，你得创建多个触发器。*/
-- MySQL虽然允许你随时定义触发器，但要求你用“DELIMITER 界符”语句指定触发器定义语句的界符（即结束符)。我们推荐你使用“;;”(即两个连续的分号)作触发器定义语句的界符。请在触发器定义结束后重新指定语句的界符(恢复为单个分号)。*/
DELIMITER ;;
CREATE TRIGGER change_isolation_state_insert AFTER INSERT
ON diagnose_record FOR EACH ROW
BEGIN
IF NEW.result = 1 THEN
UPDATE isolation_record SET state = 3
  WHERE NEW.p_id = p_id;
END IF;
END;;
DELIMITER ;

DELIMITER ;;
CREATE TRIGGER change_isolation_state_update AFTER UPDATE
ON diagnose_record FOR EACH ROW
BEGIN
IF NEW.result = 1 THEN
UPDATE isolation_record SET state = 3
  WHERE NEW.p_id = p_id;
END IF;
END;;
DELIMITER ;


