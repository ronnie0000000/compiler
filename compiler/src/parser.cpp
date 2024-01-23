/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <assert.h>
    #include <string>
    #include <stack>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
    Type *nowType;
    ArrayType *currentArray;
    std::stack<ArrayInit*> arrayStack;
    std::stack<WhileStmt*> whileStack;
    unsigned int leftBraceCount=0;
    unsigned int arrayIndex=0;
    int *arrayValue;

#line 86 "src/parser.cpp"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOATING = 5,                   /* FLOATING  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_BREAK = 9,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_CONST = 11,                     /* CONST  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_FLOAT = 14,                     /* FLOAT  */
  YYSYMBOL_LPAREN = 15,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 16,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_LSQUARE = 19,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 20,                   /* RSQUARE  */
  YYSYMBOL_SEMICOLON = 21,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_ADD = 24,                       /* ADD  */
  YYSYMBOL_SUB = 25,                       /* SUB  */
  YYSYMBOL_MUL = 26,                       /* MUL  */
  YYSYMBOL_DIV = 27,                       /* DIV  */
  YYSYMBOL_MOD = 28,                       /* MOD  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_LOGIC_OR = 31,                  /* LOGIC_OR  */
  YYSYMBOL_LOGIC_AND = 32,                 /* LOGIC_AND  */
  YYSYMBOL_LESS = 33,                      /* LESS  */
  YYSYMBOL_MORE = 34,                      /* MORE  */
  YYSYMBOL_LESSOREQUAL = 35,               /* LESSOREQUAL  */
  YYSYMBOL_MOREOREQUAL = 36,               /* MOREOREQUAL  */
  YYSYMBOL_EQUAL = 37,                     /* EQUAL  */
  YYSYMBOL_UNEQUAL = 38,                   /* UNEQUAL  */
  YYSYMBOL_ASSIGN = 39,                    /* ASSIGN  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_THEN = 41,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_Program = 43,                   /* Program  */
  YYSYMBOL_Stmts = 44,                     /* Stmts  */
  YYSYMBOL_Stmt = 45,                      /* Stmt  */
  YYSYMBOL_LVal = 46,                      /* LVal  */
  YYSYMBOL_AssignStmt = 47,                /* AssignStmt  */
  YYSYMBOL_ExprStmt = 48,                  /* ExprStmt  */
  YYSYMBOL_BlockStmt = 49,                 /* BlockStmt  */
  YYSYMBOL_50_1 = 50,                      /* $@1  */
  YYSYMBOL_IfStmt = 51,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 52,                 /* WhileStmt  */
  YYSYMBOL_53_2 = 53,                      /* @2  */
  YYSYMBOL_BreakStmt = 54,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 55,              /* ContinueStmt  */
  YYSYMBOL_ReturnStmt = 56,                /* ReturnStmt  */
  YYSYMBOL_Exp = 57,                       /* Exp  */
  YYSYMBOL_Cond = 58,                      /* Cond  */
  YYSYMBOL_PrimaryExp = 59,                /* PrimaryExp  */
  YYSYMBOL_UnaryExp = 60,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 61,               /* FuncRParams  */
  YYSYMBOL_MulExp = 62,                    /* MulExp  */
  YYSYMBOL_AddExp = 63,                    /* AddExp  */
  YYSYMBOL_RelExp = 64,                    /* RelExp  */
  YYSYMBOL_EqExp = 65,                     /* EqExp  */
  YYSYMBOL_LAndExp = 66,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 67,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 68,                  /* ConstExp  */
  YYSYMBOL_Type = 69,                      /* Type  */
  YYSYMBOL_ArrayIndices = 70,              /* ArrayIndices  */
  YYSYMBOL_DeclStmt = 71,                  /* DeclStmt  */
  YYSYMBOL_ConstDeclStmt = 72,             /* ConstDeclStmt  */
  YYSYMBOL_ConstDefList = 73,              /* ConstDefList  */
  YYSYMBOL_ConstDefStmt = 74,              /* ConstDefStmt  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_ConstInitVal = 76,              /* ConstInitVal  */
  YYSYMBOL_VarDeclStmt = 77,               /* VarDeclStmt  */
  YYSYMBOL_VarDefList = 78,                /* VarDefList  */
  YYSYMBOL_VarDefStmt = 79,                /* VarDefStmt  */
  YYSYMBOL_80_4 = 80,                      /* $@4  */
  YYSYMBOL_InitVal = 81,                   /* InitVal  */
  YYSYMBOL_82_5 = 82,                      /* $@5  */
  YYSYMBOL_InitValList = 83,               /* InitValList  */
  YYSYMBOL_FuncDef = 84,                   /* FuncDef  */
  YYSYMBOL_85_6 = 85,                      /* $@6  */
  YYSYMBOL_86_7 = 86,                      /* $@7  */
  YYSYMBOL_FuncFParams = 87,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 88                 /* FuncFParam  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   220

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    64,    65,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    85,    99,   116,   122,
     129,   128,   137,   142,   150,   160,   160,   178,   187,   196,
     199,   206,   210,   213,   216,   219,   224,   231,   235,   281,
     291,   300,   307,   308,   312,   316,   319,   336,   353,   373,
     375,   388,   403,   405,   411,   417,   423,   431,   433,   438,
     445,   447,   463,   471,   473,   489,   497,   502,   506,   510,
     516,   519,   523,   531,   536,   543,   548,   552,   555,   574,
     574,   610,   618,   625,   629,   635,   654,   677,   711,   711,
     747,   756,   771,   771,   800,   804,   810,   814,   810,   844,
     848,   852,   856,   866
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "FLOATING", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "CONST", "INT",
  "VOID", "FLOAT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LSQUARE",
  "RSQUARE", "SEMICOLON", "COMMA", "NOT", "ADD", "SUB", "MUL", "DIV",
  "MOD", "OR", "AND", "LOGIC_OR", "LOGIC_AND", "LESS", "MORE",
  "LESSOREQUAL", "MOREOREQUAL", "EQUAL", "UNEQUAL", "ASSIGN", "RETURN",
  "THEN", "$accept", "Program", "Stmts", "Stmt", "LVal", "AssignStmt",
  "ExprStmt", "BlockStmt", "$@1", "IfStmt", "WhileStmt", "@2", "BreakStmt",
  "ContinueStmt", "ReturnStmt", "Exp", "Cond", "PrimaryExp", "UnaryExp",
  "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp",
  "LOrExp", "ConstExp", "Type", "ArrayIndices", "DeclStmt",
  "ConstDeclStmt", "ConstDefList", "ConstDefStmt", "$@3", "ConstInitVal",
  "VarDeclStmt", "VarDefList", "VarDefStmt", "$@4", "InitVal", "$@5",
  "InitValList", "FuncDef", "$@6", "$@7", "FuncFParams", "FuncFParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-97)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     180,    13,   -48,   -48,    40,    44,     0,    61,    97,   -48,
     -48,   -48,    37,    16,   -48,    37,    37,    37,    14,   103,
     180,   -48,    68,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,    96,   -48,   -48,    95,    23,   116,   -48,   -48,   -48,
     -48,    37,    75,   105,    37,    37,   -48,   -48,   129,   -48,
     119,   -48,   180,   -48,   -48,   -48,   -48,   115,   -48,   -48,
      37,   -48,    37,    37,    37,    37,    37,    -3,    55,   -48,
     -48,    -2,   -48,   120,    37,   123,    23,    51,    59,   -17,
      22,   126,   -13,    94,   -48,   -48,   156,   -48,   124,   -48,
     -48,   -48,    95,    95,    89,     4,   131,   -48,   144,   -48,
      37,   -48,   128,   180,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,   -48,    37,     5,   -48,   129,   -48,
     -48,   132,   -48,   -48,   -48,    97,     6,   -48,   -48,   -48,
     142,    23,    23,    23,    23,    51,    51,    59,    59,   -17,
     -17,   180,    23,   -48,   -48,   -48,   -48,   -48,    89,    89,
     148,    11,   -48,   180,   -48,    89,   -48,    28,   -48,   133,
     -48,    97,   -48,   -48,   -48,    89,   105,   136,   -48,   -48,
     -48
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    35,    36,     0,     0,     0,     0,     0,    67,
      68,    69,     0,    20,    15,     0,     0,     0,     0,     0,
       2,     3,    34,     5,     6,     7,     8,     9,    10,    11,
      12,     0,    37,    45,    49,    31,     0,    13,    73,    74,
      14,    44,     0,    17,     0,     0,    27,    28,     0,    34,
       0,    22,     0,    41,    39,    40,    29,     0,     1,     4,
       0,    19,     0,     0,     0,     0,     0,    85,     0,    84,
      42,     0,    72,     0,     0,     0,    52,    57,    60,    63,
      32,     0,     0,     0,    77,    33,     0,    30,     0,    46,
      47,    48,    50,    51,     0,    87,     0,    82,     0,    38,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,     0,    75,     0,    21,
      18,    92,    90,    86,    88,   101,    85,    83,    43,    71,
      23,    53,    54,    55,    56,    58,    59,    62,    61,    65,
      64,     0,    66,    81,    78,    79,    76,    91,     0,     0,
       0,     0,    99,     0,    26,     0,    95,     0,    89,   102,
      97,     0,    24,    80,    93,     0,   103,     0,   100,    94,
      98
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,   111,   -12,     2,   -48,   -48,   -10,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -11,   127,   -48,    -6,   -48,
      60,   -40,    19,    20,    21,   -48,   -48,    -5,    -1,   -48,
     -48,   -48,    57,   -48,   -48,   -48,   -48,    78,   -48,   -47,
     -48,   -48,   -48,   -48,   -48,   -48,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    49,    23,    24,    25,    52,    26,
      27,   141,    28,    29,    30,    31,    75,    32,    33,    71,
      34,    35,    77,    78,    79,    80,   143,    36,    95,    37,
      38,    83,    84,   155,   144,    39,    68,    69,   149,   123,
     148,   157,    40,    96,   167,   151,   152
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    50,    22,    48,    76,    76,    42,    57,    59,    53,
      54,    55,   -96,   110,    99,   111,    42,     1,     2,     3,
     100,    46,    22,    74,    74,    42,   115,   160,    41,    12,
      70,    73,    42,   161,    51,    56,    94,    15,    16,    17,
       1,     2,     3,   124,   145,    94,   164,    65,    66,    88,
     165,   112,    12,   113,    22,    44,    89,    90,    91,    45,
      15,    16,    17,   102,   131,   132,   133,   134,    76,    76,
      76,    76,    76,    76,    59,   142,    97,    98,     1,     2,
       3,   116,    47,   122,   104,   105,   106,   107,    22,   128,
      12,   130,     1,     2,     3,    72,   108,   109,    15,    16,
      17,   156,   158,    58,    12,    22,   121,    60,   163,     9,
      10,    11,    15,    16,    17,   117,   118,    61,   169,    67,
     150,    62,    63,    64,    74,    92,    93,   135,   136,   154,
     137,   138,    82,   139,   140,    85,    87,   122,   122,   103,
     101,   162,   114,    22,   122,   120,   125,   126,   129,   153,
     147,   159,    42,    13,   122,    22,   150,   170,   166,     1,
       2,     3,     4,    86,     5,     6,     7,     8,     9,    10,
      11,    12,    81,    13,   119,   146,   127,    14,   168,    15,
      16,    17,     0,     1,     2,     3,     4,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    18,    13,     0,     0,
       0,    14,     0,    15,    16,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18
};

static const yytype_int16 yycheck[] =
{
       1,    12,     0,     8,    44,    45,    19,    18,    20,    15,
      16,    17,    15,    30,    16,    32,    19,     3,     4,     5,
      22,    21,    20,    19,    19,    19,    39,    16,    15,    15,
      41,    42,    19,    22,    18,    21,    39,    23,    24,    25,
       3,     4,     5,    39,    39,    39,    18,    24,    25,    60,
      22,    29,    15,    31,    52,    15,    62,    63,    64,    15,
      23,    24,    25,    74,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    86,   115,    21,    22,     3,     4,
       5,    82,    21,    94,    33,    34,    35,    36,    86,   100,
      15,   103,     3,     4,     5,    20,    37,    38,    23,    24,
      25,   148,   149,     0,    15,   103,    17,    39,   155,    12,
      13,    14,    23,    24,    25,    21,    22,    21,   165,     3,
     125,    26,    27,    28,    19,    65,    66,   108,   109,   141,
     110,   111,     3,   112,   113,    16,    21,   148,   149,    16,
      20,   153,    16,   141,   155,    21,    15,     3,    20,     7,
      18,     3,    19,    17,   165,   153,   161,   167,   159,     3,
       4,     5,     6,    52,     8,     9,    10,    11,    12,    13,
      14,    15,    45,    17,    18,   118,    98,    21,   161,    23,
      24,    25,    -1,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    40,    17,    -1,    -1,
      -1,    21,    -1,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    14,    15,    17,    21,    23,    24,    25,    40,    43,
      44,    45,    46,    47,    48,    49,    51,    52,    54,    55,
      56,    57,    59,    60,    62,    63,    69,    71,    72,    77,
      84,    15,    19,    70,    15,    15,    21,    21,    69,    46,
      57,    18,    50,    60,    60,    60,    21,    57,     0,    45,
      39,    21,    26,    27,    28,    24,    25,     3,    78,    79,
      57,    61,    20,    57,    19,    58,    63,    64,    65,    66,
      67,    58,     3,    73,    74,    16,    44,    21,    57,    60,
      60,    60,    62,    62,    39,    70,    85,    21,    22,    16,
      22,    20,    57,    16,    33,    34,    35,    36,    37,    38,
      30,    32,    29,    31,    16,    39,    70,    21,    22,    18,
      21,    17,    57,    81,    39,    15,     3,    79,    57,    20,
      45,    63,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    53,    63,    68,    76,    39,    74,    18,    82,    80,
      69,    87,    88,     7,    45,    75,    81,    83,    81,     3,
      16,    22,    45,    81,    18,    22,    70,    86,    88,    81,
      49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    46,    46,    47,    48,
      50,    49,    49,    51,    51,    53,    52,    54,    55,    56,
      56,    57,    58,    59,    59,    59,    59,    60,    60,    60,
      60,    60,    61,    61,    61,    62,    62,    62,    62,    63,
      63,    63,    64,    64,    64,    64,    64,    65,    65,    65,
      66,    66,    66,    67,    67,    67,    68,    69,    69,    69,
      70,    70,    70,    71,    71,    72,    73,    73,    74,    75,
      74,    76,    77,    78,    78,    79,    79,    79,    80,    79,
      81,    81,    82,    81,    83,    83,    85,    86,    84,    87,
      87,    87,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     2,
       0,     4,     2,     5,     7,     0,     6,     2,     2,     2,
       3,     1,     1,     3,     1,     1,     1,     1,     4,     2,
       2,     2,     1,     3,     0,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     1,     1,     1,
       3,     4,     2,     1,     1,     4,     3,     1,     3,     0,
       5,     1,     3,     3,     1,     1,     3,     2,     0,     5,
       1,     2,     0,     4,     3,     1,     0,     0,     8,     1,
       3,     0,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Stmts  */
