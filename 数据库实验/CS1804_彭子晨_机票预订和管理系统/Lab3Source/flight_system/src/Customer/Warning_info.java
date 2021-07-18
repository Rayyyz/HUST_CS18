package Customer;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

class Warning_info extends JFrame {
    public JButton OK;
    public Warning_info(String string){
        super("notice");
        Container container = getContentPane();
        FlowLayout layout = new FlowLayout();
        layout.setVgap(10);
        container.setLayout(layout);

        JLabel jLabel = new JLabel(string);
        OK = new JButton("OK");

        Box box = Box.createVerticalBox();
        box.add(new JLabel("   "));
        box.add(jLabel);
        box.add(new JLabel("   "));
        box.add(OK);

        container.add(box);

        setVisible(true);
        setSize(300,150);
        setResizable(false);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight(); int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);

        OK.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setVisible(false);
            }
        });
    }
}

