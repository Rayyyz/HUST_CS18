package homework.ch11_13.p4;

public class CompositeComponent extends Component{
    protected ComponentList childs;

    CompositeComponent(){
        super();
        childs = new ComponentList();
    }
    CompositeComponent(int id,String name,double price){
        super(id,name,price);
        childs = new ComponentList();
    }

    @Override
    public void add(Component component) throws UnsupportedOperationException {
        if(!childs.contains(component)){
            childs.add(component);
        }
    }

    @Override
    public void remove(Component component) throws UnsupportedOperationException {
            childs.remove(component);
    }

    @Override
    double calcPrice() {
        double allPrice = 0;
        for(Component c:childs){
            allPrice += c.calcPrice();
        }
        return allPrice;
    }

    @Override
    public Iterator iterator(){
        return new CompositeIterator(this.childs);
    }

    @Override
    public String toString() {
        String str = super.toString();
        str = str.concat("\nsub-components of "+this.getName()+":\n");
        for(Component c:childs){
            str = str.concat(c.toString()+"\n");
        }
        return str;
    }
}