#line 58 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1301 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmt  */
#line 64 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1307 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmts Stmt  */
#line 65 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1315 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 71 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1321 "src/parser.cpp"
    break;

  case 6: /* Stmt: ExprStmt  */
#line 72 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1327 "src/parser.cpp"
    break;

  case 7: /* Stmt: BlockStmt  */
#line 73 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1333 "src/parser.cpp"
    break;

  case 8: /* Stmt: IfStmt  */
#line 74 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1339 "src/parser.cpp"
    break;

  case 9: /* Stmt: WhileStmt  */
#line 75 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1345 "src/parser.cpp"
    break;

  case 10: /* Stmt: BreakStmt  */
#line 76 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1351 "src/parser.cpp"
    break;

  case 11: /* Stmt: ContinueStmt  */
#line 77 "src/parser.y"
                   {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1357 "src/parser.cpp"
    break;

  case 12: /* Stmt: ReturnStmt  */
#line 78 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1363 "src/parser.cpp"
    break;

  case 13: /* Stmt: DeclStmt  */
#line 79 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1369 "src/parser.cpp"
    break;

  case 14: /* Stmt: FuncDef  */
#line 80 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1375 "src/parser.cpp"
    break;

  case 15: /* Stmt: SEMICOLON  */
#line 81 "src/parser.y"
               {(yyval.stmttype)=new EmptyStmt();}
#line 1381 "src/parser.cpp"
    break;

  case 16: /* LVal: ID  */
#line 85 "src/parser.y"
         {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            assert(se != nullptr);
        }
        Id *id= new Id(se);
        (yyval.exprtype) = id;
        delete [](yyvsp[0].strtype);
    }
