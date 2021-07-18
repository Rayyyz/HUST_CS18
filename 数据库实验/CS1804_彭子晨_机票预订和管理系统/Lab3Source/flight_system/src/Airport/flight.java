package Airport;


import com.mysql.cj.protocol.Warning;
import Mysql.DBHelper;

import javax.print.DocFlavor;
import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.sql.*;

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
}

class addFlight extends JPanel{
    private static final int Atotal = 30;
    private static final int Btotal = 80;

    protected JComboBox<String> FI_jtf = new JComboBox<String>();
    protected JTextField DA_jtf;
    protected JTextField DT_jtf;
    protected JTextField AA_jtf;
    protected JTextField AT_jtf;
    protected JTextField AP_jtf;
    protected JTextField BP_jtf;
    protected JTextField CI_jtf;

    protected JButton Add;

    protected DBHelper dbHelper = new DBHelper();

    protected JTable jTable;
    protected JTable jTable1;

    public addFlight(){
        JLabel title = new JLabel("���ź�����");
        title.setFont(new Font("���Ŀ���",Font.BOLD,50));
        add(title);

        //���������
        JPanel FI_jpl = new JPanel();
        FI_jpl.setBackground(new Color(0xEFFBFB));
        JPanel DA_jpl = new JPanel();
        DA_jpl.setBackground(new Color(0xEFFBFB));
        JPanel DT_jpl = new JPanel();
        DT_jpl.setBackground(new Color(0xEFFBFB));
        JPanel AA_jpl = new JPanel();
        AA_jpl.setBackground(new Color(0xEFFBFB));
        JPanel AT_jpl = new JPanel();
        AT_jpl.setBackground(new Color(0xEFFBFB));
        JPanel AP_jpl = new JPanel();
        AP_jpl.setBackground(new Color(0xEFFBFB));
        JPanel BP_jpl = new JPanel();
        BP_jpl.setBackground(new Color(0xEFFBFB));
        JPanel CI_jpl = new JPanel();
        CI_jpl.setBackground(new Color(0xEFFBFB));

        JPanel text = new JPanel();
        text.setBackground(new Color(0xEFFBFB));
        text.setLayout(new GridLayout(4,2));
        text.setPreferredSize(new Dimension(400,300));

        //����FI
        FI_jtf.addItem("��ѡ�񺽰��");
        Connection connection = dbHelper.getConnection();
        try{
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from flight";
            ResultSet resultSet = statement.executeQuery(sql);
            while (resultSet.next()){
                FI_jtf.addItem(resultSet.getString("flight_id"));
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        FI_jtf.setBackground(Color.white);

        //�����
        DA_jtf = new JTextField(19);
        DT_jtf = new JTextField("2021-06-25 00:00:00",19);
        AA_jtf = new JTextField(19);
        AT_jtf = new JTextField("2021-06-25 00:00:00",19);
        AP_jtf = new JTextField(19);
        BP_jtf = new JTextField(19);
        CI_jtf = new JTextField(19);

        //��label��textfield����panel
        FI_jpl.add(new JLabel("����ţ�"));
        FI_jpl.add(FI_jtf);
        DA_jpl.add(new JLabel("����������"));
        DA_jpl.add(DA_jtf);
        DT_jpl.add(new JLabel("����ʱ�䣺"));
        DT_jpl.add(DT_jtf);
        AA_jpl.add(new JLabel("���������"));
        AA_jpl.add(AA_jtf);
        AT_jpl.add(new JLabel("����ʱ�䣺"));
        AT_jpl.add(AT_jtf);
        AP_jpl.add(new JLabel("����ռ۸�"));
        AP_jpl.add(AP_jtf);
        BP_jpl.add(new JLabel("���òռ۸�"));
        BP_jpl.add(BP_jtf);
        CI_jpl.add(new JLabel("��κţ�"));
        CI_jpl.add(CI_jtf);

        text.add(FI_jpl);
        text.add(CI_jpl);
        text.add(DA_jpl);
        text.add(AA_jpl);
        text.add(DT_jpl);
        text.add(AT_jpl);
        text.add(AP_jpl);
        text.add(BP_jpl);

        //���ذ�ť
        Add = new JButton("���Ӹú���");
        Add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    String sql = "insert into classes values (?,?,?,?,?,?,?,?,?,?);";
                    PreparedStatement preparedStatement = connection.prepareStatement(sql);
                    preparedStatement.setString(1,CI_jtf.getText());
                    preparedStatement.setString(2,DT_jtf.getText());
                    preparedStatement.setString(3,DA_jtf.getText());
                    preparedStatement.setString(4,AT_jtf.getText());
                    preparedStatement.setString(5,AA_jtf.getText());
                    preparedStatement.setInt(6,Atotal);
                    preparedStatement.setInt(7,Btotal);
                    preparedStatement.setInt(8,Integer.valueOf(AP_jtf.getText()));
                    preparedStatement.setInt(9,Integer.valueOf(BP_jtf.getText()));
                    preparedStatement.setString(10,FI_jtf.getSelectedItem().toString());
                    preparedStatement.execute();

                    Warning_info warning_info = new Warning_info("������ӳɹ�");
                    CI_jtf.setText("");
                    DT_jtf.setText("2021-06-25 00:00:00");
                    DA_jtf.setText("");
                    AA_jtf.setText("");
                    AT_jtf.setText("2021-06-25 00:00:00");
                    AP_jtf.setText("");
                    BP_jtf.setText("");

                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });
        JPanel warm = new JPanel();

        JLabel jLabel1 = new JLabel("�±�Ϊ�����İ��ʱ�䰲�ţ�����ϸ�鿴�����ͻ");
        jLabel1.setFont(new Font("���Ŀ���",Font.PLAIN,10));
        jLabel1.setForeground(Color.RED);
        warm.add(jLabel1);
        warm.setBackground(new Color(0xEFFBFB));

        //������ʾ���
        jTable = new JTable(new mytabelmodel1());
        jTable.setBackground(new Color(0xFFEBFCFF,true));
        JScrollPane jScrollPane = new JScrollPane(jTable);
        jScrollPane.setPreferredSize(new Dimension(300,100));
        warm.add(jScrollPane);

        JLabel jLabel = new JLabel("�±�Ϊ�ú����ǵ�ʱ�䰲�ţ�����ϸ�鿴�����ͻ");
        jLabel.setForeground(Color.RED);
        jLabel.setFont(new Font("���Ŀ���",Font.PLAIN,10));
        warm.add(jLabel);
        jTable1 = new JTable(new mytablemodel());
        jTable1.setBackground(new Color(0xFFEBFCFF,true));
        JScrollPane jScrollPane1 = new JScrollPane(jTable1);
        jScrollPane1.setPreferredSize(new Dimension(300,100));
        warm.add(jScrollPane1);
        warm.setPreferredSize(new Dimension(300,300));

        CI_jtf.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {

            }

            @Override
            public void focusLost(FocusEvent e) {
                try{
                    Statement statement = connection.createStatement();
                    String sql = "select * from classes";
                    ResultSet resultSet = statement.executeQuery(sql);
                    Warning_info warning_info;
                    while (resultSet.next())
                    {
                        if (CI_jtf.getText().equals(resultSet.getString("class_id"))){
                            warning_info = new Warning_info("�ð���Ѵ���");
                        }
                    }
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });

        add(text);
        add(warm);
        add(Add);
        setPreferredSize(new Dimension(715,550));
        setBackground(new Color(0xEFFBFB));

    }

