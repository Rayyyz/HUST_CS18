package lab2;

import java.lang.reflect.Array;
import java.util.Random;

//假设一个车牌号码由三个大写字母和后面的四个数字组成。编写一个程序. 随机生
//成5个不重复的车牌号码。
public class randomGenerator {
    static public void main(String[] args){
        int n = 5, i= 0;
        //记录车牌
        String[] arr = new String[n];
        //生成五个车牌
        while(i<n){
            //随机生成车牌
            char c1 = (char)((Math.random()*26)+'A');
            char c2 = (char)((Math.random()*26)+'A');
            char c3 = (char)((Math.random()*26)+'A');
            char d1=(char)(Math.random()*10+'0');
            char d2=(char)(Math.random()*10+'0');
            char d3=(char)(Math.random()*10+'0');
            char d4=(char)(Math.random()*10+'0');

            //存入字符串
            arr[i] = String.valueOf(c1)+c2+c3+d1+d2+d3+d4;

            //比较是否有重复
            for(int j=0;j<i;j++){
                //有重复则直接重新随机第i个车牌
                if(arr[i].equals(arr[j])) continue;
            }
            //无重复则打印车牌，并且i++
            System.out.println(i+1+":"+arr[i]);
            i++;
        }
    }

}
