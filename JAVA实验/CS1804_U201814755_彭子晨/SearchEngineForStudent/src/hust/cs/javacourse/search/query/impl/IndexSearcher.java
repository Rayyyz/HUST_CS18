package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;
import hust.cs.javacourse.search.util.Config;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;
/**
 * <pre>
 *  IndexSearcher是抽象类AbstractIndexSearcher的子类
 *  功能： 检索具体实现
 * </pre>
 */
public class IndexSearcher extends AbstractIndexSearcher {

    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {
        this.index = new Index();
        index.load(new File(indexFile));
    }

    /**
     * 根据单个检索词进行搜索
     * @param queryTerm ：检索词
     * @param sorter ：排序器
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        //忽略大小写
        if(Config.IGNORE_CASE){
            queryTerm.setContent(queryTerm.getContent().toLowerCase());
        }
        AbstractPostingList postingList = index.search(queryTerm);
        if(postingList==null) return new Hit[0];
        List<AbstractHit> res = new ArrayList<>();
        for(int i=0;i<postingList.size();i++){
            AbstractPosting posting = postingList.get(i);
            AbstractHit hit = new Hit(posting.getDocId(),index.getDocName(posting.getDocId()));
            hit.getTermPostingMapping().put(queryTerm,posting);
            hit.setScore(sorter.score(hit));
            res.add(hit);
        }
        sorter.sort(res);
        AbstractHit[] retRes = new AbstractHit[res.size()];
        return res.toArray(retRes);
    }

    /**
     *
     * 根据二个检索词进行搜索
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter ：    排序器
     * @param combine ：   多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        AbstractPostingList postingList1 = index.search(queryTerm1);
        AbstractPostingList postingList2 = index.search(queryTerm2);
        // 如果有一个词语不存在，那就直接返回空的数组
        if(postingList1==null && postingList2==null) return new Hit[0];
        List<AbstractHit> res = new ArrayList<>();

        if(combine == LogicalCombination.AND){  //与要求
            if(postingList1==null || postingList2==null) return new Hit[0];
            //获得交集
            for(int i=0;i< postingList1.size();i++){
                int docId = postingList1.get(i).getDocId();
                int p_index = postingList2.indexOf(docId);
                if(p_index!=-1){
                    AbstractHit hit = new Hit(docId,index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1,postingList1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2,postingList2.get(p_index));
                    hit.setScore(sorter.score(hit));
                    res.add(hit);
                }
            }
        } else if(combine==LogicalCombination.OR){    //或要求
            if(postingList1==null) return search(queryTerm2,sorter);
            if(postingList2==null) return search(queryTerm1,sorter);

            for(int i=0;i< postingList1.size();i++){
                int docId = postingList1.get(i).getDocId();
                int p_index = postingList2.indexOf(docId);
                if(p_index!=-1){    //如果postingList2中有
                    AbstractHit hit = new Hit(docId,index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1,postingList1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2,postingList2.get(p_index));
                    hit.setScore(sorter.score(hit));
                    res.add(hit);
                }else {//如果postingList2中没有
                    AbstractHit hit = new Hit(docId,index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1,postingList1.get(i));
                    hit.setScore(sorter.score(hit));
                    res.add(hit);
                }
            }
            for (int i=0;i<postingList2.size();i++){
                int docId = postingList2.get(i).getDocId();
                int p_index = postingList1.indexOf(docId);
                if(p_index==-1) {    //如果postingList1中没有
                    AbstractHit hit = new Hit(docId,index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm2,postingList2.get(i));
                    hit.setScore(sorter.score(hit));
                    res.add(hit);
                }
            }
        }

        sorter.sort(res);
        AbstractHit[] retRes = new AbstractHit[res.size()];
        return res.toArray(retRes);
    }
}
