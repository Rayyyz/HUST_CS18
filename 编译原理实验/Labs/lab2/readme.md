# Cless 2

## lab2实验内容
调研词法分析程序的自动生成工具LEX或FLEX，将实验一定义的单词文法转换为正规式，设计并实现一个能够输出单词序列（二元式）的词法分析器。要求：
(1)理解单词的分类和形式化描述；
(2)掌握自动生成工具flex的使用技术；
(3)定义保留字和操作符、界符的内部码；
(4)实现一个完整的词法分析器；
(5)显示词法分析结果（二元组）列表。

## 参考资料
词法分析就是把输入分割成一个个有意义的块，称为记号（token）。
   
函数名	定义
+ yyin	FILE*类型，指向LEX输入文件，缺省情况下指向标准输入
+ yyout	FILE*类型，指向LEX输出文件，缺省情况下指向标准输出
+ yytext	char*类型，指向识别规则中的一个正规式匹配的单词的首字符
+ yyleng	int类型，记录与识别规则中正规式匹配的单词的长度
+ yylex()	从该函数开始分析，可由lex自动生成
+ yywrap()	文件结束处理函数，如果返回值为1就停止解析。可以用来解析多个文件。
+ echo	将yytext打印到yyout


## 文件内容
+ Cless.l       ：词法分析器
+ test.c        ：测试文件
+ lex.yy.c      ：用flex对Cless.l编译后得到的词法分析源程序
+ lex.yy.exe    ：用gcc对lex.yy.c编译后得到的词法分析器
+ output.txt    ：用lex.yy.exe对test.c分析后得到的输出文件

## 执行顺序
+ 命令行：flex ./Cless.l
+ 在VSCODE中编译lex.yy.c，得到lex.yy.exe
+ 命令行：.\lex.yy.exe .\test.c .\output.txt