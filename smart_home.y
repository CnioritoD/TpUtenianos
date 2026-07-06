/* Parser SMART-HOME simple.
   Solo reconoce la estructura usada en los ejemplos de la carpeta ejemplosValidosSmart. */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern char *yytext;
extern int obtener_errores_lexicos(void);

static int errores_sintacticos = 0;

static int yyerror(const char *mensaje);
static int termina_en_smart(const char *ruta);
%}

%union {
    char *texto;
}

%token <texto> TOKEN_WHEN TOKEN_EVERY TOKEN_IF TOKEN_THEN TOKEN_ELSE TOKEN_DO TOKEN_END
%token <texto> TOKEN_AND TOKEN_OR TOKEN_NOT
%token <texto> TOKEN_BOOL TOKEN_MODO TOKEN_COLOR
%token <texto> TOKEN_ID_SENSOR_NUM TOKEN_ID_SENSOR_BOOL TOKEN_ID_DISPOSITIVO TOKEN_ATRIBUTO TOKEN_ID
%token <texto> TOKEN_EMAIL TOKEN_TEXTO TOKEN_HORA TOKEN_FECHA TOKEN_NUM_TEMP TOKEN_PERCENT TOKEN_TIME TOKEN_LUX TOKEN_NUMERO
%token <texto> TOKEN_IGUALDAD TOKEN_DIFERENTE TOKEN_MAYOR_IGUAL TOKEN_MENOR_IGUAL TOKEN_IGUAL TOKEN_MAYOR TOKEN_MENOR
%token <texto> TOKEN_PUNTO TOKEN_PARENTESIS_ABRE TOKEN_PARENTESIS_CIERRA TOKEN_ERROR

%left TOKEN_OR
%left TOKEN_AND
%right TOKEN_NOT

%start programa

%%

programa
    : instruccion
    | programa instruccion
    ;

instruccion
    : bloque_when
    | bloque_every
    | condicional
    | asignacion
    ;

bloque_when
    : TOKEN_WHEN condicion TOKEN_DO lista_acciones TOKEN_END
    ;

bloque_every
    : TOKEN_EVERY TOKEN_TIME TOKEN_DO lista_acciones TOKEN_END
    ;

condicional
    : TOKEN_IF condicion TOKEN_THEN lista_acciones TOKEN_END
    | TOKEN_IF condicion TOKEN_THEN lista_acciones TOKEN_ELSE lista_acciones TOKEN_END
    ;

lista_acciones
    : accion lista_acciones
    | accion
    ;

accion
    : asignacion
    | condicional
    ;

asignacion
    : TOKEN_ID_DISPOSITIVO TOKEN_PUNTO TOKEN_ATRIBUTO TOKEN_IGUAL valor
    ;

condicion
    : exp_logica
    ;

exp_logica
    : termino_logico TOKEN_OR exp_logica
    | termino_logico
    ;

termino_logico
    : factor_logico TOKEN_AND termino_logico
    | factor_logico
    ;

factor_logico
    : TOKEN_NOT factor_logico
    | TOKEN_PARENTESIS_ABRE exp_logica TOKEN_PARENTESIS_CIERRA
    | comparacion
    | TOKEN_BOOL
    | TOKEN_ID_SENSOR_BOOL
    ;

comparacion
    : exp_evaluada op_comp exp_evaluada
    ;

op_comp
    : TOKEN_IGUALDAD
    | TOKEN_DIFERENTE
    | TOKEN_MAYOR
    | TOKEN_MENOR
    | TOKEN_MAYOR_IGUAL
    | TOKEN_MENOR_IGUAL
    ;

exp_evaluada
    : referencia
    | valor
    ;

referencia
    : TOKEN_ID_SENSOR_NUM
    | TOKEN_ID_SENSOR_BOOL
    | TOKEN_ID_DISPOSITIVO TOKEN_PUNTO TOKEN_ATRIBUTO
    ;

valor
    : valor_numerico
    | TOKEN_BOOL
    | TOKEN_MODO
    | TOKEN_COLOR
    | TOKEN_EMAIL
    | TOKEN_TEXTO
    | TOKEN_HORA
    | TOKEN_FECHA
    | TOKEN_TIME
    ;

valor_numerico
    : TOKEN_NUM_TEMP
    | TOKEN_PERCENT
    | TOKEN_LUX
    ;

%%

static int yyerror(const char *mensaje) {
    printf("[ERROR SINTACTICO] Linea %d cerca de '%s': %s\n", yylineno, yytext, mensaje);
    errores_sintacticos++;
    return 0;
}

static int termina_en_smart(const char *ruta) {
    size_t largo = strlen(ruta);
    return largo >= 6 && strcmp(ruta + largo - 6, ".smart") == 0;
}

int main(int argc, char *argv[]) {
    int resultado;

    printf("--- Parser SMART-HOME simple ---\n");

    if (argc == 2) {
        if (!termina_en_smart(argv[1])) {
            printf("[ERROR] El archivo debe tener extension .smart\n");
            return 1;
        }

        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("[ERROR] No se pudo abrir el archivo: %s\n", argv[1]);
            return 1;
        }
    } else if (argc > 2) {
        printf("Uso: %s [archivo.smart]\n", argv[0]);
        return 1;
    }

    resultado = yyparse();

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    if (resultado == 0 && errores_sintacticos == 0 && obtener_errores_lexicos() == 0) {
        printf("Analisis sintactico correcto.\n");
        return 0;
    }

    printf("Analisis finalizado con errores.\n");
    return 1;
}
