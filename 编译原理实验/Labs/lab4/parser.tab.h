
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     INT = 259,
     FLOAT = 260,
     ID = 261,
     TYPE = 262,
     STRING = 263,
     RELOP = 264,
     CONST = 265,
     RETURN = 266,
     BREAK = 267,
     CONTINUE = 268,
     IF = 269,
     ELSE = 270,
     CASE = 271,
     SWITCH = 272,
     DEFAULT = 273,
     STRUCT_DECL = 274,
     STRUCT = 275,
     STRUCT_CREATE = 276,
     STRUCT_VISIT = 277,
     PROGRAM = 278,
     DECL_LIST = 279,
     VAR_DECL = 280,
     FUNC_DECL = 281,
     FUNC_DEF = 282,
     EXT_DEC_LIST = 283,
     ARRAY_LIST = 284,
     ARRAY_DECL = 285,
     PARA_LIST = 286,
     PARA_DECL = 287,
     STMT_LIST = 288,
     COMP_STMT = 289,
     DEF = 290,
     DEF_LIST = 291,
     DEC = 292,
     DEC_LIST = 293,
     EXP_STMT = 294,
     WHILE = 295,
     FOR = 296,
     IF_THEN = 297,
     IF_ELSE = 298,
     FOR_DECL = 299,
     FOR_EXP1 = 300,
     FOR_EXP2 = 301,
     FOR_EXP3 = 302,
     FUNC_CALL = 303,
     ARGS = 304,
     CASE_STMT = 305,
     CASE_STMT_LIST = 306,
     DEFAULT_STMT = 307,
     COLON = 308,
     COMMA = 309,
     SEMI = 310,
     LS = 311,
     RS = 312,
     LM = 313,
     RM = 314,
     LL = 315,
     RL = 316,
     ASSIGNOP = 317,
     ADD = 318,
     SUB = 319,
     MUL = 320,
     DIV = 321,
     MOD = 322,
     OR = 323,
     AND = 324,
     NOT = 325,
     DOT = 326,
     SELFADD = 327,
     SELFSUB = 328,
     UMINUS = 329,
     LOWER_THEN_ELSE = 330
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 18 "parser.y"

	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;



/* Line 1676 of yacc.c  */
#line 137 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

