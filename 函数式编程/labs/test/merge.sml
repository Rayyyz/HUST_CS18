fun Merge (Empty, t2) = t2
    | Merge (Node(l1,x,r1), t2) =
        let
    		val (l2, r2) = SplitAt(x, t2)
        in
			Node(Merge(l1, l2), x, Merge(r1, r2))
        end
