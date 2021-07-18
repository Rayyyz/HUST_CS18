package Customer;

import Mysql.DBHelper;

import javax.swing.*;
import java.awt.*;

public class order_layout extends JFrame {
    protected Container container;

    protected DBHelper dbHelper = new DBHelper();

    protected JTextField name_text;
    protected JTextField id_text;
    protected JTextField seat_text;

    protected JButton OK;

    public order_layout(int price,String type,String date,String place1,String plce2)
    {
        container = getContentPane();
        container.setLayout(new FlowLayout());

        JPanel name = new JPanel();
        JPanel id = new JPanel();
        JPanel sex = new JPanel();

        name_text = new JTextField(19);
        id_text = new JTextField(19);
        seat_text = new JTextField(19) ;

        name.add(new JLabel("��     ����"));
        name.add(name_text);
        id.add(new JLabel("֤ �� �ţ�"));
        id.add(id_text);
        sex.add(new JLabel("�� λ �ţ�"));
        sex.add(seat_text);
        OK = new JButton("�� �� �� ��");

        JLabel jLabel1 = new JLabel("��Ԥ������"+date+"    ");
        JLabel jLabel2 = new JLabel("��"+place1+"��"+plce2+"�ĺ���");
        JLabel jLabel3 = new JLabel("�۸�Ϊ"+price);
        JLabel jLabel4 = new JLabel("����Ϊ"+type);
        JLabel jLabel = new JLabel("��ȷ�Ϻ��ٸ���");
        jLabel.setForeground(new Color(0xFFDC34));

        container.add(jLabel1);
        container.add(jLabel2);
        container.add(jLabel3);
        container.add(jLabel4);
        container.add(jLabel);

        container.add(id);
        container.add(name);
        container.add(sex);
        container.add(OK);
        

        setSize(300,300);
        setVisible(true);
        setResizable(false);

        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight();int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);
    }
}
