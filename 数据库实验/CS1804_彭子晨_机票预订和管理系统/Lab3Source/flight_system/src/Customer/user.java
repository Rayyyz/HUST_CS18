package Customer;

import Mysql.DBHelper;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class user extends JFrame {
	
    String account;
    
    public user(String account) {
        super("Ô¤¶©/ÍË¶©");
        this.account = account;
        JMenuBar menuBar = new JMenuBar();
        menuBar.setBackground(new Color(0xFAFAFA));
        JMenu menu1 = new JMenu("²Ù×÷");
        Container container = getContentPane();
        FlowLayout layout = new FlowLayout();
        container.setLayout(layout);
        setLocationRelativeTo(null);

        //Ìí¼Ó²Ëµ¥À¸
        JMenuItem item11 = new JMenuItem("Ô¤¶©»úÆ±");
        JMenuItem item12 = new JMenuItem("ÍË¶©»úÆ±");

        menu1.add(item11);
        menu1.addSeparator();
        menu1.add(item12);
        menuBar.add(menu1);
        setJMenuBar(menuBar);

        plane_message_layout p1 = new plane_message_layout(account);

        container.add(p1);

        item11.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	plane_message_layout p1 = new plane_message_layout(account);
                container.removeAll();
                container.add(p1);
                p1.updateUI();
            }
        });
        item12.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                unsubscribe l2 = new unsubscribe(account);
                container.removeAll();
                container.add(l2);
                l2.updateUI();
            }
        });

        setVisible(true);
        setSize(1000, 600);
        setLocation();
        setBackground(new Color(0xEFFBFB));
    }


    public void setLocation(){
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight(); int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);
    }
}
