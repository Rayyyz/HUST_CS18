(*1*)
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

(*2*)
fun mult [ ] = 1
    | mult (x ::L) = x * (mult L);

val a1 = [2,3,4,5];
val res1 = mult a1;

(*3*)
fun Mult [ ] = 1
    | Mult (r :: R) = mult(r) * Mult (R);

val a2 = [[2,3],[4,5]];
val res2 = Mult a2;

(*4*)
fun mult' ( [ ], a) = a
	| mult' (x ::L, a) = mult'(L, x * a);

fun Mult' ( [ ], a) = a
    | Mult' (r ::R, a) = mult'(r, a) * Mult'(R, 1);

val a3 = [[2,3],[4,5]];
val b3 = 10;
val res3 = Mult'(a3,b3);

(*5*)
fun double (0 : int) : int = 0
    | double n =  2 + double (n - 1) ;
fun square (0 : int) : int = 0
    | square(1 : int) = 1
    | square n = square(n - 1) - 1 + double (n) ;

val a4 = 8;
val res4 = square a4;

(*6*)
fun divisibleByThree(0 : int) : bool = false
    | divisibleByThree 1 = false
    | divisibleByThree 2 = false    
    | divisibleByThree 3 = true
    | divisibleByThree n = if(n<0) divisibleByThree (n+3) else divisibleByThree (n-3);

val a5 = 2;
val res5 = divisibleByThree(a5);
val a6 = 6;
val res6 = divisibleByThree(a6);

(*7*)
fun oddP (0 : int) : bool = false
  	| oddP 1 = true
  	| oddP n = oddP (n - 2)

val a7 = 99;
val res7 = oddP a7;

val a8 = 100;
val res8 = oddP a8;
