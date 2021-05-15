package lab1;

import java.lang.reflect.Array;
import java.util.Locale;
import java.util.Scanner;

//编写程序，从控制台或对话框任意输入一个英文字符串，统计字符串中每个英文字母出现的次数并输出到控制台（大小写不敏感）。
public class CountLetters {
    public static void main(String[] args){
        //建立26个字母的统计数组
        int[] arr = new int[26];
        //输入字符串
        Scanner scanner = new Scanner(System.in);
        String s = scanner.next();
        //统计
        for(int i=0;i<s.length();i++){
            arr[s.toLowerCase().charAt(i)-'a'] += 1;
        }
        //输出到控制台
        for(int i=0;i<26;i++){
           System.out.println((char)('a'+i)+":"+arr[i]);
        }
    }
}