#line 1399 "src/parser.cpp"
    break;

  case 17: /* LVal: ID ArrayIndices  */
#line 99 "src/parser.y"
                   {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-1].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-1].strtype));
            delete [](char*)(yyvsp[-1].strtype);
            assert(se != nullptr);
        }
        Id *id = new Id(se,(yyvsp[0].exprtype));
        (yyval.exprtype) = id;
        delete [](yyvsp[-1].strtype);
    }
#line 1417 "src/parser.cpp"
    break;

  case 18: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 116 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1425 "src/parser.cpp"
    break;

  case 19: /* ExprStmt: Exp SEMICOLON  */
#line 122 "src/parser.y"
                    {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
    }
#line 1433 "src/parser.cpp"
    break;

  case 20: /* $@1: %empty  */
#line 129 "src/parser.y"
        {identifiers = new SymbolTable(identifiers);}
#line 1439 "src/parser.cpp"
    break;

  case 21: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 131 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *currentSymbolTable = identifiers;
            identifiers = identifiers->getPrev();
            delete currentSymbolTable;
        }
#line 1450 "src/parser.cpp"
    break;

  case 22: /* BlockStmt: LBRACE RBRACE  */
#line 137 "src/parser.y"
                    {
        (yyval.stmttype) = new CompoundStmt(nullptr);
    }