    class mytabelmodel1 extends AbstractTableModel {
        private String[] columns = {"�����������������ʱ��", "������������ý���ʱ��"};
        private Object[][] values = new Object[50][2];
        DBHelper dbHelper = new DBHelper();

        public mytabelmodel1() {
            DA_jtf.addFocusListener(new FocusListener() {
                @Override
                public void focusGained(FocusEvent e) {

                }

                @Override
                public void focusLost(FocusEvent e) {
                    Connection connection = dbHelper.getConnection();
                    try {
                        for (int j = 0; j < 50; j++) {
                            values[j][0] = "";
                        }
                        Statement statement = (Statement) connection.createStatement();
                        String sql = "select * from classes where departure_airport = '" +
                                DA_jtf.getText()+"'";

                        ResultSet resultSet = statement.executeQuery(sql);
                        int i = 0;
                        while (resultSet.next()) {
                            values[i][0] = resultSet.getString("departure_time");
                            i++;
                        }
                        jTable.updateUI();
                        jTable1.updateUI();
                    } catch (SQLException event) {
                        event.printStackTrace();
                    }
                }
            });

            AA_jtf.addFocusListener(new FocusListener() {
                @Override
                public void focusGained(FocusEvent e) {

                }

                @Override
                public void focusLost(FocusEvent e) {
                    Connection connection = dbHelper.getConnection();
                    for (int j = 0; j < 50; j++) {
                        values[j][1] = "";
                    }
                    try {
                        Statement statement = (Statement) connection.createStatement();
                        String sql = "select * from classes where arrival_airport ='" +
                                AA_jtf.getText()+"'";
                        ResultSet resultSet = statement.executeQuery(sql);
                        int i = 0;
                        while (resultSet.next()) {
                            values[i][1] = resultSet.getString("arrival_time");
                            i++;
                        }
                        jTable1.updateUI();
                        jTable.updateUI();
                    } catch (SQLException e1) {
                        e1.printStackTrace();
                    }
                }
            });
        }

