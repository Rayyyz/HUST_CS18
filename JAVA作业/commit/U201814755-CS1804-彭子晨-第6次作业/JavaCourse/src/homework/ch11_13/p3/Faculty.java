package homework.ch11_13.p3;

public class Faculty extends Person{

    /**
     * 教工Id
     */
    private int facultyId;

    /**
     * 职称
     */
    private String title;

    /**
     * 邮箱
     */
    private String email;

    public Faculty(){}
    public Faculty(String name,int age,int facultyId,String title,String email){
        super(name,age);
        this.facultyId = facultyId;
        this.title = title;
        this.email = email;
    }

    public int getFacultyId(){
        return this.facultyId;
    }

    public void setFacultyId(int facultyId) {
        this.facultyId = facultyId;
    }

    public String getTitle() {
        return this.title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getEmail() {
        return this.email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        return "name: "+getName()+", age: "+getAge()
                +", facultyId: "+getFacultyId()
                +", title: "+getTitle()+", email: "+getEmail();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Faculty){
            return  super.equals(obj)
                    && this.facultyId==((Faculty) obj).facultyId
                    && this.email.equals(((Faculty) obj).email)
                    && this.title.equals(((Faculty) obj).title);
        }
        return false;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        Faculty f = (Faculty) super.clone();
        f.title = new String(this.title);
        f.email = new String(this.email);
        f.facultyId = this.facultyId;
        return f;
    }
}
