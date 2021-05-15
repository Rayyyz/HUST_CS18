package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.LengthTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.PatternTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.StopWordTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.TermTupleScanner;

import java.io.*;
/**
 * <pre>
 * AbstractDocumentBuilder是Document构造器的抽象父类.
 *      Document构造器的功能应该是由解析文本文档得到的TermTupleStream，产生Document对象.
 * </pre>
 */
public class DocumentBuilder extends AbstractDocumentBuilder {
    /**
     * <pre>
     * 由解析文本文档得到的TermTupleStream,构造Document对象.
     * @param docId             : 文档id
     * @param docPath           : 文档绝对路径
     * @param termTupleStream   : 文档对应的TermTupleStream
     * @return ：Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream) throws IOException{
        AbstractDocument document = new Document(docId,docPath);
        AbstractTermTuple tuple = termTupleStream.next();
        while (tuple != null){
            document.addTuple(tuple);
            tuple = termTupleStream.next();
        }
        termTupleStream.close();

        return document;
    }
    /**
     * <pre>
     * 由给定的File,构造Document对象.
     * 该方法利用输入参数file构造出AbstractTermTupleStream子类对象后,内部调用
     *      AbstractDocumenv b vt build(int docId, String docPath, AbstractTermTupleStream termTupleStream)
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param file      : 文档对应File对象
     * @return          : Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        AbstractDocument document = null;
        AbstractTermTupleStream ts = null;
        try {
            ts= new TermTupleScanner(new BufferedReader(new InputStreamReader(new
                    FileInputStream(file))));
            ts = new StopWordTermTupleFilter(ts); //停用词过滤
            ts = new PatternTermTupleFilter(ts);  //正则表达式过滤
            ts = new LengthTermTupleFilter(ts);   //单词长度过滤
            document = build(docId,docPath,ts);
        }
        catch (Exception e){
            e.printStackTrace();
        }
        finally {
            ts.close();
        }

        return document;
    }
}
