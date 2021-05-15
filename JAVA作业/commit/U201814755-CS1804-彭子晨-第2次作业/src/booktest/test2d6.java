package booktest;

import java.util.Scanner;

/**
 * （求一个整数个位数的和）编写程序，读取一个在0~1000之间的整数，并将该整数的各位数字相加。
 * 例如：整数是932，各位数字之和为9+3+2=14
 */
public class test2d6 {
    public static void main(String args[]){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number between 0 and 1000:");
        int num = scanner.nextInt();
        int res = 0;

        while(num>0){
            res += num%10;
            num/=10;
        }

        System.out.println("The sum of the digits is "+ res);
    }
}
