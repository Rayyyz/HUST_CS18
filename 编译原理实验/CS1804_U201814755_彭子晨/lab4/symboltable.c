#include "def.h"
#define DEBUG 1

int LEV = 0;  //定义了层号

struct ASTNode * mknode(int num,int kind,int pos,...){
    struct ASTNode *T=(struct ASTNode *)calloc(sizeof(struct ASTNode),1);
    int i=0;
    T->kind=kind;
    T->pos=pos;
    va_list pArgs = NULL;
    va_start(pArgs, pos);
    for(i=0;i<num;i++)
        T->ptr[i]= va_arg(pArgs, struct ASTNode *);
    while (i<4) T->ptr[i++]=NULL;
    va_end(pArgs);
    return T;
}

//显示符号表
void prn_symbol() {
	int i;
    printf("\n------------------------Symbol Table---------------------------\n");
    printf("%6s\t%6s\t%6s\t%6s\t%6s\t%6s  %6s  %6s\n","序 号","名 字","层 号","类 型","标 记","偏 移 量","数 组size","参数个数");
    printf("-----------------------------------------------------------------\n");
    for(i=0;i<symbolTable.index;i++){
        printf("%6d ",i);
        printf("%6s ",symbolTable.symbols[i].name);
        printf("%6d\t",symbolTable.symbols[i].level);
        printf("%6s\t",symbolTable.symbols[i].type_name);
        printf("%6c ",symbolTable.symbols[i].flag);
        printf("%6d ",symbolTable.symbols[i].offset);
        if(symbolTable.symbols[i].flag=='A'){
            printf("%6d ",symbolTable.symbols[i].size);
        }else if(symbolTable.symbols[i].flag=='F'){
            printf("  \t%6d ",symbolTable.symbols[i].paramnum);
		}
        printf("\n");
    }
    printf("----------------------------------------------------------------\n");
}

