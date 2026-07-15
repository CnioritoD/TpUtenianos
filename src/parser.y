/* Parser SMART-HOME con analisis sintactico, validaciones semanticas
   y generacion de HTML para scripts validos.

   Regla de salida:
   - Error lexico o sintactico: no se genera HTML.
   - Error semantico: se informa el error y no se genera HTML.
   - Sin errores: se genera el archivo HTML correspondiente.
*/

%code requires {
#include "semantica_html.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include "semantica_html.h"

extern int yylex(void);
extern int yylineno;
extern char *yytext;

int errores_sintacticos = 0;

void yyerror(const char *mensaje);
%}

%union {
    char *texto;
    Valor *valor;
    Operand *operand;
}

%token <texto> TOK_WHEN TOK_EVERY TOK_IF TOK_THEN TOK_ELSE TOK_DO TOK_END
%token <texto> TOK_AND TOK_OR TOK_NOT
%token <texto> TOK_BOOL TOK_MODO TOK_COLOR
%token <texto> TOK_ID_SENSOR_NUM TOK_ID_SENSOR_BOOL TOK_ID_DISPOSITIVO TOK_ATRIBUTO TOK_ID
%token <texto> TOK_EMAIL TOK_TEXTO TOK_HORA TOK_FECHA TOK_NUM_TEMP TOK_PERCENT TOK_TIME TOK_LUX TOK_NUMERO
%token <texto> TOK_IGUALDAD TOK_DIFERENTE TOK_MAYOR TOK_MENOR TOK_MAYOR_IGUAL TOK_MENOR_IGUAL TOK_IGUAL TOK_PUNTO
%token <texto> TOK_PARENTESIS_ABRE TOK_PARENTESIS_CIERRA
%token <texto> TOK_ERROR_LEXICO

%type <valor> valor
%type <operand> operando dispositivo_atributo
%type <texto> dispositivo atributo operador_comparacion

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
      {
          validar_y_registrar_asignacion($1, $3);
          liberar_operando($1);
          liberar_valor($3);
          free($2);
      }
    ;

dispositivo_atributo
    : dispositivo TOK_PUNTO atributo
      {
          $$ = crear_operando_atributo($1, $3);
          free($2);
      }
    ;

dispositivo
    : TOK_ID_DISPOSITIVO { $$ = $1; }
    | TOK_ID
      {
          registrar_error_semantico(linea_token, $1, "dispositivo no reconocido o prefijo invalido");
          $$ = $1;
      }
    ;

atributo
    : TOK_ATRIBUTO { $$ = $1; }
    | TOK_ID
      {
          registrar_error_semantico(linea_token, $1, "atributo no reconocido");
          $$ = $1;
      }
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
      {
          if (!bool_true_false($1)) {
              registrar_error_semantico(linea_token, $1, "en una condicion booleana se esperaba TRUE o FALSE");
          }
          free($1);
      }
    | TOK_ID_SENSOR_BOOL
      {
          agregar_sensor_html($1, "", "TRUE/FALSE");
          free($1);
      }
    ;

comparacion
    : operando operador_comparacion operando
      {
          validar_comparacion($1, $2, $3);
          liberar_operando($1);
          free($2);
          liberar_operando($3);
      }
    ;

operando
    : TOK_ID_SENSOR_NUM
      {
          $$ = crear_operando_simple($1, OP_SENSOR_NUM);
      }
    | TOK_ID_SENSOR_BOOL
      {
          $$ = crear_operando_simple($1, OP_SENSOR_BOOL);
      }
    | dispositivo_atributo
      {
          $$ = $1;
      }
    | valor
      {
          $$ = crear_operando_valor($1);
          liberar_valor($1);
      }
    ;

operador_comparacion
    : TOK_IGUALDAD     { $$ = $1; }
    | TOK_DIFERENTE    { $$ = $1; }
    | TOK_MAYOR        { $$ = $1; }
    | TOK_MENOR        { $$ = $1; }
    | TOK_MAYOR_IGUAL  { $$ = $1; }
    | TOK_MENOR_IGUAL  { $$ = $1; }
    ;

valor
    : TOK_BOOL     { $$ = crear_valor($1, VAL_BOOL); }
    | TOK_MODO     { $$ = crear_valor($1, VAL_MODO); }
    | TOK_COLOR    { $$ = crear_valor($1, VAL_COLOR); }
    | TOK_EMAIL    { $$ = crear_valor($1, VAL_EMAIL); }
    | TOK_TEXTO    { $$ = crear_valor($1, VAL_TEXTO); }
    | TOK_HORA     { $$ = crear_valor($1, VAL_HORA); }
    | TOK_FECHA    { $$ = crear_valor($1, VAL_FECHA); }
    | TOK_NUM_TEMP { $$ = crear_valor($1, VAL_TEMP); }
    | TOK_PERCENT  { $$ = crear_valor($1, VAL_PERCENT); }
    | TOK_TIME     { $$ = crear_valor($1, VAL_TIME); }
    | TOK_LUX      { $$ = crear_valor($1, VAL_LUX); }
    | TOK_NUMERO   { $$ = crear_valor($1, VAL_NUMERO); }
    | TOK_ID       { $$ = crear_valor($1, VAL_ID); }
    ;

%%

void yyerror(const char *mensaje) {
    errores_sintacticos++;
    fprintf(stderr, "[ERROR SINTACTICO] Linea %d: %s cerca de '%s'\n",
            yylineno, mensaje, yytext ? yytext : "EOF");
}