        public int getColumnCount() {
            return values[0].length;
        }

        public int getRowCount() {
            return values.length;
        }

        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {
            return values[rowIndex][columnIndex];
        }

        public String getColumnName(int column) {
            return columns[column];
        }

    }

    class mytablemodel extends AbstractTableModel{
        private String[] columns = {"��ʼʹ��ʱ��","ʹ�ý���ʱ��"};
        private Object[][] values = new Object[50][2];
        DBHelper dbHelper = new DBHelper();

        public mytablemodel(){
            FI_jtf.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    for (int j = 0;j < 50;j++){
                        values[j][0] = "";
                        values[j][1] = "";
                    }
                    if (!FI_jtf.getSelectedItem().toString().equals("��ѡ�񺽰��"));
                    Connection connection = dbHelper.getConnection();
                    try{
                        Statement statement = (Statement) connection.createStatement();
                        String sql = "select * from classes where flight_id ='" +
                                FI_jtf.getSelectedItem().toString()+"'";
                        ResultSet resultSet = statement.executeQuery(sql);
                        int i = 0;
                        while (resultSet.next()){
                            values[i][0] = resultSet.getString("departure_time");
                            values[i][1] = resultSet.getString("arrival_time");
                            i++;
                        }
                        jTable.updateUI();
                        jTable1.updateUI();
                    }
                    catch (SQLException e1){
                        e1.printStackTrace();
                    }
                }
            });
        }

        public int getColumnCount() {return values[0].length;}

        public int getRowCount() {return values.length;}

        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {
            return values[rowIndex][columnIndex];
        }
        public String getColumnName(int column){return columns[column];}
    }
}

class deleteFlight extends JPanel{
    protected JTextField DT;
    protected JTextField DA;
    protected JTextField AT;
    protected JTextField AA;
    protected JTextField AN;
    protected JTextField BN;
    protected JTextField AP;
    protected JTextField BP;

    protected JButton delete;

    protected DBHelper dbHelper = new DBHelper();

    protected JComboBox<String> CI;

