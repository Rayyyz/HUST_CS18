fun oddP (0 : int) : bool = false
  	| oddP 1 = true
  	| oddP n = oddP (n - 2)

val a1 = 99;
val res1 = oddP a1;

val a2 = 100;
val res2 = oddP a2;