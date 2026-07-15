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




/* First part of user prologue.  */
#line 28 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef SMART_HOME_TYPES_DEFINED
#define SMART_HOME_TYPES_DEFINED
typedef struct Valor {
    char *texto;
    int tipo;
} Valor;

typedef struct Operand {
    char *texto;
    char *dispositivo;
    char *atributo;
    int clase;
    int valor_tipo;
} Operand;
#endif

extern int yylex(void);
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
extern int errores_lexicos;
extern int linea_token;

static int errores_sintacticos = 0;
static int errores_semanticos = 0;
static const char *archivo_entrada = NULL;
static char archivo_html[512] = "salida.html";

void yyerror(const char *mensaje);
static int tiene_extension_smart(const char *ruta);
static void construir_nombre_html(const char *ruta);
static char *copiar_texto(const char *s);
static void limpiar_ruta_ingresada(char *ruta);
static void esperar_enter_si_interactivo(int modo_interactivo);

/* Tipos de valores reconocidos por el lexer. */
enum {
    VAL_BOOL = 1,
    VAL_MODO,
    VAL_COLOR,
    VAL_EMAIL,
    VAL_TEXTO,
    VAL_HORA,
    VAL_FECHA,
    VAL_TEMP,
    VAL_PERCENT,
    VAL_TIME,
    VAL_LUX,
    VAL_NUMERO,
    VAL_ID
};

/* Tipos de operandos usados en comparaciones. */
enum {
    OP_VALOR = 1,
    OP_SENSOR_NUM,
    OP_SENSOR_BOOL,
    OP_DISP_ATTR
};

typedef struct {
    char dispositivo[128];
    char atributo[64];
    char valor[256];
    int es_email;
} HtmlAccion;

typedef struct {
    char nombre[128];
    char operador[8];
    char valor[128];
} HtmlSensor;

#define MAX_HTML_ACCIONES 300
#define MAX_HTML_SENSORES 150

static HtmlAccion acciones_html[MAX_HTML_ACCIONES];
static int cant_acciones_html = 0;

static HtmlSensor sensores_html[MAX_HTML_SENSORES];
static int cant_sensores_html = 0;

static Valor *crear_valor(char *texto, int tipo);
static void liberar_valor(Valor *v);
static Operand *crear_operando_valor(Valor *v);
static Operand *crear_operando_simple(char *texto, int clase);
static Operand *crear_operando_atributo(char *dispositivo, char *atributo);
static void liberar_operando(Operand *o);

static void registrar_error_semantico(int linea, const char *lexema, const char *mensaje);
static void validar_y_registrar_asignacion(Operand *destino, Valor *valor);
static void validar_comparacion(Operand *izq, const char *op, Operand *der);
static void generar_html(void);

static int igual_icase(const char *a, const char *b);
static int empieza_icase(const char *texto, const char *prefijo);
static int contiene_icase(const char *texto, const char *frag);
static void a_minusculas(char *dst, const char *src, size_t max);
static void normalizar_atributo(char *dst, const char *src, size_t max);
static const char *tipo_dispositivo(const char *disp);
static int atributo_permitido(const char *tipo_disp, const char *attr);
static int es_solo_lectura(const char *tipo_disp, const char *attr);
static int numero_de_valor(const char *texto, double *out);
static int porcentaje_en_rango(const char *texto, double min, double max);
static int temp_en_rango(const char *texto, double min, double max);
static int lux_en_rango(const char *texto, double min, double max);
static int hora_valida(const char *texto);
static int fecha_valida_general(const char *texto);
static int email_valido(const char *texto);
static int bool_on_off(const char *texto);
static int bool_true_false(const char *texto);
static int valor_es_email_por_atributo(const char *attr);
static void agregar_accion_html(const char *disp, const char *attr, const char *valor);
static void agregar_sensor_html(const char *nombre, const char *op, const char *valor);
static void html_escape(FILE *f, const char *s);
static void html_valor(FILE *f, const char *attr, const char *valor);

