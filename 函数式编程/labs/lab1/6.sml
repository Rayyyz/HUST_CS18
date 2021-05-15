fun divisibleByThree(0 : int) : bool = true
    | divisibleByThree 1 = false
    | divisibleByThree 2 = false    
    | divisibleByThree 3 = true
    | divisibleByThree n = if(n<0) then divisibleByThree (n+3) else divisibleByThree (n-3);


val a1 = 2;
val res1 = divisibleByThree(a1);
val a2 = 6;
val res2 = divisibleByThree(a2);
val a3 = ~9;
val res3 = divisibleByThree(a3);
