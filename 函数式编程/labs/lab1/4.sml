fun mult' ( [ ], a) = a
	| mult' (x ::L, a) = mult'(L, x * a);

fun Mult' ( [ ], a) = a
    | Mult' (r ::R, a) = mult'(r, a) * Mult'(R, 1);

val a = [[2,3],[4,5]];
val b = 10;
val res = Mult'(a,b);