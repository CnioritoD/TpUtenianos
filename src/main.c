#include <stdio.h>

#include "semantica_html.h"

extern FILE *yyin;
extern int errores_lexicos;
extern int yyparse(void);

static int finalizar(int codigo, int modo_interactivo) {
    esperar_enter_si_interactivo(modo_interactivo);
    return codigo;
}

int main(int argc, char **argv) {
    int resultado;
    int modo_interactivo = argc == 1;
    const char *archivo_entrada;
    char ruta_interactiva[512];

    if (argc > 2) {
        fprintf(stderr, "Uso: %s archivo.smart\n", argv[0]);
        return finalizar(1, modo_interactivo);
    }

    if (modo_interactivo) {
        printf("--- Parser SMART-HOME ---\n");
        printf("Ingrese la ruta de un archivo .smart y presione Enter.\n");
        printf("Ejemplos si abre desde bin: ..\\prueba\\ejemplo_valido_catedra.smart\n");
        printf("Ejemplos desde la carpeta principal: prueba\\ejemplo_valido_catedra.smart\n");
        printf("> ");
        fflush(stdout);

        if (!fgets(ruta_interactiva, sizeof(ruta_interactiva), stdin)) {
            fprintf(stderr, "[ERROR DE EJECUCION] No se pudo leer la ruta ingresada.\n");
            return finalizar(1, modo_interactivo);
        }

        limpiar_ruta_ingresada(ruta_interactiva);
        if (ruta_interactiva[0] == '\0') {
            fprintf(stderr, "[ERROR DE EJECUCION] Debe ingresar un archivo .smart.\n");
            return finalizar(1, modo_interactivo);
        }

        archivo_entrada = ruta_interactiva;
    } else {
        archivo_entrada = argv[1];
    }

    if (!tiene_extension_smart(archivo_entrada)) {
        fprintf(stderr, "[ERROR DE EJECUCION] El archivo debe tener extension .smart\n");
        return finalizar(1, modo_interactivo);
    }

    yyin = fopen(archivo_entrada, "r");
    if (!yyin) {
        fprintf(stderr, "[ERROR DE EJECUCION] No se pudo abrir el archivo: %s\n", archivo_entrada);
        return finalizar(1, modo_interactivo);
    }

    construir_nombre_html(archivo_entrada);

    if (!modo_interactivo) printf("--- Parser SMART-HOME ---\n");
    resultado = yyparse();

    if (yyin && yyin != stdin) fclose(yyin);

    if (resultado == 0 && errores_lexicos == 0 && errores_sintacticos == 0) {
        printf("Analisis lexico y sintactico exitoso.\n");

        if (errores_semanticos > 0) {
            printf("Analisis semantico finalizado con %d error(es).\n", errores_semanticos);
            printf("No se genera HTML porque el archivo contiene errores semanticos.\n");
            return finalizar(2, modo_interactivo);
        }

        printf("Analisis semantico exitoso.\n");
        generar_html();
        printf("HTML generado correctamente: %s\n", archivo_html);
        return finalizar(0, modo_interactivo);
    }

    printf("Analisis finalizado con errores lexicos o sintacticos. No se genera HTML.\n");
    return finalizar(1, modo_interactivo);
}
