/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_SMART_HOME_H_INCLUDED
# define YY_YY_PARSER_SMART_HOME_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 10 "parser.y"

#include "semantica_html.h"

#line 53 "parser_smart_home.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_WHEN = 258,                /* TOK_WHEN  */
    TOK_EVERY = 259,               /* TOK_EVERY  */
    TOK_IF = 260,                  /* TOK_IF  */
    TOK_THEN = 261,                /* TOK_THEN  */
    TOK_ELSE = 262,                /* TOK_ELSE  */
    TOK_DO = 263,                  /* TOK_DO  */
    TOK_END = 264,                 /* TOK_END  */
    TOK_AND = 265,                 /* TOK_AND  */
    TOK_OR = 266,                  /* TOK_OR  */
    TOK_NOT = 267,                 /* TOK_NOT  */
    TOK_BOOL = 268,                /* TOK_BOOL  */
    TOK_MODO = 269,                /* TOK_MODO  */
    TOK_COLOR = 270,               /* TOK_COLOR  */
    TOK_ID_SENSOR_NUM = 271,       /* TOK_ID_SENSOR_NUM  */
    TOK_ID_SENSOR_BOOL = 272,      /* TOK_ID_SENSOR_BOOL  */
    TOK_ID_DISPOSITIVO = 273,      /* TOK_ID_DISPOSITIVO  */
    TOK_ATRIBUTO = 274,            /* TOK_ATRIBUTO  */
    TOK_ID = 275,                  /* TOK_ID  */
    TOK_EMAIL = 276,               /* TOK_EMAIL  */
    TOK_TEXTO = 277,               /* TOK_TEXTO  */
    TOK_HORA = 278,                /* TOK_HORA  */
    TOK_FECHA = 279,               /* TOK_FECHA  */
    TOK_NUM_TEMP = 280,            /* TOK_NUM_TEMP  */
    TOK_PERCENT = 281,             /* TOK_PERCENT  */
    TOK_TIME = 282,                /* TOK_TIME  */
    TOK_LUX = 283,                 /* TOK_LUX  */
    TOK_NUMERO = 284,              /* TOK_NUMERO  */
    TOK_IGUALDAD = 285,            /* TOK_IGUALDAD  */
    TOK_DIFERENTE = 286,           /* TOK_DIFERENTE  */
    TOK_MAYOR = 287,               /* TOK_MAYOR  */
    TOK_MENOR = 288,               /* TOK_MENOR  */
    TOK_MAYOR_IGUAL = 289,         /* TOK_MAYOR_IGUAL  */
    TOK_MENOR_IGUAL = 290,         /* TOK_MENOR_IGUAL  */
    TOK_IGUAL = 291,               /* TOK_IGUAL  */
    TOK_PUNTO = 292,               /* TOK_PUNTO  */
    TOK_PARENTESIS_ABRE = 293,     /* TOK_PARENTESIS_ABRE  */
    TOK_PARENTESIS_CIERRA = 294,   /* TOK_PARENTESIS_CIERRA  */
    TOK_ERROR_LEXICO = 295         /* TOK_ERROR_LEXICO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

    char *texto;
    Valor *valor;
    Operand *operand;

#line 116 "parser_smart_home.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_SMART_HOME_H_INCLUDED  */
