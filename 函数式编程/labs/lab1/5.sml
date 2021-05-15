fun double (0 : int) : int = 0
    | double n =  2 + double (n - 1) ;
fun square (0 : int) : int = 0
    | square(1 : int) = 1
    | square n = square(n - 1) - 1 + double (n) ;


val a = 8;
val res = square a;