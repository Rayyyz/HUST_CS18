3 + 4;
3.0 + 2.0; (*类型不同,3>3.0*)
it + 6.0;  (*类型不同,6>6.0*)
val it = "hello";
it ^ " world";  (*连接符号+>^*)
it ^ "5";     (*类型不同,+>^,5>"5"*)
val a = 5;
a = 6;
a + 8; 
val twice = (fn x => 2 * x);
twice a;
let val x = 1 in x end; (*let后面加上val*)
(*foo;(*foo未绑定*)*)
(*[1, "foo"];整数和string类型不能在一个list中出现*)
