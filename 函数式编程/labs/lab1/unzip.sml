
fun unzip ([] :(string * int) list) : (string list * int list) = ([],[])
   |unzip ((x,y)::L) = 
   let
      val (L1,L2) = unzip(L)
   in
      (x::L1,y::L2)
   end

val res1 = unzip[];
val res2 = unzip[("aa",1),("bbb",5),("cc",10)];