#line 1458 "src/parser.cpp"
    break;

  case 23: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 142 "src/parser.y"
                                            {
        if(!(yyvsp[-2].exprtype)->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            (yyvsp[-2].exprtype) = new BinaryExpr(se_temp, BinaryExpr::UNEQUAL, (yyvsp[-2].exprtype), new Constant(se_zero));
        }
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1471 "src/parser.cpp"
    break;

  case 24: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 150 "src/parser.y"
                                           {
        if(!(yyvsp[-4].exprtype)->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            (yyvsp[-4].exprtype) = new BinaryExpr(se_temp, BinaryExpr::UNEQUAL, (yyvsp[-4].exprtype), new Constant(se_zero));
        }
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1484 "src/parser.cpp"
    break;

  case 25: /* @2: %empty  */
#line 160 "src/parser.y"
                               {
        if(!(yyvsp[-1].exprtype)->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            (yyvsp[-1].exprtype) = new BinaryExpr(se_temp, BinaryExpr::UNEQUAL, (yyvsp[-1].exprtype), new Constant(se_zero));
        }
        WhileStmt* whileStmt = new WhileStmt((yyvsp[-1].exprtype),nullptr);
        (yyval.stmttype) = whileStmt;
        whileStack.push(whileStmt);
    }
#line 1499 "src/parser.cpp"
    break;

  case 26: /* WhileStmt: WHILE LPAREN Cond RPAREN @2 Stmt  */
#line 170 "src/parser.y"
         {
        StmtNode *whileStmt = (yyvsp[-1].stmttype); 
        ((WhileStmt*)whileStmt)->setStmt((yyvsp[0].stmttype));
        (yyval.stmttype)=whileStmt;
        whileStack.pop();
    }
#line 1510 "src/parser.cpp"
    break;

  case 27: /* BreakStmt: BREAK SEMICOLON  */
#line 178 "src/parser.y"
                      {
        if(whileStack.empty()){
            fprintf(stderr,"break stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        (yyval.stmttype) = new BreakStmt(whileStack.top());
    }
#line 1522 "src/parser.cpp"
    break;

  case 28: /* ContinueStmt: CONTINUE SEMICOLON  */
#line 187 "src/parser.y"
                         {
        if(whileStack.empty()){
            fprintf(stderr,"continue stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        (yyval.stmttype) = new ContinueStmt(whileStack.top());
    }
#line 1534 "src/parser.cpp"
    break;

  case 29: /* ReturnStmt: RETURN SEMICOLON  */
#line 196 "src/parser.y"
                       {
        (yyval.stmttype) = new ReturnStmt();
    }
#line 1542 "src/parser.cpp"
    break;

  case 30: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 199 "src/parser.y"
                           {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1550 "src/parser.cpp"
    break;

  case 31: /* Exp: AddExp  */
#line 206 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1556 "src/parser.cpp"
    break;

  case 32: /* Cond: LOrExp  */
#line 210 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1562 "src/parser.cpp"
    break;

  case 33: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 213 "src/parser.y"
                        {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1570 "src/parser.cpp"
    break;

  case 34: /* PrimaryExp: LVal  */
#line 216 "src/parser.y"
           {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1578 "src/parser.cpp"
    break;

  case 35: /* PrimaryExp: INTEGER  */
#line 219 "src/parser.y"
              {
        //符号表元素添加值
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1588 "src/parser.cpp"
    break;

  case 36: /* PrimaryExp: FLOATING  */
#line 224 "src/parser.y"
               {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, (yyvsp[0].ftype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1597 "src/parser.cpp"
    break;

  case 37: /* UnaryExp: PrimaryExp  */
#line 231 "src/parser.y"
               {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1605 "src/parser.cpp"
    break;

  case 38: /* UnaryExp: ID LPAREN FuncRParams RPAREN  */
#line 235 "src/parser.y"
                                  {
        
        SymbolEntry* se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)(yyvsp[-3].strtype));
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }
        std::vector<Type*> paramsType = ((FunctionType*)(se->getType()))->getParamsType();
        ExprNode* callParamsType = (yyvsp[-1].exprtype);
        int paramCount = 0;
        
        while(callParamsType){
            paramCount++;
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        
        while(se){
            if(((FunctionType*)(se->getType()))->getParamsType().size() == paramCount){
                break;
            }
            se = se->getNext();
        }
        if(se == nullptr){
            fprintf(stderr, "function \"%s\" having %d params, is undefined\n", (char*)(yyvsp[-3].strtype), paramCount);
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }

        callParamsType = (yyvsp[-1].exprtype);

        for(auto &params:paramsType){
            if(params != callParamsType->getSymbolEntry()->getType()){
                 if(callParamsType->getSymbolEntry()->getType()->isArray() && params->isArray()){
                    callParamsType = (ExprNode*)callParamsType->getNext();
                    continue;
                }
                fprintf(stderr, "your param TYPE should be %s, but when you call func you use %s\n",
                        params->toStr().c_str(),callParamsType->getSymbolEntry()->getType()->toStr().c_str());
            }
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        (yyval.exprtype) = new FuncExpr(se,(yyvsp[-1].exprtype));
    }
#line 1656 "src/parser.cpp"
    break;

  case 39: /* UnaryExp: ADD UnaryExp  */
#line 281 "src/parser.y"
                  {
        /*SymbolEntry *se;
        if($2->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());

        $$ = new UnaryExpr(se,UnaryExpr::ADD, $2);*/
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1671 "src/parser.cpp"
    break;

  case 40: /* UnaryExp: SUB UnaryExp  */
#line 291 "src/parser.y"
                  {
        SymbolEntry *se;
        if((yyvsp[0].exprtype)->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(se, UnaryExpr::SUB, (yyvsp[0].exprtype));

    }
#line 1685 "src/parser.cpp"
    break;

  case 41: /* UnaryExp: NOT UnaryExp  */
#line 300 "src/parser.y"
                  {
        SymbolEntry *se;
        se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(se, UnaryExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1695 "src/parser.cpp"
    break;

  case 42: /* FuncRParams: Exp  */
#line 307 "src/parser.y"
          {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1701 "src/parser.cpp"
    break;

  case 43: /* FuncRParams: FuncRParams COMMA Exp  */
#line 308 "src/parser.y"
                            {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
        (yyval.exprtype)->setNext((yyvsp[0].exprtype));
    }
#line 1710 "src/parser.cpp"
    break;

  case 44: /* FuncRParams: %empty  */
#line 312 "src/parser.y"
             {(yyval.exprtype)=nullptr;}
#line 1716 "src/parser.cpp"
    break;

  case 45: /* MulExp: UnaryExp  */
#line 316 "src/parser.y"
            {
        (yyval.exprtype)=(yyvsp[0].exprtype);
    }
#line 1724 "src/parser.cpp"
    break;

  case 46: /* MulExp: MulExp MUL UnaryExp  */
#line 319 "src/parser.y"
                         {
        SymbolEntry* se;

        if ((yyvsp[-2].exprtype)->getType()->isBool() || (yyvsp[0].exprtype)->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MUL\n");
            assert(!(yyvsp[-2].exprtype)->getType()->isBool());
            assert(!(yyvsp[0].exprtype)->getType()->isBool());
        }

        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1746 "src/parser.cpp"
    break;

  case 47: /* MulExp: MulExp DIV UnaryExp  */
#line 336 "src/parser.y"
                         {
        SymbolEntry* se;

        if ((yyvsp[-2].exprtype)->getType()->isBool() || (yyvsp[0].exprtype)->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in DIV\n");
            assert(!(yyvsp[-2].exprtype)->getType()->isBool());
            assert(!(yyvsp[0].exprtype)->getType()->isBool());
        }

        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1768 "src/parser.cpp"
    break;

  case 48: /* MulExp: MulExp MOD UnaryExp  */
#line 353 "src/parser.y"
                         {
        SymbolEntry* se;
        
        if ((yyvsp[-2].exprtype)->getType()->isBool() || (yyvsp[0].exprtype)->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MOD\n");
            assert(!(yyvsp[-2].exprtype)->getType()->isBool());
            assert(!(yyvsp[0].exprtype)->getType()->isBool());
        }

        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1790 "src/parser.cpp"
    break;

  case 49: /* AddExp: MulExp  */
#line 373 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1796 "src/parser.cpp"
    break;

  case 50: /* AddExp: AddExp ADD MulExp  */
#line 376 "src/parser.y"
    {
        SymbolEntry* se;

        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1812 "src/parser.cpp"
    break;

  case 51: /* AddExp: AddExp SUB MulExp  */
#line 389 "src/parser.y"
    {
        SymbolEntry* se;

        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1828 "src/parser.cpp"
    break;

  case 52: /* RelExp: AddExp  */
#line 403 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1834 "src/parser.cpp"
    break;

  case 53: /* RelExp: RelExp LESS AddExp  */
#line 406 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1843 "src/parser.cpp"
    break;

  case 54: /* RelExp: RelExp MORE AddExp  */
#line 412 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MORE, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1852 "src/parser.cpp"
    break;

  case 55: /* RelExp: RelExp LESSOREQUAL AddExp  */
#line 418 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSOREQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1861 "src/parser.cpp"
    break;

  case 56: /* RelExp: RelExp MOREOREQUAL AddExp  */
#line 424 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOREOREQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1870 "src/parser.cpp"
    break;

  case 57: /* EqExp: RelExp  */
#line 431 "src/parser.y"
           {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1876 "src/parser.cpp"
    break;

  case 58: /* EqExp: EqExp EQUAL RelExp  */
#line 433 "src/parser.y"
                      {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1885 "src/parser.cpp"
    break;

  case 59: /* EqExp: EqExp UNEQUAL RelExp  */
#line 438 "src/parser.y"
                        {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::UNEQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1894 "src/parser.cpp"
    break;

  case 60: /* LAndExp: EqExp  */
#line 445 "src/parser.y"
          {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1900 "src/parser.cpp"
    break;

  case 61: /* LAndExp: LAndExp LOGIC_AND EqExp  */
#line 448 "src/parser.y"
    {
        SymbolEntry *boolSe;
        if(!(yyvsp[-2].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[-2].exprtype) = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, (yyvsp[-2].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!(yyvsp[0].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[0].exprtype) = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, (yyvsp[0].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LOGIC_AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1919 "src/parser.cpp"
    break;

  case 62: /* LAndExp: LAndExp AND EqExp  */
#line 464 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1928 "src/parser.cpp"
    break;

  case 63: /* LOrExp: LAndExp  */
#line 471 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1934 "src/parser.cpp"
    break;

  case 64: /* LOrExp: LOrExp LOGIC_OR LAndExp  */
#line 474 "src/parser.y"
    {
        SymbolEntry *boolSe;
        if(!(yyvsp[-2].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[-2].exprtype) = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, (yyvsp[-2].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!(yyvsp[0].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[0].exprtype) = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, (yyvsp[0].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LOGIC_OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1953 "src/parser.cpp"
    break;

  case 65: /* LOrExp: LOrExp OR LAndExp  */
#line 490 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1962 "src/parser.cpp"
    break;

  case 66: /* ConstExp: AddExp  */
#line 497 "src/parser.y"
          {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1970 "src/parser.cpp"
    break;

  case 67: /* Type: INT  */
#line 502 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
        nowType = TypeSystem::intType;
    }
#line 1979 "src/parser.cpp"
    break;

  case 68: /* Type: VOID  */
#line 506 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
        nowType = TypeSystem::voidType;
    }
#line 1988 "src/parser.cpp"
    break;

  case 69: /* Type: FLOAT  */
#line 510 "src/parser.y"
            {
         (yyval.type) = TypeSystem::floatType;
         nowType = TypeSystem::floatType;
    }
#line 1997 "src/parser.cpp"
    break;

  case 70: /* ArrayIndices: LSQUARE Exp RSQUARE  */
#line 516 "src/parser.y"
                          {
        (yyval.exprtype)=(yyvsp[-1].exprtype);
    }
#line 2005 "src/parser.cpp"
    break;

  case 71: /* ArrayIndices: ArrayIndices LSQUARE Exp RSQUARE  */
#line 519 "src/parser.y"
                                       {
        (yyval.exprtype)=(yyvsp[-3].exprtype);
        (yyvsp[-3].exprtype)->setNext((yyvsp[-1].exprtype));
    }
#line 2014 "src/parser.cpp"
    break;

  case 72: /* ArrayIndices: LSQUARE RSQUARE  */
#line 523 "src/parser.y"
                     {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
        (yyval.exprtype) = new Constant(se);
    }
#line 2023 "src/parser.cpp"
    break;

  case 73: /* DeclStmt: ConstDeclStmt  */
#line 531 "src/parser.y"
                 {
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 2031 "src/parser.cpp"
    break;

  case 74: /* DeclStmt: VarDeclStmt  */
#line 536 "src/parser.y"
               {
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 2039 "src/parser.cpp"
    break;

  case 75: /* ConstDeclStmt: CONST Type ConstDefList SEMICOLON  */
#line 543 "src/parser.y"
                                     {
        (yyval.stmttype)=(yyvsp[-1].stmttype);
    }
#line 2047 "src/parser.cpp"
    break;

  case 76: /* ConstDefList: ConstDefList COMMA ConstDefStmt  */
#line 548 "src/parser.y"
                                      {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyvsp[-2].stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2056 "src/parser.cpp"
    break;

  case 77: /* ConstDefList: ConstDefStmt  */
#line 552 "src/parser.y"
                   {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2062 "src/parser.cpp"
    break;

  case 78: /* ConstDefStmt: ID ASSIGN ConstInitVal  */
#line 555 "src/parser.y"
                             {
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::constIntType, (yyvsp[-2].strtype), identifiers->getLevel());
            ((IdentifierSymbolEntry*)se)->setValue((yyvsp[0].exprtype)->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::constFloatType, (yyvsp[-2].strtype), identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue((yyvsp[0].exprtype)->getFValue());
            }
        }
        if (!identifiers->install((yyvsp[-2].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-2].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 2085 "src/parser.cpp"
    break;

  case 79: /* $@3: %empty  */
#line 574 "src/parser.y"
                          {
        // type a[]={...}
        ExprNode* t=(yyvsp[-1].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=nowType->isInt()?TypeSystem::constIntType:TypeSystem::constFloatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
#line 2113 "src/parser.cpp"
    break;

  case 80: /* ConstDefStmt: ID ArrayIndices ASSIGN $@3 InitVal  */
#line 597 "src/parser.y"
           {
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, (yyvsp[-4].strtype), identifiers->getLevel());
        if (!identifiers->install((yyvsp[-4].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-4].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-4].strtype);
    }
#line 2128 "src/parser.cpp"
    break;

  case 81: /* ConstInitVal: ConstExp  */
#line 610 "src/parser.y"
            {
        //需要补充
        (yyval.exprtype)=(yyvsp[0].exprtype);
    }
#line 2137 "src/parser.cpp"
    break;

  case 82: /* VarDeclStmt: Type VarDefList SEMICOLON  */
#line 618 "src/parser.y"
                             {
        (yyval.stmttype)=(yyvsp[-1].stmttype);
    }
#line 2145 "src/parser.cpp"
    break;

  case 83: /* VarDefList: VarDefList COMMA VarDefStmt  */
#line 625 "src/parser.y"
                                {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyvsp[-2].stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2154 "src/parser.cpp"
    break;

  case 84: /* VarDefList: VarDefStmt  */
#line 629 "src/parser.y"
                 { (yyval.stmttype) = (yyvsp[0].stmttype); }
#line 2160 "src/parser.cpp"
    break;

  case 85: /* VarDefStmt: ID  */
#line 635 "src/parser.y"
       {
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::intType, (yyvsp[0].strtype), identifiers->getLevel());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, (yyvsp[0].strtype), identifiers->getLevel()); 
            }
        }
        if (!identifiers->install((yyvsp[0].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[0].strtype));
            assert(false);
        }
        //identifiers->install($1,se);
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[0].strtype);
    }
#line 2182 "src/parser.cpp"
    break;

  case 86: /* VarDefStmt: ID ASSIGN InitVal  */
#line 654 "src/parser.y"
                      {
        SymbolEntry*se;
            if(nowType->isInt()){
                se=new IdentifierSymbolEntry(TypeSystem::intType,(yyvsp[-2].strtype),identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setValue((yyvsp[0].exprtype)->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, (yyvsp[-2].strtype), identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue((yyvsp[0].exprtype)->getFValue());
            }
        }
        if (!identifiers->install((yyvsp[-2].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-2].strtype));
            assert(false);
        }
        //这里还暂时不知道怎么存具体的值，因为InitVal还没实现
        //SymbolEntry*ss=new ConstantSymbolEntry(TypeSystem::intType,$1,)
        (yyval.stmttype) = new DeclStmt(new Id(se),(yyvsp[0].exprtype));
        //不知道这里为什么要delete$1
        delete [](yyvsp[-2].strtype);
    }
#line 2208 "src/parser.cpp"
    break;

  case 87: /* VarDefStmt: ID ArrayIndices  */
#line 677 "src/parser.y"
                    {
        ExprNode* t=(yyvsp[0].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        
        Type*tempType;
        while(!v.empty()){            //te用来接受最新的数组
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, (yyvsp[-1].strtype), identifiers->getLevel());
        //全局变量，初始化为全0
        if(dynamic_cast<IdentifierSymbolEntry*>(se)->isGlobal()){
            dynamic_cast<IdentifierSymbolEntry*>(se)->setAllZero(true);
        }
        if (!identifiers->install((yyvsp[-1].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-1].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[-1].strtype);
    }
#line 2246 "src/parser.cpp"
    break;

  case 88: /* $@4: %empty  */
#line 711 "src/parser.y"
                          {
        // type a[]={...}
        ExprNode* t=(yyvsp[-1].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
#line 2274 "src/parser.cpp"
    break;

  case 89: /* VarDefStmt: ID ArrayIndices ASSIGN $@4 InitVal  */
#line 734 "src/parser.y"
           {
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, (yyvsp[-4].strtype), identifiers->getLevel());
        if (!identifiers->install((yyvsp[-4].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-4].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-4].strtype);
    }
#line 2289 "src/parser.cpp"
    break;

  case 90: /* InitVal: Exp  */
#line 747 "src/parser.y"
       {
        //需要补充
        (yyval.exprtype)=(yyvsp[0].exprtype);
        if(!arrayStack.empty()){
            //初始化数组
            arrayStack.top()->addExpr((yyvsp[0].exprtype));
        }  

    }
#line 2303 "src/parser.cpp"
    break;

  case 91: /* InitVal: LBRACE RBRACE  */
#line 756 "src/parser.y"
                   {
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);
        ArrayInit *arrayNode = new ArrayInit(se,true);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);

        if(!arrayStack.empty())
            currentArray=(ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        (yyval.exprtype)=arrayNode;

    }
#line 2323 "src/parser.cpp"
    break;

  case 92: /* $@5: %empty  */
#line 771 "src/parser.y"
             {
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);

        //if(currentArray->getElementType() != TypeSystem::intType && currentArray->getElementType() != TypeSystem::floatType){
        //    currentArray = (ArrayType*)(currentArray->getElementType());
        //}

        ArrayInit *arrayNode = new ArrayInit(se);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);
        
        arrayStack.push(arrayNode);
        //$<exprtype>$=arrayNode;
    }
#line 2346 "src/parser.cpp"
    break;

  case 93: /* InitVal: LBRACE $@5 InitValList RBRACE  */
#line 789 "src/parser.y"
                      {
        //assert(arrayStack.top()==$<exprtype>2);
        (yyval.exprtype) = arrayStack.top();
        arrayStack.pop();
        if(!arrayStack.empty())
            currentArray=((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()));
        //把0补充上?没必要，遇到第一个大括号就把整个数组设置为0就行
    }
#line 2359 "src/parser.cpp"
    break;

  case 94: /* InitValList: InitValList COMMA InitVal  */
#line 800 "src/parser.y"
                             {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
    }
#line 2367 "src/parser.cpp"
    break;

  case 95: /* InitValList: InitVal  */
#line 804 "src/parser.y"
           {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2375 "src/parser.cpp"
    break;

  case 96: /* $@6: %empty  */
#line 810 "src/parser.y"
            {
        //这里有问题 不能在这里把函数的定义插入 要获取完整的参数之后才能插入
        identifiers = new SymbolTable(identifiers);
    }
#line 2384 "src/parser.cpp"
    break;

  case 97: /* $@7: %empty  */
#line 814 "src/parser.y"
                              {

        Type* funcType;
        std::vector<SymbolEntry*> vec;
        //std::vector<SymbolEntry*> symVec;
        DeclStmt* temp = (DeclStmt*)(yyvsp[-1].stmttype);
        while(temp){
            vec.push_back(temp->getId()->getSymbolEntry());
            //symVec.push_back(temp->getId()->getSymbolEntry());
            temp = (DeclStmt*)(temp->getNext());
        }
        //funcType = new FunctionType($1, vec, symVec);
        funcType = new FunctionType((yyvsp[-5].type), vec);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, (yyvsp[-4].strtype), identifiers->getPrev()->getLevel());
        assert(identifiers->getPrev()->install((yyvsp[-4].strtype), se));
    }
#line 2405 "src/parser.cpp"
    break;

  case 98: /* FuncDef: Type ID $@6 LPAREN FuncFParams RPAREN $@7 BlockStmt  */
#line 831 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-6].strtype));
        assert(se != nullptr);
        (yyval.stmttype) = new FunctionDef(se, (DeclStmt*)(yyvsp[-3].stmttype),(yyvsp[0].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-6].strtype);
    }
#line 2420 "src/parser.cpp"
    break;

  case 99: /* FuncFParams: FuncFParam  */
#line 844 "src/parser.y"
              {
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 2428 "src/parser.cpp"
    break;

  case 100: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 848 "src/parser.y"
                                {
        (yyval.stmttype)=(yyvsp[-2].stmttype);
        (yyval.stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2437 "src/parser.cpp"
    break;

  case 101: /* FuncFParams: %empty  */
#line 852 "src/parser.y"
             {(yyval.stmttype)=nullptr;}
#line 2443 "src/parser.cpp"
    break;

  case 102: /* FuncFParam: Type ID  */
#line 856 "src/parser.y"
           {
        SymbolEntry*se;
        se=new IdentifierSymbolEntry((yyvsp[-1].type),(yyvsp[0].strtype),identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install((yyvsp[0].strtype),se);
        (yyval.stmttype)=new DeclStmt(new Id(se));
        delete[](yyvsp[0].strtype);
    }
#line 2457 "src/parser.cpp"
    break;

  case 103: /* FuncFParam: Type ID ArrayIndices  */
#line 866 "src/parser.y"
                        {
        ExprNode* t=(yyvsp[0].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=(yyvsp[-2].type)->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            //te用来接受最新的数组
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, (yyvsp[-1].strtype), identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install((yyvsp[-1].strtype), se);
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[-1].strtype);
    }
#line 2490 "src/parser.cpp"
    break;


#line 2494 "src/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 896 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
