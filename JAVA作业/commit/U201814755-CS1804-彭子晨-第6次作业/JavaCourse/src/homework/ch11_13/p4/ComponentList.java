package homework.ch11_13.p4;

import java.util.ArrayList;

public class ComponentList extends ArrayList<Component> implements Iterator {
    private int position;

    public ComponentList(){
        position = 0;
    }

    public boolean hasNext(){
        return position < this.size();
    }

    public Component next(){
        if(this.hasNext())
            return this.get(position++);
        else return null;
    }
}
