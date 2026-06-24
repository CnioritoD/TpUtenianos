#include <stdio.h>
#include <ctype.h>
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

static int es_comando_salir(const char *entrada) {
    const char salir[] = "salir";
    int i;

    for (i = 0; salir[i] != '\0'; i++) {
        if (tolower((unsigned char)entrada[i]) != salir[i]) {
            return 0;
        }
    }

    while (entrada[i] != '\0') {
        if (!isspace((unsigned char)entrada[i])) {
            return 0;
        }
        i++;
    }

    return 1;
}

/* Modo interactivo: permite probar varias lineas sin que el programa se cierre. */
static int analizar_interactivo(void) {
    char entrada[512];
    int numero_linea = 1;
    int errores = 0;

    printf("Modo interactivo. Escribi codigo SMART-HOME y presiona Enter.\n");
    printf("Para salir escribi salir.\n");

    while (1) {
        printf("> ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            break;
        }

        if (entrada[0] == '\n' || entrada[0] == '\r') {
            continue;
        }

        if (es_comando_salir(entrada)) {
            break;
        }

        errores += analizar_linea(entrada, numero_linea);
        numero_linea++;
    }

    return errores;
}

static void mostrar_uso(const char *programa) {
    printf("Uso:\n");
    printf("  %s                 Ejecuta el modo interactivo\n", programa);
    printf("  %s archivo.txt     Analiza el archivo indicado\n", programa);
}

int main(int argc, char *argv[]) {
    int errores = 0;

    printf("--- Lexer SMART-HOME: reconocimiento de tokens ---\n");

    if (argc == 1) {
        errores = analizar_interactivo();
    } else if (argc == 2) {
        errores = analizar_archivo(argv[1]);
    } else {
        mostrar_uso(argv[0]);
        return 1;
    }

    if (errores == 0) {
        printf("\nAnalisis lexico finalizado sin errores.\n");
    } else {
        printf("\nAnalisis lexico finalizado con %d error(es).\n", errores);
    }

    return errores == 0 ? 0 : 1;
}
