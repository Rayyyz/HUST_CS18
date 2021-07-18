%option yylineno
%{
    #include "parser.tab.h"
    #include <string.h>
    #include "def.h"

    int yycolumn=1;
    #define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
    
    typedef union {
        int     type_int;
        char    type_char;
        float   type_float;
        char    type_id[32];
        struct  node *ptr;
    } YYLVAL;
    #define YYSTYPE YYLVAL
    
%}

DIGIT   [0-9]
LETTER  [A-Za-z]
ID      [A-Za-z][A-Za-z0-9]*
INT     [-+]?[1-9][0-9]*|0
FLOAT   [-+]?([0-9]*\.?[0-9]+|[0-9]+\.)

%%
\n                  { yycolumn = 1;}
[/][/][^\n]*        {printf("line %d:(LINE_COMMENT, %s)\n",yylineno,yytext);  }
[/][*][^\n]*[*][/]  {printf("line %d:(COMMENT, %s)\n",yylineno,yytext); }

"for"       {printf("line %d:(KEYWORD_FOR, %s)\n",yylineno,yytext); return FOR;}
"if"        {printf("line %d:(KEYWORD_IF, %s)\n",yylineno,yytext); return IF;}
"else"      {printf("line %d:(KEYWORD_ELSE, %s)\n",yylineno,yytext); return ELSE;}
"while"     {printf("line %d:(KEYWORD_WHILE, %s)\n",yylineno,yytext); return WHILE;}
"continue"  {printf("line %d:(KEYWORD_CONTINUE, %s)\n",yylineno,yytext); return CONTINUE;}
"break"     {printf("line %d:(KEYWORD_BREAK, %s)\n",yylineno,yytext); return BREAK;}
"return"    {printf("line %d:(KEYWORD_RETURN, %s)\n",yylineno,yytext); return RETURN;}
"switch"    {printf("line %d:(KEYWORD_SWITCH, %s)\n",yylineno,yytext); return SWITCH;}
"case"      {printf("line %d:(KEYWORD_CASE, %s)\n",yylineno,yytext); return CASE;}
"default"   {printf("line %d:(KEYWORD_DEFAULT, %s)\n",yylineno,yytext); return DEFAULT;}
"struct"    {printf("line %d:(KEYWORD_STRUCT, %s)\n",yylineno,yytext); return STRUCT;}

"void"      {printf("line %d:(TYPE_VOID, %s)\n",yylineno,yytext); strcpy(yylval.type_id, yytext); return TYPE;}
"int"       {printf("line %d:(TYPE_INT, %s)\n",yylineno,yytext); strcpy(yylval.type_id, yytext); return TYPE;}
"char"      {printf("line %d:(TYPE_CHAR, %s)\n",yylineno,yytext); strcpy(yylval.type_id, yytext); return TYPE;} 
"float"     {printf("line %d:(TYPE_FLOAT, %s)\n",yylineno,yytext); strcpy(yylval.type_id, yytext); return TYPE;}
"string"    {printf("line %d:(TYPE_STRING, %s)\n",yylineno,yytext); strcpy(yylval.type_id, yytext); return TYPE;}

['][^\n]['] {printf("line %d:(CHAR, %s)\n",yylineno,yytext); yylval.type_char=yytext[1]; return CHAR;}
["][^\n]*["] {printf("line %d:(STRING, %s)\n",yylineno,yytext); strncpy(yylval.type_id,yytext+1,strlen(yytext)-2); return STRING;}
{INT}       {printf("line %d:(INTEGER, %s)\n",yylineno,yytext); yylval.type_int=atoi(yytext); return INT;}
{FLOAT}     {printf("line %d:(FLOAT, %s)\n",yylineno,yytext); yylval.type_float=atof(yytext); return FLOAT;}
{ID}        {printf("line %d:(IDENTIFIER, %s)\n",yylineno,yytext); strcpy(yylval.type_id,yytext); return ID;}

":"     {printf("line %d:(COLON, %s)\n",yylineno,yytext); return COLON;}
","     {printf("line %d:(COMMA, %s)\n",yylineno,yytext); return COMMA;}
";"     {printf("line %d:(SEMI, %s)\n",yylineno,yytext); return SEMI;}
">"|"<"|">="|"<="|"=="|"!=" {printf("line %d:(RELOP, %s)\n",yylineno,yytext); strcpy(yylval.type_id, yytext); return RELOP;}
"="     {printf("line %d:(ASSIGNOP, %s)\n",yylineno,yytext); return ASSIGNOP;}
"+"     {printf("line %d:(ADD, %s)\n",yylineno,yytext); return ADD;}
"-"     {printf("line %d:(SUB, %s)\n",yylineno,yytext); return SUB;} 
"*"     {printf("line %d:(MUL, %s)\n",yylineno,yytext); return MUL;}
"/"     {printf("line %d:(DIV, %s)\n",yylineno,yytext); return DIV;}
"%"     {printf("line %d:(MOD, %s)\n",yylineno,yytext); return MOD;}
"||"    {printf("line %d:(OR, %s)\n",yylineno,yytext); return OR;}
"&&"    {printf("line %d:(AND, %s)\n",yylineno,yytext); return AND;}
"!"     {printf("line %d:(NOT, %s)\n",yylineno,yytext); return NOT;}
"++"    {printf("line %d:(SELFADD, %s)\n",yylineno,yytext); return SELFADD;}
"--"    {printf("line %d:(SELFSUB, %s)\n",yylineno,yytext); return SELFSUB;} 
"."     {printf("line %d:(DOT, %s)\n",yylineno,yytext); return DOT;} 

"("     {printf("line %d:(ROUND_BRACKET_LEFT, %s)\n",yylineno,yytext); return LS;}
")"     {printf("line %d:(ROUND_BRACKET_RIGHT, %s)\n",yylineno,yytext); return RS;}
"["     {printf("line %d:(SQUARE_BRACKET_LEFT, %s)\n",yylineno,yytext); return LM;}
"]"     {printf("line %d:(SQUARE_BRACKET_RIGHT, %s)\n",yylineno,yytext); return RM;}
"{"     {printf("line %d:(BRACE_LEFT, %s)\n",yylineno,yytext); return LL;}
"}"     {printf("line %d:(BRACE_RIGHT, %s)\n",yylineno,yytext); return RL;}

[ \r\t] { }

[0-9][A-Za-z0-9]* {printf("line %d:(ErrorAlert:format can't found, %s)\n",yylineno,yytext);}
.      {printf("line %d:(ErrorAlert:can't find the signal definition, %s)\n",yylineno,yytext); }

%%
/*函数部分*/
/*
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
    printf("token\n");
    yylex();
    printf("yylineno: %8d\n",yylineno);
}
*/
int yywrap()
{
    return 1;
}