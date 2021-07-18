package Customer;

import Mysql.DBHelper;

import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

//支付账单详情、取票详情（展示页面）
public class payment_layout extends JFrame{
    protected Container container;
    
    public JPanel notice;
    public JPanel payment;
    
	public payment_layout() {
        container = getContentPane();
		
		notice = new JPanel();
		
		payment = new JPanel();
		
        setVisible(true);
        setSize(1000,600);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();
        int screenWidth = screenSize.width/2;
        int screenHeight = screenSize.height/2;
        int height = this.getHeight();int width = this.getWidth();
        setLocation(screenWidth-width/2,screenHeight-height/2);	
	}

}
