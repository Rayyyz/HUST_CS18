
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "parser.y"

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


/* Line 189 of yacc.c  */
#line 88 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     DECL_LIST = 278,
     VAR_DECL = 279,
     FUNC_DECL = 280,
     FUNC_DEF = 281,
     EXT_DEC_LIST = 282,
     ARRAY_LIST = 283,
     PARA_LIST = 284,
     PARA_DECL = 285,
     STMT_LIST = 286,
     COMP_STMT = 287,
     DEF = 288,
     DEF_LIST = 289,
     DEC = 290,
     DEC_LIST = 291,
     EXP_STMT = 292,
     WHILE = 293,
     FOR = 294,
     IF_THEN = 295,
     IF_ELSE = 296,
     FOR_DECL = 297,
     FOR_EXP1 = 298,
     FOR_EXP2 = 299,
     FOR_EXP3 = 300,
     FUNC_CALL = 301,
     ARGS = 302,
     CASE_STMT = 303,
     CASE_STMT_LIST = 304,
     DEFAULT_STMT = 305,
     COLON = 306,
     COMMA = 307,
     SEMI = 308,
     LS = 309,
     RS = 310,
     LM = 311,
     RM = 312,
     LL = 313,
     RL = 314,
     ASSIGNOP = 315,
     ADD = 316,
     SUB = 317,
     MUL = 318,
     DIV = 319,
     MOD = 320,
     OR = 321,
     AND = 322,
     NOT = 323,
     DOT = 324,
     SELFADD = 325,
     SELFSUB = 326,
     UMINUS = 327,
     LOWER_THEN_ELSE = 328
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 18 "parser.y"

	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;



