package homework.ch11_13.p3;

public class Student extends Person {
    /**
     * 所在班级
     */
    private String classNo;

    /**
     * 所在院系
     */
    private String department;

    /**
     * 学生Id
     */
    private int studentId;

    public Student(){}
    public Student(String name,int age,int studentId,String department,String classNo){
        super(name,age);
        this.studentId = studentId;
        this.department = department;
        this.classNo = classNo;
    }

    public String getDepartment(){
        return department;
    }
    public void setDepartment(String department){
        this.department = department;
    }

    public String getClassNo(){
        return this.classNo;
    }
    public void setClassNo(String classNo){
        this.classNo = classNo;
    }

    public int getStudentId(){
        return this.studentId;
    }
    public void setStudentId(int studentId) {
        this.studentId = studentId;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        Student s = (Student) super.clone();
        s.department = new String(this.department);
        s.classNo = new String(this.classNo);
        s.studentId = this.studentId;
        return s;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Student){
            return super.equals(obj)
                    && this.studentId==((Student) obj).studentId
                    && this.classNo.equals(((Student) obj).classNo)
                    && this.department.equals(((Student) obj).department);
        }
        return false;
    }

    @Override
    public String toString() {
        return "name: "+getName()+", age: "+getAge()
                +", studentId: "+getStudentId()
                +", department: "+getDepartment()
                +", classNo: "+getClassNo();
    }
}
