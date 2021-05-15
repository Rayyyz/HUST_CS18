package Test3;

import java.util.Scanner;

public class Test3 {
    /**
     * 主函数
     * 输入进行测试
     * @param args
     */
   public static void main(String[] args){
       Scanner scanner = new Scanner(System.in);
       System.out.println("请输入row: ");
       int row = scanner.nextInt();
       int[][] array = createArray(row);
       printArray(array);
   }
    /**
     *  创建一个不规则二维数组
     *  第一行row列
     *  第二行row - 1列
     *  ...
     *  最后一行1列
     *	数组元素值都为默认值
     * @param row 行数
     * @return 创建好的不规则数组
     */
    public static int[][] createArray(int row){
        if(row<=0) {
            System.out.println("row小于等于零！");
            return null;
        }
        int[][] arr = new int[row][];
        for(int i=0;i<row;i++){
            arr[i] = new int[row-i];
        }
        return arr;
    }

    /**
     * 逐行打印出二维数组，数组元素之间以空格分开
     * @param a
     */
    public static void printArray(int[][] a){
        if(a==null){
            System.out.println("数组为null！");
            return;
        }
        for(int i=0;i<a.length;i++) {
            for (int j = 0; j < a[i].length; j++) {
                System.out.print(a[i][j]+" ");
            }
            System.out.print("\n");
        }
    }
}