#line 195 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_WHEN = 3,                   /* TOK_WHEN  */
  YYSYMBOL_TOK_EVERY = 4,                  /* TOK_EVERY  */
  YYSYMBOL_TOK_IF = 5,                     /* TOK_IF  */
  YYSYMBOL_TOK_THEN = 6,                   /* TOK_THEN  */
  YYSYMBOL_TOK_ELSE = 7,                   /* TOK_ELSE  */
  YYSYMBOL_TOK_DO = 8,                     /* TOK_DO  */
  YYSYMBOL_TOK_END = 9,                    /* TOK_END  */
  YYSYMBOL_TOK_AND = 10,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 11,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 12,                   /* TOK_NOT  */
  YYSYMBOL_TOK_BOOL = 13,                  /* TOK_BOOL  */
  YYSYMBOL_TOK_MODO = 14,                  /* TOK_MODO  */
  YYSYMBOL_TOK_COLOR = 15,                 /* TOK_COLOR  */
  YYSYMBOL_TOK_ID_SENSOR_NUM = 16,         /* TOK_ID_SENSOR_NUM  */
  YYSYMBOL_TOK_ID_SENSOR_BOOL = 17,        /* TOK_ID_SENSOR_BOOL  */
  YYSYMBOL_TOK_ID_DISPOSITIVO = 18,        /* TOK_ID_DISPOSITIVO  */
  YYSYMBOL_TOK_ATRIBUTO = 19,              /* TOK_ATRIBUTO  */
  YYSYMBOL_TOK_ID = 20,                    /* TOK_ID  */
  YYSYMBOL_TOK_EMAIL = 21,                 /* TOK_EMAIL  */
  YYSYMBOL_TOK_TEXTO = 22,                 /* TOK_TEXTO  */
  YYSYMBOL_TOK_HORA = 23,                  /* TOK_HORA  */
  YYSYMBOL_TOK_FECHA = 24,                 /* TOK_FECHA  */
  YYSYMBOL_TOK_NUM_TEMP = 25,              /* TOK_NUM_TEMP  */
  YYSYMBOL_TOK_PERCENT = 26,               /* TOK_PERCENT  */
  YYSYMBOL_TOK_TIME = 27,                  /* TOK_TIME  */
  YYSYMBOL_TOK_LUX = 28,                   /* TOK_LUX  */
  YYSYMBOL_TOK_NUMERO = 29,                /* TOK_NUMERO  */
  YYSYMBOL_TOK_IGUALDAD = 30,              /* TOK_IGUALDAD  */
  YYSYMBOL_TOK_DIFERENTE = 31,             /* TOK_DIFERENTE  */
  YYSYMBOL_TOK_MAYOR = 32,                 /* TOK_MAYOR  */
  YYSYMBOL_TOK_MENOR = 33,                 /* TOK_MENOR  */
  YYSYMBOL_TOK_MAYOR_IGUAL = 34,           /* TOK_MAYOR_IGUAL  */
  YYSYMBOL_TOK_MENOR_IGUAL = 35,           /* TOK_MENOR_IGUAL  */
  YYSYMBOL_TOK_IGUAL = 36,                 /* TOK_IGUAL  */
  YYSYMBOL_TOK_PUNTO = 37,                 /* TOK_PUNTO  */
  YYSYMBOL_TOK_PARENTESIS_ABRE = 38,       /* TOK_PARENTESIS_ABRE  */
  YYSYMBOL_TOK_PARENTESIS_CIERRA = 39,     /* TOK_PARENTESIS_CIERRA  */
  YYSYMBOL_TOK_ERROR_LEXICO = 40,          /* TOK_ERROR_LEXICO  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_programa = 42,                  /* programa  */
  YYSYMBOL_lista_instrucciones = 43,       /* lista_instrucciones  */
  YYSYMBOL_instruccion = 44,               /* instruccion  */
  YYSYMBOL_bloque_when = 45,               /* bloque_when  */
  YYSYMBOL_bloque_every = 46,              /* bloque_every  */
  YYSYMBOL_bloque_if = 47,                 /* bloque_if  */
  YYSYMBOL_opt_else = 48,                  /* opt_else  */
  YYSYMBOL_lista_acciones = 49,            /* lista_acciones  */
  YYSYMBOL_accion = 50,                    /* accion  */
  YYSYMBOL_asignacion = 51,                /* asignacion  */
  YYSYMBOL_dispositivo_atributo = 52,      /* dispositivo_atributo  */
  YYSYMBOL_dispositivo = 53,               /* dispositivo  */
  YYSYMBOL_atributo = 54,                  /* atributo  */
  YYSYMBOL_condicion = 55,                 /* condicion  */
  YYSYMBOL_termino_logico = 56,            /* termino_logico  */
  YYSYMBOL_factor_logico = 57,             /* factor_logico  */
  YYSYMBOL_comparacion = 58,               /* comparacion  */
  YYSYMBOL_operando = 59,                  /* operando  */
  YYSYMBOL_operador_comparacion = 60,      /* operador_comparacion  */
  YYSYMBOL_valor = 61                      /* valor  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   180,   180,   184,   185,   189,   190,   191,   192,   196,
     200,   204,   208,   209,   213,   214,   218,   219,   223,   233,
     241,   242,   250,   251,   259,   260,   264,   265,   269,   270,
     271,   272,   279,   287,   297,   301,   305,   309,   317,   318,
     319,   320,   321,   322,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_WHEN",
  "TOK_EVERY", "TOK_IF", "TOK_THEN", "TOK_ELSE", "TOK_DO", "TOK_END",
  "TOK_AND", "TOK_OR", "TOK_NOT", "TOK_BOOL", "TOK_MODO", "TOK_COLOR",
  "TOK_ID_SENSOR_NUM", "TOK_ID_SENSOR_BOOL", "TOK_ID_DISPOSITIVO",
  "TOK_ATRIBUTO", "TOK_ID", "TOK_EMAIL", "TOK_TEXTO", "TOK_HORA",
  "TOK_FECHA", "TOK_NUM_TEMP", "TOK_PERCENT", "TOK_TIME", "TOK_LUX",
  "TOK_NUMERO", "TOK_IGUALDAD", "TOK_DIFERENTE", "TOK_MAYOR", "TOK_MENOR",
  "TOK_MAYOR_IGUAL", "TOK_MENOR_IGUAL", "TOK_IGUAL", "TOK_PUNTO",
  "TOK_PARENTESIS_ABRE", "TOK_PARENTESIS_CIERRA", "TOK_ERROR_LEXICO",
  "$accept", "programa", "lista_instrucciones", "instruccion",
  "bloque_when", "bloque_every", "bloque_if", "opt_else", "lista_acciones",
  "accion", "asignacion", "dispositivo_atributo", "dispositivo",
  "atributo", "condicion", "termino_logico", "factor_logico",
  "comparacion", "operando", "operador_comparacion", "valor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-33)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      19,    44,   -10,    44,   -56,   -56,    27,    19,   -56,   -56,
     -56,   -56,   -56,    14,    -4,    44,    -3,   -56,   -56,   -56,
       5,    26,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,    44,   -56,    10,    64,   -56,   -56,    85,   -56,    67,
      40,   -56,   -56,    80,    34,   -56,    -7,    23,    44,    44,
     -56,   -56,   -56,   -56,   -56,   -56,    63,    23,    23,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,    20,   -56,   -56,
      64,   -56,   -56,   -56,   105,   106,   -56,   -56,   -56,    23,
      87,    23,   -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,    20,    21,     0,     2,     3,     5,
       6,     7,     8,     0,     0,     0,    44,    45,    46,    34,
      35,    56,    47,    48,    49,    50,    51,    52,    53,    54,
      55,     0,    36,     0,    25,    27,    30,     0,    37,     0,
       0,     1,     4,     0,     0,    28,     0,     0,     0,     0,
      38,    39,    40,    41,    42,    43,     0,     0,     0,    44,
      56,    18,    22,    23,    19,    29,    17,     0,    14,    16,
      24,    26,    35,    33,     0,    12,     9,    15,    10,     0,
       0,    13,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,    90,   -56,   -56,    42,   -56,   -48,   -55,
      45,    -1,   -56,   -56,     3,    50,   -14,   -56,    43,   -56,
      69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    66,    80,    67,    68,
      69,    13,    14,    64,    33,    34,    35,    36,    37,    56,
      38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    45,    32,   -31,    48,   -31,    40,   -31,   -31,    74,
      75,   -32,    77,   -32,    32,   -32,   -32,    39,    47,    77,
      77,    48,     1,     2,     3,     3,    77,    41,     3,    76,
      32,    81,    65,    44,    46,    71,   -31,     4,     4,     5,
       5,     4,    11,     5,   -32,    12,    58,    32,    32,    11,
      43,    48,    12,    62,    63,    32,    15,    16,    17,    18,
      19,    20,     4,   -21,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    49,    57,    59,    17,    18,    19,
      72,     4,    31,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    59,    17,    18,    82,    42,    70,    73,
      60,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       3,     3,    61,    79,    78,    50,    51,    52,    53,    54,
      55,     0,     0,     4,     4,     5,     5
};

static const yytype_int8 yycheck[] =
{
       1,    15,     3,     6,    11,     8,     3,    10,    11,    57,
      58,     6,    67,     8,    15,    10,    11,    27,     8,    74,
      75,    11,     3,     4,     5,     5,    81,     0,     5,     9,
      31,    79,    39,    37,    31,    49,    39,    18,    18,    20,
      20,    18,     0,    20,    39,     0,     6,    48,    49,     7,
      36,    11,     7,    19,    20,    56,    12,    13,    14,    15,
      16,    17,    18,    37,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    10,     8,    13,    14,    15,    16,
      17,    18,    38,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    13,    14,    15,     9,     7,    48,    56,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
       5,     5,    43,     7,     9,    30,    31,    32,    33,    34,
      35,    -1,    -1,    18,    18,    20,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    18,    20,    42,    43,    44,    45,
      46,    47,    51,    52,    53,    12,    13,    14,    15,    16,
      17,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    38,    52,    55,    56,    57,    58,    59,    61,    27,
      55,     0,    44,    36,    37,    57,    55,     8,    11,    10,
      30,    31,    32,    33,    34,    35,    60,     8,     6,    13,
      20,    61,    19,    20,    54,    39,    47,    49,    50,    51,
      56,    57,    17,    59,    49,    49,     9,    50,     9,     7,
      48,    49,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    45,
      46,    47,    48,    48,    49,    49,    50,    50,    51,    52,
      53,    53,    54,    54,    55,    55,    56,    56,    57,    57,
      57,    57,    57,    58,    59,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     5,
       5,     6,     0,     2,     1,     2,     1,     1,     3,     3,
       1,     1,     1,     1,     3,     1,     3,     1,     2,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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
  case 18: /* asignacion: dispositivo_atributo TOK_IGUAL valor  */
