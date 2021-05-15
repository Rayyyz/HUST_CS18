package homework.ch11_13.p4;

import java.util.ArrayList;
import java.util.List;

public class AtomicComponent extends Component{
    AtomicComponent(){
        super();
    }
    AtomicComponent(int id,String name,double price){
        super(id,name,price);
    }

    @Override
    public void add(Component component) throws UnsupportedOperationException {
        throw new UnsupportedOperationException();
    }

    @Override
    public void remove(Component component) throws UnsupportedOperationException {
        throw new UnsupportedOperationException();
    }

    @Override
    double calcPrice() {
        return this.price;
    }

    @Override
    public Iterator iterator() {
        return new NullIterator();
    }
}
