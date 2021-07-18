flex Cless.l
echo "FLEX Completed"
bison -d -v parser.y
echo "BISON Completed"
gcc -o parser lex.yy.c parser.tab.c ast.c
echo "GCC 连接完毕"
.\parser %1
echo "编译完成:%1"