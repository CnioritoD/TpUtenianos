/* Lexer SMART-HOME en formato Flex (.l).
   Genera un analizador lexico equivalente al lexer manual del proyecto. */

%option noyywrap
%option yylineno
%option caseless
%option nounput
%option noinput

%{
#include <stdio.h>
#include <stdlib.h>

static int errores = 0;

static void imprimir_token(const char *tipo, const char *valor) {
    printf("Linea %-3d | %-24s | %s\n", yylineno, tipo, valor);
}

static void imprimir_error(const char *valor) {
    imprimir_token("TOKEN_ERROR", valor);
    printf("          [ERROR LEXICO] Simbolo o cadena no reconocida: %s\n", valor);
    errores++;
}
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

"WHEN"                  { imprimir_token("TOKEN_WHEN", yytext); }
"EVERY"                 { imprimir_token("TOKEN_EVERY", yytext); }
"IF"                    { imprimir_token("TOKEN_IF", yytext); }
"THEN"                  { imprimir_token("TOKEN_THEN", yytext); }
"ELSE"                  { imprimir_token("TOKEN_ELSE", yytext); }
"DO"                    { imprimir_token("TOKEN_DO", yytext); }
"END"                   { imprimir_token("TOKEN_END", yytext); }
"AND"                   { imprimir_token("TOKEN_AND", yytext); }
"OR"                    { imprimir_token("TOKEN_OR", yytext); }
"NOT"                   { imprimir_token("TOKEN_NOT", yytext); }

"TRUE"|"FALSE"|"ON"|"OFF" {
                            imprimir_token("TOKEN_BOOL", yytext);
                        }

"FRIO"|"CALOR"|"VENT"   { imprimir_token("TOKEN_MODO", yytext); }
"BLANCO"|"ROJO"|"AZUL"|"WHITE"|"RED"|"BLUE" {
                            imprimir_token("TOKEN_COLOR", yytext);
                        }

"SENSOR_TEMP"|"SENSOR_TEMP_INT"|"SENSOR_HUMEDAD"|"SENSOR_LUZ" {
                            imprimir_token("TOKEN_ID_SENSOR_NUM", yytext);
                        }

"SENSOR_MOVIMIENTO"|"SENSOR_HUMO" {
                            imprimir_token("TOKEN_ID_SENSOR_BOOL", yytext);
                        }

("FOCO_"|"AIRE_"|"PERSIANA_"|"CERRADURA_"|"RELOJ_"|"ALTAVOZ_"|"ALARMA_")[A-Za-z0-9_-]+ {
                            imprimir_token("TOKEN_ID_DISPOSITIVO", yytext);
                        }
"RELOJ"|"ALARMA"        { imprimir_token("TOKEN_ID_DISPOSITIVO", yytext); }

"ESTADO"|"BRILLO"|"COLOR"|"MODO"|"TEMP_OBJ"|"TEMP_OBJETIVO"|"TEMP_ACT"|"TEMP_ACTUAL"|"POSICION"|"HORA"|"FECHA"|"VOLUMEN"|"MUTE"|"MENSAJE"|"EMAIL"|"EMAIL_NOTIF"|"ACTIVADA" {
                            imprimir_token("TOKEN_ATRIBUTO", yytext);
                        }

{EMAIL}                 { imprimir_token("TOKEN_EMAIL", yytext); }
{TEXTO}                 { imprimir_token("TOKEN_TEXTO", yytext); }
{HORA}                  { imprimir_token("TOKEN_HORA", yytext); }
{FECHA}                 { imprimir_token("TOKEN_FECHA", yytext); }
{TEMP}                  { imprimir_token("TOKEN_NUM_TEMP", yytext); }
{PORCENTAJE}            { imprimir_token("TOKEN_PERCENT", yytext); }
{TIEMPO}                { imprimir_token("TOKEN_TIME", yytext); }
{LUX}                   { imprimir_token("TOKEN_LUX", yytext); }
{NUMERO}                { imprimir_token("TOKEN_NUMERO", yytext); }

"=="                    { imprimir_token("TOKEN_IGUALDAD", yytext); }
"!="                    { imprimir_token("TOKEN_DIFERENTE", yytext); }
">="                    { imprimir_token("TOKEN_MAYOR_IGUAL", yytext); }
"<="                    { imprimir_token("TOKEN_MENOR_IGUAL", yytext); }
"="                     { imprimir_token("TOKEN_IGUAL", yytext); }
">"                     { imprimir_token("TOKEN_MAYOR", yytext); }
"<"                     { imprimir_token("TOKEN_MENOR", yytext); }
"."                     { imprimir_token("TOKEN_PUNTO", yytext); }
"("                     { imprimir_token("TOKEN_PARENTESIS_ABRE", yytext); }
")"                     { imprimir_token("TOKEN_PARENTESIS_CIERRA", yytext); }

{ID}                    { imprimir_token("TOKEN_ID", yytext); }
.                       { imprimir_error(yytext); }

%%

int main(int argc, char *argv[]) {
    printf("--- Lexer SMART-HOME: reconocimiento de tokens ---\n");

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("[ERROR] No se pudo abrir el archivo: %s\n", argv[1]);
            return 1;
        }
    } else if (argc > 2) {
        printf("Uso: %s [archivo]\n", argv[0]);
        return 1;
    }

    yylex();

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    if (errores == 0) {
        printf("\nAnalisis lexico finalizado sin errores.\n");
    } else {
        printf("\nAnalisis lexico finalizado con %d error(es).\n", errores);
    }

    return errores == 0 ? 0 : 1;
}
