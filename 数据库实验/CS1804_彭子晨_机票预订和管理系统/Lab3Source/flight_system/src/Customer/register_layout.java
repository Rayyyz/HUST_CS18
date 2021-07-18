package Customer;

import Mysql.DBHelper;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

public class register_layout extends JFrame {
    protected JTextField new_account_text;
    protected JTextField new_password_text;
    protected JTextField new_name_text;
    protected JTextField new_tel_text;
    protected JComboBox<String> new_sex_text;
    protected JTextField new_age_text;

    protected JButton register;

    protected DBHelper dbHelper = new DBHelper();

    public register_layout(){
        super("register");
        Container container = getContentPane();
        FlowLayout layout = new FlowLayout(FlowLayout.CENTER);
        layout.setVgap(25);
        container.setLayout(layout);
        container.setBackground(new Color(0xEFFBFB));
        setResizable(false);

        String[] sexType = {"男","女"};
        
        JPanel id = new JPanel();
        JPanel tel = new JPanel();
        JPanel sex = new JPanel();
        JPanel age = new JPanel();
        
        JPanel account = new JPanel();
        account.setPreferredSize(new Dimension(600,30));
        account.setBackground(new Color(0xEFFBFB));
        
        JPanel password = new JPanel();
        password.setBackground(new Color(0xEFFBFB));
        password.setPreferredSize(new Dimension(600,30));
        
        JPanel name = new JPanel();
        name.setPreferredSize(new Dimension(600,30));
        name.setBackground(new Color(0xEFFBFB));
        
        tel.setBackground(new Color(0xEFFBFB));
        tel.setPreferredSize(new Dimension(600,30));
        
        sex.setPreferredSize(new Dimension(600,30));
        sex.setBackground(new Color(0xEFFBFB));
        
        age.setBackground(new Color(0xEFFBFB));
        age.setPreferredSize(new Dimension(600,30));

        new_account_text = new JTextField(15);
        new_name_text = new JTextField(15);
        new_password_text = new JPasswordField(15);
        new_age_text = new JTextField(16);
        new_tel_text = new JTextField(16);
        new_sex_text = new JComboBox<>(sexType);
        
        register = new JButton("注册");

        JLabel sign1 = new JLabel("*");
        sign1.setForeground(Color.RED);
        JLabel sign2 = new JLabel("*");
        sign2.setForeground(Color.RED);
        JLabel sign3 = new JLabel("*");
        sign3.setForeground(Color.RED);

        account.add(new JLabel("账 号："));
        password.add(new JLabel("密 码："));
        name.add(new JLabel("姓 名："));
        tel.add(new JLabel("电 话："));
        sex.add(new JLabel("性 别："));
        age.add(new JLabel("年 龄："));

        account.add(new_account_text);
        password.add(new_password_text);
        name.add(new_name_text);
        tel.add(new_tel_text);
        sex.add(new_sex_text);
        age.add(new_age_text);
        account.add(sign1);
        password.add(sign2);
        name.add(sign3);

        container.add(account);
        container.add(password);
        container.add(name);
        container.add(tel);
        container.add(age);
        container.add(sex);

        container.add(register);

        register.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int flag = 0;
                if (new_account_text.getText().equals("") || new_password_text.getText().equals("") || new_name_text.getText().equals("")){
                	setVisible(false);
                	register_layout register_layout = new register_layout();
                	Warning_info warning_info = new Warning_info("标有红色的不能为空");
                }
                else if(!new_account_text.getText().equals("") && !new_tel_text.getText().matches("[0-9]{11}")) {
                	setVisible(false);
                	register_layout register_layout = new register_layout();
                	Warning_info warning_info = new Warning_info("手机号格式不正确");
                }
                else {
                    flag = register_new_user(new_account_text.getText(), new_password_text.getText(), new_name_text.getText(),
                            new_sex_text.getSelectedItem().toString(), new_age_text.getText(), new_tel_text.getText());
                    if (flag == 0){
                        setVisible(false);
                        login_layout login_layout = new login_layout();
                        Warning_info warning_info = new Warning_info("账号注册成功，返回到登录界面");
                        warning_info.setTitle("注册成功");
                    }
                }
                
            }
        });
        setVisible(true);
        setSize(600,520);
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight(); int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);
    }

    public int register_new_user(String account,String password,String name,
                                 String sex,String age,String tel){
        dbHelper = new DBHelper();
        int flag = 0;
        Connection connection = dbHelper.getConnection();
        try{
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from users where account ='" +
                    account + "'";
            ResultSet resultSet = statement.executeQuery(sql);
            while(resultSet.next()){
            	 if (account.equals(resultSet.getString("account"))){
                     Warning_info warning_info = new Warning_info("该用户已存在");
                     flag=1;
                 }	
            }
            resultSet.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }
        if (flag == 0){
        	
            String sql = "insert into users (account, password, age,sex, tel, name ) values (?,?,?,?,?,?)";
            try{
                PreparedStatement preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setString(1,account);
                preparedStatement.setString(2,password);
                if (!age.equals(""))
                    preparedStatement.setInt(3,Integer.valueOf(age));
                if (!sex.equals(""));
                preparedStatement.setString(4,sex);
                if (!tel.equals(""))
                    preparedStatement.setString(5,tel);
                preparedStatement.setString(6,name);
                preparedStatement.executeUpdate();
                
                preparedStatement.close();
                
            }catch (SQLException e){
                e.printStackTrace();
            }
        }
        
        return flag;
        
    }
}
