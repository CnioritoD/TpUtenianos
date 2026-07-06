/* Lexer SMART-HOME simple.
   Reconoce los tokens usados por los ejemplos de ejemplosValidosSmart. */

%option noyywrap
%option yylineno
%option caseless
%option nounput
%option noinput

%{
#include <stdio.h>
#include "smart_home.tab.h"

static int errores_lexicos = 0;

static void imprimir_token(const char *tipo, const char *valor) {
    printf("Linea %-3d | %-24s | %s\n", yylineno, tipo, valor);
}

int obtener_errores_lexicos(void) {
    return errores_lexicos;
}

#ifdef LEXER_STANDALONE
#define TOKEN(tipo, nombre) do { imprimir_token((nombre), yytext); return (tipo); } while (0)
#else
#define TOKEN(tipo, nombre) return (tipo)
#endif
%}

DIGITO      [0-9]
LETRA       [A-Za-z_]
ID          {LETRA}[A-Za-z0-9_-]*
NUMERO      -?{DIGITO}+(\.{DIGITO}+)?
EMAIL       [A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}
TEXTO       \"[^\"\r\n]*\"|\342\200\234[^\r\n]*\342\200\235
HORA        {DIGITO}{DIGITO}:{DIGITO}{DIGITO}
FECHA       {DIGITO}{DIGITO}\/{DIGITO}{DIGITO}\/{DIGITO}{DIGITO}{DIGITO}{DIGITO}
TEMP        {NUMERO}(\302\260)?[cC]
PORCENTAJE  {NUMERO}%
TIEMPO      {NUMERO}[smhSMH]
LUX         {NUMERO}[lL][uU][xX]

%%

[ \t\r\n]+      ;
"//".*          ;

"WHEN"          { TOKEN(TOKEN_WHEN, "TOKEN_WHEN"); }
"EVERY"         { TOKEN(TOKEN_EVERY, "TOKEN_EVERY"); }
"IF"            { TOKEN(TOKEN_IF, "TOKEN_IF"); }
"THEN"          { TOKEN(TOKEN_THEN, "TOKEN_THEN"); }
"ELSE"          { TOKEN(TOKEN_ELSE, "TOKEN_ELSE"); }
"DO"            { TOKEN(TOKEN_DO, "TOKEN_DO"); }
"END"           { TOKEN(TOKEN_END, "TOKEN_END"); }
"AND"           { TOKEN(TOKEN_AND, "TOKEN_AND"); }
"OR"            { TOKEN(TOKEN_OR, "TOKEN_OR"); }
"NOT"           { TOKEN(TOKEN_NOT, "TOKEN_NOT"); }

"TRUE"|"FALSE"|"ON"|"OFF" {
                    TOKEN(TOKEN_BOOL, "TOKEN_BOOL");
                }

"FRIO"|"CALOR"|"VENT" {
                    TOKEN(TOKEN_MODO, "TOKEN_MODO");
                }

"BLANCO"|"ROJO"|"AZUL"|"WHITE"|"RED"|"BLUE" {
                    TOKEN(TOKEN_COLOR, "TOKEN_COLOR");
                }

"SENSOR_TEMP"|"SENSOR_TEMP_INT"|"SENSOR_HUMEDAD"|"SENSOR_LUZ" {
                    TOKEN(TOKEN_ID_SENSOR_NUM, "TOKEN_ID_SENSOR_NUM");
                }

"SENSOR_MOVIMIENTO"|"SENSOR_HUMO" {
                    TOKEN(TOKEN_ID_SENSOR_BOOL, "TOKEN_ID_SENSOR_BOOL");
                }

("FOCO_"|"AIRE_"|"PERSIANA_"|"CERRADURA_"|"RELOJ_"|"ALTAVOZ_"|"ALARMA_")[A-Za-z0-9_-]+ {
                    TOKEN(TOKEN_ID_DISPOSITIVO, "TOKEN_ID_DISPOSITIVO");
                }

"RELOJ"|"ALARMA" {
                    TOKEN(TOKEN_ID_DISPOSITIVO, "TOKEN_ID_DISPOSITIVO");
                }

"ESTADO"|"BRILLO"|"COLOR"|"MODO"|"TEMP_OBJ"|"TEMP_OBJETIVO"|"TEMP_ACT"|"TEMP_ACTUAL"|"POSICION"|"HORA"|"FECHA"|"VOLUMEN"|"MUTE"|"MENSAJE"|"EMAIL"|"EMAIL_NOTIF"|"ACTIVADA" {
                    TOKEN(TOKEN_ATRIBUTO, "TOKEN_ATRIBUTO");
                }

{EMAIL}         { TOKEN(TOKEN_EMAIL, "TOKEN_EMAIL"); }
{TEXTO}         { TOKEN(TOKEN_TEXTO, "TOKEN_TEXTO"); }
{HORA}          { TOKEN(TOKEN_HORA, "TOKEN_HORA"); }
{FECHA}         { TOKEN(TOKEN_FECHA, "TOKEN_FECHA"); }
{TEMP}          { TOKEN(TOKEN_NUM_TEMP, "TOKEN_NUM_TEMP"); }
{PORCENTAJE}    { TOKEN(TOKEN_PERCENT, "TOKEN_PERCENT"); }
{TIEMPO}        { TOKEN(TOKEN_TIME, "TOKEN_TIME"); }
{LUX}           { TOKEN(TOKEN_LUX, "TOKEN_LUX"); }
{NUMERO}        { TOKEN(TOKEN_NUMERO, "TOKEN_NUMERO"); }

"=="            { TOKEN(TOKEN_IGUALDAD, "TOKEN_IGUALDAD"); }
"!="            { TOKEN(TOKEN_DIFERENTE, "TOKEN_DIFERENTE"); }
">="            { TOKEN(TOKEN_MAYOR_IGUAL, "TOKEN_MAYOR_IGUAL"); }
"<="            { TOKEN(TOKEN_MENOR_IGUAL, "TOKEN_MENOR_IGUAL"); }
"="             { TOKEN(TOKEN_IGUAL, "TOKEN_IGUAL"); }
">"             { TOKEN(TOKEN_MAYOR, "TOKEN_MAYOR"); }
"<"             { TOKEN(TOKEN_MENOR, "TOKEN_MENOR"); }
"."             { TOKEN(TOKEN_PUNTO, "TOKEN_PUNTO"); }
"("             { TOKEN(TOKEN_PARENTESIS_ABRE, "TOKEN_PARENTESIS_ABRE"); }
")"             { TOKEN(TOKEN_PARENTESIS_CIERRA, "TOKEN_PARENTESIS_CIERRA"); }

{ID}            { TOKEN(TOKEN_ID, "TOKEN_ID"); }

.               {
                    imprimir_token("TOKEN_ERROR", yytext);
                    printf("          [ERROR LEXICO] Simbolo no reconocido: %s\n", yytext);
                    errores_lexicos++;
                    return TOKEN_ERROR;
                }

%%

#ifdef LEXER_STANDALONE
int main(int argc, char *argv[]) {
    printf("--- Lexer SMART-HOME simple ---\n");

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

    while (yylex() != 0) {
    }

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    if (errores_lexicos == 0) {
        printf("\nAnalisis lexico finalizado sin errores.\n");
    } else {
        printf("\nAnalisis lexico finalizado con %d error(es).\n", errores_lexicos);
    }

    return errores_lexicos == 0 ? 0 : 1;
}
#endif