    public deleteFlight(){
        Connection connection = dbHelper.getConnection();
        JPanel DTjpl = new JPanel();
        JPanel DAjpl = new JPanel();
        JPanel ATjpl = new JPanel();
        JPanel AAjpl = new JPanel();
        JPanel ANjpl = new JPanel();
        JPanel BNjpl = new JPanel();
        JPanel APjpl = new JPanel();
        JPanel BPjpl = new JPanel();
        JPanel CIjpl = new JPanel();

        DT = new JTextField(15);
        DA = new JTextField(15);
        AT = new JTextField(15);
        AA = new JTextField(15);
        AN = new JTextField(15);
        BN = new JTextField(15);
        AP = new JTextField(15);
        BP = new JTextField(15);
        CI = new JComboBox<>();

        CI.addItem("��ѡ���κ�");
        try {
            Statement statement = (Statement) connection.createStatement();
            String sql = "select * from classes;";
            ResultSet resultSet = statement.executeQuery(sql);
            while (resultSet.next()){
                CI.addItem(resultSet.getString("class_id"));
            }
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        CI.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    Statement statement = (Statement) connection.createStatement();
                    String sql = "select * from classes where class_id = '" +
                            CI.getSelectedItem().toString()+"'";
                    ResultSet resultSet = statement.executeQuery(sql);
                    resultSet.next();
                    DT.setText(resultSet.getString("departure_time"));
                    DA.setText(resultSet.getString("departure_airport"));
                    AT.setText(resultSet.getString("arrival_time"));
                    AA.setText(resultSet.getString("arrival_airport"));
                    AP.setText(resultSet.getString("a_price"));
                    BP.setText(resultSet.getString("b_price"));
                    AN.setText(resultSet.getString("a_number"));
                    BN.setText(resultSet.getString("b_number"));
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });

        DTjpl.add(new JLabel("����ʱ�䣺"));
        DTjpl.add(DT);
        DTjpl.setBackground(new Color(0xEFFBFB));
        DAjpl.add(new JLabel("����������"));
        DAjpl.add(DA);
        DAjpl.setBackground(new Color(0xEFFBFB));
        ATjpl.add(new JLabel("����ʱ�䣺"));
        ATjpl.add(AT);
        ATjpl.setBackground(new Color(0xEFFBFB));
        AAjpl.add(new JLabel("���������"));
        AAjpl.add(AA);
        AAjpl.setBackground(new Color(0xEFFBFB));
        ANjpl.add(new JLabel("�������Ʊ��"));
        ANjpl.add(AN);
        ANjpl.setBackground(new Color(0xEFFBFB));
        BNjpl.add(new JLabel("���ò���Ʊ��"));
        BNjpl.add(BN);
        BNjpl.setBackground(new Color(0xEFFBFB));
        APjpl.add(new JLabel("����ռ۸�"));
        APjpl.add(AP);
        APjpl.setBackground(new Color(0xEFFBFB));
        BPjpl.add(new JLabel("���òռ۸�"));
        BPjpl.add(BP);
        BPjpl.setBackground(new Color(0xEFFBFB));
        CIjpl.add(new JLabel("��κţ�"));
        CIjpl.add(CI);
        CIjpl.setBackground(new Color(0xEFFBFB));
        delete = new JButton("ȷ��ȡ���ú���");

        delete.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String sqlp = "delete from passengers where class_id = '" +
                            CI.getSelectedItem().toString()+"'";
                    PreparedStatement preparedStatement = connection.prepareStatement(sqlp);

                    String sql = "delete from classes where class_id = '" +
                            CI.getSelectedItem().toString()+"'";
                    PreparedStatement preparedStatement1 = connection.prepareStatement(sql);
                    preparedStatement.execute();
                    preparedStatement1.execute();
                    Warning_info warning_info = new Warning_info("���ȡ���ɹ�");
                }
                catch (SQLException e1){
                    e1.printStackTrace();
                }
            }
        });

        JLabel jLabel = new JLabel("ȡ��������");
        jLabel.setFont(new Font("���Ŀ���",Font.PLAIN,50));
        setPreferredSize(new Dimension(715,550));

        JPanel jPanel = new JPanel(new GridLayout(4,2));
        jPanel.setBackground(new Color(0xEFFBFB));
        jPanel.setPreferredSize(new Dimension(700,300));
        jPanel.add(DTjpl);
        jPanel.add(ATjpl);
        jPanel.add(DAjpl);
        jPanel.add(AAjpl);
        jPanel.add(ANjpl);
        jPanel.add(BNjpl);
        jPanel.add(APjpl);
        jPanel.add(BPjpl);

        JPanel panel = new JPanel();
        panel.setBackground(new Color(0xEFFBFB));
        panel.setPreferredSize(new Dimension(700,50));
        panel.add(CIjpl);
        panel.add(delete);

        setPreferredSize(new Dimension(715,550));
        setBackground(new Color(0xEFFBFB));

        add(jLabel);
        add(jPanel);
        add(panel);
    }
}