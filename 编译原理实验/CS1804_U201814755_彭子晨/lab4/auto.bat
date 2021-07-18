flex Cless.l
echo "FLEX Completed"
bison -d parser.y
echo "BISON Completed"
gcc parser.tab.c lex.yy.c symboltable.c -o parser
echo "GCC 连接完毕"
.\parser %1
echo "编译完成:%1"