package homework.ch11_13.p4;

abstract public class Component {
    protected int id;
    protected String name;
    protected double price;

    Component(){
        this.id = 0;
        this.name = "";
        this.price = 0;
    }
    Component(int id,String name,double price){
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return this.calcPrice();
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public abstract void add(Component component) throws UnsupportedOperationException;

    public abstract void remove(Component component) throws UnsupportedOperationException;

    abstract double calcPrice();

    public abstract Iterator iterator();


    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Component){
            return this.id == ((Component) obj).id
                    && this.name.equals(((Component) obj).name)
                    && this.price==((Component) obj).price;
        }
        return false;
    }

    @Override
    public String toString() {
        return "id: "+this.id+", name: "+this.name+", price: "+this.price;
    }
}
