#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

Token token_actual;
const char **codigo_fuente;

// Función para pedirle al lexer el siguiente token
void avanzar() {
    token_actual = obtener_siguiente_token(codigo_fuente);
}

// Función que comprueba si el token actual es el esperado
void coincidir(TipoToken esperado, const char* nombre_esperado) {
    if (token_actual.tipo == esperado) {
        avanzar(); // Si es correcto, pasamos al siguiente
    } else {
        printf("\n[ERROR SINTACTICO] Se esperaba '%s', pero se encontro otra cosa.\n", nombre_esperado);
        exit(1); // Detiene el programa si hay un error
    }
}

// --- REGLAS BASICAS ---

void parse_condicion() {
    printf("  -> Validando CONDICION (Dispositivo.Atributo = Valor)...\n");
    coincidir(TOKEN_ID, "nombre del sensor");
    coincidir(TOKEN_PUNTO, "punto (.)");
    coincidir(TOKEN_ID, "atributo (ej: temp)");
    coincidir(TOKEN_IGUAL, "signo igual (=)");
    coincidir(TOKEN_NUMERO, "valor numerico");
    printf("     [OK] Condicion valida.\n");
}

void parse_accion() {
    printf("  -> Validando ACCION (Asignacion)...\n");
    coincidir(TOKEN_ID, "dispositivo destino");
    coincidir(TOKEN_IGUAL, "signo igual (=)");
    coincidir(TOKEN_NUMERO, "valor a asignar");
    printf("     [OK] Accion valida.\n");
}

// --- REGLAS DE BLOQUES ---

void parse_bloque_when() {
    printf("\n>>> Iniciando analisis de BLOQUE_WHEN...\n");
    coincidir(TOKEN_WHEN, "WHEN");
    parse_condicion();
    coincidir(TOKEN_DO, "DO");
    parse_accion();
    coincidir(TOKEN_END, "END");
    printf(">>> [EXITO] Bloque WHEN validado correctamente!\n\n");
}

void parse_bloque_every() {
    printf("\n>>> Iniciando analisis de BLOQUE_EVERY...\n");
    coincidir(TOKEN_EVERY, "EVERY");
    // Por ahora usamos NUMERO para simular el TK_TIME
    coincidir(TOKEN_NUMERO, "valor de tiempo (ej: 60)"); 
    coincidir(TOKEN_DO, "DO");
    parse_accion(); // Reutilizamos la accion!
    coincidir(TOKEN_END, "END");
    printf(">>> [EXITO] Bloque EVERY validado correctamente!\n\n");
}

// --- EL SEMÁFORO (REGLA INSTRUCCION) ---

void parse_instruccion() {
    if (token_actual.tipo == TOKEN_WHEN) {
        parse_bloque_when();
    } 
    else if (token_actual.tipo == TOKEN_EVERY) {
        parse_bloque_every();
    } 
    else {
        printf("\n[ERROR] Instruccion no reconocida. El programa debe empezar con WHEN o EVERY.\n");
        exit(1);
    }
}

// Punto de entrada del parser
void iniciar_parser(const char **cadena) {
    codigo_fuente = cadena;
    avanzar(); // Cargamos el primer token para empezar
    
    // Llamamos al semáforo para que decida qué ruta tomar
    parse_instruccion(); 
}