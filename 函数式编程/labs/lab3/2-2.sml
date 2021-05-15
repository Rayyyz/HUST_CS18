fun mapList'(func) = 
    let
        fun f([]) = []
            |f(x::L) = (func x)::f(L)
    in
        f
    end

fun double(x) = 2*x;
fun square(x) = x*x;
fun pow(x,0) = 1
    |pow(x,n) = x*pow(x,n-1);


val a1 = (fn x=>double(x))
val f1 = mapList'(a1) [2,3,4,5];

val a2 = (fn x=>square(x))
val f2 = mapList'(a2) [2,3,4,5];

val a3 = (fn x=>pow(x,3))
val f3 = mapList'(a3) [2,3,4,5];
