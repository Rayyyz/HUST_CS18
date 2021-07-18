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

        String[] company = {"中国航空","东方航空","南方航空","春秋航空"};

        String[] type = {"波音737-700","波音737-800", "空中客车A319","空中客车A319-100"
        ,"空中客车A320","空中客车A320-200", "空中客车A330-300", "ATR72"};
        CN = new JComboBox<>(company);
        CN.setBackground(Color.white);
        PT = new JComboBox<>(type);
        PT.setBackground(Color.white);
        FI = new JTextField(15);
        DC = new JTextField(15);
        AC = new JTextField(15);

        JPanel CNjpl = new JPanel();
        CNjpl.add(new JLabel("选择航空公司："));
        CNjpl.setBackground(new Color(0xEFFBFB));
        CNjpl.add(CN);
        JPanel PTjpl = new JPanel();
        PTjpl.add(new JLabel("选择飞机机型："));
        PTjpl.setBackground(new Color(0xEFFBFB));
        PTjpl.add(PT);
        JPanel FIjpl = new JPanel();
        FIjpl.setBackground(new Color(0xEFFBFB));
        FIjpl.add(new JLabel("航班号："));
        FIjpl.add(FI);
        JPanel DCjpl = new JPanel();
        DCjpl.setBackground(new Color(0xEFFBFB));
        DCjpl.add(new JLabel("出发城市："));
        DCjpl.add(DC);
        JPanel ACjpl = new JPanel();
        ACjpl.setBackground(new Color(0xEFFBFB));
        ACjpl.add(new JLabel("到达城市："));
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
                        Warning_info  waring_info = new Warning_info("该航班已存在");
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

        JLabel jLabel = new JLabel("增加飞机航班");
        jLabel.setFont(new Font("华文楷体",Font.PLAIN,50));

        OK = new JButton("确定添加航班");
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
                    Warning_info warning_info = new Warning_info("添加成功");
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