int i,j,t,counter=0;
//cmd = 0:定义新符号
//		1:使用符号
//		2:定义结构体
//		3:定义结构体成员
int semantic_Analysis(struct ASTNode* T,int type,char* type_name,int level,char flag,int cmd)
{//对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
	struct ASTNode* T0;
	int type1,type2;
	if (T)
	{
		switch (T->kind) {
		case PROGRAM:
				T->ptr[0]->offset = 0;  //全局变量定义 初始偏移量为0
                T->offset = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                T->ptr[1]->offset = 0;  //main函数体，初始offset为0
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                break;
		case DECL_LIST:
				T->ptr[0]->offset = 0;
				T->offset = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);  
				if (T->ptr[1]) {
					T->ptr[1]->offset = T->offset;
					T->offset = semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd); //访问该外部定义列表中的其它外部定义
				}
				return T->offset;
				break;
		case VAR_DECL:  
				//处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
				T->width = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
				T->ptr[1]->width = T->width;
				T->ptr[1]->type = T->ptr[0]->type;
				T->ptr[1]->offset = T->offset;
				if(T->ptr[1]->kind==DECL_LIST){
					return semantic_Analysis(T->ptr[1],T->ptr[0]->type,T->ptr[0]->type_id,level,'V',0);
				}else{
					semantic_Analysis(T->ptr[1],T->ptr[0]->type,T->ptr[0]->type_id,level,'V',0);
					return T->offset+T->width;
				}
				break;
		case EXT_DEC_LIST:
                T->ptr[0]->type = T->type;
                T->ptr[0]->width = T->width;
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0],type,type_name,level,'V',cmd);
                T->offset=T->ptr[1]->offset = T->ptr[0]->offset+T->ptr[0]->width;
                T->ptr[1]->type = T->type;
                T->ptr[1]->width = T->width;
                if(T->ptr[1]->kind == EXT_DEC_LIST){
                    return semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                }else{
                    semantic_Analysis(T->ptr[1],type,type_name,level,'V',cmd);
                    return T->ptr[1]->offset+T->ptr[1]->width;
                }
                break;	
		case TYPE:
                if(T->type==STRUCT){  //在符号表查找是否有这个结构体 
                    for(int k=0;k<symbolTable.index && symbolTable.symbols[k].level==0;k++){
                        if(symbolTable.symbols[k].type==STRUCT && 
                        !strcmp(symbolTable.symbols[k].name,T->type_id)){
                            T->width=symbolTable.symbols[k].width;
                            return T->width;
                        }
                    }
                    printf("ERROR！第%d行：未定义类型%s\n",T->pos,T->type_id);
                    return 0;
                }else{
                    if(T->type==INT || T->type==FLOAT){
                        return 4;
                    }else{
                        return 1;
                    }
                }
                break;
            case ID://检测新的变量名是否唯一
                if(flag=='P'){  //定义函数形参
                    for(i=symbolTable.index-1;i>=0 && symbolTable.symbols[i].flag=='P';i--){
                        if(!strcmp(symbolTable.symbols[i].name,T->type_id)){
                            printf("ERROR！第%d行：函数参数中出现相同符号名%s\n",T->pos,T->type_id);
                            return 0;
                        }
                    }
                    strcpy(symbolTable.symbols[symbolTable.index].name,T->type_id);
                    strcpy(symbolTable.symbols[symbolTable.index].type_name,type_name);
                    symbolTable.symbols[symbolTable.index].type=type;
                    symbolTable.symbols[symbolTable.index].flag=flag;
                    symbolTable.symbols[symbolTable.index].width=T->width;
                    symbolTable.symbols[symbolTable.index].level=-1;
                    symbolTable.symbols[symbolTable.index].offset=-1;
                    symbolTable.index++;
                }
                else{  
                    i=0;
                    if(cmd==0){//定义变量 'A' 'V' 'F'
                        i=0;
                        while(i<symbolTable.index){
                            if(strcmp(symbolTable.symbols[i].name,T->type_id)==0 &&
                                symbolTable.symbols[i].flag!='P' && symbolTable.symbols[i].flag!='S' &&
                                symbolTable.symbols[i].level==level){
                                printf("ERROR！第%d行：全局变量中出现相同符号名%s\n",T->pos,T->type_id);
                                printf("sysmbol %d",i);
                                return 0;
                            }
                            i++;
                        }
                        strcpy(symbolTable.symbols[symbolTable.index].name,T->type_id);
                        strcpy(symbolTable.symbols[symbolTable.index].type_name,type_name);
                        symbolTable.symbols[symbolTable.index].level=level;
                        symbolTable.symbols[symbolTable.index].type=type;
                        symbolTable.symbols[symbolTable.index].flag=flag;
                        symbolTable.symbols[symbolTable.index].offset=T->offset;
                        symbolTable.symbols[symbolTable.index].size=T->size;
                        symbolTable.index++;
                    }
                    else if(cmd==1){//使用变量
                        i=symbolTable.index-1;
                        while(i>=0){
                            if(strcmp(symbolTable.symbols[i].name,T->type_id)==0&&(symbolTable.symbols[i].flag!='I')){
                                return symbolTable.symbols[i].type;
                            }
                            i--;
                        }
                        if(i<0){
                            printf("ERROR！第%d行：变量名%s未定义\n",T->pos,T->type_id);
                        }
                    }else if(cmd==2){  //定义结构体
                        for(int i=0;i<symbolTable.index && symbolTable.symbols[i].level==0;i++){
                            if(strcmp(symbolTable.symbols[i].name,T->type_id)==0 &&
                                symbolTable.symbols[i].flag!='P' && symbolTable.symbols[i].flag!='S'){
                                printf("ERROR！第%d行：自定义类型出现相同符号名%s\n",T->pos,T->type_id);
                                return 0;
                            }
                        }
                        strcpy(symbolTable.symbols[symbolTable.index].name,T->type_id);
                        strcpy(symbolTable.symbols[symbolTable.index].type_name,"struct");
                        symbolTable.symbols[symbolTable.index].level=level;
                        symbolTable.symbols[symbolTable.index].type=type;
                        symbolTable.symbols[symbolTable.index].flag=flag;
                        symbolTable.index++;
                    }else if(cmd==3){  //flag='S'  定义结构体成员
                        for(i=symbolTable.index-1;i>=0 && symbolTable.symbols[i].flag=='S';i--){
                            if(!strcmp(symbolTable.symbols[i].name,T->type_id)){
                                printf("ERROR！第%d行：结构体成员中出现相同符号名%s\n",T->pos,T->type_id);
                                return 0;
                            }
                        }
                        strcpy(symbolTable.symbols[symbolTable.index].name,T->type_id);
                        strcpy(symbolTable.symbols[symbolTable.index].type_name,type_name);
                        symbolTable.symbols[symbolTable.index].level=-1;
                        symbolTable.symbols[symbolTable.index].type=type;
                        symbolTable.symbols[symbolTable.index].flag='S';
                        symbolTable.symbols[symbolTable.index].offset=T->offset;
                        symbolTable.index++;
                    }
                }
                break;
		case STRUCT_DECL:
			    semantic_Analysis(T->ptr[0],STRUCT,type_name,level,'S',2);  
                T->ptr[1]->offset=0;   //结构体内的偏移从0开始
                int tmp_index = symbolTable.index;
                return T->offset;
                break;
		case ARRAY_DECL:
		        T->ptr[0]->width = T->width;
                T->ptr[0]->type = T->ptr[0]->type;
                T->ptr[0]->offset = T->offset;
                T->ptr[0]->size = T->size;
                semantic_Analysis(T->ptr[0],type,type_name,level,'A',cmd);
                return T->offset+(T->width)*(T->size);
                break;
		case FUNC_DECL:      //填写函数定义信息到符号表
				T->width = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                T->ptr[1]->type = T->ptr[0]->type;
                T->ptr[1]->width = T->width;
                semantic_Analysis(T->ptr[1],T->ptr[0]->type,T->ptr[0]->type_id,level,flag,cmd);
                semantic_Analysis(T->ptr[2],type,type_name,level,flag,cmd);
                return T->offset;  //函数定义不占存储
                break;
		case FUNC_DEF:      //根据返回类型，函数名填写符号表
                T->ptr[0]->type = T->type;
                semantic_Analysis(T->ptr[0],type,type_name,level,'F',0);//函数名记入，参数个数暂时空缺
                if(T->ptr[1]){
                    T->num = semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);//函数形参
                }else{
                    T->num=0;
                }
                symbolTable.symbols[symbolTable.index - T->num - 1].paramnum=T->num;  //补上参数个数
                break;
		case PARA_LIST:    //处理函数形式参数列表
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                if(T->ptr[1]){
                    return 1+semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                }else{
                    return 1;
                }
                break;
		case  PARA_DECL:
			    T->width = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                T->ptr[1]->width = T->width;
                T->ptr[1]->type = T->ptr[0]->type;
                semantic_Analysis(T->ptr[1],T->ptr[1]->type,T->ptr[0]->type_id,level+1,'P',0);
                break;
		case COMP_STMT:
			    scopeTX.TX[scopeTX.top]=symbolTable.index;
                scopeTX.top++;
                T->ptr[0]->offset=T->offset;  //一般来说都是0，但for循环除外
                semantic_Analysis(T->ptr[0],type,type_name,level+1,flag,0);//分析定义列表
                prn_symbol();
                semantic_Analysis(T->ptr[1],type,type_name,level+1,flag,1);//分析语句列表
                symbolTable.index=scopeTX.TX[scopeTX.top-1];
                scopeTX.top--;
				break;
		case DEF_LIST:
                T->ptr[0]->offset = T->offset;
                T->offset = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                if(T->ptr[1]){
                    T->ptr[1]->offset = T->offset;
                    T->offset = semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                }
                return T->offset;
				break;
		case DEF:
                T->width = semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                T->ptr[1]->width = T->width;
                T->ptr[1]->type = T->ptr[0]->type;
                T->ptr[1]->offset = T->offset;
                return semantic_Analysis(T->ptr[1],T->ptr[0]->type,T->ptr[0]->type_id,level,flag,cmd);
                break;
		case DEC_LIST:
				T->ptr[0]->width = T->width;
                T->type = T->ptr[0]->type = T->ptr[0]->type;
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0],type,type_name,level,'V',cmd);
                if(T->ptr[1]){  
                    T->ptr[1]->width = T->width;
                    T->ptr[1]->type = T->type;
                    T->ptr[1]->offset = T->offset+T->width;
                    return semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                }else{
                    return T->offset+T->width;
                }
                break;
		case ASSIGNOP:
				T->ptr[0]->width = T->width;
                T->ptr[0]->type = T->type;
                T->ptr[0]->offset = T->offset;      
                semantic_Analysis(T->ptr[0],type,type_name,level,'V',cmd);
                break;
		case STMT_LIST:
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,1);  //使用变量
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,1);
                break;
		case IF_THEN:
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                break;
		case IF_ELSE:
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                semantic_Analysis(T->ptr[2],type,type_name,level,flag,cmd);
                break;
		case WHILE: 
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                break;
		case EXP_STMT:
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                break;
		case RETURN:
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                break;
		case FOR:
                T->ptr[1]->offset = semantic_Analysis(T->ptr[0],type,type_name,level,flag,0);
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                break;
		case FOR_DECL:
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                semantic_Analysis(T->ptr[2],type,type_name,level,flag,cmd);
                return T->offset;
		case FOR_EXP1:
		case FOR_EXP2:
		case FOR_EXP3:
		case BREAK:
		case CONTINUE:
				break;
		case INT:
				return INT;
		case FLOAT:
				return FLOAT;
		case CHAR:
				return CHAR;
		case AND:
		case OR:
		case RELOP:
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		        type1=semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                type2=semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                if(type1==type2)
                    return type1;
                break;
		case FUNC_CALL:
                j=0;
                while(symbolTable.symbols[j].level==0&&j<symbolTable.index){
                    if(strcmp(symbolTable.symbols[j].name,T->type_id)==0){
                        if(symbolTable.symbols[j].flag!='F')
                            printf("ERROR！第%d行：函数名%s在符号表中定义为变量\n",T->pos,T->type_id);
                        break;
                    }
                    j++;
                }
                if(symbolTable.symbols[j].level==1||j==symbolTable.index){
                    printf("ERROR！第%d行：函数%s未定义\n",T->pos,T->type_id);
                    break;
                }
                type=symbolTable.symbols[j+1].type;
                counter=0;
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);//分析参数
                if(symbolTable.symbols[j].paramnum!=counter)
                    printf("ERROR！第%d行：函数调用%s参数个数不匹配\n",T->pos,T->type_id);
                break;
		case SELFADD:
		case SELFSUB:
			    semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                break;
		case NOT:
		case UMINUS:
        case ARGS:
                counter++;
                t=semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                if(type!=t)
                    printf("ERROR！第%d行：函数调用的第%d个参数类型不匹配\n",T->pos,counter);
                type=symbolTable.symbols[j+counter+1].type;
                semantic_Analysis(T->ptr[1],type,type_name,level,flag,cmd);
                break;
		case DEFAULT_STMT:
                semantic_Analysis(T->ptr[0],type,type_name,level,flag,cmd);
                break;
		}
	}
}
