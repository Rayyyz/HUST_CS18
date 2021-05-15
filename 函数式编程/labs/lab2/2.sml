fun interleave ([],[]) = []
    |interleave(L1,[])  = L1
    |interleave([],L2)  = L2
    |interleave(x::L1,y::L2) = x::y::interleave(L1,L2)

val ans1 = interleave([2],[4]);
val ans2 = interleave([2,3],[4,5]);
val ans3 = interleave([2,3],[4,5,6,7,8,9]);
val ans4 = interleave([2,3],[]);
