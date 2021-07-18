%{
    int chars = 0;
    int words = 0;
    int lines = 0;
    
    enum yytokentype{
        IDENTIFIER = 1000,  //标识符    aB79s
        INTEGER,            //整数      21
        DECIMAL,            //浮点数    21.12
        CHAR,               //字符      'a'
        STRING,             //字符串    'abcd'
        KEYWORD,            //关键字
        TYPE_INT,           //类型      int
        TYPE_FLOAT,         //类型      float
        TYPE_CHAR,          //类型      char
        TYPE_STRING,        //类型      string
        TYPE_BOOL,          //类型      bool
        KEYWORD_IF,         //关键字    if
        KEYWORD_ELSE,       //关键字    else
        KEYWORD_WHILE,      //关键字    while
        KEYWORD_FOR,        //关键字    for
        KEYWORD_RETURN,     //关键字    return
        OP_ADD,             //加号      +
        OP_SUB,             //减号      -
        OP_MUL,             //乘号      *
        OP_DIV,             //除号      /
        OP_MOD,             //MOD       %
        OP_EQU,             //等号      =
        SELFOP_NOT,         //非        !
        SELFOP_ADD,         //自增      ++
        SELFOP_SUB,         //自减      --
        OP_OR,              //或        ||
        OP_AND,             //与        &&
        ROUND_BRACKET_LEFT,     //左括号    (
        ROUND_BRACKET_RIGHT,    //右括号    )
        SQUARE_BRACKET_LEFT,    //左中括号  [
        SQUARE_BRACKET_RIGHT,   //右中括号  ]
        BRACE_LEFT,         //左大括号      {
        BRACE_RIGHT,        //右大括号}
        COMMA,              //逗号          ,
        SEMICOLON,          //分号          ;
        LINE_COMMENT,       //单行注释      //
        COMMENT             //多行注释      /* */
};
%}
[a-zA-z]+   { words++; chars += strlen(yytext);}
\n          { chars++; lines++;}
.           { chars++; }
KEYWORDS ("int"|"char"|"float"|"bool"|"if"|"else"|"while"|"for"|"return"|"main"|"ture"|"false")
%%

{KEYWORDS}  {fprintf(yyout,"line %d:(KEYWORD,%d,%s)\n",lines,KEYWORD,yytext); return KEYWORD;}
%%

main(int argc, char** argv)
{
    yylex();
    printf("%d %d %d\n",lines,words,chars);
}
