datatype tree = Empty | Node of tree*int*tree;

(*获得数组长度*)
fun length [] = 0
    |length (x::L) = 1+length(L)

(*获得L数组中l-r的子数组，不包括r*)
fun get ([],l,r) = []
    |get(_,_,0) = []
    |get (x::L,l,r) =
    if(l=0) then
        x::get(L,0,r-1)
    else get(L,l-1,r-1)
    
(*获得L数组中第n个int值*)
fun indexN([],_) = 0
    |indexN(x::L,0)= x
    |indexN(x::L,n)= indexN(L,n-1)

(*生成tree*)
fun listToTree [] = Empty
    |listToTree[x] = Node(Empty,x,Empty)
    |listToTree(L)= 
    let
        val index = length(L) div 2
        val mid = indexN(L,index)
        val left = get(L,0,index)
        val right = get(L,index+1,length(L))
    in
        Node(listToTree(left),mid,listToTree(right))
    end

val l1 = [1,2,3,4,5,6,7,8,9];
val l2 = [10,11,12];
val listtotree1 = listToTree(l1);
val listtotree2 = listToTree(l2);
