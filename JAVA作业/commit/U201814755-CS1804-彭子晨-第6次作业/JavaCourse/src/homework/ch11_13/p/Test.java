package homework.ch11_13.p;

public class Test {
    public static void main(String[] args){
        //测试三个具体类
        System.out.println("1. 测试三个具体类");
        TaskA p1 = new TaskA();
        p1.execute();
        TaskB p2 = new TaskB();
        p2.execute();
        TaskC p3 = new TaskC();
        p3.execute();

        //实例化多个具体的任务类对象和TaskService对象,并由TaskService对象执行这些任务
        System.out.println("2. 启动TaskService对象按213顺序添加任务并执行");
        TaskServiceImpl taskServiceImpl = new TaskServiceImpl();
        taskServiceImpl.execute();

        //添加三个具体类的任务，顺序为213
        taskServiceImpl.addTask(p2);
        taskServiceImpl.addTask(p1);
        taskServiceImpl.addTask(p3);

        //执行任务
        taskServiceImpl.executeTasks();
    }
}
