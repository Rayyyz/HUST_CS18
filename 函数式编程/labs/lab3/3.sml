fun findOdd([]) = NONE
    |findOdd(x::L) = 
        if x mod 2 = 0 
        then findOdd(L) 
        else SOME x;


val a1 = [2,4,6,8];
val ans1 = findOdd(a1);

val a2 = [0,2,3,7,8];
val ans2 = findOdd(a2);