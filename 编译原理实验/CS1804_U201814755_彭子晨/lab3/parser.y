%error-verbose
%locations
%{
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include "def.h"
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    extern FILE* yyout;
    int yylex();
    void yyerror(const char* fmt, ...);
    void display(struct ASTNode *,int);
%}

//辅助定义部分
%union {
	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;
};

//规则
// %type  定义非终结符
%type <ptr> Program DeclList Decl Specifier ExtDecList VarDecl VarList Dec DecList Def DefList
%type <ptr> FuncDecl ParaDecl StructDecl StructName
%type <ptr> Stmt StmtList CompStmt ForDecl ForExp1 ForExp2 ForExp3 ArrayList CaseStmt DefaultStmt CaseStmtList
%type <ptr> Exp Args 
// %token 定义终结符
%token <type_char> CHAR
%token <type_int> INT
%token <type_float> FLOAT
%token <type_id> ID TYPE STRING RELOP 
%token CONST RETURN BREAK CONTINUE IF ELSE CASE SWITCH DEFAULT
%token STRUCT_DECL STRUCT STRUCT_CREATE STRUCT_VISIT
%token DECL_LIST VAR_DECL FUNC_DECL FUNC_DEF EXT_DEC_LIST ARRAY_LIST PARA_LIST PARA_DECL STMT_LIST COMP_STMT DEF DEF_LIST DEC DEC_LIST EXP_STMT
%token WHILE FOR IF_THEN IF_ELSE FOR_DECL FOR_EXP1 FOR_EXP2 FOR_EXP3 FUNC_CALL ARGS CASE_STMT CASE_STMT_LIST DEFAULT_STMT
%token COLON COMMA SEMI LS RS LM RM LL RL 
%token ASSIGNOP ADD SUB MUL DIV MOD OR AND NOT DOT SELFADD SELFSUB

// 左/右结合 优先级
%left ASSIGNOP 
%left OR
%left AND
%left RELOP
%left ADD SUB
%left MUL DIV MOD
%left SELFADD SELFSUB
%right NOT UMINUS
%left LS RS LM RM DOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

//规则定义
%%
Program : DeclList  { display($1,0); /*semantic_Analysis0($1);*/}     //显示语法树,语义分析
        ; 
DeclList: {$$=NULL;}
        | Decl DeclList   {$$=mknode(2,DECL_LIST,yylineno,$1,$2);}   //每一个DeclList的结点，其第1棵子树对应一个外部变量声明或函数
        ;  
