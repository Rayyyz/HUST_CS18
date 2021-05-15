package homework.ch11_13.p3;

import java.util.ArrayList;
import java.util.List;

public class Course implements Cloneable{
    /**
     * 课程名称
     */
    private String courseName;

    /**
     * 选修课程的学生列表，保存在ArrayList里
     */
    private List<Person> students;

    /**
     * 课程的授课老师
     */
    private Person teacher;

    public Course(String courseName,Person teacher){
        this.students = new ArrayList<Person>();
        this.courseName = courseName;
        this.teacher = teacher;
    }

    public void register(Person s){
        int index = students.indexOf(s);
        if(index==-1){
            students.add(s);
        }
    }

    public void unregister(Person s){
        int index = students.indexOf(s);
        if(index!=-1){
            students.remove(s);
        }
    }

    public int getNumberOfStudent(){
        return students.size();
    }

    public String getCourseName() {
        return courseName;
    }

    public List<Person> getStudents() {
        return students;
    }

    public Person getTeacher() {
        return teacher;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        Course c = (Course) super.clone();
        c.teacher = (Person) this.teacher.clone();
        c.courseName = new String(this.courseName);
        c.students = new ArrayList<Person>();
        for(Person p : this.students){
            c.register((Person) p.clone());
        }
        return c;
    }

    @Override
    public String toString() {
        String str =  "Course Name: "+getCourseName()+"\n"
                + "Teacher Info: "+getTeacher().toString()+"\n"
                + "Student List: " + "\n";
        for(Person student : students){
            str = str.concat(student.toString());
            str = str.concat("\n");
        }
        str = str.concat("Totally: "+getNumberOfStudent()+" students.\n");
        return str;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Course){
            return this.courseName.equals(((Course) obj).courseName)
                    && this.teacher.equals(((Course) obj).teacher)
                    && this.students.size() == ((Course) obj).students.size()
                    && this.students.containsAll(((Course) obj).students);
        }
        return false;
    }
}
