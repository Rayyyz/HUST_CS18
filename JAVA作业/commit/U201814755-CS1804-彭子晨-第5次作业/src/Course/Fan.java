package Course;


public class Fan {
    static final int SLOW =1;
    static final int MEDIUM =2;
    static final int FAST = 3;

    private int speed;      //风扇速度
    private boolean on;     //风扇是否开启
    private double radius;  //风扇半径
    String color;           //风扇颜色

    /**
     * 无参构造函数
     */
    public Fan(){
        this.speed = SLOW;
        this.on = false;
        this.radius = 5.0;
        this.color = "blue";
    }

    /**
     * toString()
     */
    public String toString(){
        if(this.on == true){
            String onmsg = this.speed+","+this.color+","+this.radius;
            return onmsg;
        }else {
            String offmsg = "fan is off."+this.color+","+this.radius;
            return offmsg;
        }
    }

    /**
     * speed访问及设置
     */
    public int getSpeed(){
        return this.speed;
    }
    public void setSpeed(int newSpeed){
        this.speed = newSpeed;
    }

    /**
     * on访问及设置
     */
    public boolean getOn(){
        return this.on;
    }
    public void setOn(boolean newOn){
        this.on = newOn;
    }
    /**
     * radius访问及设置
     */
    public double getRadius(){
        return this.radius;
    }
    public void setRadius(double newRadius){
        this.radius = newRadius;
    }
    /**
     * color访问及设置
     */
    public String getColor(){
        return this.color;
    }
    public void setColor(String newColor){
        this.color = newColor.substring(0);
    }


    /**
     * main
     */
    public static void main(String[] args){
        Fan f1 = new Fan();
        Fan f2 = new Fan();

        f1.setOn(true);
        f1.setSpeed(FAST);
        f1.setRadius(10);
        f1.setColor("yellow");

        f2.setOn(false);
        f2.setSpeed(MEDIUM);
        f2.setRadius(5);
        f2.setColor("blue");

        System.out.println(f1.toString());
        System.out.println(f2.toString());

    }
}
