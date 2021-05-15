package homework.ch11_13.p;


import java.util.ArrayList;

/**
 * 实现TaskService接口
 * @author touko
 */
public class TaskServiceImpl implements TaskService {
    /**
     * tasks保存要执行的任务
     */
    ArrayList<Task> tasks = new ArrayList<>();

    /**
     * 执行任务队列中的任务
     */
    @Override
    public void executeTasks() {
        for(Task task : tasks){
            task.execute();
        }
    }

    /**
     * 向任务队列添加任务
     * @param t 新添加的任务
     */
    @Override
    public void addTask(Task t) {
        tasks.add(t);
    }

    /**
     * TaskServiceImpl启动
     */
    public void execute(){
        System.out.println("TaskServiceImpl executed.");
    }
}