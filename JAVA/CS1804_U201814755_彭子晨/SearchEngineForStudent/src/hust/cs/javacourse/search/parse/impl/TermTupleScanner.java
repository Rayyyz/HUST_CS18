package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Queue;
/**
 * 抽象类AbstractTermTupleScanner的子类
 * 需要实现next方法获得文本文件里的三元组
 */
public class TermTupleScanner extends AbstractTermTupleScanner {
    /**
     * 无参构造函数
     */
    public TermTupleScanner(){}

    /**
     * 构造函数
     * @param input：缓冲输入
     */
    public TermTupleScanner(BufferedReader input){
        super(input);
    }

    Queue<AbstractTermTuple> buf = new LinkedList<>();
    int pos = 0;

    /**
     * 获得下一个三元组
     * @return 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() throws IOException{
        //如果队列中有三元组，则抛出第一个三元组并在队列中删除
        if(buf.size()!=0){
            return buf.poll();
        }
        //如果队列中没有三元组，则读入新行并解析获得三元组存入buf队列中
        String str = input.readLine();
        if(str == null) return null;
        //过滤空行
        while (str.trim().length()==0){
            str = input.readLine();
            if(str == null) return null;
        }
        //分离单词
        StringSplitter splitter = new StringSplitter();
        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
        for(String word : splitter.splitByRegex(str)){
            TermTuple tuple = new TermTuple();
            tuple.term = new Term(word.toLowerCase());
            tuple.curPos = pos;
            buf.add(tuple);
            pos++;
        }
        //抛出第一个三元组并在队列中删除
        return buf.poll();
    }
}
