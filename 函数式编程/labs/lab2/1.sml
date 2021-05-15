fun reverse [] = []
    | reverse [x] = [x]
    | reverse (x::L) = reverse(L)@[x]

val ans1 = reverse [1,2,3,4,5,6,7];

(*下面错惹，不能改变reverse的参数形式*)
fun reverse' ([],y) = y
    | reverse' (x::L, y) = reverse' (L,x::y)

val ans2 = reverse' ([2,3,4,5,6,7,8],[]);