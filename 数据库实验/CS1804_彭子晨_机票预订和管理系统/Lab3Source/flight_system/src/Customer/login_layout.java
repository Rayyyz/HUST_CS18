package Customer;

import com.mysql.cj.protocol.Warning;

import Mysql.DBHelper;

import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class login_layout extends JFrame {

    protected JTextField account_text;
    protected JTextField password_text;

    protected JButton register_button;
    protected JButton login_button;

    protected Container container;
    protected GridLayout layout;
    protected JPanel account;
    protected JPanel password;
    protected JPanel button;

    protected DBHelper dbHelper;

    public login_layout(){
        super("login");
        container = getContentPane();
        layout = new GridLayout(2,1);
        container.setLayout(layout);
        container.setBackground(new Color(0xFFFFFF));
        setResizable(false);

        sqlInit();

        account_text = new JTextField(15);
        password_text = new JPasswordField(15);
        login_button = new MyButtonUI("µ«¬º");
        register_button = new MyButtonUI("◊¢≤·");
        JLabel labelAccount = new JLabel("’À∫≈£∫");
        JLabel labelPassword = new JLabel("√‹¬Î£∫");
        ImageIcon pic = new ImageIcon("src/pic/plane.jpg");
        pic.setImage(pic.getImage().getScaledInstance(600,350,Image.SCALE_DEFAULT));

        account = new JPanel();
        account.setBackground(new Color(0xFFFFFF));
        password = new JPanel();
        password.setBackground(new Color(0xFFFFFF));
        button = new JPanel();
        button.setBackground(new Color(0xFFFFFF));

        FlowLayout button_layout = new FlowLayout();
        button_layout.setHgap(30);
        button.setLayout(button_layout);

        account.add(labelAccount);
        account.add(account_text);
        password.add(labelPassword);
        password.add(password_text);
        button.add(login_button);
        button.add(register_button);

        JPanel jPanel = new JPanel();
        jPanel.setBackground(new Color(0xFFF0F5));
        jPanel.setLayout(new GridLayout(3,1));

        jPanel.add(account);
        jPanel.add(password);
        jPanel.add(button);

        container.add(new JLabel(pic));
        container.add(jPanel);

        register_button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                register_layout registerLayout = new register_layout();
                registerLayout.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                setVisible(false);
            }
        });

        login_button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String old_account = account_text.getText();
                String old_password = password_text.getText();
                login_system(old_account,old_password);
            }
        });
        setVisible(true);
        setSize(600,520);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight();int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);
    }

    public  void sqlInit(){
        dbHelper = new DBHelper();

    }

    public void login_system(String old_account,String old_password){
        Connection connection = dbHelper.getConnection();
        
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from users where account ='" +
                    old_account+"'";
            ResultSet resultSet = statement.executeQuery(sql);
            if(resultSet.next()) {
	            do {
	            	if (old_password.equals(resultSet.getString("password")))
	                {
	            		user u1 = new user(old_account);
	                    this.setVisible(false);
	                }
	                else{
	                    Warning_info warning_info = new Warning_info("√‹¬Î¥ÌŒÛ£¨«Î÷ÿ–¬ ‰»Î");
	                    account_text.setText("");
	                    password_text.setText("");
	
	                }
	            } while(resultSet.next());
            }
            else {
                Warning_info warning_info = new Warning_info("’À∫≈≤ª¥Ê‘⁄£¨«Î◊¢≤·’À∫≈ªÚ÷ÿ–¬ ‰»Î");
                account_text.setText("");
                password_text.setText("");
            }
            resultSet.close();  
        }catch (SQLException e){
            e.printStackTrace();
        }finally{
        	
        }
    }
}
