#include <stdio.h>
#include "lexer.h"

int main() {
    char entrada[256];
    
    printf("--- Compilador IoT: Analisis Lexico y Sintactico ---\n");
    printf("Escribi tu codigo de prueba:\n> ");
    
    if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        const char *puntero_cadena = entrada;
        
        // En vez de hacer el bucle pidiendo tokens, le pasamos el control al Parser
        iniciar_parser(&puntero_cadena);
    }
    
    return 0;
}