package Airport;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class main_system extends JFrame {

    public main_system() {
        super("机场系统");
        JMenuBar menuBar = new JMenuBar();
        menuBar.setBackground(new Color(0xFAFAFA));
        JMenu menu1 = new JMenu("查询");
        JMenu menu2 = new JMenu("班次");
        Container container = getContentPane();
        FlowLayout layout = new FlowLayout();
        container.setLayout(layout);
        setLocationRelativeTo(null);

        //添加菜单栏
        JMenuItem item11 = new JMenuItem("航班信息");
        JMenuItem item12 = new JMenuItem("订单信息");
        JMenuItem item21 = new JMenuItem("安排班次");
        JMenuItem item22 = new JMenuItem("取消班次");

        menu1.add(item11);
        menu1.addSeparator();
        menu1.add(item12);

        menu2.add(item21);
        menu2.addSeparator();
        menu2.add(item22);

        menuBar.add(menu1);
        menuBar.add(menu2);

        setJMenuBar(menuBar);

        research_plane l1 = new research_plane();

        container.add(l1);

        item11.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                research_plane l1 = new research_plane();
                container.removeAll();
                container.add(l1);
                l1.updateUI();
            }
        });
        item12.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                research_book l2 = new research_book();
                container.removeAll();
                container.add(l2);
                l2.updateUI();
            }
        });
        item21.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addFlight l3 = new addFlight();
                container.removeAll();
                container.add(l3);
                l3.updateUI();
            }
        });
        item22.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                deleteFlight l4 = new deleteFlight();
                container.removeAll();
                container.add(l4);
                l4.updateUI();
            }
        });

        setVisible(true);
        setSize(720, 580);
        setLocation();
        setBackground(new Color(0xEFFBFB));
    }

    public  static void  main(String args[]){
        main_system s = new main_system();
        s.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void  setLocation(){
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight(); int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);
    }
}