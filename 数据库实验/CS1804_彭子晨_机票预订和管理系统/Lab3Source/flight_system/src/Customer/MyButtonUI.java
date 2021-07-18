package Customer;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.geom.RoundRectangle2D;

public class MyButtonUI extends JButton {
    private static final long serialVersionUID = 39082560987930759L;
    public Color BUTTON_COLOR1 = new Color(93,225,189,225);
    public Color BUTTON_COLOR2 = new Color(35,252,119);
    public static final Color BUTTON_FOREGROUND_COLOR = Color.BLACK;

    private boolean hover;

    public void setButtonColor(Color color1,Color color2){
        BUTTON_COLOR1 = color1;
        BUTTON_COLOR2 = color2;
    }

    public MyButtonUI(String name) {
        this.setText(name);
        setFont(new Font("ËÎÌו", Font.BOLD, 12));
        setBorderPainted(false);
        setForeground(Color.BLACK);
        setFocusPainted(false);
        setContentAreaFilled(false);
        setForeground(BUTTON_FOREGROUND_COLOR);
        hover = true;
        repaint();

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
            }

            @Override
            public void mouseReleased(MouseEvent e) {

            }
        });
    }

    @Override
    protected void paintComponent(Graphics g) {
        Graphics2D g2d = (Graphics2D) g.create();
        int h = getHeight();
        int w = getWidth();
        float tran = 1F;
        if (!hover){
            tran = 0.3F;
        }

        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        GradientPaint p1;
        GradientPaint p2;
        if (getModel().isPressed()){
            p1 = new GradientPaint(0,0,new Color(67,249,241),0,h-1,new Color(67,249,241));
            p2 = new GradientPaint(0,1,new Color(68,255,247,237),0,h-1,new Color(67,249,241,100));
        }
        else {
            p2 = new GradientPaint(0,1,new Color(68,255,247),0,h-3,new Color(68,255,247,195));

            p1 = new GradientPaint(0, 0, new Color(67, 249, 241), 0, h - 1, new Color(68, 255, 247));
        }
        g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER,tran));
        RoundRectangle2D.Float r2d = new RoundRectangle2D.Float(0,0,w-1,h-1,101,0);
        Shape clip = g2d.getClip();
        g2d.clip(r2d);
        GradientPaint gp = new GradientPaint(0.0F,0.0F,BUTTON_COLOR1,0.0F,h,BUTTON_COLOR2,true);
        g2d.setPaint(gp);
        g2d.fillRect(0,0,w,h);
        g2d.setClip(clip);
        g2d.drawRoundRect(0,0,w-1,h-1,10,10);
        g2d.setPaint(p2);
        g2d.drawRoundRect(1,1,w-3,h-3,9,9);
        g2d.dispose();
        super.paintComponent(g);
    }
}
