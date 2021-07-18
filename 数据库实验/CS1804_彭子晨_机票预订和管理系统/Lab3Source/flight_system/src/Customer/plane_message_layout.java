package Customer;

import Mysql.DBHelper;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.Date;

//预订机票
public class plane_message_layout extends JPanel {
    public JScrollPane plane_information;
    JLabel title1;
    search ticket_form;
    public JTextField departurePlace_text;
    public JTextField arrivalPlace_text;
    public JTextField departure_time_text;
    public JTextField backData_text;

    public JComboBox<String> aviation_company;
    public JComboBox<String> seat_type;

    protected MyButtonUI research;

    public String[] seat_list;
    public String[] aviation_list;
    public Color color1 = new Color(0x4F93FF);

    public JPanel plane_info;

    public ButtonGroup type;

    public JPanel title;
    public JPanel jPanel;

    String depart_city = "出发城市";
    String arrival_city = "到达城市";
    String data_ = "出发时间";
    String company = "";
    String account;
    String class_id;
    int a_number,b_number;
    String ticketType1,ticketType2;
    int a_price,b_price;

    public plane_message_layout(String account){
        FlowLayout layout = new FlowLayout();
        layout.setVgap(15);
        setLayout(layout);
        
        jPanel = new JPanel();

        ticket_form = new search();
        ticket_form.setBackground(Color.WHITE);
        plane_information = new JScrollPane();
        
        this.account = account;

        Font font1 = new Font("黑体",Font.PLAIN,14);
        Font font2 = new Font("黑体",Font.PLAIN,12);
        
        JLabel departurePlace = new JLabel("出发城市  ");
        departurePlace.setFont(font1);
        JLabel arrivalPlace = new JLabel("到达城市  ");
        arrivalPlace.setFont(font1);
        departurePlace_text = new JTextField("武汉",19);
        arrivalPlace_text = new JTextField("上海",19);
        departurePlace.setFont(font2);
        arrivalPlace.setFont(font2);

        JLabel departure_time = new JLabel("出发日期  ");
        departure_time.setFont(font1);
        JLabel backData = new JLabel("返回日期  ");
        backData.setFont(font1);
        departure_time_text = new JTextField("2021-06-25",19);
        backData_text = new JTextField("2021-06-25",19);
        departure_time.setFont(font2);
        backData.setFont(font2);

        add_aviation_company();

        JLabel aviation =  new JLabel("航空公司 ");
        aviation.setFont(font2);
        aviation_company = new JComboBox<>(aviation_list);
        aviation_company.setBackground(Color.white);
        aviation_company.setFont(font2);

        JLabel seat = new JLabel("舱位等级 ");
        seat.setFont(font2);
        seat_type = new JComboBox<>(seat_list);
        seat_type.setBackground(Color.white);
        seat_type.setFont(font2);

        research = new MyButtonUI("搜索 ");
        research.setButtonColor(new Color(0xFFBD5A),new Color(0xFFCA49));
        research.setFont(font2);

        {
            ticket_form.add(new JLabel("                                                                   "));
            ticket_form.add(new JLabel("                                                                   "));
            ticket_form.add(departurePlace);
            ticket_form.add(departurePlace_text);
            ticket_form.add(arrivalPlace);
            ticket_form.add(arrivalPlace_text);
            ticket_form.add(departure_time);
            ticket_form.add(departure_time_text);
            ticket_form.add(backData);
            ticket_form.add(backData_text);
            ticket_form.add(new JLabel("- - - - - - - - - - - - - - - - - - - - - - - " +
                    " - - - - - - - - - - - - - - - "));
            ticket_form.add(new JLabel("                                                                             "));
            ticket_form.add(aviation);
            ticket_form.add(aviation_company);
            ticket_form.add(seat);
            ticket_form.add(seat_type);
            ticket_form.add(new JLabel("                                                                   "));
            ticket_form.add(new JLabel("             "));
            ticket_form.add(research);
        }

        title1 = new JLabel("机 票 查 询");
        title1.setFont(new Font("黑体",Font.ITALIC,48));
        title1.setBounds(40,40,300,70);
        title1.setForeground(new Color(0xFFCA49));

        message_layout(depart_city,arrival_city,data_);

        //查询监听器
        research.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                remove(title);
                message_layout(departurePlace_text.getText(),arrivalPlace_text.getText(),departure_time_text.getText());
                setinfo(account,departure_time_text.getText(),departurePlace_text.getText(),arrivalPlace_text.getText());
            }
        });
        setLayout(null);
        plane_information.setBounds(350,100,600,430);
        plane_information.setLayout(new ScrollPaneLayout());
        plane_information.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        plane_information.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        ticket_form.setBounds(20,150,300,350);

        add(plane_information);
        add(title1);
        add(ticket_form);

        setBackground(new Color(0xEFFBFB));
        setPreferredSize(new Dimension(995,600));
        
    }

    public void setinfo(String account,String data,String departPlace,String ArrivalPlace){
        String Name,Time1,Time2,Place1,Place2,NO;
        Name= Time1 = Time2 = Place2 = Place1 = NO ="";

        FlowLayout layout = new FlowLayout();
        layout.setVgap(5);
        plane_info = new JPanel(layout);
        int count = 1;
        company = aviation_company.getSelectedItem().toString();
        company = company.equals(aviation_list[0])?"":company;
        DBHelper dbHelper = new DBHelper();
        Connection connection = dbHelper.getConnection();
        try{
            String sql = "select * from classes,flight where flight.departure_city = '" +
                    departPlace+"' and flight.arrival_city = '" +
                    ArrivalPlace+"' and departure_time between '"+data+ " 00:00:00' and '"+data
                    +" 23:59:59' and flight.flight_id = classes.flight_id";
            if(company!="") sql = sql + " and flight.company_name = '"+company+"'";
            Statement statement0 = (Statement) connection.createStatement();
            ResultSet resultSet0 = statement0.executeQuery(sql);

            while (resultSet0.next()){
                count++;
                Name = resultSet0.getString("company_name");
                Time1 = resultSet0.getString("departure_time");
                Time1 = Time1.substring(11,19);
                Time2 = resultSet0.getString("arrival_time");
                Time2 = Time2.substring(11,19);
                Place1 = resultSet0.getString("departure_airport");
                Place2 = resultSet0.getString("arrival_airport");
                a_price = resultSet0.getInt("a_price");
                b_price = resultSet0.getInt("b_price");
                a_number = resultSet0.getInt("a_number");
                b_number = resultSet0.getInt("b_number");
                NO = resultSet0.getString("plane_type");
                class_id = resultSet0.getString("class_id");
                
                JPanel infoPanel = new info();
                JPanel name_time = new JPanel();
                name_time.setBackground(Color.white);
                JLabel name = new JLabel(Name);
                JLabel time1 = new JLabel(Time1);
                JLabel time2 = new JLabel(Time2);
                JLabel place1 = new JLabel(Place1);
                JLabel place2 = new JLabel(Place2);
                JLabel no = new JLabel(NO);

                name.setFont(new Font("黑体",Font.PLAIN,15));
                no.setFont(new Font("华文楷体",Font.PLAIN,10));
                time1.setFont(new Font("宋体",Font.BOLD,19));
                time2.setFont(new Font("宋体",Font.BOLD,19));
                place1.setFont(new Font("华文楷体",Font.PLAIN,9));
                place2.setFont(new Font("华文楷体",Font.PLAIN,9));

                Box box = Box.createVerticalBox();
                box.add(name);
                box.add(no);
                Box box1 = Box.createVerticalBox();
                box1.add(time1);
                box1.add(place1);
                Box box2 = Box.createVerticalBox();
                box2.add(time2);
                box2.add(place2);
                JLabel NULL = new JLabel("         " ) ;

                name_time.add(box);
                name_time.add(NULL);
                name_time.add(box1);
                name_time.add(box2);
                infoPanel.add(name_time);

                ticketType1 = "";
                ticketType2 = "";
                MyButtonUI book1 = new MyButtonUI("预定");
            	MyButtonUI book2 = new MyButtonUI("预定");
                for (int i = 0;i < 2;i++){
                    try{
                        Statement statement1 = (Statement) connection.createStatement();
                        String sql1 = "select * from classes where class_id = '" +
                                class_id+"'";
                        ResultSet resultSet1 = statement1.executeQuery(sql1);
                        while(resultSet1.next()){
                        	if (i == 0){
                                ticketType1 = "商务舱";
                                a_price = resultSet1.getInt("a_price");
                                a_number = resultSet1.getInt("a_number");
                            }
                            else {
                                ticketType2 = "经济舱";
                                b_price = resultSet1.getInt("b_price");
                                b_number = resultSet1.getInt("b_number");
                            }
                        }
                        resultSet1.close();
                        }catch (SQLException e){
                        e.printStackTrace();
                    }             
                }
                
                book1.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        order_layout o = new order_layout(a_price,ticketType1,data,departPlace,ArrivalPlace);

                        o.OK.addActionListener(new ActionListener() {
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                String name = o.name_text.getText();
                                String id = o.id_text.getText();
                                String seat = o.seat_text.getText();
                                Date date = new Date();
                                SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                                try{
                                	String sql1 = "select order_id from passengers where seat='"+seat+"' and class_id='"+class_id+"'";
                                    Statement statement1 = (Statement) connection.createStatement();
                                    ResultSet resultSet1 = statement1.executeQuery(sql1);
                                    if(resultSet1.next()) {
                                    	Warning_info warning_info = new Warning_info("输入的座位号已被占用,请重新购票");
                                    }
                                    else {
                                    	String sql2 = "select max(order_id) as number from passengers";
                                        String sql3 = "insert into passengers values (?,?,?,?,?,?,?,?)";
                                        Statement statement2 = (Statement) connection.createStatement();
                                        ResultSet resultSet2 = statement2.executeQuery(sql2);
                                        while(resultSet2.next()){
                                        	  int n = resultSet2.getInt("number");
                                              PreparedStatement preparedStatement = connection.prepareStatement(sql3);
                                              preparedStatement.setInt(1,n+1);
                                              preparedStatement.setString(2,name);
                                              preparedStatement.setString(3,account);
                                              preparedStatement.setString(4,id);
                                              preparedStatement.setString(5,dateFormat.format(date));
                                              preparedStatement.setString(6,seat);
                                              preparedStatement.setString(7,"A");
                                              preparedStatement.setString(8,class_id);
                                              preparedStatement.execute();
                                              preparedStatement.close();
                                        }
                                        o.setVisible(true);
                                        Warning_info warning_info = new Warning_info("预定成功");
                                        resultSet2.close();
                                        
                                        //票数减一
                                        int cur_number = a_number-1;
                                        String sql4 = "update classes set a_number ='" +cur_number +"' where class_id='"+class_id+"'";
                                        PreparedStatement preparedStatement = connection.prepareStatement(sql4);
                                        preparedStatement.execute();
                                    }
                                    resultSet1.close();

                                    o.setVisible(false);
                                }
                                catch (SQLException e1){
                                    e1.printStackTrace();
                                }
                                
                            }
                        });
                    }
                });
              
               
                
                book2.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        order_layout o = new order_layout(b_price,ticketType2,data,departPlace,ArrivalPlace);

                        o.OK.addActionListener(new ActionListener() {
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                String name = o.name_text.getText();
                                String id = o.id_text.getText();
                                String seat = o.seat_text.getText();
                                Date date = new Date();
                                SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                                try{
                                	String sql1 = "select order_id from passengers where seat='"+seat+"' and class_id='"+class_id+"'";
                                    Statement statement1 = (Statement) connection.createStatement();
                                    ResultSet resultSet1 = statement1.executeQuery(sql1);
                                    if(resultSet1.next()) {
                                    	Warning_info warning_info = new Warning_info("输入的座位号已被占用,请重新购票");
	                                }
                                    else {
                                    	String sql2 = "select max(order_id) as number from passengers";
	                                    String sql3 = "insert into passengers values (?,?,?,?,?,?,?,?)";
	                                    Statement statement2 = (Statement) connection.createStatement();
	                                    ResultSet resultSet2 = statement2.executeQuery(sql2);
	                                    while(resultSet2.next()){
	                                    	  int n = resultSet2.getInt("number");
	                                          PreparedStatement preparedStatement = connection.prepareStatement(sql3);
	                                          preparedStatement.setInt(1,n+1);
	                                          preparedStatement.setString(2,name);
	                                          preparedStatement.setString(3,account);
	                                          preparedStatement.setString(4,id);
	                                          preparedStatement.setString(5,dateFormat.format(date));
	                                          preparedStatement.setString(6,seat);
	                                          preparedStatement.setString(7,"B");
	                                          preparedStatement.setString(8,class_id);
	                                          preparedStatement.execute();
	                                          preparedStatement.close();
	                                    }
	                                    o.setVisible(true);
	                                    Warning_info warning_info = new Warning_info("预定成功");
	                                    resultSet2.close();
	                                    
                                        //票数减一
                                        int cur_number = b_number-1;
                                        String sql4 = "update classes set b_number ='" +cur_number+"' where class_id='"+class_id+"'";
                                        PreparedStatement preparedStatement = connection.prepareStatement(sql4);
                                        preparedStatement.execute();

                                    }
                                    resultSet1.close();
                                    
                                    o.setVisible(false);
                                }
                                catch (SQLException e1){
                                    e1.printStackTrace();
                                }
                                
                            }
                        });
                    }
                });
                
                
             
                JLabel ticket_type1 = new JLabel(ticketType1);
                ticket_type1.setFont(new Font("宋体",Font.PLAIN,15));
                JLabel price1 = new JLabel("￥"+String.valueOf(a_price));
                price1.setFont(new Font("宋体",Font.PLAIN,18));
                price1.setForeground(new Color(0xFF5B20));
                book1.setForeground(Color.WHITE);
                book1.setButtonColor(new Color(0x2999FF),new Color(0x2999FF));
                
                JPanel ticket1 = new JPanel(null);
                ticket1.setPreferredSize(new Dimension(600,30));
                ticket1.setBackground(new Color(0x0000000,true));
                ticket_type1.setBounds(50,0,50,30);
                price1.setBounds(420,0,60,30);
                book1.setBounds(500,0,60,30);
                ticket1.add(ticket_type1);
                ticket1.add(price1);
                ticket1.add(book1);
                infoPanel.add(ticket1);
                ticket1.updateUI();
                
                JLabel ticket_type2 = new JLabel(ticketType2);
                ticket_type2.setFont(new Font("宋体",Font.PLAIN,15));
                JLabel price2 = new JLabel("￥"+String.valueOf(b_price));
                price2.setFont(new Font("宋体",Font.PLAIN,18));
                price2.setForeground(new Color(0xFF5B20));
                book1.setForeground(Color.WHITE);
                book1.setButtonColor(new Color(0x2999FF),new Color(0x2999FF));
                
                JPanel ticket2 = new JPanel(null);
                ticket2.setPreferredSize(new Dimension(600,30));
                ticket2.setBackground(new Color(0x0000000,true));
                ticket_type2.setBounds(50,0,50,30);
                price2.setBounds(420,0,60,30);
                book2.setBounds(500,0,60,30);
                ticket2.add(ticket_type2);
                ticket2.add(price2);
                ticket2.add(book2);
                infoPanel.add(ticket2);
                ticket2.updateUI();
                infoPanel.setPreferredSize(new Dimension(600,120));
                
                plane_info.add(infoPanel);
                plane_info.setBackground(Color.white);
                plane_information.setViewportView(plane_info);
                plane_information.setBackground(Color.white);

                infoPanel.repaint();
                infoPanel.updateUI();
                plane_information.updateUI();

                
            }
            resultSet0.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }
        plane_info.setPreferredSize(new Dimension(600,count*120));

    }

    public void add_aviation_company(){
        aviation_list = new String[] {"- - - 请选择航空公司 - - -","中国航空","东方航空","南方航空","春秋航空"};
        seat_list = new String[] {"- - - 请选择舱位等级 - - -","商务舱","经济舱"};
    }

    public class info extends JPanel{
        @Override
        public void paintComponent(Graphics g){
            g.setColor(new Color(0x1D000000,true));
            g.drawRect(0,0,600,50);
            g.fillRect(0,50,600,70);
            g.setColor(new Color(0x3F000007,true));
            g.setColor(Color.white);
            g.drawLine(0,85,600,85);
            setBackground(Color.white);
            setOpaque(false);
        }
    }
    public class search extends JPanel{
        @Override
        protected void paintComponent(Graphics g) {
            g.setColor(color1);
            g.fillRoundRect(0,0,300,350,10,10);
            g.setColor(Color.white);
            g.fillRect(4,37,292,308);
            setBackground(Color.white);
            setOpaque(false);
        }
    }
    public void message_layout(String place1,String place2,String day){
        String Mes = "航班" + "       "+place1+" to "+place2+"      "+day;
        title = new JPanel();
        JLabel mes = new JLabel(Mes);
        mes.setFont(new Font("宋体",Font.BOLD,22));
        mes.setFont(new Font("宋体",Font.BOLD,22));
        mes.setForeground(Color.white);

        title.add(mes);
        title.setBounds(350,55,600,40);
        title.setBackground(new Color(0x6E6E6E));
        add(title);
        title.updateUI();

    }
}
