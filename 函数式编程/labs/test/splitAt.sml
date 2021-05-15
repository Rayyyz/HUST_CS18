datatype tree = Empty | Node of tree*int*tree;

(* REQUIRES t is a sorted tree 		*)
(* ENSURES SplitAt(y, t) = a pair (t1, t2)
    such that
    	every item in t1 is ≤ y,
        every item in t2 is ≥ y,
    and t1,t2 consist of the items in t *)

fun SplitAt(y, Empty) = (Empty, Empty)    
    | SplitAt(y, Node(t1, x, t2)) =
	    case compare(x, y) of	      
            GREATER => let
                        val (l1, r1) = SplitAt(y, t1) (*左子树查询*)
                       in   (l1, Node(r1, x, t2))
                       end
                | _ => let
                        val (l2, r2) = SplitAt(y, t2) (*右子树查询*)
                       in   (Node(t1, x, l2), r2)
                       end


