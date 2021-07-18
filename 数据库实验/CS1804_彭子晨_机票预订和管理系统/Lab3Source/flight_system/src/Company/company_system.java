package Company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class company_system extends JFrame {
    JMenuBar jMenuBar = new JMenuBar();
    JMenu menu1 = new JMenu("增加航班");
    JMenuItem item1 = new JMenuItem("增加航班");

    public company_system(){
        jMenuBar.setBackground(new Color(0xFAFAFA));
        Container container = getContentPane();
        setJMenuBar(jMenuBar);
        jMenuBar.add(menu1);
        menu1.add(item1);

        addflight l2 = new addflight();
        container.add(l2);

        item1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                container.removeAll();
                container.add(l2);
                l2.updateUI();
            }
        });

        setVisible(true);
        setSize(715,550);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight();int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);
        setBackground(new Color(0xEFFBFB));
    }

    public static void main(String args[]){
        company_system system = new company_system();
        system.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
