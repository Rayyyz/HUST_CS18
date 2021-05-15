fun thenAddOne(func , x:int) = func x + 1;

fun double(x) = 2*x;
fun square(x) = x*x;
fun pow(x,0) = 1
    |pow(x,n) = x*pow(x,n-1);


val a1 = (fn x=>double(x))
val ans1 = thenAddOne(a1, 3);

val a2 = (fn x=>square(x))
val ans2 = thenAddOne(a2, 3);

val a3 = (fn x=>pow(x,3))
val ans3 = thenAddOne(a3, 3);