#line 224 "parser.y"
      {
          validar_y_registrar_asignacion((yyvsp[-2].operand), (yyvsp[0].valor));
          liberar_operando((yyvsp[-2].operand));
          liberar_valor((yyvsp[0].valor));
          free((yyvsp[-1].texto));
      }
#line 1317 "parser.tab.c"
    break;

  case 19: /* dispositivo_atributo: dispositivo TOK_PUNTO atributo  */
#line 234 "parser.y"
      {
          (yyval.operand) = crear_operando_atributo((yyvsp[-2].texto), (yyvsp[0].texto));
          free((yyvsp[-1].texto));
      }
#line 1326 "parser.tab.c"
    break;

  case 20: /* dispositivo: TOK_ID_DISPOSITIVO  */
#line 241 "parser.y"
                         { (yyval.texto) = (yyvsp[0].texto); }
#line 1332 "parser.tab.c"
    break;

  case 21: /* dispositivo: TOK_ID  */
#line 243 "parser.y"
      {
          registrar_error_semantico(linea_token, (yyvsp[0].texto), "dispositivo no reconocido o prefijo invalido");
          (yyval.texto) = (yyvsp[0].texto);
      }
#line 1341 "parser.tab.c"
    break;

  case 22: /* atributo: TOK_ATRIBUTO  */
#line 250 "parser.y"
                   { (yyval.texto) = (yyvsp[0].texto); }
#line 1347 "parser.tab.c"
    break;

  case 23: /* atributo: TOK_ID  */
#line 252 "parser.y"
      {
          registrar_error_semantico(linea_token, (yyvsp[0].texto), "atributo no reconocido");
          (yyval.texto) = (yyvsp[0].texto);
      }
#line 1356 "parser.tab.c"
    break;

  case 31: /* factor_logico: TOK_BOOL  */
#line 273 "parser.y"
      {
          if (!bool_true_false((yyvsp[0].texto))) {
              registrar_error_semantico(linea_token, (yyvsp[0].texto), "en una condicion booleana se esperaba TRUE o FALSE");
          }
          free((yyvsp[0].texto));
      }
#line 1367 "parser.tab.c"
    break;

  case 32: /* factor_logico: TOK_ID_SENSOR_BOOL  */
#line 280 "parser.y"
      {
          agregar_sensor_html((yyvsp[0].texto), "", "TRUE/FALSE");
          free((yyvsp[0].texto));
      }
#line 1376 "parser.tab.c"
    break;

  case 33: /* comparacion: operando operador_comparacion operando  */
#line 288 "parser.y"
      {
          validar_comparacion((yyvsp[-2].operand), (yyvsp[-1].texto), (yyvsp[0].operand));
          liberar_operando((yyvsp[-2].operand));
          free((yyvsp[-1].texto));
          liberar_operando((yyvsp[0].operand));
      }
