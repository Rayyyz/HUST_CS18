package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

import java.io.IOException;
/**
 * 抽象类AbstarctTermTupleFilter的子类
 * 功能：
 *      基于正则表达式，过滤非英文字符
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     * @param input : 输入流
     * */
    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    /**
     * 获得下一个三元组
     * 基于正则表达式，过滤非英文字符
     * @return 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        AbstractTermTuple termTuple = input.next();
        if(termTuple==null) return null;
        while (!termTuple.term.getContent().matches(Config.TERM_FILTER_PATTERN)){
            termTuple = input.next();
            if(termTuple==null) return null;
        }
        return termTuple;
    }



}
