package Mysql;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBHelper {
	//加载驱动
	static{
		try{
			Class.forName("com.mysql.cj.jdbc.Driver");
		}catch(ClassNotFoundException e){
			e.printStackTrace();
		}
	}
	
	//连接
	private static String url = "jdbc:mysql://localhost:3306/flight_system?serverTimezone = GMT";
	private static String name = "root";
	private static String password = "123456";
	private static Connection connection = null;
	public Connection getConnection(){
		try{
			connection = (Connection) DriverManager.getConnection(url,name,password);
		}catch(SQLException e){
			e.printStackTrace();
		}
		return connection;
	}
	

}
