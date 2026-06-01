#include <stdio.h>
#include "lexer.h"

int main() {
    char entrada[256];

    printf("--- Compilador IoT: Analisis Lexico ---\n");
    printf("Escribi tu codigo de prueba:\n> ");

    if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        const char *puntero_cadena = entrada;
        Token token;

        do {
            token = obtener_siguiente_token(&puntero_cadena);
            printf("%s -> %s\n", nombre_token(token.tipo), token.valor);
        } while (token.tipo != TOKEN_EOF && token.tipo != TOKEN_ERROR);
    }

    return 0;
}