#line 1387 "parser.tab.c"
    break;

  case 34: /* operando: TOK_ID_SENSOR_NUM  */
#line 298 "parser.y"
      {
          (yyval.operand) = crear_operando_simple((yyvsp[0].texto), OP_SENSOR_NUM);
      }
#line 1395 "parser.tab.c"
    break;

  case 35: /* operando: TOK_ID_SENSOR_BOOL  */
#line 302 "parser.y"
      {
          (yyval.operand) = crear_operando_simple((yyvsp[0].texto), OP_SENSOR_BOOL);
      }
#line 1403 "parser.tab.c"
    break;

  case 36: /* operando: dispositivo_atributo  */
#line 306 "parser.y"
      {
          (yyval.operand) = (yyvsp[0].operand);
      }
#line 1411 "parser.tab.c"
    break;

  case 37: /* operando: valor  */
#line 310 "parser.y"
      {
          (yyval.operand) = crear_operando_valor((yyvsp[0].valor));
          liberar_valor((yyvsp[0].valor));
      }
#line 1420 "parser.tab.c"
    break;

  case 38: /* operador_comparacion: TOK_IGUALDAD  */
#line 317 "parser.y"
                       { (yyval.texto) = (yyvsp[0].texto); }
#line 1426 "parser.tab.c"
    break;

  case 39: /* operador_comparacion: TOK_DIFERENTE  */
#line 318 "parser.y"
                       { (yyval.texto) = (yyvsp[0].texto); }
#line 1432 "parser.tab.c"
    break;

  case 40: /* operador_comparacion: TOK_MAYOR  */
#line 319 "parser.y"
                       { (yyval.texto) = (yyvsp[0].texto); }
#line 1438 "parser.tab.c"
    break;

  case 41: /* operador_comparacion: TOK_MENOR  */
#line 320 "parser.y"
                       { (yyval.texto) = (yyvsp[0].texto); }
#line 1444 "parser.tab.c"
    break;

  case 42: /* operador_comparacion: TOK_MAYOR_IGUAL  */
#line 321 "parser.y"
                       { (yyval.texto) = (yyvsp[0].texto); }
#line 1450 "parser.tab.c"
    break;

  case 43: /* operador_comparacion: TOK_MENOR_IGUAL  */
#line 322 "parser.y"
                       { (yyval.texto) = (yyvsp[0].texto); }
#line 1456 "parser.tab.c"
    break;

  case 44: /* valor: TOK_BOOL  */
#line 326 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_BOOL); }
#line 1462 "parser.tab.c"
    break;

  case 45: /* valor: TOK_MODO  */
#line 327 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_MODO); }
#line 1468 "parser.tab.c"
    break;

  case 46: /* valor: TOK_COLOR  */
#line 328 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_COLOR); }
#line 1474 "parser.tab.c"
    break;

  case 47: /* valor: TOK_EMAIL  */
#line 329 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_EMAIL); }
#line 1480 "parser.tab.c"
    break;

  case 48: /* valor: TOK_TEXTO  */
#line 330 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_TEXTO); }
#line 1486 "parser.tab.c"
    break;

  case 49: /* valor: TOK_HORA  */
#line 331 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_HORA); }
#line 1492 "parser.tab.c"
    break;

  case 50: /* valor: TOK_FECHA  */
#line 332 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_FECHA); }
#line 1498 "parser.tab.c"
    break;

  case 51: /* valor: TOK_NUM_TEMP  */
#line 333 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_TEMP); }
#line 1504 "parser.tab.c"
    break;

  case 52: /* valor: TOK_PERCENT  */
#line 334 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_PERCENT); }
#line 1510 "parser.tab.c"
    break;

  case 53: /* valor: TOK_TIME  */
#line 335 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_TIME); }
#line 1516 "parser.tab.c"
    break;

  case 54: /* valor: TOK_LUX  */
#line 336 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_LUX); }
#line 1522 "parser.tab.c"
    break;

  case 55: /* valor: TOK_NUMERO  */
#line 337 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_NUMERO); }
#line 1528 "parser.tab.c"
    break;

  case 56: /* valor: TOK_ID  */
#line 338 "parser.y"
                   { (yyval.valor) = crear_valor((yyvsp[0].texto), VAL_ID); }
#line 1534 "parser.tab.c"
    break;


#line 1538 "parser.tab.c"

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

#line 341 "parser.y"


static char *copiar_texto(const char *s) {
    size_t n;
    char *r;
    if (!s) s = "";
    n = strlen(s);
    r = (char *)malloc(n + 1);
    if (!r) {
        fprintf(stderr, "Sin memoria.\n");
        exit(1);
    }
    memcpy(r, s, n + 1);
    return r;
}

static Valor *crear_valor(char *texto, int tipo) {
    Valor *v = (Valor *)malloc(sizeof(Valor));
    if (!v) exit(1);
    v->texto = texto;
    v->tipo = tipo;
    return v;
}

static void liberar_valor(Valor *v) {
    if (!v) return;
    free(v->texto);
    free(v);
}

static Operand *crear_operando_simple(char *texto, int clase) {
    Operand *o = (Operand *)calloc(1, sizeof(Operand));
    if (!o) exit(1);
    o->texto = texto;
    o->clase = clase;
    o->valor_tipo = 0;
    return o;
}

static Operand *crear_operando_atributo(char *dispositivo, char *atributo) {
    Operand *o = (Operand *)calloc(1, sizeof(Operand));
    if (!o) exit(1);
    o->dispositivo = dispositivo;
    o->atributo = atributo;
    o->clase = OP_DISP_ATTR;
    o->valor_tipo = 0;

    o->texto = (char *)malloc(strlen(dispositivo) + strlen(atributo) + 2);
    if (!o->texto) exit(1);
    sprintf(o->texto, "%s.%s", dispositivo, atributo);
    return o;
}

