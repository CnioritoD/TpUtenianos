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

#ifndef YY_YY_SMART_HOME_TAB_H_INCLUDED
# define YY_YY_SMART_HOME_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_WHEN = 258,              /* TOKEN_WHEN  */
    TOKEN_EVERY = 259,             /* TOKEN_EVERY  */
    TOKEN_IF = 260,                /* TOKEN_IF  */
    TOKEN_THEN = 261,              /* TOKEN_THEN  */
    TOKEN_ELSE = 262,              /* TOKEN_ELSE  */
    TOKEN_DO = 263,                /* TOKEN_DO  */
    TOKEN_END = 264,               /* TOKEN_END  */
    TOKEN_AND = 265,               /* TOKEN_AND  */
    TOKEN_OR = 266,                /* TOKEN_OR  */
    TOKEN_NOT = 267,               /* TOKEN_NOT  */
    TOKEN_BOOL = 268,              /* TOKEN_BOOL  */
    TOKEN_MODO = 269,              /* TOKEN_MODO  */
    TOKEN_COLOR = 270,             /* TOKEN_COLOR  */
    TOKEN_ID_SENSOR_NUM = 271,     /* TOKEN_ID_SENSOR_NUM  */
    TOKEN_ID_SENSOR_BOOL = 272,    /* TOKEN_ID_SENSOR_BOOL  */
    TOKEN_ID_DISPOSITIVO = 273,    /* TOKEN_ID_DISPOSITIVO  */
    TOKEN_ATRIBUTO = 274,          /* TOKEN_ATRIBUTO  */
    TOKEN_ID = 275,                /* TOKEN_ID  */
    TOKEN_EMAIL = 276,             /* TOKEN_EMAIL  */
    TOKEN_TEXTO = 277,             /* TOKEN_TEXTO  */
    TOKEN_HORA = 278,              /* TOKEN_HORA  */
    TOKEN_FECHA = 279,             /* TOKEN_FECHA  */
    TOKEN_NUM_TEMP = 280,          /* TOKEN_NUM_TEMP  */
    TOKEN_PERCENT = 281,           /* TOKEN_PERCENT  */
    TOKEN_TIME = 282,              /* TOKEN_TIME  */
    TOKEN_LUX = 283,               /* TOKEN_LUX  */
    TOKEN_NUMERO = 284,            /* TOKEN_NUMERO  */
    TOKEN_IGUALDAD = 285,          /* TOKEN_IGUALDAD  */
    TOKEN_DIFERENTE = 286,         /* TOKEN_DIFERENTE  */
    TOKEN_MAYOR_IGUAL = 287,       /* TOKEN_MAYOR_IGUAL  */
    TOKEN_MENOR_IGUAL = 288,       /* TOKEN_MENOR_IGUAL  */
    TOKEN_IGUAL = 289,             /* TOKEN_IGUAL  */
    TOKEN_MAYOR = 290,             /* TOKEN_MAYOR  */
    TOKEN_MENOR = 291,             /* TOKEN_MENOR  */
    TOKEN_PUNTO = 292,             /* TOKEN_PUNTO  */
    TOKEN_PARENTESIS_ABRE = 293,   /* TOKEN_PARENTESIS_ABRE  */
    TOKEN_PARENTESIS_CIERRA = 294, /* TOKEN_PARENTESIS_CIERRA  */
    TOKEN_ERROR = 295              /* TOKEN_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "smart_home.y"

    char *texto;

#line 108 "smart_home.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SMART_HOME_TAB_H_INCLUDED  */