Decl    : Specifier ExtDecList SEMI   {$$=mknode(2,VAR_DECL,yylineno,$1,$2);}   //该结点对应一个外部变量声明
        | Specifier FuncDecl CompStmt   {$$=mknode(3,FUNC_DECL,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
        | StructDecl SEMI       {$$=mknode(1,STRUCT_DECL,yylineno,$1);}
        | error SEMI    {$$=NULL;}
        ;
Specifier: TYPE {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);$$->type=!strcmp($1,"int")?INT:FLOAT;}   
           ;      
ExtDecList: VarDecl   {$$=$1;}       /*每一个ExtDecList的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
        | VarDecl COMMA ExtDecList    {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
        ;  
VarDecl : ID    {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}   //ID结点，标识符符号串存放结点的type_id
        | ID ArrayList  {$$=mknode(1,ARRAY_LIST,yylineno,$2);strcpy($$->type_id,$1);} 
        ;
ArrayList: LM INT RM    {$$=mknode(0,ARRAY_LIST,yylineno);$$->type_int=$2;} 
        | LM INT RM ArrayList   {$$=mknode(2,ARRAY_LIST,yylineno,$2,$4);$$->type_int=$2;} 
        ;
FuncDecl: ID LS VarList RS  {$$=mknode(1,FUNC_DEF,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
	| ID LS RS  {$$=mknode(0,FUNC_DEF,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}//函数名存放在$$->type_id    
        ; 
VarList : ParaDecl  {$$=mknode(1,PARA_LIST,yylineno,$1);}
        | ParaDecl COMMA VarList    {$$=mknode(2,PARA_LIST,yylineno,$1,$3);}
        ;
ParaDecl: Specifier VarDecl     {$$=mknode(2,PARA_DECL,yylineno,$1,$2);}
        ;
CompStmt: LL DefList StmtList RL   {$$=mknode(2,COMP_STMT,yylineno,$2,$3);}
        ;
DefList : {$$=NULL; }
        | Def DefList   {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        | error SEMI    {$$=NULL;}
        ;
Def     : Specifier DecList SEMI {$$=mknode(2,DEF,yylineno,$1,$2);}
        | StructDecl SEMI {$$=$1}
        ;
DecList : Dec   {$$=mknode(1,DEC_LIST,yylineno,$1);}
        | Dec COMMA DecList {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
	;
Dec     : VarDecl  {$$=$1;}
        | VarDecl ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
        ;
StmtList: {$$=NULL; }  
        | Stmt StmtList  {$$=mknode(2,STMT_LIST,yylineno,$1,$2);}
        ;
Stmt    : Exp SEMI   {$$=mknode(1,EXP_STMT,yylineno,$1);}
        | CompStmt   {$$=$1;}      //复合语句结点直接最为语句结点，不再生成新的结点
        | RETURN Exp SEMI {$$=mknode(1,RETURN,yylineno,$2);}
        | IF LS Exp RS Stmt %prec LOWER_THEN_ELSE {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
        | IF LS Exp RS Stmt ELSE Stmt {$$=mknode(3,IF_ELSE,yylineno,$3,$5,$7);}
        | WHILE LS Exp RS Stmt        {$$=mknode(2,WHILE,yylineno,$3,$5);}
        | FOR LS ForDecl RS Stmt      {$$=mknode(2,FOR,yylineno,$3,$5);}  //FOR循环
        | CONTINUE SEMI   {$$ = mknode(0,CONTINUE,yylineno); strcpy($$->type_id, "CONTINUE"); }
        | BREAK SEMI      {$$ = mknode(0,BREAK,yylineno); strcpy($$->type_id, "BREAK"); }
        | SWITCH LS Exp RS LL CaseStmtList RL {$$ = mknode(2,SWITCH,yylineno,$3,$6); }
        ;
CaseStmt: CASE INT COLON StmtList {$$=mknode(1, CASE_STMT, yylineno, $4);$$->type_int=$2;$$->type=INT;}
        | CASE CHAR COLON StmtList {$$=mknode(1, CASE_STMT, yylineno, $4);$$->type_char=$2;$$->type=CHAR;}
        ;
DefaultStmt: DEFAULT COLON StmtList {$$=mknode(1, DEFAULT_STMT, yylineno, $3);}
        ;
CaseStmtList: {$$=NULL;}
        | CaseStmt CaseStmtList {$$=mknode(2, CASE_STMT_LIST, yylineno, $1, $2);}
        | DefaultStmt       {$$=mknode(1, CASE_STMT_LIST, yylineno,$1);}
        ;
ForDecl : ForExp1 SEMI ForExp2 SEMI ForExp3   {$$=mknode(3, FOR_DECL,yylineno,$1,$3,$5);}
        | ForExp1 SEMI SEMI ForExp3  {$$=mknode(3, FOR_DECL,yylineno,$1,NULL,$4);}
        | ForExp1 SEMI ForExp2 SEMI  {$$=mknode(3, FOR_DECL,yylineno,$1,$3,NULL);}
        | SEMI ForExp2 SEMI ForExp3  {$$=mknode(3, FOR_DECL,yylineno,NULL,$2,$4);}
        | ForExp1 SEMI SEMI  {$$=mknode(3, FOR_DECL,yylineno,$1,NULL,NULL);}
        | SEMI ForExp2 SEMI  {$$=mknode(3, FOR_DECL,yylineno,NULL,$2,NULL);}
        | SEMI SEMI ForExp3  {$$=mknode(3, FOR_DECL,yylineno,NULL,NULL,$3);}     
        | SEMI SEMI          {$$=mknode(3, FOR_DECL, yylineno, NULL, NULL, NULL);}  
        ;
ForExp1 : DecList  {$$=mknode(1, FOR_EXP1, yylineno, $1);}
        | Specifier DecList {$$=mknode(2, FOR_EXP1, yylineno, $1, $2);}
        ;
ForExp2 : Exp   {$$=mknode(1, FOR_EXP2, yylineno, $1);}
        ;
ForExp3 : Exp COMMA ForExp3  {$$=mknode(2, FOR_EXP3, yylineno, $1,$3);}
        | Exp   {$$=mknode(2, FOR_EXP3, yylineno, $1, NULL);}
        ;
Exp     : {$$=NULL;}
        | Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
        | Exp AND Exp {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
        | Exp OR Exp  {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
        | Exp ADD Exp {$$=mknode(2,ADD,yylineno,$1,$3);strcpy($$->type_id,"ADD");}
        | Exp SUB Exp {$$=mknode(2,SUB,yylineno,$1,$3);strcpy($$->type_id,"SUB");}
        | Exp MUL Exp {$$=mknode(2,MUL,yylineno,$1,$3);strcpy($$->type_id,"MUL");}
        | Exp DIV Exp {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
        | Exp MOD Exp {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"MOD");}
        | Exp RELOP Exp  {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
        | SELFADD Exp {$$=mknode(1,SELFADD,yylineno,$2);strcpy($$->type_id,"SELFADD");}
        | SELFSUB Exp {$$=mknode(1,SELFSUB,yylineno,$2);strcpy($$->type_id,"SELFSUB");}
        | Exp SELFADD {$$=mknode(1,SELFADD,yylineno,$1);strcpy($$->type_id,"SELFADD");}
        | Exp SELFSUB {$$=mknode(1,SELFSUB,yylineno,$1);strcpy($$->type_id,"SELFSUB");}
        | LS Exp RS   {$$=$2;}
        | SUB Exp %prec UMINUS  {$$=mknode(1,UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}
        | NOT Exp   {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
        | ID LS Args RS {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}
        | ID LS RS  {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
        | ID        {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
        | INT       {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
        | CHAR      {$$=mknode(0,CHAR,yylineno);$$->type_char=$1;$$->type=CHAR;}
        | FLOAT     {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
        | STRING    {$$=mknode(0,STRING,yylineno);strcpy($$->type_id,$1);$$->type=STRING;}
        | LM Args RM    {$$=$2} //数组
        | ID ArrayList  {$$=mknode(1,ID,yylineno,$2);strcpy($$->type_id,$1);} 
        | Exp DOT ID {$$=mknode(1,STRUCT_VISIT,yylineno,$1);strcpy($$->type_id,$3);}
        ;
Args    : Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
        | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
        ;
StructDecl: STRUCT StructName LL DefList RL {$$=mknode(2, STRUCT_CREATE, yylineno, $2, $4);}
        ;
StructName:  {$$=NULL;}
        | ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
        ;
%%

int main(int argc, char *argv[]){
        yyin=fopen(argv[1],"r");
	if (!yyin) 
        return 0;
	yylineno=1;
	yyparse();
	return 0;
}

void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
