package homework.ch11_13.p3;

public class Person implements Cloneable{
    /**
     * 姓名
     */
    private String name;

    /**
     * 年龄
     */
    private int age;

    /**
     * 缺省构造函数
     */
    public Person(){}

    /**
     * 构造函数
     * @param name-姓名
     * @param age-年龄
     */
    public Person(String name, int age){
        this.name = name;
        this.age = age;
    }

    /**
     * 获取姓名
     * @return 姓名
     */
    public String getName(){
        return this.name;
    }

    /**
     * 设置姓名
     * @param name-姓名
     */
    public void setName(String name){
        this.name = name;
    }

    /**
     * 获取年龄
     * @return 年龄
     */
    public int getAge(){
        return this.age;
    }

    /**
     * 设置年龄
     * @param age-年龄
     */
    public void setAge(int age){
        this.age = age;
    }

    /**
     * 覆盖toString
     * @return 描述Person对象信息的字符串
     */
    @Override
    public String toString() {
        return "name: "+this.name+", age: "+this.age;
    }

    /**
     * 比较两个Person对象的内容是否相等
     * @param obj-另外一个对象
     * @return 当二个对象所有数据成员的内容相等，返回true
     */
    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Person) {
                return this.name.equals(((Person) obj).name)
                        && this.age==((Person) obj).age;
        }
        return false;
    }

    /**
     * Person的深拷贝克隆
     * @return 克隆出来的对象
     * @throws CloneNotSupportedException
     */
    @Override
    protected Object clone() throws CloneNotSupportedException{
        Person p = (Person) super.clone();
        p.name = new String(this.name);
        p.age = this.age;
        return p;
    }
}
