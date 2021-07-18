%{
    int yycolumn=1;
    int lines = 1;
    typedef union {
        int    type_int;
        char   type_char;
        float  type_float;
        char  type_id[32];
        struct ASTNode *ptr;	
    } TYPES;
%}
%option yylineno


DIGIT   [0-9]
LETTER  [A-Za-z]
ID      [A-Za-z][A-Za-z0-9]*
INT     [-+]?[1-9][0-9]*|0
FLOAT   [-+]?([0-9]*\.?[0-9]+|[0-9]+\.)

%%
\n            {lines++; yycolumn = 1;}
[/][/][^\n]*  {fprintf(yyout,"line %d:(LINE_COMMENT, %s)\n",lines,yytext); }
[/][*][^\n]*[*][/]  {fprintf(yyout,"line %d:(COMMENT, %s)\n",lines,yytext); }

"for" {fprintf(yyout,"line %d:(KEYWORD_FOR, %s)\n",lines,yytext); }
"main" {fprintf(yyout,"line %d:(KEYWORD_MAIN, %s)\n",lines,yytext); }
"if"  {fprintf(yyout,"line %d:(KEYWORD_IF, %s)\n",lines,yytext); }
"else"  {fprintf(yyout,"line %d:(KEYWORD_ELSE, %s)\n",lines,yytext); }
"continue" {fprintf(yyout,"line %d:(KEYWORD_CONTINUE, %s)\n",lines,yytext); }
"break" {fprintf(yyout,"line %d:(KEYWORD_BREAK, %s)\n",lines,yytext); }
"return" {fprintf(yyout,"line %d:(KEYWORD_RETURN, %s)\n",lines,yytext); }

"int" {fprintf(yyout,"line %d:(TYPE_INT, %s)\n",lines,yytext); }
"char" {fprintf(yyout,"line %d:(TYPE_CHAR, %s)\n",lines,yytext); } 
"float"  {fprintf(yyout,"line %d:(TYPE_FLOAT, %s)\n",lines,yytext); }
"string" {fprintf(yyout,"line %d:(TYPE_STRING, %s)\n",lines,yytext); }
"bool" {fprintf(yyout,"line %d:(TYPE_BOOL, %s)\n",lines,yytext); }

['][^\n]['] {fprintf(yyout,"line %d:(CHAR, %s)\n",lines,yytext);}
["][^\n]*["] {fprintf(yyout,"line %d:(STRING, %s)\n",lines,yytext); }
{ID}  {fprintf(yyout,"line %d:(IDENTIFIER, %s)\n",lines,yytext); }
{INT} {fprintf(yyout,"line %d:(INTEGER, %s)\n",lines,yytext); }
{FLOAT} {fprintf(yyout,"line %d:(DECIMAL, %s)\n",lines,yytext); }

"+"     {fprintf(yyout,"line %d:(OP_ADD, %s)\n",lines,yytext); }
"-"  {fprintf(yyout,"line %d:(OP_SUB, %s)\n",lines,yytext); } 
"*"  {fprintf(yyout,"line %d:(OP_MUL, %s)\n",lines,yytext); }
"/"  {fprintf(yyout,"line %d:(OP_DIV, %s)\n",lines,yytext); }
"%"  {fprintf(yyout,"line %d:(OP_MOD, %s)\n",lines,yytext); }
"="  {fprintf(yyout,"line %d:(OP_EQU, %s)\n",lines,yytext); }
">"  {fprintf(yyout,"line %d:(OP_BGZ, %s)\n",lines,yytext); }
"<"  {fprintf(yyout,"line %d:(OP_SMZ, %s)\n",lines,yytext); }
">="  {fprintf(yyout,"line %d:(OP_BGEZ, %s)\n",lines,yytext); }
"<="  {fprintf(yyout,"line %d:(OP_SMEZ, %s)\n",lines,yytext); }
"!"  {fprintf(yyout,"line %d:(SELFOP_NOT, %s)\n",lines,yytext); }
"++" {fprintf(yyout,"line %d:(SELFOP_ADD, %s)\n",lines,yytext); }
"--" {fprintf(yyout,"line %d:(SELFOP_SUB, %s)\n",lines,yytext); } 
"||" {fprintf(yyout,"line %d:(OP_OR, %s)\n",lines,yytext); }
"&&" {fprintf(yyout,"line %d:(OP_AND, %s)\n",lines,yytext); }
"("  {fprintf(yyout,"line %d:(ROUND_BRACKET_LEFT, %s)\n",lines,yytext); }
")"  {fprintf(yyout,"line %d:(ROUND_BRACKET_RIGHT, %s)\n",lines,yytext); }
"["  {fprintf(yyout,"line %d:(SQUARE_BRACKET_LEFT, %s)\n",lines,yytext); }
"]"  {fprintf(yyout,"line %d:(SQUARE_BRACKET_RIGHT, %s)\n",lines,yytext); }
"{"  {fprintf(yyout,"line %d:(BRACE_LEFT, %s)\n",lines,yytext); }
"}"  {fprintf(yyout,"line %d:(BRACE_RIGHT, %s)\n",lines,yytext); }
","  {fprintf(yyout,"line %d:(COMMA, %s)\n",lines,yytext); }
";"  {fprintf(yyout,"line %d:(SEMICOLON, %s)\n",lines,yytext); }
[ \r\t] { }

.   {fprintf(yyout,"line %d:(ErrorAlert:can't find the signal definition, %s)\n",lines,yytext); }

%%
/*函数部分*/
int main(int argc, char** argv)
{
    if(argc>2){
        if(!(yyin = fopen(argv[1],"r"))){
            perror(argv[1]);
            printf("ERROR:open test.c\n");
            return 1;
        }
        if(!(yyout = fopen(argv[2],"w+"))){
            perror(argv[2]);
            printf("ERROR:open output.txt\n");
            return 1;
        }
    }else{
        yyin = stdin;
        yyout = stdout;
    }
    fprintf(yyout,"token\n");
    yylex();
    printf("lines: %8d\n",lines);
}

int yywrap()
{
    return 1;
}