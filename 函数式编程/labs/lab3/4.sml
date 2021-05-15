datatype 'a tree = Empty|Node of 'a tree * 'a * 'a tree;

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

(*将树中满足条件P(‘a -> bool)的节点封装成option类型保留,否则替换成NONE。*)
fun treeFilter(_, Empty) = Empty
    |treeFilter(func,Node(left,x,right)) =
        if func x = true
        then Node(treeFilter(func,left),SOME(x),treeFilter(func,right))
        else Node(treeFilter(func,left),NONE  ,treeFilter(func,right));

(*设置条件，可以被3整除*)
fun mod3(x) = (x mod 3 = 0);


(*test*)
val l1 = [2,3,4,5,6];
val t1 = listToTree(l1);
val ans1 = treeFilter(mod3,t1);

val l2 = [11,12,13];
val t2 = listToTree(l2);
val ans2 = treeFilter(mod3,t2);