static Operand *crear_operando_valor(Valor *v) {
    Operand *o = (Operand *)calloc(1, sizeof(Operand));
    if (!o) exit(1);
    o->texto = copiar_texto(v->texto);
    o->clase = OP_VALOR;
    o->valor_tipo = v->tipo;
    return o;
}

static void liberar_operando(Operand *o) {
    if (!o) return;
    free(o->texto);
    free(o->dispositivo);
    free(o->atributo);
    free(o);
}

void yyerror(const char *mensaje) {
    errores_sintacticos++;
    fprintf(stderr, "[ERROR SINTACTICO] Linea %d: %s cerca de '%s'\n",
            yylineno, mensaje, yytext ? yytext : "EOF");
}

static void registrar_error_semantico(int linea, const char *lexema, const char *mensaje) {
    errores_semanticos++;
    fprintf(stderr, "[ERROR SEMANTICO] Linea %d: %s cerca de '%s'\n",
            linea > 0 ? linea : yylineno,
            mensaje,
            lexema ? lexema : "");
}

static int igual_icase(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

static int empieza_icase(const char *texto, const char *prefijo) {
    if (!texto || !prefijo) return 0;
    while (*prefijo) {
        if (tolower((unsigned char)*texto) != tolower((unsigned char)*prefijo)) return 0;
        texto++;
        prefijo++;
    }
    return 1;
}

static int contiene_icase(const char *texto, const char *frag) {
    size_t n, m, i, j;
    if (!texto || !frag) return 0;
    n = strlen(texto);
    m = strlen(frag);
    if (m == 0 || m > n) return 0;
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (tolower((unsigned char)texto[i + j]) != tolower((unsigned char)frag[j])) break;
        }
        if (j == m) return 1;
    }
    return 0;
}

