package homework.ch11_13.p4;

import java.util.Iterator;

public class ComponentFactory {
    public ComponentFactory(){}
    public static Component create(){
        int id = 0;
        //创建计算对象
        Component computer = new CompositeComponent(id++,"Think Pad",0.0);

        //创建键盘对象
        Component keyboard = new AtomicComponent(id++,"Keyboard",20.0);
        //创建鼠标对象
        Component mouse = new AtomicComponent(id++,"Mouse",20.0);
        //创建显示器对象
        Component monitor = new AtomicComponent(id++,"Monitor",1000.0);
        computer.add(keyboard);
        computer.add(mouse);
        computer.add(monitor);

        //创建主机对象
        Component mainFrame = new CompositeComponent(id++,"Main frame",0.0);
        //创建硬盘对象
        Component hardDisk = new AtomicComponent(id++,"Hard disk",1000);
        //创建电源对象
        Component powerSupplier = new AtomicComponent(id++,"Power supplier",500);
        mainFrame.add(hardDisk);
        mainFrame.add(powerSupplier);

        //创建主板对象
        Component mainBoard = new CompositeComponent(id++,"Main board",0.0);
        //创建CPU对象
        Component cpu = new AtomicComponent(id++,"CPU",1500.0);
        //创建显卡对象
        Component videoCard = new AtomicComponent(id++,"Video card",900);
        //创建网卡对象
        Component networkCard = new AtomicComponent(id++,"Network card",100);
        mainBoard.add(cpu);
        mainBoard.add(videoCard);
        mainBoard.add(networkCard);

        mainFrame.add(mainBoard);
        computer.add(mainFrame);

        return computer;
    }
}
