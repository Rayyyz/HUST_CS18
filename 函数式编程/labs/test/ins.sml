datatype tree = Empty | Node of tree*int*tree;

fun Ins (x, Empty) = Node(Empty, x, Empty)
    | Ins (x, Node(t1, y, t2)) =
    	case compare(x, y) of
    	    GREATER => Node(t1, y, Ins(x, t2))
    	    | 	_ 	=> Node(Ins(x, t1), y, t2);
