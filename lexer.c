#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// La función mantiene la firma exacta que hizo Martín
Token obtener_siguiente_token(const char **cadena) {
    Token t;
    t.valor[0] = '\0';
    
    // 1. Saltar espacios y saltos de línea
    while (isspace(**cadena)) {
        (*cadena)++;
    }

    // 2. Si llegamos al final de lo que escribiste
    if (**cadena == '\0') {
        t.tipo = TOKEN_EOF;
        strcpy(t.valor, "EOF");
        return t;
    }

    char c = **cadena;

    // 3. Símbolos simples (Punto e Igual)
    if (c == '.') {
        t.tipo = TOKEN_PUNTO;
        t.valor[0] = c; t.valor[1] = '\0';
        (*cadena)++;
        return t;
    }
    if (c == '=') {
        t.tipo = TOKEN_IGUAL;
        t.valor[0] = c; t.valor[1] = '\0';
        (*cadena)++;
        return t;
    }

    // 4. Leer números (ej: 25)
    if (isdigit(c)) {
        int i = 0;
        while (isdigit(**cadena)) {
            t.valor[i++] = **cadena;
            (*cadena)++;
        }
        t.valor[i] = '\0';
        t.tipo = TOKEN_NUMERO;
        return t;
    }

    // 5. Leer palabras (nombres de sensores o palabras reservadas)
    if (isalpha(c)) {
        int i = 0;
        // Agrupa mientras sean letras o números
        while (isalnum(**cadena) || **cadena == '_') {
            t.valor[i++] = **cadena;
            (*cadena)++;
        }
        t.valor[i] = '\0';

        // Verifica si la palabra es una de las tuyas
        if (strcmp(t.valor, "WHEN") == 0) t.tipo = TOKEN_WHEN;
        else if (strcmp(t.valor, "EVERY") == 0) t.tipo = TOKEN_EVERY;
        else if (strcmp(t.valor, "DO") == 0) t.tipo = TOKEN_DO;
        else if (strcmp(t.valor, "END") == 0) t.tipo = TOKEN_END;
        else if (strcmp(t.valor, "IF") == 0) t.tipo = TOKEN_IF;
        else if (strcmp(t.valor, "THEN") == 0) t.tipo = TOKEN_THEN;
        else if (strcmp(t.valor, "ELSE") == 0) t.tipo = TOKEN_ELSE;
        else t.tipo = TOKEN_ID; // Si no es ninguna, es un dispositivo/atributo

        return t;
    }

    // 6. Si escribís un símbolo que el lenguaje no conoce
    t.tipo = TOKEN_ERROR;
    t.valor[0] = c; t.valor[1] = '\0';
    (*cadena)++;
    return t;
}