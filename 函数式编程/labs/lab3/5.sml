datatype tree = Empty|Node of tree*int*tree;

fun value (Empty) = 999999
    |value(Node(left,x,right)) = x;

fun min (x,y) = if(x<y) then x else y;

fun change (Empty, y) = Node(Empty,y,Empty)
    |change(Node(left,x,right), y) = Node(left,y,right);

(* when given two trees, returns a value of type order, based on which tree has a larger
value at the root node *) 
fun treecompare (Empty,t2) = LESS
    |treecompare(t1,Empty) = GREATER
    |treecompare(t1,t2) = case Int.compare(value(t1),value(t2)) of
        GREATER => GREATER
        |EQUAL => EQUAL
        |LESS => LESS;

(* REQUIRES the subtrees of t are both minheaps
* ENSURES swapDown(t) = if t is Empty or all of t’s immediate children are empty then
* just return t, otherwise returns a minheap which contains exactly the elements in t. *)
fun SwapDown(Empty) = Empty
    |SwapDown(Node(Empty,x,Empty)) = Node(Empty,x,Empty)
    |SwapDown(Node(left,x,right)) = 
    let
        val v1 = value(left)
        val v2 = value(right)
        val v = min(v1,v2)
    in
        if(x<v) then Node(left,x,right)
        else if(v=v1) then Node(SwapDown(change(left,x)),v,right)
        else Node(left,v,SwapDown(change(right,x)))
    end
    
(* given an arbitrary tree t, evaluates to a minheap with exactly the elements of t.  *)
fun heapify(Empty) = Empty
    |heapify(Node(left,x,right)) = SwapDown(Node(heapify(left),x,heapify(right)));


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

(**)
val t1 = listToTree([1,2,3,4,5,6]);
val t2 = listToTree([4,5,6,7,8]);
val t3 = listToTree([4,5,9,6,1]);
val a = "";
val h1 = heapify(t1);
val h2 = heapify(t2);
val h3 = heapify(t3);

val cp = treecompare(h1,h2);
