package Company;

import com.mysql.cj.protocol.Warning;
import Mysql.DBHelper;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.sql.*;

public class addflight extends JPanel {
    protected JComboBox<String> CN;
    protected JComboBox<String>  PT;
    protected JTextField FI;
    protected JTextField DC;
    protected JTextField AC;

    protected JButton OK;

    protected DBHelper dbHelper = new DBHelper();
    public addflight(){
        Connection connection = dbHelper.getConnection();

        String[] company = {"�й�����","��������","�Ϸ�����","���ﺽ��"};

        String[] type = {"����737-700","����737-800", "���пͳ�A319","���пͳ�A319-100"
        ,"���пͳ�A320","���пͳ�A320-200", "���пͳ�A330-300", "ATR72"};
        CN = new JComboBox<>(company);
        CN.setBackground(Color.white);
        PT = new JComboBox<>(type);
        PT.setBackground(Color.white);
        FI = new JTextField(15);
        DC = new JTextField(15);
        AC = new JTextField(15);

        JPanel CNjpl = new JPanel();
        CNjpl.add(new JLabel("ѡ�񺽿չ�˾��"));
        CNjpl.setBackground(new Color(0xEFFBFB));
        CNjpl.add(CN);
        JPanel PTjpl = new JPanel();
        PTjpl.add(new JLabel("ѡ��ɻ����ͣ�"));
        PTjpl.setBackground(new Color(0xEFFBFB));
        PTjpl.add(PT);
        JPanel FIjpl = new JPanel();
        FIjpl.setBackground(new Color(0xEFFBFB));
        FIjpl.add(new JLabel("����ţ�"));
        FIjpl.add(FI);
        JPanel DCjpl = new JPanel();
        DCjpl.setBackground(new Color(0xEFFBFB));
        DCjpl.add(new JLabel("�������У�"));
        DCjpl.add(DC);
        JPanel ACjpl = new JPanel();
        ACjpl.setBackground(new Color(0xEFFBFB));
        ACjpl.add(new JLabel("������У�"));
        ACjpl.add(AC);

        FI.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {

            }

            @Override
            public void focusLost(FocusEvent e) {
                try{
                    Statement statement = (Statement) connection.createStatement();
                    String sql = "select * from flight where flight_id = '" +
                            FI.getText()+"'";
                    ResultSet resultSet = statement.executeQuery(sql);
                    if (resultSet.next()){
                        Warning_info  waring_info = new Warning_info("�ú����Ѵ���");
                    }

                    resultSet.close();
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });

        JPanel jPanel = new JPanel(new GridLayout(3,2));
        jPanel.setBackground(new Color(0xEFFBFB));
        jPanel.setPreferredSize(new Dimension(715,300));
        jPanel.add(CNjpl);
        jPanel.add(PTjpl);
        jPanel.add(DCjpl);
        jPanel.add(ACjpl);
        jPanel.add(FIjpl);

        JLabel jLabel = new JLabel("���ӷɻ�����");
        jLabel.setFont(new Font("���Ŀ���",Font.PLAIN,50));

        OK = new JButton("ȷ����Ӻ���");
        OK.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    String sql = "insert into flight values (?,?,?,?,?);";
                    PreparedStatement preparedStatement = connection.prepareStatement(sql);
                    preparedStatement.setString(1,FI.getText());
                    preparedStatement.setString(2,CN.getSelectedItem().toString());
                    preparedStatement.setString(3,PT.getSelectedItem().toString());
                    preparedStatement.setString(4,DC.getText());
                    preparedStatement.setString(5,AC.getText());
                    Warning_info warning_info = new Warning_info("��ӳɹ�");
                    FI.setText("");
                    DC.setText("");
                    AC.setText("");
                    preparedStatement.execute();
                    preparedStatement.close();
                    
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });
        add(jLabel);
        add(jPanel);
        setBackground(new Color(0xEFFBFB));
        add(OK);
        setPreferredSize(new Dimension(715,550));

    }

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
    }}

