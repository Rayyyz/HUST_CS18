package Airport;

import Mysql.DBHelper;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

class research_plane extends JPanel{
    protected planeTableValues tv;
    protected JButton button;
    protected JTextField no;
    protected JTextField place1;
    protected JTextField place2;
    protected JTextField day;

    JTable table;
    JScrollPane jsp;

    public research_plane(){
        FlowLayout layout = new FlowLayout();
        layout.setVgap(15);
        setLayout(layout);

        //查询输入
        button = new JButton("搜索");
        no = new JTextField(9);
        place1 = new JTextField(9);
        place2 = new JTextField(9);
        day = new JTextField(9);
        JPanel jPanel = new JPanel();
        jPanel.add(new JLabel("航空公司："));
        jPanel.add(no);
        jPanel.add(new JLabel("出发地："));
        jPanel.add(place1);
        jPanel.add(new JLabel("到达地："));
        jPanel.add(place2);
        jPanel.add(new JLabel("出发日期："));
        jPanel.add(day);
        jPanel.add(button);
        jPanel.setBackground(new Color(0xEFFBFB));

        //表格
        tv = new planeTableValues();
        table = new JTable(tv);
        table.setRowHeight(30);
        table.setBackground(new Color(0xFFEBFCFF,true));
        table.updateUI();

        jsp = new JScrollPane(table);
        jsp.setPreferredSize(new Dimension(700,350));
        {
            table.getColumnModel().getColumn(0).setPreferredWidth(80);
            table.getColumnModel().getColumn(1).setPreferredWidth(140);
            table.getColumnModel().getColumn(2).setPreferredWidth(140);
            table.getColumnModel().getColumn(3).setPreferredWidth(110);
            table.getColumnModel().getColumn(4).setPreferredWidth(90);
            table.getColumnModel().getColumn(5).setPreferredWidth(90);
        }
        //标签
        JLabel label = new JLabel("班次信息查询");
        label.setFont(new Font("华文楷体",Font.BOLD,50));

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                tv = new planeTableValues();
                table = new JTable(tv);
                table.setRowHeight(30);
                table.setBackground(new Color(0xFFEBFCFF,true));
                remove(jsp);
                jsp = new JScrollPane(table);
                {
                    table.getColumnModel().getColumn(0).setPreferredWidth(80);
                    table.getColumnModel().getColumn(1).setPreferredWidth(140);
                    table.getColumnModel().getColumn(2).setPreferredWidth(140);
                    table.getColumnModel().getColumn(3).setPreferredWidth(100);
                    table.getColumnModel().getColumn(4).setPreferredWidth(90);
                    table.getColumnModel().getColumn(5).setPreferredWidth(90);
                }
                jsp.setPreferredSize(new Dimension(700,350));
                add(jsp);
                updateUI();
            }
        });

        add(label);
        add(jPanel);
        add(jsp);
        setBackground(new Color(0xEFFBFB));
        setPreferredSize(new Dimension(715,580));
    }
    class planeTableValues extends AbstractTableModel{
        private String[] columnNames = {"班次编号","出发时间","到达时间","出发机场","到达机场","商务舱余票","经济舱余票"};
        public Object[][] values = new Object[1000][7];
        public DBHelper dbHelper = new DBHelper();

        public planeTableValues(){
            String noText = no.getText();
            String place1Text = place1.getText();
            String place2Text = place2.getText();
            String dayText = day.getText();
            String sql = "SELECT * from flight,classes where classes.flight_id = flight.flight_id";
            if (!noText.equals(""))
            {
                sql += " and company_name = '"+noText+"'";
            }
            if (!place1Text.equals("")){
                sql += " and departure_city = '"+place1Text+"'";
            }
            if (!place2Text.equals("")){
                sql += " and arrival_city ='"+place2Text+"'";
            }
            if (!dayText.equals("")){
                sql += " and departure_time like'"+dayText+"%'";
            }
            Connection connection = dbHelper.getConnection();
            try {
                Statement statement = (Statement) connection.createStatement();
                ResultSet resultSet = statement.executeQuery(sql);
                int i = 0;
                while (resultSet.next()){
                    values[i][0] = resultSet.getString("class_id");
                    values[i][1] = resultSet.getString("departure_time");
                    values[i][2] = resultSet.getString("arrival_time");
                    values[i][3] = resultSet.getString("departure_airport");
                    values[i][4] = resultSet.getString("arrival_airport");
                    values[i][5] = resultSet.getString("a_number");
                    values[i][6] = resultSet.getString("b_number");
                    i++;
                }
                resultSet.close();
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }
        public int getColumnCount() {return  values[0].length;}

        public int getRowCount() {return values.length;}

        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {
            return values[rowIndex][columnIndex];
        }

        //设置列名
        public String getColumnName(int column){return  columnNames[column];}

    }
}

