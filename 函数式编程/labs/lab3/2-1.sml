fun mapList(func, []) = []
    |mapList(func, x::L) = (func x)::mapList(func,L);

fun double(x) = 2*x;
fun square(x) = x*x;
fun pow(x,0) = 1
    |pow(x,n) = x*pow(x,n-1);


val a1 = (fn x=>double(x))
val ans1 = mapList(a1, [2,3,4,5]);

val a2 = (fn x=>square(x))
val ans2 = mapList(a2, [2,3,4,5]);

val a3 = (fn x=>pow(x,3))
val ans3 = mapList(a3, [2,3,4,5]);