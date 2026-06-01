#include <stdio.h>
#include <string.h>
#include "lexer.h"

/* Recorre una linea completa y muestra cada token encontrado. */
static int analizar_linea(const char *linea, int numero_linea) {
    const char *cursor = linea;
    Token token;
    int errores = 0;

    do {
        token = obtener_siguiente_token(&cursor);

        /* TOKEN_EOF marca fin de linea/archivo; no hace falta imprimirlo. */
        if (token.tipo == TOKEN_EOF) {
            break;
        }

        printf("Linea %-3d | %-24s | %s\n",
               numero_linea,
               nombre_token(token.tipo),
               token.valor);

        /* Para la entrega del lexer mostramos errores lexicos con numero de linea. */
        if (token.tipo == TOKEN_ERROR) {
            printf("          [ERROR LEXICO] Simbolo o cadena no reconocida: %s\n", token.valor);
            errores++;
        }
    } while (token.tipo != TOKEN_EOF);

    return errores;
}

/* Modo opcional: analiza un archivo pasado por argumento. */
static int analizar_archivo(const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    char linea[512];
    int numero_linea = 1;
    int errores = 0;

    if (archivo == NULL) {
        printf("[ERROR] No se pudo abrir el archivo: %s\n", ruta);
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        errores += analizar_linea(linea, numero_linea);
        numero_linea++;
    }

    fclose(archivo);
    return errores;
}

int main(int argc, char *argv[]) {
    char entrada[512];
    int errores = 0;

    printf("--- Lexer SMART-HOME: reconocimiento de tokens ---\n");

    /* Sin argumentos funciona interactivo; con argumento analiza ese archivo. */
    if (argc > 1) {
        errores = analizar_archivo(argv[1]);
    } else {
        printf("Modo interactivo. Escribi codigo SMART-HOME y presiona Enter.\n");
        printf("> ");

        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            errores = analizar_linea(entrada, 1);
        }
    }

    if (errores == 0) {
        printf("\nAnalisis lexico finalizado sin errores.\n");
    } else {
        printf("\nAnalisis lexico finalizado con %d error(es).\n", errores);
    }

    return errores == 0 ? 0 : 1;
}
