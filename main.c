#include <stdio.h>
#include "lexer.h"

int main() {
    char entrada[256];//Espacio en memoria para guardar tu texto

    printf("--- Analizador Léxico Interactivo ---\n");
    printf("Escribi tu codigo de prueba:\n> ");
    // Lee la línea de texto que ingresa el usuario por teclado (stdin)
    

    //si la entrada no es nula
    if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        const char *puntero_cadena = entrada;
        Token token;

        printf("\n--- Resultados del Análisis ---\n");
    
        // Bucle principal: procesa los tokens de la cadena ingresada
        do {
            token = obtener_siguiente_token(&puntero_cadena);

            printf("%s -> %s\n", nombre_token(token.tipo), token.valor);

        } while (token.tipo != TOKEN_EOF && token.tipo != TOKEN_ERROR);
    }
    printf("--------------------------------\n"); 
    return 0;
}