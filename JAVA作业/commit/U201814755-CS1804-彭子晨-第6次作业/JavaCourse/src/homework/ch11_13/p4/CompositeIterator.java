package homework.ch11_13.p4;

import java.util.ArrayList;
import java.util.List;

public class CompositeIterator implements Iterator {
    protected List<Iterator> iterators;

    public CompositeIterator(Iterator iterator){
        this.iterators = new ArrayList<Iterator>();
        if(iterator.hasNext()){
            this.iterators.add(iterator);
        }
    }

    public boolean hasNext(){
        return !(iterators.isEmpty());
    }

    public Component next(){
        if(this.hasNext()){
            Iterator iterator = this.iterators.get(0);
            if(iterator.hasNext()){
                Component c = iterator.next();
                if(c instanceof CompositeComponent && ((CompositeComponent) c).childs.hasNext()){
                    this.iterators.add(((CompositeComponent) c).childs);
                }
                if(!iterator.hasNext()){
                    this.iterators.remove(iterator);
                }
                return c;
            }
        }
        return null;
    }
}