class research_book extends JPanel{
    protected bookTableValues tv;
    protected JButton button;
    protected JTextField flight_id;
    protected JTextField passenger_name;
    protected JTextField account;
    protected JTextField user_name;

    JTable table;
    JScrollPane jsp;

    public research_book(){
        FlowLayout layout = new FlowLayout();
        layout.setVgap(15);
        setLayout(layout);

        //查询输入
        button = new JButton("搜索");
        user_name = new JTextField(8);
        passenger_name = new JTextField(8);
        account = new JTextField(8);
        flight_id = new JTextField(8);
        JPanel jPanel = new JPanel();
        jPanel.add(new JLabel("预定时间："));
        jPanel.add(flight_id);
        jPanel.add(new JLabel("乘客姓名："));
        jPanel.add(passenger_name);
        jPanel.add(new JLabel("下单账号："));
        jPanel.add(account);
        jPanel.add(new JLabel("班次编号："));
        jPanel.add(user_name);
        jPanel.add(button);
        jPanel.setBackground(new Color(0xEFFBFB));

        //表格
        tv = new bookTableValues();
        table = new JTable(tv);
        table.setRowHeight(30);
        table.setBackground(new Color(0xFFEBFCFF,true));

        jsp = new JScrollPane(table);
        jsp.setPreferredSize(new Dimension(700,350));
        {
            table.getColumnModel().getColumn(0).setPreferredWidth(80);
            table.getColumnModel().getColumn(1).setPreferredWidth(80);
            table.getColumnModel().getColumn(2).setPreferredWidth(80);
            table.getColumnModel().getColumn(3).setPreferredWidth(140);
            table.getColumnModel().getColumn(4).setPreferredWidth(60);
            table.getColumnModel().getColumn(5).setPreferredWidth(60);
            table.getColumnModel().getColumn(6).setPreferredWidth(130);
        }

        //标签
        JLabel label = new JLabel("订单信息查询");
        label.setFont(new Font("华文楷体",Font.BOLD,50));

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                tv = new bookTableValues();
                table = new JTable(tv);
                table.setRowHeight(30);
                remove(jsp);
                jsp = new JScrollPane(table);
                {
                    table.getColumnModel().getColumn(0).setPreferredWidth(80);
                    table.getColumnModel().getColumn(1).setPreferredWidth(80);
                    table.getColumnModel().getColumn(2).setPreferredWidth(80);
                    table.getColumnModel().getColumn(3).setPreferredWidth(140);
                    table.getColumnModel().getColumn(4).setPreferredWidth(60);
                    table.getColumnModel().getColumn(5).setPreferredWidth(130);
                }
                jsp.setPreferredSize(new Dimension(700,350));
                add(jsp);
                table.setBackground(new Color(0xFFEBFCFF,true));
                updateUI();
            }
        });
        add(label);
        add(jPanel);
        add(jsp);
        setBackground(new Color(0xEFFBFB));
        setPreferredSize(new Dimension(715,550));
    }

    class bookTableValues extends AbstractTableModel{
        private String[] columnNames = {"订单号","下单账号","乘客姓名","证件号","座位号","舱位","预定时间"};
        public  Object[][] values = new Object[1000][7];
        public DBHelper dbHelper = new DBHelper();

        public bookTableValues(){
            String flightText = flight_id.getText();
            String PNText = passenger_name.getText();
            String UNText = user_name.getText();
            String AccountText = account.getText();
            String sql = "select * from passengers,users where users.account = passengers.account";

            if(!flightText.equals("")){
                sql += " and order_time like '"+flightText+"%'";
            }
            if (!PNText.equals("")){
                sql += " and passengers.name = '"+PNText+"'";
            }
            if (!UNText.equals("")){
                sql += " and class_id = '"+UNText+"'";
            }
            if (!AccountText.equals("")){
                sql += " and users.account = '"+AccountText+"'";
            }
            Connection connection = dbHelper.getConnection();
            try{
                Statement statement = (Statement) connection.createStatement();
                ResultSet resultSet = statement.executeQuery(sql);
                int i = 0;
                while (resultSet.next()) {
                    values[i][0] = resultSet.getString("order_id");
                    values[i][1] = resultSet.getString("account");
                    values[i][2] = resultSet.getString("passengers.name");
                    values[i][3] = resultSet.getString("id");
                    values[i][4] = resultSet.getString("seat");
                    values[i][5] = resultSet.getString("degree");
                    values[i][6] = resultSet.getString("order_time");
                    i++;
                }
                resultSet.close();
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }
        public int getColumnCount(){return values[0].length;}

        @Override
        public int getRowCount() {
            return values.length;
        }

        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {
            return values[rowIndex][columnIndex];
        }

        public  String getColumnName(int column) {return columnNames[column];}
    }
}