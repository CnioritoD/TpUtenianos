/* Lexer SMART-HOME para conectar con Bison.
   Devuelve tokens al parser y reporta errores lexicos con linea y lexema. */

%option noyywrap
%option yylineno
%option caseless
%option nounput
%option noinput

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int errores_lexicos = 0;
int linea_token = 1;

static char *copiar_yytext(void) {
    size_t n = strlen(yytext);
    char *r = (char *)malloc(n + 1);
    if (!r) exit(1);
    memcpy(r, yytext, n + 1);
    return r;
}

#define RET(tok) do { linea_token = yylineno; yylval.texto = copiar_yytext(); return tok; } while (0)
#define LEXERR(msg) do { linea_token = yylineno; errores_lexicos++; fprintf(stderr, "[ERROR LEXICO] Linea %d: %s cerca de '%s'\n", yylineno, msg, yytext); yylval.texto = copiar_yytext(); return TOK_ERROR_LEXICO; } while (0)
%}

DIGITO          [0-9]
LETRA           [A-Za-z_]
ID              {LETRA}[A-Za-z0-9_-]*
NUMERO          -?{DIGITO}+(\.{DIGITO}+)?
EMAIL           [A-Za-z0-9._%+-]+@([A-Za-z0-9-]+\.)+[A-Za-z]{2,4}
EMAIL_MALO      [A-Za-z0-9._%+-]*@[^ \t\r\n\"()<>!=]+
TEXTO           \"[^\"\r\n]*\"
TEXTO_CURVO     “[^”\r\n]*”
HORA            {DIGITO}{DIGITO}:{DIGITO}{DIGITO}
FECHA           {DIGITO}{DIGITO}\/{DIGITO}{DIGITO}\/{DIGITO}{DIGITO}{DIGITO}{DIGITO}
TEMP            {NUMERO}(\302\260)?[cC]
PORCENTAJE      {NUMERO}%
TIEMPO          {NUMERO}[smhSMH]
LUX             {NUMERO}[lL][uU][xX]
UNIDAD_MALA     {NUMERO}[A-Za-z%°][A-Za-z0-9%°]*

%%

[ \t\r\n]+              ;
"//".*                  ;

"WHEN"                  { RET(TOK_WHEN); }
"EVERY"                 { RET(TOK_EVERY); }
"IF"                    { RET(TOK_IF); }
"THEN"                  { RET(TOK_THEN); }
"ELSE"                  { RET(TOK_ELSE); }
"DO"                    { RET(TOK_DO); }
"END"                   { RET(TOK_END); }
"AND"                   { RET(TOK_AND); }
"OR"                    { RET(TOK_OR); }
"NOT"                   { RET(TOK_NOT); }

"TRUE"|"FALSE"|"ON"|"OFF" { RET(TOK_BOOL); }

"FRIO"|"CALOR"|"VENT"  { RET(TOK_MODO); }
"BLANCO"|"ROJO"|"AZUL"|"WHITE"|"RED"|"BLUE" { RET(TOK_COLOR); }

"SENSOR_TEMP"|"SENSOR_TEMP_INT"|"SENSOR_HUMEDAD"|"SENSOR_LUZ" { RET(TOK_ID_SENSOR_NUM); }
"SENSOR_MOVIMIENTO"|"SENSOR_HUMO" { RET(TOK_ID_SENSOR_BOOL); }

("FOCO_"|"AIRE_"|"PERSIANA_"|"CERRADURA_"|"RELOJ_"|"ALTAVOZ_"|"ALARMA_")[A-Za-z0-9_-]+ { RET(TOK_ID_DISPOSITIVO); }
"RELOJ"|"ALARMA"        { RET(TOK_ID_DISPOSITIVO); }

"ESTADO"|"BRILLO"|"COLOR"|"MODO"|"TEMP_OBJ"|"TEMP_OBJETIVO"|"TEMP_ACT"|"TEMP_ACTUAL"|"POSICION"|"HORA"|"FECHA"|"VOLUMEN"|"MUTE"|"MENSAJE"|"EMAIL"|"EMAIL_NOTIF"|"ACTIVADA" { RET(TOK_ATRIBUTO); }

{EMAIL}                 { RET(TOK_EMAIL); }
{EMAIL_MALO}            { LEXERR("email invalido"); }
{TEXTO}                 { RET(TOK_TEXTO); }
{TEXTO_CURVO}           { RET(TOK_TEXTO); }
{HORA}                  { RET(TOK_HORA); }
{FECHA}                 { RET(TOK_FECHA); }
{TEMP}                  { RET(TOK_NUM_TEMP); }
{PORCENTAJE}            { RET(TOK_PERCENT); }
{TIEMPO}                { RET(TOK_TIME); }
{LUX}                   { RET(TOK_LUX); }
{UNIDAD_MALA}           { LEXERR("unidad numerica invalida"); }
{NUMERO}                { RET(TOK_NUMERO); }

"=="                    { RET(TOK_IGUALDAD); }
"!="                    { RET(TOK_DIFERENTE); }
">="                    { RET(TOK_MAYOR_IGUAL); }
"<="                    { RET(TOK_MENOR_IGUAL); }
"="                     { RET(TOK_IGUAL); }
">"                     { RET(TOK_MAYOR); }
"<"                     { RET(TOK_MENOR); }
"."                     { RET(TOK_PUNTO); }
"("                     { RET(TOK_PARENTESIS_ABRE); }
")"                     { RET(TOK_PARENTESIS_CIERRA); }

{ID}                    { RET(TOK_ID); }
"@"                     { LEXERR("arroba fuera de un email valido"); }
.                       { LEXERR("simbolo o cadena no reconocida"); }

%%
