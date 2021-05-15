package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.*;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * AbstractIndex的具体实现类
 */
public class Index extends AbstractIndex {

    public Index(){}

    /**
     * 返回索引的字符串表示
     *
     * @return 索引的字符串表示
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("docId-----docPath mapping\n");
        for(Map.Entry<Integer,String> entry: docIdToDocPathMapping.entrySet()){
            builder.append(entry.getKey());
            builder.append("\t---->\t");
            builder.append(entry.getValue());
            builder.append("\n");
        }
        builder.append("PostingList:\n");
        for(Map.Entry<AbstractTerm,AbstractPostingList> entry: termToPostingListMapping.entrySet()){
            builder.append(entry.getKey().toString());
            builder.append("\t---->\t");
            builder.append(entry.getValue().toString());
            builder.append("\n");
        }
        return builder.toString();
    }

    /**
     * 添加文档到索引，更新索引内部的HashMap
     *
     * @param document ：文档的AbstractDocument子类型表示
     */
    @Override
    public void addDocument(AbstractDocument document) {
        docIdToDocPathMapping.put(document.getDocId(),document.getDocPath());
        for(AbstractTermTuple termTuple: document.getTuples()){
            if(!termToPostingListMapping.containsKey(termTuple.term)){
                //如果不包含单词
                Posting posting = new Posting();
                posting.setDocId(document.getDocId());
                posting.setFreq(termTuple.freq);
                List<Integer> positions = new ArrayList<>();
                positions.add(termTuple.curPos);
                posting.setPositions(positions);

                termToPostingListMapping.put(termTuple.term,new PostingList());
                termToPostingListMapping.get(termTuple.term).add(posting);
            } else {
                //已经包含了该单词
                boolean flag = false;
                for(int i = 0; i < termToPostingListMapping.get(termTuple.term).size();i++){
                    if(termToPostingListMapping.get(termTuple.term).get(i).getDocId() == document.getDocId()){
                        //假设postingList中该文档之前已有过同个单词,则在positions列表加入新的pos,并使freq+1
                        termToPostingListMapping.get(termTuple.term).get(i).getPositions().add(termTuple.curPos);
                        termToPostingListMapping.get(termTuple.term).get(i).setFreq(termToPostingListMapping.get(termTuple.term).get(i).getFreq()+1);
                        flag = true;
                    }
                }
                if(!flag){
                    //如果这个单词是postingList中该文档的首个单词，则为这个单词的postingList新建一个posting
                    Posting posting = new Posting();
                    posting.setDocId(document.getDocId());
                    posting.setFreq(termTuple.freq);
                    List<Integer> positions = new ArrayList<>();
                    positions.add(termTuple.curPos);
                    posting.setPositions(positions);
                    termToPostingListMapping.get(termTuple.term).add(posting);
                }
            }
        }
        optimize();
    }

    /**
     * <pre>
     * 从索引文件里加载已经构建好的索引.内部调用FileSerializable接口方法readObject即可
     * @param file ：索引文件
     * </pre>
     */
    @Override
    public void load(File file) {
        if(file==null) return;
        try {
            readObject(new ObjectInputStream(new FileInputStream(file)));
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * <pre>
     * 将在内存里构建好的索引写入到文件. 内部调用FileSerializable接口方法writeObject即可
     * @param file ：写入的目标索引文件
     * </pre>
     */
    @Override
    public void save(File file) {
        try {
            writeObject(new ObjectOutputStream(new FileOutputStream(file)));
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 返回指定单词的PostingList
     *
     * @param term : 指定的单词
     * @return ：指定单词的PostingList;如果索引字典没有该单词，则返回null
     */
    @Override
    public AbstractPostingList search(AbstractTerm term) {
        return termToPostingListMapping.get(term);
    }

    /**
     * 返回索引的字典.字典为索引里所有单词的并集
     *
     * @return ：索引中Term列表
     */
    @Override
    public Set<AbstractTerm> getDictionary() {
        return termToPostingListMapping.keySet();
    }

    /**
     * <pre>
     * 对索引进行优化，包括：
     *      对索引里每个单词的PostingList按docId从小到大排序
     *      同时对每个Posting里的positions从小到大排序
     * 在内存中把索引构建完后执行该方法
     * </pre>
     */
    @Override
    public void optimize() {
        for(Map.Entry<AbstractTerm,AbstractPostingList> entry: termToPostingListMapping.entrySet()){
            //按positions对postingList排序
            for(int i=0;i<entry.getValue().size();i++){
                entry.getValue().get(i).sort();
            }
            //按docId对Posting排序
            entry.getValue().sort();
        }
    }

    /**
     * 根据docId获得对应文档的完全路径名
     *
     * @param docId ：文档id
     * @return : 对应文档的完全路径名
     */
    @Override
    public String getDocName(int docId) {
        return docIdToDocPathMapping.get(docId);
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(docIdToDocPathMapping.size());
            out.writeObject(termToPostingListMapping.size());
            for (Map.Entry<Integer,String> entry : docIdToDocPathMapping.entrySet()){
                out.writeObject(entry.getKey());
                out.writeObject(entry.getValue());
            }
            for (Map.Entry<AbstractTerm,AbstractPostingList> entry : termToPostingListMapping.entrySet()){
                entry.getKey().writeObject(out);
                entry.getValue().writeObject(out);
            }
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     *
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try {
            int docSize = (Integer)in.readObject();
            int termSize = (Integer)in.readObject();
            for(int i=0;i<docSize;i++){
                Integer docId = (Integer) in.readObject();
                String docPath = (String) in.readObject();
                docIdToDocPathMapping.put(docId,docPath);
            }
            for(int i=0;i<termSize;i++){
                AbstractTerm term = new Term();
                AbstractPostingList postingList = new PostingList();
                term.readObject(in);
                postingList.readObject(in);
                termToPostingListMapping.put(term,postingList);
            }
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

}
