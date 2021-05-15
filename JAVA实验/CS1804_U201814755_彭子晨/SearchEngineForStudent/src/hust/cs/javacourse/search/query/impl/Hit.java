package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;

import java.util.Map;
/**
 * <pre>
 * AbstractHit是一个搜索命中结果的抽象类. 该类子类要实现Comparable接口.
 * 实现该接口是因为需要必须比较大小，用于命中结果的排序.
 * </pre>
 */
public class Hit extends AbstractHit {
    /**
     *无参构造函数
     */
    public Hit(){}
    /**
     * 构造函数
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     */
    public Hit(int docId, String docPath) {
        super(docId, docPath);
    }

    /**
     * 构造函数
     * @param docId              ：文档id
     * @param docPath            ：文档绝对路径
     * @param termPostingMapping ：命中的三元组列表
     */
    public Hit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping) {
        super(docId, docPath, termPostingMapping);
    }
    /**
     * 获得文档id
     * @return ： 文档id
     */
    @Override
    public int getDocId() {
        return this.docId;
    }

    /**
     * 获得文档绝对路径
     * @return ：文档绝对路径
     */
    @Override
    public String getDocPath() {
        return this.docPath;
    }

    /**
     * 获得文档内容
     * @return ： 文档内容
     */
    @Override
    public String getContent() {
        return this.content;
    }

    /**
     * 设置文档内容
     * @param content ：文档内容
     */
    @Override
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 获得文档得分
     * @return ： 文档得分
     */
    @Override
    public double getScore() {
        return this.score;
    }

    /**
     * 设置文档得分
     * @param score ：文档得分
     */
    @Override
    public void setScore(double score) {
        this.score = score;
    }

    /**
     * 获得命中的单词和对应的Posting键值对
     * @return ：命中的单词和对应的Posting键值对
     */
    @Override
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping() {
        return termPostingMapping;
    }

    /**
     * 获得命中结果的字符串表示, 用于显示搜索结果.
     * 高亮显示搜索关键词
     * @return : 命中结果的字符串表示
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("-----------------------------\n");
        builder.append("docId: ").append(docId).append("\n");
        builder.append("docPath: ").append(docPath).append("\n");
        builder.append("content: ").append(content).append("\n");
        builder.append("score: ").append(-score).append("\n");
        builder.append("TermPostingMapping: ").append("\n");
        for(Map.Entry<AbstractTerm,AbstractPosting> entry: termPostingMapping.entrySet()){
            builder.append(entry.getKey().toString()).append("\t---->\t");
            builder.append(entry.getValue().toString()).append("\n");;
        }
        return builder.toString();
    }

    /**
     * 根据score比较二个命中结果的大小
     * @param o ：要比较的名字结果
     * @return ：二个命中结果得分的差值
     */
    @Override
    public int compareTo(AbstractHit o) {
        //从大到小排序
        return (int)(getScore()-o.getScore());
    }
}