/* Line 214 of yacc.c  */
#line 207 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 232 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   585

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNRULES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    17,    20,    23,
      25,    27,    31,    33,    36,    40,    45,    50,    54,    56,
      60,    63,    68,    69,    72,    75,    79,    82,    84,    88,
      90,    94,    95,    98,   101,   103,   107,   113,   121,   127,
     133,   136,   139,   147,   152,   157,   161,   162,   165,   167,
     173,   178,   183,   188,   192,   196,   200,   203,   205,   208,
     210,   214,   216,   217,   221,   225,   229,   233,   237,   241,
     245,   249,   253,   256,   259,   262,   265,   269,   272,   275,
     280,   284,   286,   288,   290,   292,   294,   298,   301,   305,
     309,   311,   317,   318
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      75,     0,    -1,    76,    -1,    -1,    77,    76,    -1,    78,
      79,    53,    -1,    78,    82,    85,    -1,   101,    53,    -1,
       1,    53,    -1,     7,    -1,    80,    -1,    80,    52,    79,
      -1,     6,    -1,     6,    81,    -1,    56,     4,    57,    -1,
      56,     4,    57,    81,    -1,     6,    54,    83,    55,    -1,
       6,    54,    55,    -1,    84,    -1,    84,    52,    83,    -1,
      78,    80,    -1,    58,    86,    90,    59,    -1,    -1,    87,
      86,    -1,     1,    53,    -1,    78,    88,    53,    -1,   101,
      53,    -1,    89,    -1,    89,    52,    88,    -1,    80,    -1,
      80,    60,    99,    -1,    -1,    91,    90,    -1,    99,    53,
      -1,    85,    -1,    11,    99,    53,    -1,    14,    54,    99,
      55,    91,    -1,    14,    54,    99,    55,    91,    15,    91,
      -1,    38,    54,    99,    55,    91,    -1,    39,    54,    95,
      55,    91,    -1,    13,    53,    -1,    12,    53,    -1,    17,
      54,    99,    55,    58,    94,    59,    -1,    16,     4,    51,
      90,    -1,    16,     3,    51,    90,    -1,    18,    51,    90,
      -1,    -1,    92,    94,    -1,    93,    -1,    96,    53,    97,
      53,    98,    -1,    96,    53,    53,    98,    -1,    96,    53,
      97,    53,    -1,    53,    97,    53,    98,    -1,    96,    53,
      53,    -1,    53,    97,    53,    -1,    53,    53,    98,    -1,
      53,    53,    -1,    88,    -1,    78,    88,    -1,    99,    -1,
      99,    52,    98,    -1,    99,    -1,    -1,    99,    60,    99,
      -1,    99,    67,    99,    -1,    99,    66,    99,    -1,    99,
      61,    99,    -1,    99,    62,    99,    -1,    99,    63,    99,
      -1,    99,    64,    99,    -1,    99,    65,    99,    -1,    99,
       9,    99,    -1,    70,    99,    -1,    71,    99,    -1,    99,
      70,    -1,    99,    71,    -1,    54,    99,    55,    -1,    62,
      99,    -1,    68,    99,    -1,     6,    54,   100,    55,    -1,
       6,    54,    55,    -1,     6,    -1,     4,    -1,     3,    -1,
       5,    -1,     8,    -1,    56,   100,    57,    -1,     6,    81,
      -1,    99,    69,     6,    -1,    99,    52,   100,    -1,    99,
      -1,    20,   102,    58,    86,    59,    -1,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    60,    60,    62,    63,    65,    66,    67,    68,    70,
      72,    73,    75,    76,    78,    79,    81,    82,    84,    85,
      87,    89,    91,    92,    93,    95,    96,    98,    99,   101,
     102,   104,   105,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   118,   119,   121,   123,   124,   125,   127,
     128,   129,   130,   131,   132,   133,   134,   136,   137,   139,
     141,   142,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   172,
     173,   175,   177,   178
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "INT", "FLOAT", "ID", "TYPE",
  "STRING", "RELOP", "CONST", "RETURN", "BREAK", "CONTINUE", "IF", "ELSE",
  "CASE", "SWITCH", "DEFAULT", "STRUCT_DECL", "STRUCT", "STRUCT_CREATE",
  "STRUCT_VISIT", "DECL_LIST", "VAR_DECL", "FUNC_DECL", "FUNC_DEF",
  "EXT_DEC_LIST", "ARRAY_LIST", "PARA_LIST", "PARA_DECL", "STMT_LIST",
  "COMP_STMT", "DEF", "DEF_LIST", "DEC", "DEC_LIST", "EXP_STMT", "WHILE",
  "FOR", "IF_THEN", "IF_ELSE", "FOR_DECL", "FOR_EXP1", "FOR_EXP2",
  "FOR_EXP3", "FUNC_CALL", "ARGS", "CASE_STMT", "CASE_STMT_LIST",
  "DEFAULT_STMT", "COLON", "COMMA", "SEMI", "LS", "RS", "LM", "RM", "LL",
  "RL", "ASSIGNOP", "ADD", "SUB", "MUL", "DIV", "MOD", "OR", "AND", "NOT",
  "DOT", "SELFADD", "SELFSUB", "UMINUS", "LOWER_THEN_ELSE", "$accept",
  "Program", "DeclList", "Decl", "Specifier", "ExtDecList", "VarDecl",
  "ArrayList", "FuncDecl", "VarList", "ParaDecl", "CompStmt", "DefList",
  "Def", "DecList", "Dec", "StmtList", "Stmt", "CaseStmt", "DefaultStmt",
  "CaseStmtList", "ForDecl", "ForExp1", "ForExp2", "ForExp3", "Exp",
  "Args", "StructDecl", "StructName", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    77,    77,    77,    78,
      79,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      84,    85,    86,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    92,    92,    93,    94,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    96,    96,    97,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   102,   102
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     2,     1,
       1,     3,     1,     2,     3,     4,     4,     3,     1,     3,
       2,     4,     0,     2,     2,     3,     2,     1,     3,     1,
       3,     0,     2,     2,     1,     3,     5,     7,     5,     5,
       2,     2,     7,     4,     4,     3,     0,     2,     1,     5,
       4,     4,     4,     3,     3,     3,     2,     1,     2,     1,
       3,     1,     0,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     3,     2,     2,     4,
       3,     1,     1,     1,     1,     1,     3,     2,     3,     3,
       1,     5,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     9,    92,     0,     2,     0,     0,     0,     8,
      93,     0,     1,     4,    12,     0,    10,     0,     7,     0,
       0,     0,    13,     5,     0,     0,     6,     0,     0,     0,
       0,     0,    17,     0,     0,    18,     0,    12,    11,    62,
      24,    29,     0,    27,    91,    23,    26,    20,    16,     0,
      14,    83,    82,    84,    81,    85,    62,     0,     0,     0,
       0,     0,     0,    62,    62,    62,    62,    62,    62,    34,
       0,    62,     0,    62,    25,     0,    19,    15,    62,    87,
       0,    41,    40,    62,    62,    62,     0,     0,    90,     0,
      77,    78,    72,    73,    21,    32,    62,    33,    62,    62,
      62,    62,    62,    62,    62,    62,     0,    74,    75,    30,
      28,    80,     0,    35,     0,     0,     0,    62,     0,    57,
       0,     0,    76,    62,    86,    71,    63,    66,    67,    68,
      69,    70,    65,    64,    88,    79,    62,     0,    62,    62,
       0,    59,    58,    62,    62,    89,    36,    46,    38,    55,
      61,    62,    39,    62,     0,    62,     0,     0,    46,    48,
       0,    62,    52,    50,    62,    37,     0,     0,    62,    47,
      42,    60,    49,    62,    62,    45,    44,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    28,    15,    41,    22,    17,    34,
      35,    69,    29,    30,    42,    43,    70,    71,   158,   159,
     160,   120,   121,   140,   149,    72,    89,    31,    11
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -71
static const yytype_int16 yypact[] =
{
     207,   -51,   -71,    10,    20,   -71,   207,    33,   -21,   -71,
     -71,    31,   -71,   -71,   -18,    18,    23,    38,   -71,    14,
      -4,    87,   -71,   -71,    96,    73,   -71,    53,    96,    50,
      73,    57,   -71,    96,    67,    78,    71,    93,   -71,   180,
     -71,    91,    99,   109,   -71,   -71,   -71,   -71,   -71,   155,
      93,   -71,   -71,   -71,    16,   -71,   376,   110,   119,   122,
     124,   128,   135,   376,   376,   376,   376,   376,   376,   -71,
     136,   142,    54,   376,   -71,    96,   -71,   -71,   241,   -71,
     104,   -71,   -71,   376,   376,   376,    -1,   388,   404,   145,
     130,   130,   130,   130,   -71,   -71,   376,   -71,   376,   376,
     376,   376,   376,   376,   376,   376,   197,   -71,   -71,   480,
     -71,   -71,   150,   -71,   417,   430,   451,   260,    96,   -71,
     151,   156,   -71,   376,   -71,   229,   493,   335,   335,   -16,
     -16,   -16,   514,    -5,   -71,   -71,   218,   153,   218,   279,
     162,   480,   -71,   218,   302,   -71,   201,    76,   -71,   -71,
     467,   321,   -71,   340,   164,   218,    97,   169,    76,   -71,
     166,   376,   -71,   -71,   363,   -71,   177,   182,   180,   -71,
     -71,   -71,   -71,   142,   142,   -71,   -71,   -71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   231,   -71,    13,   216,    17,   -36,   -71,   192,
     -71,   226,     5,   -71,   -49,   -71,   -70,   116,   -71,   -71,
      95,   -71,   -71,   111,    26,   -56,   -55,    25,   -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -57
static const yytype_int16 yytable[] =
{
      80,    95,     9,     2,    96,    37,     2,    87,    88,    90,
      91,    92,    93,     7,    77,    27,    10,   109,    79,     7,
      12,     2,    88,   112,    16,     8,   110,   114,   115,   116,
      39,     8,    18,    33,     3,    45,    20,   119,    21,    14,
     125,    16,   126,   127,   128,   129,   130,   131,   132,   133,
      47,    32,   117,   106,   107,   108,    99,   100,   101,   102,
     103,   141,    33,    96,   106,   107,   108,    88,   145,   142,
      78,    23,    21,   -22,    27,    24,   -22,   -22,   -22,   -22,
       2,   -22,   -22,   150,   -22,   -22,   -22,   -22,   141,    19,
     -22,    36,   156,     3,   157,   150,    25,   150,   175,   118,
     166,   167,    37,   176,   177,   150,    40,    97,   150,    44,
      46,   -22,   -22,    96,    98,    99,   100,   101,   102,   103,
     104,   105,    48,   106,   107,   108,   -22,   -22,    50,   -22,
      49,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,    51,    52,    53,    54,    21,
      55,    73,    74,    56,    57,    58,    59,   113,   -31,    60,
     -31,    75,     2,    81,    98,    99,   100,   101,   102,   103,
     104,   105,    82,   106,   107,   108,    83,   162,    84,   163,
      61,    62,    85,    51,    52,    53,    54,   171,    55,    86,
     172,    56,    57,    58,    59,    94,    63,    60,    64,   106,
      25,   -31,   124,   134,    65,   135,   143,    -3,     1,   144,
      66,   147,    67,    68,     2,   151,   155,   164,    61,    62,
     168,    51,    52,    53,    54,   170,    55,     3,   173,    56,
      57,    58,    59,   174,    63,    60,    64,    13,    25,   -31,
      38,    76,    65,    26,    51,    52,    53,    54,    66,    55,
      67,    68,   146,   169,   148,   154,    61,    62,     0,   152,
       0,     0,     0,    51,    52,    53,    54,     0,    55,     0,
       0,   165,    63,     0,    64,     0,    25,     0,     0,     0,
      65,     0,    51,    52,    53,    54,    66,    55,    67,    68,
      99,   100,   101,   102,   103,    63,   111,    64,   106,   107,
     108,     0,     0,    65,     0,    51,    52,    53,    54,    66,
      55,    67,    68,   139,    63,     0,    64,     0,     0,     0,
       0,     0,    65,     0,    51,    52,    53,    54,    66,    55,
      67,    68,     0,    63,   -56,    64,     0,     0,     0,     0,
       0,    65,     0,    51,    52,    53,    54,    66,    55,    67,
      68,     0,     0,     0,     0,   153,    63,     0,    64,     0,
       0,     0,     0,     0,    65,     0,    51,    52,    53,    54,
      66,    55,    67,    68,     0,    63,   -54,    64,     0,    51,
      52,    53,    54,    65,    55,     0,     0,     0,     0,    66,
       0,    67,    68,     0,    63,   -53,    64,    96,   101,   102,
     103,     0,    65,     0,   106,   107,   108,     0,    66,     0,
      67,    68,     0,    96,     0,     0,     0,    63,   -51,    64,
       0,     0,     0,     0,     0,    65,    96,     0,     0,     0,
      63,    66,    64,    67,    68,     0,     0,     0,    65,    96,
       0,     0,     0,   122,    66,     0,    67,    68,    98,    99,
     100,   101,   102,   103,   104,   105,   123,   106,   107,   108,
      96,     0,     0,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   136,   106,   107,   108,    96,    98,    99,   100,
     101,   102,   103,   104,   105,   137,   106,   107,   108,    96,
      98,    99,   100,   101,   102,   103,   104,   105,     0,   106,
     107,   108,    96,     0,     0,     0,   138,     0,     0,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   161,
     106,   107,   108,    96,     0,     0,     0,    98,    99,   100,
     101,   102,   103,   104,   105,     0,   106,   107,   108,     0,
      98,    99,   100,   101,   102,   103,   104,   105,     0,   106,
     107,   108,     0,     0,    99,   100,   101,   102,   103,   104,
     105,     0,   106,   107,   108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,   100,   101,   102,   103,
       0,   105,     0,   106,   107,   108
};

static const yytype_int16 yycheck[] =
{
      56,    71,    53,     7,     9,     6,     7,    63,    64,    65,
      66,    67,    68,     0,    50,     1,     6,    73,    54,     6,
       0,     7,    78,    78,     7,     0,    75,    83,    84,    85,
      25,     6,    53,    20,    20,    30,    54,    86,    56,     6,
      96,    24,    98,    99,   100,   101,   102,   103,   104,   105,
      33,    55,    53,    69,    70,    71,    61,    62,    63,    64,
      65,   117,    49,     9,    69,    70,    71,   123,   123,   118,
      54,    53,    56,    59,     1,    52,     3,     4,     5,     6,
       7,     8,     9,   139,    11,    12,    13,    14,   144,    58,
      17,     4,    16,    20,    18,   151,    58,   153,   168,    86,
       3,     4,     6,   173,   174,   161,    53,    53,   164,    59,
      53,    38,    39,     9,    60,    61,    62,    63,    64,    65,
      66,    67,    55,    69,    70,    71,    53,    54,    57,    56,
      52,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     3,     4,     5,     6,    56,
       8,    60,    53,    11,    12,    13,    14,    53,    16,    17,
      18,    52,     7,    53,    60,    61,    62,    63,    64,    65,
      66,    67,    53,    69,    70,    71,    54,   151,    54,   153,
      38,    39,    54,     3,     4,     5,     6,   161,     8,    54,
     164,    11,    12,    13,    14,    59,    54,    17,    56,    69,
      58,    59,    57,     6,    62,    55,    55,     0,     1,    53,
      68,    58,    70,    71,     7,    53,    15,    53,    38,    39,
      51,     3,     4,     5,     6,    59,     8,    20,    51,    11,
      12,    13,    14,    51,    54,    17,    56,     6,    58,    59,
      24,    49,    62,    17,     3,     4,     5,     6,    68,     8,
      70,    71,   136,   158,   138,   144,    38,    39,    -1,   143,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,    -1,
      -1,   155,    54,    -1,    56,    -1,    58,    -1,    -1,    -1,
      62,    -1,     3,     4,     5,     6,    68,     8,    70,    71,
      61,    62,    63,    64,    65,    54,    55,    56,    69,    70,
      71,    -1,    -1,    62,    -1,     3,     4,     5,     6,    68,
       8,    70,    71,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,     3,     4,     5,     6,    68,     8,
      70,    71,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,     3,     4,     5,     6,    68,     8,    70,
      71,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,     3,     4,     5,     6,
      68,     8,    70,    71,    -1,    54,    55,    56,    -1,     3,
       4,     5,     6,    62,     8,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    -1,    54,    55,    56,     9,    63,    64,
      65,    -1,    62,    -1,    69,    70,    71,    -1,    68,    -1,
      70,    71,    -1,     9,    -1,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    62,     9,    -1,    -1,    -1,
      54,    68,    56,    70,    71,    -1,    -1,    -1,    62,     9,
      -1,    -1,    -1,    55,    68,    -1,    70,    71,    60,    61,
      62,    63,    64,    65,    66,    67,    52,    69,    70,    71,
       9,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    55,    69,    70,    71,     9,    60,    61,    62,
      63,    64,    65,    66,    67,    55,    69,    70,    71,     9,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    71,     9,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    52,
      69,    70,    71,     9,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    71,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    61,    62,    63,    64,    65,    66,
      67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      -1,    67,    -1,    69,    70,    71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,    20,    75,    76,    77,    78,   101,    53,
       6,   102,     0,    76,     6,    79,    80,    82,    53,    58,
      54,    56,    81,    53,    52,    58,    85,     1,    78,    86,
      87,   101,    55,    78,    83,    84,     4,     6,    79,    86,
      53,    80,    88,    89,    59,    86,    53,    80,    55,    52,
      57,     3,     4,     5,     6,     8,    11,    12,    13,    14,
      17,    38,    39,    54,    56,    62,    68,    70,    71,    85,
      90,    91,    99,    60,    53,    52,    83,    81,    54,    81,
      99,    53,    53,    54,    54,    54,    54,    99,    99,   100,
      99,    99,    99,    99,    59,    90,     9,    53,    60,    61,
      62,    63,    64,    65,    66,    67,    69,    70,    71,    99,
      88,    55,   100,    53,    99,    99,    99,    53,    78,    88,
      95,    96,    55,    52,    57,    99,    99,    99,    99,    99,
      99,    99,    99,    99,     6,    55,    55,    55,    55,    53,
      97,    99,    88,    55,    53,   100,    91,    58,    91,    98,
      99,    53,    91,    53,    97,    15,    16,    18,    92,    93,
      94,    52,    98,    98,    53,    91,     3,     4,    51,    94,
      59,    98,    98,    51,    51,    90,    90,    90
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 60 "parser.y"
    { display((yyvsp[(1) - (1)].ptr),0); /*semantic_Analysis0($1);*/;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 62 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 63 "parser.y"
    {(yyval.ptr)=mknode(2,DECL_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 65 "parser.y"
    {(yyval.ptr)=mknode(2,VAR_DECL,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 66 "parser.y"
    {(yyval.ptr)=mknode(3,FUNC_DECL,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 67 "parser.y"
    {(yyval.ptr)=mknode(1,STRUCT_DECL,yylineno,(yyvsp[(1) - (2)].ptr));;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 68 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 70 "parser.y"
    {(yyval.ptr)=mknode(0,TYPE,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));(yyval.ptr)->type=!strcmp((yyvsp[(1) - (1)].type_id),"int")?INT:FLOAT;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 72 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 73 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_DEC_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 75 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 76 "parser.y"
    {(yyval.ptr)=mknode(1,ARRAY_LIST,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (2)].type_id));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 78 "parser.y"
    {(yyval.ptr)=mknode(0,ARRAY_LIST,yylineno);(yyval.ptr)->type_int=(yyvsp[(2) - (3)].type_int);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 79 "parser.y"
    {(yyval.ptr)=mknode(2,ARRAY_LIST,yylineno,(yyvsp[(2) - (4)].type_int),(yyvsp[(4) - (4)].ptr));(yyval.ptr)->type_int=(yyvsp[(2) - (4)].type_int);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    {(yyval.ptr)=mknode(1,FUNC_DEF,yylineno,(yyvsp[(3) - (4)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    {(yyval.ptr)=mknode(0,FUNC_DEF,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));(yyval.ptr)->ptr[0]=NULL;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 84 "parser.y"
    {(yyval.ptr)=mknode(1,PARA_LIST,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 85 "parser.y"
    {(yyval.ptr)=mknode(2,PARA_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 87 "parser.y"
    {(yyval.ptr)=mknode(2,PARA_DECL,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 89 "parser.y"
    {(yyval.ptr)=mknode(2,COMP_STMT,yylineno,(yyvsp[(2) - (4)].ptr),(yyvsp[(3) - (4)].ptr));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 92 "parser.y"
    {(yyval.ptr)=mknode(2,DEF_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 95 "parser.y"
    {(yyval.ptr)=mknode(2,DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (2)].ptr);}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 98 "parser.y"
    {(yyval.ptr)=mknode(1,DEC_LIST,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 99 "parser.y"
    {(yyval.ptr)=mknode(2,DEC_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 101 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 102 "parser.y"
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    {(yyval.ptr)=mknode(2,STMT_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    {(yyval.ptr)=mknode(1,EXP_STMT,yylineno,(yyvsp[(1) - (2)].ptr));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    {(yyval.ptr)=mknode(1,RETURN,yylineno,(yyvsp[(2) - (3)].ptr));;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    {(yyval.ptr)=mknode(2,IF_THEN,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    {(yyval.ptr)=mknode(3,IF_ELSE,yylineno,(yyvsp[(3) - (7)].ptr),(yyvsp[(5) - (7)].ptr),(yyvsp[(7) - (7)].ptr));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    {(yyval.ptr)=mknode(2,WHILE,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    {(yyval.ptr)=mknode(2,FOR,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    {(yyval.ptr) = mknode(0,CONTINUE,yylineno); strcpy((yyval.ptr)->type_id, "CONTINUE"); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {(yyval.ptr) = mknode(0,BREAK,yylineno); strcpy((yyval.ptr)->type_id, "BREAK"); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    {(yyval.ptr) = mknode(2,SWITCH,yylineno,(yyvsp[(3) - (7)].ptr),(yyvsp[(6) - (7)].ptr)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    {(yyval.ptr)=mknode(1, CASE_STMT, yylineno, (yyvsp[(4) - (4)].ptr));(yyval.ptr)->type_int=(yyvsp[(2) - (4)].type_int);(yyval.ptr)->type=INT;;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    {(yyval.ptr)=mknode(1, CASE_STMT, yylineno, (yyvsp[(4) - (4)].ptr));(yyval.ptr)->type_char=(yyvsp[(2) - (4)].type_char);(yyval.ptr)->type=CHAR;;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 121 "parser.y"
    {(yyval.ptr)=mknode(1, DEFAULT_STMT, yylineno, (yyvsp[(3) - (3)].ptr));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    {(yyval.ptr)=mknode(2, CASE_STMT_LIST, yylineno, (yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    {(yyval.ptr)=mknode(1, CASE_STMT_LIST, yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,(yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,(yyvsp[(1) - (4)].ptr),NULL,(yyvsp[(4) - (4)].ptr));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,NULL,(yyvsp[(2) - (4)].ptr),(yyvsp[(4) - (4)].ptr));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,(yyvsp[(1) - (3)].ptr),NULL,NULL);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,NULL,(yyvsp[(2) - (3)].ptr),NULL);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL,yylineno,NULL,NULL,(yyvsp[(3) - (3)].ptr));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DECL, yylineno, NULL, NULL, NULL);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 136 "parser.y"
    {(yyval.ptr)=mknode(1, FOR_EXP1, yylineno, (yyvsp[(1) - (1)].ptr));;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP1, yylineno, (yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr));;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    {(yyval.ptr)=mknode(1, FOR_EXP2, yylineno, (yyvsp[(1) - (1)].ptr));;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP3, yylineno, (yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP3, yylineno, (yyvsp[(1) - (1)].ptr), NULL);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    {(yyval.ptr)=mknode(2,AND,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"AND");;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    {(yyval.ptr)=mknode(2,OR,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"OR");;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    {(yyval.ptr)=mknode(2,ADD,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ADD");;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    {(yyval.ptr)=mknode(2,SUB,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"SUB");;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    {(yyval.ptr)=mknode(2,MUL,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"MUL");;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"DIV");;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"MOD");;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    {(yyval.ptr)=mknode(2,RELOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(2) - (3)].type_id));;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    {(yyval.ptr)=mknode(1,SELFADD,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"SELFADD");;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {(yyval.ptr)=mknode(1,SELFSUB,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"SELFSUB");;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    {(yyval.ptr)=mknode(1,SELFADD,yylineno,(yyvsp[(1) - (2)].ptr));strcpy((yyval.ptr)->type_id,"SELFADD");;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    {(yyval.ptr)=mknode(1,SELFSUB,yylineno,(yyvsp[(1) - (2)].ptr));strcpy((yyval.ptr)->type_id,"SELFSUB");;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    {(yyval.ptr)=mknode(1,UMINUS,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"UMINUS");;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    {(yyval.ptr)=mknode(1,NOT,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"NOT");;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    {(yyval.ptr)=mknode(1,FUNC_CALL,yylineno,(yyvsp[(3) - (4)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    {(yyval.ptr)=mknode(0,FUNC_CALL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[(1) - (1)].type_int);(yyval.ptr)->type=INT;;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {(yyval.ptr)=mknode(0,CHAR,yylineno);(yyval.ptr)->type_char=(yyvsp[(1) - (1)].type_char);(yyval.ptr)->type=CHAR;;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    {(yyval.ptr)=mknode(0,FLOAT,yylineno);(yyval.ptr)->type_float=(yyvsp[(1) - (1)].type_float);(yyval.ptr)->type=FLOAT;;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    {(yyval.ptr)=mknode(0,STRING,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));(yyval.ptr)->type=STRING;;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {(yyval.ptr)=mknode(1,ID,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (2)].type_id));;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    {(yyval.ptr)=mknode(1,STRUCT_VISIT,yylineno,(yyvsp[(1) - (3)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(3) - (3)].type_id));;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    {(yyval.ptr)=mknode(2,ARGS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 173 "parser.y"
    {(yyval.ptr)=mknode(1,ARGS,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    {(yyval.ptr)=mknode(2, STRUCT_CREATE, yylineno, (yyvsp[(2) - (5)].ptr), (yyvsp[(4) - (5)].ptr));;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;



/* Line 1455 of yacc.c  */
#line 2356 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 180 "parser.y"


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

