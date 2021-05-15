fun zip ([] :string list, _ :int list) : (string * int) list  = []
    | zip( _ : string list, [] :int list) : (string * int) list = []
    | zip(s :: strList, i :: intList) = (s,i)::zip(strList,intList)

val res1 = zip([],[2,3]);
val res2 = zip(["aa","bbb","cc"],[2,3]);



