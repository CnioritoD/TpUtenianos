/* Parser minimo para SMART-HOME usando Bison.
   Valida estructuras principales: WHEN, EVERY, IF/ELSE y asignaciones.
   Se conecta con smart_home_parser.l, que devuelve tokens desde Flex. */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(void);
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

static int errores_sintacticos = 0;

void yyerror(const char *mensaje);
static int tiene_extension_smart(const char *ruta);
%}

%token TOK_WHEN TOK_EVERY TOK_IF TOK_THEN TOK_ELSE TOK_DO TOK_END
%token TOK_AND TOK_OR TOK_NOT
%token TOK_BOOL TOK_MODO TOK_COLOR
%token TOK_ID_SENSOR_NUM TOK_ID_SENSOR_BOOL TOK_ID_DISPOSITIVO TOK_ATRIBUTO TOK_ID
%token TOK_EMAIL TOK_TEXTO TOK_HORA TOK_FECHA TOK_NUM_TEMP TOK_PERCENT TOK_TIME TOK_LUX TOK_NUMERO
%token TOK_IGUALDAD TOK_DIFERENTE TOK_MAYOR TOK_MENOR TOK_MAYOR_IGUAL TOK_MENOR_IGUAL TOK_IGUAL TOK_PUNTO
%token TOK_PARENTESIS_ABRE TOK_PARENTESIS_CIERRA
%token TOK_ERROR_LEXICO

%left TOK_OR
%left TOK_AND
%right TOK_NOT

%start programa

%%

programa
    : lista_instrucciones
    ;

lista_instrucciones
    : instruccion
    | lista_instrucciones instruccion
    ;

instruccion
    : bloque_when
    | bloque_every
    | bloque_if
    | asignacion
    ;

bloque_when
    : TOK_WHEN condicion TOK_DO lista_acciones TOK_END
    ;

bloque_every
    : TOK_EVERY TOK_TIME TOK_DO lista_acciones TOK_END
    ;

bloque_if
    : TOK_IF condicion TOK_THEN lista_acciones opt_else TOK_END
    ;

opt_else
    : /* vacio */
    | TOK_ELSE lista_acciones
    ;

lista_acciones
    : accion
    | lista_acciones accion
    ;

accion
    : asignacion
    | bloque_if
    ;

asignacion
    : dispositivo_atributo TOK_IGUAL valor
    ;

dispositivo_atributo
    : TOK_ID_DISPOSITIVO TOK_PUNTO TOK_ATRIBUTO
    ;

condicion
    : condicion TOK_OR termino_logico
    | termino_logico
    ;

termino_logico
    : termino_logico TOK_AND factor_logico
    | factor_logico
    ;

factor_logico
    : TOK_NOT factor_logico
    | TOK_PARENTESIS_ABRE condicion TOK_PARENTESIS_CIERRA
    | comparacion
    | TOK_BOOL
    | TOK_ID_SENSOR_BOOL
    ;

comparacion
    : operando operador_comparacion operando
    ;

operando
    : TOK_ID_SENSOR_NUM
    | TOK_ID_SENSOR_BOOL
    | dispositivo_atributo
    | valor
    ;

operador_comparacion
    : TOK_IGUALDAD
    | TOK_DIFERENTE
    | TOK_MAYOR
    | TOK_MENOR
    | TOK_MAYOR_IGUAL
    | TOK_MENOR_IGUAL
    ;

valor
    : TOK_BOOL
    | TOK_MODO
    | TOK_COLOR
    | TOK_EMAIL
    | TOK_TEXTO
    | TOK_HORA
    | TOK_FECHA
    | TOK_NUM_TEMP
    | TOK_PERCENT
    | TOK_TIME
    | TOK_LUX
    | TOK_NUMERO
    | TOK_ID
    ;

%%

void yyerror(const char *mensaje) {
    errores_sintacticos++;
    fprintf(stderr, "[ERROR SINTACTICO] Linea %d: %s cerca de '%s'\n",
            yylineno, mensaje, yytext ? yytext : "EOF");
}

static int tiene_extension_smart(const char *ruta) {
    const char *punto = strrchr(ruta, '.');
    return punto != NULL && strcmp(punto, ".smart") == 0;
}

int main(int argc, char **argv) {
    if (argc > 2) {
        fprintf(stderr, "Uso: %s [archivo.smart]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        if (!tiene_extension_smart(argv[1])) {
            fprintf(stderr, "[ERROR DE EJECUCION] El archivo debe tener extension .smart\n");
            return 1;
        }

        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "[ERROR DE EJECUCION] No se pudo abrir el archivo: %s\n", argv[1]);
            return 1;
        }
    } else {
        printf("Modo interactivo. Escribi una instruccion SMART-HOME y presiona Ctrl+Z/Ctrl+D para terminar.\n");
    }

    printf("--- Parser SMART-HOME ---\n");

    if (yyparse() == 0 && errores_sintacticos == 0) {
        printf("Analisis sintactico exitoso: archivo correctamente codificado.\n");
        if (yyin && yyin != stdin) fclose(yyin);
        return 0;
    }

    printf("Analisis sintactico finalizado con errores.\n");
    if (yyin && yyin != stdin) fclose(yyin);
    return 1;
}