static void a_minusculas(char *dst, const char *src, size_t max) {
    size_t i;
    for (i = 0; src && src[i] && i + 1 < max; i++) {
        dst[i] = (char)tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

static void normalizar_atributo(char *dst, const char *src, size_t max) {
    a_minusculas(dst, src, max);
    if (igual_icase(dst, "temp_objetivo")) strncpy(dst, "temp_obj", max);
    if (igual_icase(dst, "temp_actual")) strncpy(dst, "temp_act", max);
    dst[max - 1] = '\0';
}

static const char *tipo_dispositivo(const char *disp) {
    if (empieza_icase(disp, "foco_")) return "foco";
    if (empieza_icase(disp, "aire_")) return "aire";
    if (empieza_icase(disp, "persiana_")) return "persiana";
    if (empieza_icase(disp, "cerradura_")) return "cerradura";
    if (empieza_icase(disp, "reloj_" ) || igual_icase(disp, "reloj")) return "reloj";
    if (empieza_icase(disp, "altavoz_")) return "altavoz";
    if (empieza_icase(disp, "alarma_" ) || igual_icase(disp, "alarma")) return "alarma";
    return NULL;
}

static int atributo_permitido(const char *tipo_disp, const char *attr_original) {
    char attr[64];
    normalizar_atributo(attr, attr_original, sizeof(attr));
    if (!tipo_disp) return 0;
    if (igual_icase(tipo_disp, "foco"))
        return igual_icase(attr,"estado") || igual_icase(attr,"brillo") || igual_icase(attr,"color");
    if (igual_icase(tipo_disp, "aire"))
        return igual_icase(attr,"estado") || igual_icase(attr,"modo") || igual_icase(attr,"temp_obj") || igual_icase(attr,"temp_act");
    if (igual_icase(tipo_disp, "persiana"))
        return igual_icase(attr,"posicion");
    if (igual_icase(tipo_disp, "cerradura"))
        return igual_icase(attr,"estado");
    if (igual_icase(tipo_disp, "reloj"))
        return igual_icase(attr,"hora") || igual_icase(attr,"fecha");
    if (igual_icase(tipo_disp, "altavoz"))
        return igual_icase(attr,"volumen") || igual_icase(attr,"mute") || igual_icase(attr,"mensaje") || igual_icase(attr,"email") || igual_icase(attr,"email_notif");
    if (igual_icase(tipo_disp, "alarma"))
        return igual_icase(attr,"estado") || igual_icase(attr,"activada");
    return 0;
}

static int es_solo_lectura(const char *tipo_disp, const char *attr_original) {
    char attr[64];
    normalizar_atributo(attr, attr_original, sizeof(attr));
    return (igual_icase(tipo_disp, "aire") && igual_icase(attr, "temp_act")) ||
           (igual_icase(tipo_disp, "reloj") && (igual_icase(attr, "hora") || igual_icase(attr, "fecha")));
}

static int numero_de_valor(const char *texto, double *out) {
    char *fin;
    if (!texto) return 0;
    *out = strtod(texto, &fin);
    return fin != texto;
}

static int porcentaje_en_rango(const char *texto, double min, double max) {
    double n;
    if (!contiene_icase(texto, "%")) return 0;
    if (!numero_de_valor(texto, &n)) return 0;
    return n >= min && n <= max;
}

static int temp_en_rango(const char *texto, double min, double max) {
    double n;
    if (!contiene_icase(texto, "c")) return 0;
    if (!numero_de_valor(texto, &n)) return 0;
    return n >= min && n <= max;
}

static int lux_en_rango(const char *texto, double min, double max) {
    double n;
    if (!contiene_icase(texto, "lux")) return 0;
    if (!numero_de_valor(texto, &n)) return 0;
    return n >= min && n <= max;
}

static int hora_valida(const char *texto) {
    int h, m;
    if (!texto || sscanf(texto, "%2d:%2d", &h, &m) != 2) return 0;
    return h >= 0 && h <= 23 && m >= 0 && m <= 59;
}

static int fecha_valida_general(const char *texto) {
    int d, m, a;
    if (!texto || sscanf(texto, "%2d/%2d/%4d", &d, &m, &a) != 3) return 0;
    return d >= 1 && d <= 31 && m >= 1 && m <= 12 && a >= 1900 && a <= 2099;
}

static int email_valido(const char *texto) {
    const char *arroba, *punto;
    int puntos_seguidos = 0;
    int cant_arroba = 0;
    int largo_ext;
    const char *p;
    if (!texto) return 0;
    for (p = texto; *p; p++) {
        if (*p == '@') cant_arroba++;
        if (*p == '.' && p[1] == '.') puntos_seguidos = 1;
    }
    if (cant_arroba != 1 || puntos_seguidos) return 0;
    arroba = strchr(texto, '@');
    punto = strrchr(texto, '.');
    if (!arroba || !punto || punto < arroba + 2) return 0;
    largo_ext = (int)strlen(punto + 1);
    return largo_ext >= 2 && largo_ext <= 4;
}

static int bool_on_off(const char *texto) {
    return igual_icase(texto, "ON") || igual_icase(texto, "OFF");
}

static int bool_true_false(const char *texto) {
    return igual_icase(texto, "TRUE") || igual_icase(texto, "FALSE");
}

static int valor_es_email_por_atributo(const char *attr) {
    return igual_icase(attr, "email") || igual_icase(attr, "email_notif");
}

static void validar_tipo_valor(const char *tipo_disp, const char *attr_original, Valor *valor, const char *contexto) {
    char attr[64];
    normalizar_atributo(attr, attr_original, sizeof(attr));

    if (igual_icase(attr, "estado") || igual_icase(attr, "activada") || igual_icase(attr, "mute")) {
        if (valor->tipo != VAL_BOOL || !bool_on_off(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "se esperaba valor booleano ON/OFF");
    } else if (igual_icase(attr, "brillo") || igual_icase(attr, "posicion") || igual_icase(attr, "volumen")) {
        if (valor->tipo != VAL_PERCENT || !porcentaje_en_rango(valor->texto, 0, 100))
            registrar_error_semantico(linea_token, valor->texto, "porcentaje fuera de rango permitido 0% a 100%");
    } else if (igual_icase(attr, "color")) {
        if (valor->tipo != VAL_COLOR)
            registrar_error_semantico(linea_token, valor->texto, "color no valido, se esperaba blanco, rojo o azul");
    } else if (igual_icase(attr, "modo")) {
        if (valor->tipo != VAL_MODO)
            registrar_error_semantico(linea_token, valor->texto, "modo no valido, se esperaba FRIO, CALOR o VENT");
    } else if (igual_icase(attr, "temp_obj")) {
        if (valor->tipo != VAL_TEMP || !temp_en_rango(valor->texto, 16, 30))
            registrar_error_semantico(linea_token, valor->texto, "temp_obj fuera de rango permitido 16C a 30C");
    } else if (igual_icase(attr, "temp_act")) {
        if (valor->tipo != VAL_TEMP || !temp_en_rango(valor->texto, -10, 50))
            registrar_error_semantico(linea_token, valor->texto, "temp_act fuera de rango permitido -10C a 50C");
    } else if (igual_icase(attr, "hora")) {
        if (valor->tipo != VAL_HORA || !hora_valida(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "hora invalida, se esperaba 00:00 a 23:59");
    } else if (igual_icase(attr, "fecha")) {
        if (valor->tipo != VAL_FECHA || !fecha_valida_general(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "fecha invalida, se esperaba DD/MM/AAAA con rangos validos");
    } else if (igual_icase(attr, "mensaje")) {
        if (valor->tipo != VAL_TEXTO)
            registrar_error_semantico(linea_token, valor->texto, "mensaje debe estar entre comillas");
    } else if (valor_es_email_por_atributo(attr)) {
        if (valor->tipo != VAL_EMAIL || !email_valido(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "email invalido");
    } else {
        (void)tipo_disp;
        (void)contexto;
    }
}

static void validar_y_registrar_asignacion(Operand *destino, Valor *valor) {
    const char *tipo;
    char attr[64];
    if (!destino || destino->clase != OP_DISP_ATTR) return;

    tipo = tipo_dispositivo(destino->dispositivo);
    normalizar_atributo(attr, destino->atributo, sizeof(attr));

    if (!tipo) {
        registrar_error_semantico(linea_token, destino->dispositivo, "dispositivo con prefijo invalido");
    } else {
        if (!atributo_permitido(tipo, attr)) {
            registrar_error_semantico(linea_token, destino->atributo, "atributo no permitido para ese dispositivo");
        }
        if (es_solo_lectura(tipo, attr)) {
            registrar_error_semantico(linea_token, destino->texto, "atributo de solo lectura, no puede asignarse");
        }
        validar_tipo_valor(tipo, attr, valor, "asignacion");
    }

    agregar_accion_html(destino->dispositivo, attr, valor->texto);
}

static void validar_sensor_con_valor(Operand *sensor, const char *op, Operand *valor) {
    (void)op;
    if (!sensor || !valor || valor->clase != OP_VALOR) return;

    if (sensor->clase == OP_SENSOR_NUM) {
        if (contiene_icase(sensor->texto, "luz")) {
            if (valor->valor_tipo != VAL_LUX || !lux_en_rango(valor->texto, 0, 1000))
                registrar_error_semantico(linea_token, valor->texto, "sensor_luz espera lux en rango 0 a 1000");
        } else if (contiene_icase(sensor->texto, "humedad")) {
            if (valor->valor_tipo != VAL_PERCENT || !porcentaje_en_rango(valor->texto, 0, 100))
                registrar_error_semantico(linea_token, valor->texto, "sensor_humedad espera porcentaje 0% a 100%");
        } else if (contiene_icase(sensor->texto, "temp")) {
            if (valor->valor_tipo != VAL_TEMP || !temp_en_rango(valor->texto, -10, 50))
                registrar_error_semantico(linea_token, valor->texto, "sensor_temp espera temperatura -10C a 50C");
        }
    } else if (sensor->clase == OP_SENSOR_BOOL) {
        if (valor->valor_tipo != VAL_BOOL || !bool_true_false(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "sensor booleano espera TRUE o FALSE");
    } else if (sensor->clase == OP_DISP_ATTR) {
        const char *tipo = tipo_dispositivo(sensor->dispositivo);
        Valor tmp;
        tmp.texto = valor->texto;
        tmp.tipo = valor->valor_tipo;
        if (tipo) validar_tipo_valor(tipo, sensor->atributo, &tmp, "comparacion");
    }
}

static void validar_comparacion(Operand *izq, const char *op, Operand *der) {
    if (izq && der) {
        if ((izq->clase == OP_SENSOR_NUM || izq->clase == OP_SENSOR_BOOL || izq->clase == OP_DISP_ATTR) && der->clase == OP_VALOR) {
            validar_sensor_con_valor(izq, op, der);
            agregar_sensor_html(izq->texto, op, der->texto);
        } else if ((der->clase == OP_SENSOR_NUM || der->clase == OP_SENSOR_BOOL || der->clase == OP_DISP_ATTR) && izq->clase == OP_VALOR) {
            validar_sensor_con_valor(der, op, izq);
            agregar_sensor_html(der->texto, op, izq->texto);
        } else if (izq->clase == OP_SENSOR_NUM || izq->clase == OP_SENSOR_BOOL || izq->clase == OP_DISP_ATTR) {
            agregar_sensor_html(izq->texto, op, der->texto);
        }
    }
}

static void agregar_accion_html(const char *disp, const char *attr, const char *valor) {
    if (cant_acciones_html >= MAX_HTML_ACCIONES) return;
    snprintf(acciones_html[cant_acciones_html].dispositivo, sizeof(acciones_html[cant_acciones_html].dispositivo), "%s", disp ? disp : "");
    snprintf(acciones_html[cant_acciones_html].atributo, sizeof(acciones_html[cant_acciones_html].atributo), "%s", attr ? attr : "");
    snprintf(acciones_html[cant_acciones_html].valor, sizeof(acciones_html[cant_acciones_html].valor), "%s", valor ? valor : "");
    acciones_html[cant_acciones_html].es_email = attr && valor_es_email_por_atributo(attr);
    cant_acciones_html++;
}

static void agregar_sensor_html(const char *nombre, const char *op, const char *valor) {
    int i;
    if (!nombre || cant_sensores_html >= MAX_HTML_SENSORES) return;
    for (i = 0; i < cant_sensores_html; i++) {
        if (igual_icase(sensores_html[i].nombre, nombre) && igual_icase(sensores_html[i].valor, valor ? valor : "")) return;
    }
    snprintf(sensores_html[cant_sensores_html].nombre, sizeof(sensores_html[cant_sensores_html].nombre), "%s", nombre);
    snprintf(sensores_html[cant_sensores_html].operador, sizeof(sensores_html[cant_sensores_html].operador), "%s", op ? op : "");
    snprintf(sensores_html[cant_sensores_html].valor, sizeof(sensores_html[cant_sensores_html].valor), "%s", valor ? valor : "");
    cant_sensores_html++;
}

static void html_escape(FILE *f, const char *s) {
    if (!s) return;
    while (*s) {
        switch (*s) {
            case '&': fputs("&amp;", f); break;
            case '<': fputs("&lt;", f); break;
            case '>': fputs("&gt;", f); break;
            case '"': fputs("&quot;", f); break;
            default: fputc(*s, f); break;
        }
        s++;
    }
}

static void html_valor(FILE *f, const char *attr, const char *valor) {
    if (attr && valor_es_email_por_atributo(attr) && email_valido(valor)) {
        const char *arroba = strchr(valor, '@');
        char usuario[128];
        size_t n = arroba ? (size_t)(arroba - valor) : strlen(valor);
        if (n >= sizeof(usuario)) n = sizeof(usuario) - 1;
        memcpy(usuario, valor, n);
        usuario[n] = '\0';
        fputs("<a href=\"mailto:", f);
        html_escape(f, valor);
        fputs("\">Contactar a ", f);
        html_escape(f, usuario);
        fputs("</a>", f);
    } else {
        html_escape(f, valor);
    }
}

static void generar_html(void) {
    FILE *f = fopen(archivo_html, "w");
    int i, j;
    if (!f) {
        fprintf(stderr, "[ERROR DE EJECUCION] No se pudo crear el archivo HTML: %s\n", archivo_html);
        return;
    }

    fprintf(f, "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n<meta charset=\"UTF-8\">\n");
    fprintf(f, "<title>SMART-HOME</title>\n</head>\n<body>\n");
    fprintf(f, "<h1>Dashboard SMART-HOME</h1>\n");


    fprintf(f, "<div style=\"border:1px solid green; padding:20px; margin:10px;\">\n");
    fprintf(f, "<h1>Estado de sensores y condiciones</h1>\n");
    if (cant_sensores_html == 0) {
        fprintf(f, "<p>No se detectaron condiciones sobre sensores.</p>\n");
    }
    for (i = 0; i < cant_sensores_html; i++) {
        fprintf(f, "<h2>");
        html_escape(f, sensores_html[i].nombre);
        if (strlen(sensores_html[i].operador) > 0) {
            fprintf(f, " ");
            html_escape(f, sensores_html[i].operador);
            fprintf(f, " ");
            html_escape(f, sensores_html[i].valor);
        }
        fprintf(f, "</h2>\n");
    }
    fprintf(f, "</div>\n");

    fprintf(f, "<h1>Actuadores</h1>\n");
    for (i = 0; i < cant_acciones_html; i++) {
        int ya_impreso = 0;
        for (j = 0; j < i; j++) {
            if (igual_icase(acciones_html[i].dispositivo, acciones_html[j].dispositivo)) {
                ya_impreso = 1;
                break;
            }
        }
        if (ya_impreso) continue;

        fprintf(f, "<div style=\"border:1px solid gray; padding:20px; margin:10px;\">\n<h1>");
        html_escape(f, acciones_html[i].dispositivo);
        fprintf(f, "</h1>\n<ul>\n");
        for (j = i; j < cant_acciones_html; j++) {
            if (igual_icase(acciones_html[i].dispositivo, acciones_html[j].dispositivo)) {
                fprintf(f, "<li>");
                html_escape(f, acciones_html[j].atributo);
                fprintf(f, ": ");
                html_valor(f, acciones_html[j].atributo, acciones_html[j].valor);
                fprintf(f, "</li>\n");
            }
        }
        fprintf(f, "</ul>\n</div>\n");
    }

    fprintf(f, "</body>\n</html>\n");
    fclose(f);
}

static int tiene_extension_smart(const char *ruta) {
    const char *punto = strrchr(ruta, '.');
    return punto != NULL && igual_icase(punto, ".smart");
}

static void construir_nombre_html(const char *ruta) {
    const char *ultimo_sep1 = strrchr(ruta, '/');
    const char *ultimo_sep2 = strrchr(ruta, '\\');
    const char *base = ultimo_sep1 > ultimo_sep2 ? ultimo_sep1 : ultimo_sep2;
    const char *nombre = base ? base + 1 : ruta;
    const char *punto = strrchr(nombre, '.');
    size_t n = punto ? (size_t)(punto - nombre) : strlen(nombre);
    if (n > sizeof(archivo_html) - 6) n = sizeof(archivo_html) - 6;
    memcpy(archivo_html, nombre, n);
    archivo_html[n] = '\0';
    strcat(archivo_html, ".html");
}

static void limpiar_ruta_ingresada(char *ruta) {
    size_t n;
    char *inicio = ruta;

    if (!ruta) return;

    while (*inicio && isspace((unsigned char)*inicio)) inicio++;
    if (inicio != ruta) memmove(ruta, inicio, strlen(inicio) + 1);

    n = strlen(ruta);
    while (n > 0 && isspace((unsigned char)ruta[n - 1])) {
        ruta[n - 1] = '\0';
        n--;
    }

    if (n >= 2 && ruta[0] == '"' && ruta[n - 1] == '"') {
        memmove(ruta, ruta + 1, n - 2);
        ruta[n - 2] = '\0';
    }
}

static void esperar_enter_si_interactivo(int modo_interactivo) {
    int c;
    if (!modo_interactivo) return;

    printf("\nPresione Enter para cerrar...");
    fflush(stdout);

    while ((c = getchar()) != '\n' && c != EOF) {
        /* descartar caracteres pendientes */
    }
}

int main(int argc, char **argv) {
    int resultado;
    int modo_interactivo = argc == 1;
    char ruta_interactiva[512];

    if (argc > 2) {
        fprintf(stderr, "Uso: %s archivo.smart\n", argv[0]);
        esperar_enter_si_interactivo(modo_interactivo);
        return 1;
    }

    if (modo_interactivo) {
        printf("--- Parser SMART-HOME ---\n");
        printf("Ingrese la ruta de un archivo .smart y presione Enter.\n");
        printf("Ejemplos si abre desde bin: ..\\prueba\\ejemplo_valido_catedra.smart\n");
        printf("Ejemplos desde la carpeta principal: prueba\\ejemplo_valido_catedra.smart\n");
        printf("> ");
        fflush(stdout);

        if (!fgets(ruta_interactiva, sizeof(ruta_interactiva), stdin)) {
            fprintf(stderr, "[ERROR DE EJECUCION] No se pudo leer la ruta ingresada.\n");
            esperar_enter_si_interactivo(modo_interactivo);
            return 1;
        }

        limpiar_ruta_ingresada(ruta_interactiva);
        if (ruta_interactiva[0] == '\0') {
            fprintf(stderr, "[ERROR DE EJECUCION] Debe ingresar un archivo .smart.\n");
            esperar_enter_si_interactivo(modo_interactivo);
            return 1;
        }

        archivo_entrada = ruta_interactiva;
    } else {
        archivo_entrada = argv[1];
    }

    if (!tiene_extension_smart(archivo_entrada)) {
        fprintf(stderr, "[ERROR DE EJECUCION] El archivo debe tener extension .smart\n");
        esperar_enter_si_interactivo(modo_interactivo);
        return 1;
    }

    yyin = fopen(archivo_entrada, "r");
    if (!yyin) {
        fprintf(stderr, "[ERROR DE EJECUCION] No se pudo abrir el archivo: %s\n", archivo_entrada);
        esperar_enter_si_interactivo(modo_interactivo);
        return 1;
    }

    construir_nombre_html(archivo_entrada);

    if (!modo_interactivo) printf("--- Parser SMART-HOME ---\n");
    resultado = yyparse();

    if (yyin && yyin != stdin) fclose(yyin);

  
    if (resultado == 0 && errores_lexicos == 0 && errores_sintacticos == 0) {
        printf("Analisis lexico y sintactico exitoso.\n");

        if (errores_semanticos > 0) {
            printf("Analisis semantico finalizado con %d error(es).\n", errores_semanticos);
            printf("No se genera HTML porque el archivo contiene errores semanticos.\n");
            esperar_enter_si_interactivo(modo_interactivo);
            return 2;
        }

        printf("Analisis semantico exitoso.\n");
        generar_html();
        printf("HTML generado correctamente: %s\n", archivo_html);
        esperar_enter_si_interactivo(modo_interactivo);
        return 0;
    }

    printf("Analisis finalizado con errores lexicos o sintacticos. No se genera HTML.\n");
    esperar_enter_si_interactivo(modo_interactivo);
    return 1;
}
