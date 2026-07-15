#ifndef SEMANTICA_HTML_H
#define SEMANTICA_HTML_H

#ifndef SMART_HOME_TYPES_DEFINED
#define SMART_HOME_TYPES_DEFINED
typedef struct Valor {
    char *texto;
    int tipo;
} Valor;

typedef struct Operand {
    char *texto;
    char *dispositivo;
    char *atributo;
    int clase;
    int valor_tipo;
} Operand;
#endif

extern int errores_semanticos;
extern int errores_sintacticos;
extern int linea_token;
extern char archivo_html[512];

enum {
    VAL_BOOL = 1,
    VAL_MODO,
    VAL_COLOR,
    VAL_EMAIL,
    VAL_TEXTO,
    VAL_HORA,
    VAL_FECHA,
    VAL_TEMP,
    VAL_PERCENT,
    VAL_TIME,
    VAL_LUX,
    VAL_NUMERO,
    VAL_ID
};

enum {
    OP_VALOR = 1,
    OP_SENSOR_NUM,
    OP_SENSOR_BOOL,
    OP_DISP_ATTR
};

Valor *crear_valor(char *texto, int tipo);
void liberar_valor(Valor *v);
Operand *crear_operando_valor(Valor *v);
Operand *crear_operando_simple(char *texto, int clase);
Operand *crear_operando_atributo(char *dispositivo, char *atributo);
void liberar_operando(Operand *o);

void registrar_error_semantico(int linea, const char *lexema, const char *mensaje);
void validar_y_registrar_asignacion(Operand *destino, Valor *valor);
void validar_comparacion(Operand *izq, const char *op, Operand *der);
int bool_true_false(const char *texto);
void agregar_sensor_html(const char *nombre, const char *op, const char *valor);

void generar_html(void);
void construir_nombre_html(const char *ruta);

int tiene_extension_smart(const char *ruta);
void limpiar_ruta_ingresada(char *ruta);
void esperar_enter_si_interactivo(int modo_interactivo);

#endif
