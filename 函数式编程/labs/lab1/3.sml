fun mult [ ] = 1
    | mult (x ::L) = x * (mult L);

fun Mult [ ] = 1
    | Mult (r :: R) = mult(r) * Mult (R);

val a = [[2,3],[4,5]];
val res = Mult a;
