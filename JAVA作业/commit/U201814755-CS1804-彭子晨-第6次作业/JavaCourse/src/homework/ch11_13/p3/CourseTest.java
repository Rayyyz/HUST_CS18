package homework.ch11_13.p3;

import java.util.ArrayList;
import java.util.List;

public class CourseTest {
    /**
     * 程序入口函数 在这里实例化教师对象、课程对象。同时实例化多个学生对象向课程注册。
     * 需要创建一个Course数组，包含至少二门课程，每门课程至少注册三名学生。
     * 最后打印出每门课程的详细信息。
     * 同时测试Person、Student、Faculty、Course的深拷贝功能，
     * 深拷贝测试包括： 克隆出来的对象和源对象内容相等；
     *              克隆出来的对象和源对象所有引用类型数据成员指向的是不同对象
     * @param args - 命令行参数
     * @throws CloneNotSupportedException
     */
    public static void main(String[] args) throws CloneNotSupportedException{
        Person teacher = new Faculty("James Gosling",65,0000,"Professor",
                "http://nighthacks.com/jag/bio/index.html");
        Course javaCourse = new Course("Java Language Programming",teacher);
        Person student1 = new Student("aaa",20,20170101,"CS","CS1704");
        Person student2 = new Student("bbb",20,20170102,"CS","CS1705");
        Person student3 = new Student("ccc",20,20170103,"CS","CS1706");
        javaCourse.register(student1);
        javaCourse.register(student2);
        javaCourse.register(student3);
        System.out.println(javaCourse); //打印课程详细信息
        javaCourse.unregister(student3);
        System.out.println(javaCourse);
        //测试是否为深拷贝
        Course javaCourse2 = (Course)javaCourse.clone();
        System.out.println(javaCourse.equals(javaCourse2)); //测试对象内容是否相等
        System.out.println(javaCourse != javaCourse2);
        System.out.println(javaCourse.getCourseName() != javaCourse2.getCourseName());
        System.out.println(javaCourse.getTeacher() != javaCourse2.getTeacher());
        System.out.println(javaCourse.getStudents() != javaCourse2.getStudents());
        System.out.println(javaCourse2);

        //创建courses数组,存储课程
//        List<Course> courses = new ArrayList<>();
//
//        //创建老师1：Mary,老师2：Emma
//        Faculty teacher1 = new Faculty("Mary",25,1203,"Master","mary@11.com");
//        Faculty teacher2 = new Faculty("Emma",38,1004,"Professor","emma@22.com");
//
//        //创建学生1：Amy,学生2：Bob,学生3:Candy,学生4：David,学生5：Emily,学生6：Frank
//        Student student1 = new Student("Amy",20,10001,"ComputerScience","CS2012");
//        Student student2 = new Student("Bob",20,20002,"ComputerScience","CS2005");
//        Student student3 = new Student("Candy",21,20003,"ChineseLanguage","CL1910");
//        Student student4 = new Student("David",21,30004,"ChineseLanguage","CL1901");
//        Student student5 = new Student("Emily",21,30005,"MusicTheory","MT1902");
//        Student student6 = new Student("Frank",22,30006,"ComputerScience","CS1804");
//
//        //创建课程1：Math,课程2：English
//        Course course1 = new Course("Math",teacher1);
//        Course course2 = new Course("English",teacher2);
//
//        //课程1注册学生1,2,3；课程2注册学生4,5,6
//        course1.register(student1);
//        course1.register(student2);
//        course1.register(student3);
//        course2.register(student4);
//        course2.register(student5);
//        course2.register(student6);
//        courses.add(course1);
//        courses.add(course2);
//
//        //打印课程信息
//        System.out.println("-------1. Courses Data-------");
//        for(Course course : courses){
//            System.out.println(course.toString());
//        }
//
//        //深拷贝测试
//        System.out.println("-------2. Clone Test-------");
//        //测试Person深拷贝对象
//        System.out.println("-------Person clone-------");
//        Person p0 = new Person("Person0",19);
//        Person p1 = (Person)p0.clone();
//        System.out.println(p0.toString());
//        System.out.println(p1.toString());
//        System.out.println("被拷贝对象Name修改为AAA之后：");
//        p0.setName("AAA");
//        System.out.println(p0.toString());
//        System.out.println(p1.toString());
//        System.out.println("");
//
//        //测试Student深拷贝对象
//        System.out.println("-------Student clone-------");
//        Student s0 = new Student("Student0",18,10000,"CS","CS1804");
//        Student s1 = (Student)s0.clone();
//        System.out.println(s0.toString());
//        System.out.println(s1.toString());
//        System.out.println("被拷贝对象ClassNo修改为GE1901,id改为9999之后：");
//        s0.setClassNo("GE1901");
//        s0.setStudentId(9999);
//        System.out.println(s0.toString());
//        System.out.println(s1.toString());
//        System.out.println("");
//
//        //测试Faculty深拷贝对象
//        System.out.println("-------Faculty clone-------");
//        Faculty f0 = new Faculty("Faculty0",25,2333,"Master","aaa@123.com");
//        Faculty f1 = (Faculty) f0.clone();
//        System.out.println(f0.toString());
//        System.out.println(f1.toString());
//        System.out.println("被拷贝对象name修改为F1,拷贝对象title改为Professor之后：");
//        f0.setName("F1");
//        f1.setTitle("Professor");
//        System.out.println(f0.toString());
//        System.out.println(f1.toString());
//        System.out.println("");
//
//        //测试Course深拷贝对象
//        System.out.println("-------Course clone-------");
//        Course c0 = new Course("Course0",f0);
//        Course c1 = (Course) c0.clone();
//        System.out.println(c0.toString());
//        System.out.println(c1.toString());
//        System.out.println("被拷贝对象注册了两个学生之后：");
//        c0.register(s0);
//        c0.register(s1);
//        System.out.println(c0.toString());
//        System.out.println(c1.toString());
//        System.out.println("");
//
//        System.out.println("测试完毕。深拷贝测试结果成功，克隆对象");
    }
}
