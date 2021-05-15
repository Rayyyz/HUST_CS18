fun sum [ ] = 0
    | sum (x ::L) = x + (sum L);

val a1 = [2,3,4,5];
val b1 = sum a1;

fun mult [ ] = 1
    | mult (x ::L) = x * (mult L);

val a2 = [2,3,4,5];
val b2 = mult a2;
