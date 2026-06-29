/* Lexer SMART-HOME para conectar con Bison.
   Este no imprime tokens: los devuelve al parser. */

%option noyywrap
%option yylineno
%option caseless
%option nounput
%option noinput

%{
#include <stdio.h>
#include "parser.tab.h"
%}

DIGITO          [0-9]
LETRA           [A-Za-z_]
ID              {LETRA}[A-Za-z0-9_-]*
NUMERO          -?{DIGITO}+(\.{DIGITO}+)?
EMAIL           [A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}
TEXTO           \"[^\"\r\n]*\"
HORA            {DIGITO}{DIGITO}:{DIGITO}{DIGITO}
FECHA           {DIGITO}{DIGITO}\/{DIGITO}{DIGITO}\/{DIGITO}{DIGITO}{DIGITO}{DIGITO}
TEMP            {NUMERO}(\302\260)?[cC]
PORCENTAJE      {NUMERO}%
TIEMPO          {NUMERO}[smhSMH]
LUX             {NUMERO}[lL][uU][xX]

%%

[ \t\r\n]+              ;
"//".*                  ;

"WHEN"                  { return TOK_WHEN; }
"EVERY"                 { return TOK_EVERY; }
"IF"                    { return TOK_IF; }
"THEN"                  { return TOK_THEN; }
"ELSE"                  { return TOK_ELSE; }
"DO"                    { return TOK_DO; }
"END"                   { return TOK_END; }
"AND"                   { return TOK_AND; }
"OR"                    { return TOK_OR; }
"NOT"                   { return TOK_NOT; }

"TRUE"|"FALSE"|"ON"|"OFF" { return TOK_BOOL; }

"FRIO"|"CALOR"|"VENT"  { return TOK_MODO; }
"BLANCO"|"ROJO"|"AZUL"|"WHITE"|"RED"|"BLUE" { return TOK_COLOR; }

"SENSOR_TEMP"|"SENSOR_TEMP_INT"|"SENSOR_HUMEDAD"|"SENSOR_LUZ" { return TOK_ID_SENSOR_NUM; }
"SENSOR_MOVIMIENTO"|"SENSOR_HUMO" { return TOK_ID_SENSOR_BOOL; }

("FOCO_"|"AIRE_"|"PERSIANA_"|"CERRADURA_"|"RELOJ_"|"ALTAVOZ_"|"ALARMA_")[A-Za-z0-9_-]+ { return TOK_ID_DISPOSITIVO; }
"RELOJ"|"ALARMA"        { return TOK_ID_DISPOSITIVO; }

"ESTADO"|"BRILLO"|"COLOR"|"MODO"|"TEMP_OBJ"|"TEMP_OBJETIVO"|"TEMP_ACT"|"TEMP_ACTUAL"|"POSICION"|"HORA"|"FECHA"|"VOLUMEN"|"MUTE"|"MENSAJE"|"EMAIL"|"EMAIL_NOTIF"|"ACTIVADA" { return TOK_ATRIBUTO; }

{EMAIL}                 { return TOK_EMAIL; }
{TEXTO}                 { return TOK_TEXTO; }
{HORA}                  { return TOK_HORA; }
{FECHA}                 { return TOK_FECHA; }
{TEMP}                  { return TOK_NUM_TEMP; }
{PORCENTAJE}            { return TOK_PERCENT; }
{TIEMPO}                { return TOK_TIME; }
{LUX}                   { return TOK_LUX; }
{NUMERO}                { return TOK_NUMERO; }

"=="                    { return TOK_IGUALDAD; }
"!="                    { return TOK_DIFERENTE; }
">="                    { return TOK_MAYOR_IGUAL; }
"<="                    { return TOK_MENOR_IGUAL; }
"="                     { return TOK_IGUAL; }
">"                     { return TOK_MAYOR; }
"<"                     { return TOK_MENOR; }
"."                     { return TOK_PUNTO; }
"("                     { return TOK_PARENTESIS_ABRE; }
")"                     { return TOK_PARENTESIS_CIERRA; }

{ID}                    { return TOK_ID; }
.                       { return TOK_ERROR_LEXICO; }

%%
