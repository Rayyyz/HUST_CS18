package Customer;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.AbstractTableModel;

import Mysql.DBHelper;

//退订机票
class unsubscribe extends JPanel{
    protected JTextField Name;
    protected JTextField Id;
    protected JTextField Degree;
    protected JTextField Seat;
    protected JTextField Ordertime;
    protected JTextField ClassId;

    protected JButton delete;

    protected DBHelper dbHelper = new DBHelper();

    protected JComboBox<String> OrderId;
    protected String account;

	int a_number = 0, b_number = 0;

    public unsubscribe(String account){
        Connection connection = dbHelper.getConnection();
        JPanel Namejpl = new JPanel();
        JPanel Idjpl = new JPanel();
        JPanel Degreejpl = new JPanel();
        JPanel Seatjpl = new JPanel();
        JPanel Ordertimejpl = new JPanel();
        JPanel ClassIdjpl = new JPanel();
        JPanel OrderIdjpl = new JPanel();

        this.account = account;
        Name = new JTextField(15);
        Id = new JTextField(15);
        Degree = new JTextField(15);
        Seat = new JTextField(15);
        Ordertime = new JTextField(15);
        ClassId = new JTextField(15);
        OrderId = new JComboBox<>();

        OrderId.addItem("请选择订单号");
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from passengers where account ='"+account+"'";
            ResultSet resultSet = statement.executeQuery(sql);
            while (resultSet.next()){
                OrderId.addItem(resultSet.getString("order_id"));
            }
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        OrderId.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    Statement statement = (Statement) connection.createStatement();
                    String sql = "select * from passengers where account = '" + account+"' and order_id = '" +
                            OrderId.getSelectedItem().toString()+"'";
                    ResultSet resultSet = statement.executeQuery(sql);
                    resultSet.next();
                    Name.setText(resultSet.getString("name"));
                    Id.setText(resultSet.getString("id"));
                    Degree.setText(resultSet.getString("degree"));
                    Seat.setText(resultSet.getString("seat"));
                    Ordertime.setText(resultSet.getString("order_time"));
                    ClassId.setText(resultSet.getString("class_id"));
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });

        Namejpl.add(new JLabel("乘客姓名："));
        Namejpl.add(Name);
        Namejpl.setBackground(new Color(0xEFFBFB));
        Idjpl.add(new JLabel("身份证号："));
        Idjpl.add(Id);
        Idjpl.setBackground(new Color(0xEFFBFB));
        Degreejpl.add(new JLabel("预订舱位："));
        Degreejpl.add(Degree);
        Degreejpl.setBackground(new Color(0xEFFBFB));
        Seatjpl.add(new JLabel("座位号："));
        Seatjpl.add(Seat);
        Seatjpl.setBackground(new Color(0xEFFBFB));
        Ordertimejpl.add(new JLabel("预定时间："));
        Ordertimejpl.add(Ordertime);
        Ordertimejpl.setBackground(new Color(0xEFFBFB));
        ClassIdjpl.add(new JLabel("班次序号："));
        ClassIdjpl.add(ClassId);
        ClassIdjpl.setBackground(new Color(0xEFFBFB));
        OrderIdjpl.add(new JLabel("订票号："));
        OrderIdjpl.add(OrderId);
        OrderIdjpl.setBackground(new Color(0xEFFBFB));
        delete = new JButton("确定取消该订单");

        delete.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                	
                    String sql = "select a_number, b_number from classes where class_id = '"+ClassId+ "'";
                    Statement statement = (Statement) connection.createStatement();
                    ResultSet resultSet = statement.executeQuery(sql);
                    while (resultSet.next()){
                        a_number = resultSet.getInt("a_number");
                        b_number = resultSet.getInt("b_number");
                    }
                    resultSet.close();
                    
                    String sql1 = "delete from passengers where order_id = '"+ OrderId.getSelectedItem().toString()+"'";
                    PreparedStatement preparedStatement1 = connection.prepareStatement(sql1);
                    
                    String sql2;
                    if(Degree.getText() == "A") {
                    	int cur_number = a_number+1;
                    	sql2 = "update classes set a_number ='"+cur_number+"' where class_id='"+ClassId+"'";
                    }
                    else {
                    	int cur_number = b_number+1;
                    	sql2 = "update classes set b_number ='"+cur_number+"' where class_id='"+ClassId+"'";
                    }
                    
                    PreparedStatement preparedStatement2 = connection.prepareStatement(sql2);
                    preparedStatement1.execute();
                    preparedStatement2.execute();
                    Warning_info warning_info = new Warning_info("班次取消成功");
                    
                    updateUI();
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                    Warning_info warning_info = new Warning_info("出现错误");
                }
            }
        });

        JLabel jLabel = new JLabel("退订机票");
        jLabel.setFont(new Font("华文楷体",Font.PLAIN,50));
        setPreferredSize(new Dimension(715,550));

        JPanel jPanel = new JPanel(new GridLayout(4,2));
        jPanel.setBackground(new Color(0xEFFBFB));
        jPanel.setPreferredSize(new Dimension(700,300));
        jPanel.add(Namejpl);
        jPanel.add(Degreejpl);
        jPanel.add(Idjpl);
        jPanel.add(Seatjpl);
        jPanel.add(Ordertimejpl);
        jPanel.add(ClassIdjpl);

        JPanel panel = new JPanel();
        panel.setBackground(new Color(0xEFFBFB));
        panel.setPreferredSize(new Dimension(700,50));
        panel.add(OrderIdjpl);
        panel.add(delete);

        setPreferredSize(new Dimension(995,600));
        setBackground(new Color(0xEFFBFB));

        add(jLabel);
        add(jPanel);
        add(panel);
    }
}

