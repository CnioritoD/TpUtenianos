#include "semantica_html.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int linea_token;

typedef struct {
    char dispositivo[128];
    char atributo[64];
    char valor[256];
    int es_email;
} HtmlAccion;

typedef struct {
    char nombre[128];
    char operador[8];
    char valor[128];
} HtmlSensor;

#define MAX_HTML_ACCIONES 300
#define MAX_HTML_SENSORES 150

int errores_semanticos = 0;
char archivo_html[512] = "salida.html";

static HtmlAccion acciones_html[MAX_HTML_ACCIONES];
static int cant_acciones_html = 0;

static HtmlSensor sensores_html[MAX_HTML_SENSORES];
static int cant_sensores_html = 0;

static char *copiar_texto(const char *s);
static int igual_icase(const char *a, const char *b);
static int esta_en_lista(const char *texto, const char *const lista[]);
static int empieza_icase(const char *texto, const char *prefijo);
static int contiene_icase(const char *texto, const char *frag);
static void a_minusculas(char *dst, const char *src, size_t max);
static void normalizar_atributo(char *dst, const char *src, size_t max);
static const char *tipo_dispositivo(const char *disp);
static int atributo_permitido(const char *tipo_disp, const char *attr);
static int es_solo_lectura(const char *tipo_disp, const char *attr);
static int numero_de_valor(const char *texto, double *out);
static int porcentaje_en_rango(const char *texto, double min, double max);
static int temp_en_rango(const char *texto, double min, double max);
static int lux_en_rango(const char *texto, double min, double max);
static int hora_valida(const char *texto);
static int es_bisiesto(int anio);
static int dias_del_mes(int mes, int anio);
static int fecha_valida_general(const char *texto);
static int email_valido(const char *texto);
static int bool_on_off(const char *texto);
static int valor_es_email_por_atributo(const char *attr);
static void validar_tipo_valor(const char *tipo_disp, const char *attr_original, Valor *valor);
static void validar_sensor_con_valor(Operand *sensor, const char *op, Operand *valor);
static void agregar_accion_html(const char *disp, const char *attr, const char *valor);
static void html_escape(FILE *f, const char *s);
static void html_valor(FILE *f, const char *attr, const char *valor);

static char *copiar_texto(const char *s) {
    size_t n;
    char *r;
    if (!s) s = "";
    n = strlen(s);
    r = (char *)malloc(n + 1);
    if (!r) {
        fprintf(stderr, "Sin memoria.\n");
        exit(1);
    }
    memcpy(r, s, n + 1);
    return r;
}

Valor *crear_valor(char *texto, int tipo) {
    Valor *v = (Valor *)malloc(sizeof(Valor));
    if (!v) exit(1);
    v->texto = texto;
    v->tipo = tipo;
    return v;
}

void liberar_valor(Valor *v) {
    if (!v) return;
    free(v->texto);
    free(v);
}

Operand *crear_operando_simple(char *texto, int clase) {
    Operand *o = (Operand *)calloc(1, sizeof(Operand));
    if (!o) exit(1);
    o->texto = texto;
    o->clase = clase;
    o->valor_tipo = 0;
    return o;
}

Operand *crear_operando_atributo(char *dispositivo, char *atributo) {
    Operand *o = (Operand *)calloc(1, sizeof(Operand));
    if (!o) exit(1);
    o->dispositivo = dispositivo;
    o->atributo = atributo;
    o->clase = OP_DISP_ATTR;
    o->valor_tipo = 0;

    o->texto = (char *)malloc(strlen(dispositivo) + strlen(atributo) + 2);
    if (!o->texto) exit(1);
    sprintf(o->texto, "%s.%s", dispositivo, atributo);
    return o;
}

Operand *crear_operando_valor(Valor *v) {
    Operand *o = (Operand *)calloc(1, sizeof(Operand));
    if (!o) exit(1);
    o->texto = copiar_texto(v->texto);
    o->clase = OP_VALOR;
    o->valor_tipo = v->tipo;
    return o;
}

void liberar_operando(Operand *o) {
    if (!o) return;
    free(o->texto);
    free(o->dispositivo);
    free(o->atributo);
    free(o);
}

void registrar_error_semantico(int linea, const char *lexema, const char *mensaje) {
    errores_semanticos++;
    fprintf(stderr, "[ERROR SEMANTICO] Linea %d: %s cerca de '%s'\n",
            linea > 0 ? linea : yylineno,
            mensaje,
            lexema ? lexema : "");
}

static int igual_icase(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

static int esta_en_lista(const char *texto, const char *const lista[]) {
    int i;
    if (!texto || !lista) return 0;
    for (i = 0; lista[i]; i++) {
        if (igual_icase(texto, lista[i])) return 1;
    }
    return 0;
}

static int empieza_icase(const char *texto, const char *prefijo) {
    if (!texto || !prefijo) return 0;
    while (*prefijo) {
        if (tolower((unsigned char)*texto) != tolower((unsigned char)*prefijo)) return 0;
        texto++;
        prefijo++;
    }
    return 1;
}

static int contiene_icase(const char *texto, const char *frag) {
    size_t n, m, i, j;
    if (!texto || !frag) return 0;
    n = strlen(texto);
    m = strlen(frag);
    if (m == 0 || m > n) return 0;
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (tolower((unsigned char)texto[i + j]) != tolower((unsigned char)frag[j])) break;
        }
        if (j == m) return 1;
    }
    return 0;
}

static void a_minusculas(char *dst, const char *src, size_t max) {
    size_t i;
    for (i = 0; src && src[i] && i + 1 < max; i++) {
        dst[i] = (char)tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

static void normalizar_atributo(char *dst, const char *src, size_t max) {
    a_minusculas(dst, src, max);
    if (igual_icase(dst, "temp_objetivo")) strncpy(dst, "temp_obj", max);
    if (igual_icase(dst, "temp_actual")) strncpy(dst, "temp_act", max);
    dst[max - 1] = '\0';
}

static const char *tipo_dispositivo(const char *disp) {
    static const struct {
        const char *prefijo;
        const char *tipo;
    } tipos[] = {
        {"foco_", "foco"},
        {"aire_", "aire"},
        {"persiana_", "persiana"},
        {"cerradura_", "cerradura"},
        {"reloj_", "reloj"},
        {"altavoz_", "altavoz"},
        {"alarma_", "alarma"},
        {NULL, NULL}
    };
    int i;
    for (i = 0; tipos[i].prefijo; i++) {
        if (empieza_icase(disp, tipos[i].prefijo)) return tipos[i].tipo;
    }
    if (igual_icase(disp, "reloj")) return "reloj";
    if (igual_icase(disp, "alarma")) return "alarma";
    return NULL;
}

static int atributo_permitido(const char *tipo_disp, const char *attr_original) {
    static const char *const attrs_foco[] = {"estado", "brillo", "color", NULL};
    static const char *const attrs_aire[] = {"estado", "modo", "temp_obj", "temp_act", NULL};
    static const char *const attrs_persiana[] = {"posicion", NULL};
    static const char *const attrs_cerradura[] = {"estado", NULL};
    static const char *const attrs_reloj[] = {"hora", "fecha", NULL};
    static const char *const attrs_altavoz[] = {"volumen", "mute", "mensaje", "email", "email_notif", NULL};
    static const char *const attrs_alarma[] = {"estado", "activada", NULL};
    static const struct {
        const char *tipo;
        const char *const *attrs;
    } permisos[] = {
        {"foco", attrs_foco},
        {"aire", attrs_aire},
        {"persiana", attrs_persiana},
        {"cerradura", attrs_cerradura},
        {"reloj", attrs_reloj},
        {"altavoz", attrs_altavoz},
        {"alarma", attrs_alarma},
        {NULL, NULL}
    };
    char attr[64];
    int i;

    normalizar_atributo(attr, attr_original, sizeof(attr));
    if (!tipo_disp) return 0;

    for (i = 0; permisos[i].tipo; i++) {
        if (igual_icase(tipo_disp, permisos[i].tipo)) {
            return esta_en_lista(attr, permisos[i].attrs);
        }
    }
    return 0;
}

static int es_solo_lectura(const char *tipo_disp, const char *attr_original) {
    static const char *const attrs_reloj[] = {"hora", "fecha", NULL};
    char attr[64];
    normalizar_atributo(attr, attr_original, sizeof(attr));
    return (igual_icase(tipo_disp, "aire") && igual_icase(attr, "temp_act")) ||
           (igual_icase(tipo_disp, "reloj") && esta_en_lista(attr, attrs_reloj));
}

static int numero_de_valor(const char *texto, double *out) {
    char *fin;
    if (!texto) return 0;
    *out = strtod(texto, &fin);
    return fin != texto;
}

static int porcentaje_en_rango(const char *texto, double min, double max) {
    double n;
    if (!contiene_icase(texto, "%")) return 0;
    if (!numero_de_valor(texto, &n)) return 0;
    return n >= min && n <= max;
}

static int temp_en_rango(const char *texto, double min, double max) {
    double n;
    if (!contiene_icase(texto, "c")) return 0;
    if (!numero_de_valor(texto, &n)) return 0;
    return n >= min && n <= max;
}

static int lux_en_rango(const char *texto, double min, double max) {
    double n;
    if (!contiene_icase(texto, "lux")) return 0;
    if (!numero_de_valor(texto, &n)) return 0;
    return n >= min && n <= max;
}

static int hora_valida(const char *texto) {
    int h, m, usados;
    if (!texto || sscanf(texto, "%2d:%2d%n", &h, &m, &usados) != 2) return 0;
    if (texto[usados] != '\0') return 0;
    return h >= 0 && h <= 23 && m >= 0 && m <= 59;
}

static int es_bisiesto(int anio) {
    return (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);
}

static int dias_del_mes(int mes, int anio) {
    static const int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) return 0;
    if (mes == 2 && es_bisiesto(anio)) return 29;
    return dias[mes];
}

static int fecha_valida_general(const char *texto) {
    int d, m, a, usados;
    if (!texto || sscanf(texto, "%2d/%2d/%4d%n", &d, &m, &a, &usados) != 3) return 0;
    if (texto[usados] != '\0') return 0;
    if (a < 1900 || a > 2099) return 0;
    return d >= 1 && d <= dias_del_mes(m, a);
}

static int email_valido(const char *texto) {
    const char *arroba, *punto;
    int puntos_seguidos = 0;
    int cant_arroba = 0;
    int largo_ext;
    const char *p;
    if (!texto) return 0;
    for (p = texto; *p; p++) {
        if (*p == '@') cant_arroba++;
        if (*p == '.' && p[1] == '.') puntos_seguidos = 1;
    }
    if (cant_arroba != 1 || puntos_seguidos) return 0;
    arroba = strchr(texto, '@');
    punto = strrchr(texto, '.');
    if (!arroba || !punto || punto < arroba + 2) return 0;
    largo_ext = (int)strlen(punto + 1);
    return largo_ext >= 2 && largo_ext <= 4;
}

static int bool_on_off(const char *texto) {
    return igual_icase(texto, "ON") || igual_icase(texto, "OFF");
}

int bool_true_false(const char *texto) {
    return igual_icase(texto, "TRUE") || igual_icase(texto, "FALSE");
}

static int valor_es_email_por_atributo(const char *attr) {
    return igual_icase(attr, "email") || igual_icase(attr, "email_notif");
}

static void validar_tipo_valor(const char *tipo_disp, const char *attr_original, Valor *valor) {
    static const char *const attrs_bool[] = {"estado", "activada", "mute", NULL};
    static const char *const attrs_porcentaje[] = {"brillo", "posicion", "volumen", NULL};
    char attr[64];
    normalizar_atributo(attr, attr_original, sizeof(attr));

    if (esta_en_lista(attr, attrs_bool)) {
        if (valor->tipo != VAL_BOOL || !bool_on_off(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "se esperaba valor booleano ON/OFF");
    } else if (esta_en_lista(attr, attrs_porcentaje)) {
        if (valor->tipo != VAL_PERCENT || !porcentaje_en_rango(valor->texto, 0, 100))
            registrar_error_semantico(linea_token, valor->texto, "porcentaje fuera de rango permitido 0% a 100%");
    } else if (igual_icase(attr, "color")) {
        if (valor->tipo != VAL_COLOR)
            registrar_error_semantico(linea_token, valor->texto, "color no valido, se esperaba blanco, rojo o azul");
    } else if (igual_icase(attr, "modo")) {
        if (valor->tipo != VAL_MODO)
            registrar_error_semantico(linea_token, valor->texto, "modo no valido, se esperaba FRIO, CALOR o VENT");
    } else if (igual_icase(attr, "temp_obj")) {
        if (valor->tipo != VAL_TEMP || !temp_en_rango(valor->texto, 16, 30))
            registrar_error_semantico(linea_token, valor->texto, "temp_obj fuera de rango permitido 16C a 30C");
    } else if (igual_icase(attr, "temp_act")) {
        if (valor->tipo != VAL_TEMP || !temp_en_rango(valor->texto, -10, 50))
            registrar_error_semantico(linea_token, valor->texto, "temp_act fuera de rango permitido -10C a 50C");
    } else if (igual_icase(attr, "hora")) {
        if (valor->tipo != VAL_HORA || !hora_valida(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "hora invalida, se esperaba 00:00 a 23:59");
    } else if (igual_icase(attr, "fecha")) {
        if (valor->tipo != VAL_FECHA || !fecha_valida_general(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "fecha invalida, se esperaba DD/MM/AAAA con rangos validos");
    } else if (igual_icase(attr, "mensaje")) {
        if (valor->tipo != VAL_TEXTO)
            registrar_error_semantico(linea_token, valor->texto, "mensaje debe estar entre comillas");
    } else if (valor_es_email_por_atributo(attr)) {
        if (valor->tipo != VAL_EMAIL || !email_valido(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "email invalido");
    } else {
        (void)tipo_disp;
    }
}

void validar_y_registrar_asignacion(Operand *destino, Valor *valor) {
    const char *tipo;
    char attr[64];
    if (!destino || destino->clase != OP_DISP_ATTR) return;

    tipo = tipo_dispositivo(destino->dispositivo);
    normalizar_atributo(attr, destino->atributo, sizeof(attr));

    if (!tipo) {
        registrar_error_semantico(linea_token, destino->dispositivo, "dispositivo con prefijo invalido");
    } else {
        if (!atributo_permitido(tipo, attr)) {
            registrar_error_semantico(linea_token, destino->atributo, "atributo no permitido para ese dispositivo");
        }
        if (es_solo_lectura(tipo, attr)) {
            registrar_error_semantico(linea_token, destino->texto, "atributo de solo lectura, no puede asignarse");
        }
        validar_tipo_valor(tipo, attr, valor);
    }

    agregar_accion_html(destino->dispositivo, attr, valor->texto);
}

static void validar_sensor_con_valor(Operand *sensor, const char *op, Operand *valor) {
    (void)op;
    if (!sensor || !valor || valor->clase != OP_VALOR) return;

    if (sensor->clase == OP_SENSOR_NUM) {
        if (contiene_icase(sensor->texto, "luz")) {
            if (valor->valor_tipo != VAL_LUX || !lux_en_rango(valor->texto, 0, 1000))
                registrar_error_semantico(linea_token, valor->texto, "sensor_luz espera lux en rango 0 a 1000");
        } else if (contiene_icase(sensor->texto, "humedad")) {
            if (valor->valor_tipo != VAL_PERCENT || !porcentaje_en_rango(valor->texto, 0, 100))
                registrar_error_semantico(linea_token, valor->texto, "sensor_humedad espera porcentaje 0% a 100%");
        } else if (contiene_icase(sensor->texto, "temp")) {
            if (valor->valor_tipo != VAL_TEMP || !temp_en_rango(valor->texto, -10, 50))
                registrar_error_semantico(linea_token, valor->texto, "sensor_temp espera temperatura -10C a 50C");
        }
    } else if (sensor->clase == OP_SENSOR_BOOL) {
        if (valor->valor_tipo != VAL_BOOL || !bool_true_false(valor->texto))
            registrar_error_semantico(linea_token, valor->texto, "sensor booleano espera TRUE o FALSE");
    } else if (sensor->clase == OP_DISP_ATTR) {
        const char *tipo = tipo_dispositivo(sensor->dispositivo);
        Valor tmp;
        tmp.texto = valor->texto;
        tmp.tipo = valor->valor_tipo;
        if (tipo) validar_tipo_valor(tipo, sensor->atributo, &tmp);
    }
}

void validar_comparacion(Operand *izq, const char *op, Operand *der) {
    if (izq && der) {
        if ((izq->clase == OP_SENSOR_NUM || izq->clase == OP_SENSOR_BOOL || izq->clase == OP_DISP_ATTR) && der->clase == OP_VALOR) {
            validar_sensor_con_valor(izq, op, der);
            agregar_sensor_html(izq->texto, op, der->texto);
        } else if ((der->clase == OP_SENSOR_NUM || der->clase == OP_SENSOR_BOOL || der->clase == OP_DISP_ATTR) && izq->clase == OP_VALOR) {
            validar_sensor_con_valor(der, op, izq);
            agregar_sensor_html(der->texto, op, izq->texto);
        } else if (izq->clase == OP_SENSOR_NUM || izq->clase == OP_SENSOR_BOOL || izq->clase == OP_DISP_ATTR) {
            agregar_sensor_html(izq->texto, op, der->texto);
        }
    }
}

static void agregar_accion_html(const char *disp, const char *attr, const char *valor) {
    if (cant_acciones_html >= MAX_HTML_ACCIONES) return;
    snprintf(acciones_html[cant_acciones_html].dispositivo, sizeof(acciones_html[cant_acciones_html].dispositivo), "%s", disp ? disp : "");
    snprintf(acciones_html[cant_acciones_html].atributo, sizeof(acciones_html[cant_acciones_html].atributo), "%s", attr ? attr : "");
    snprintf(acciones_html[cant_acciones_html].valor, sizeof(acciones_html[cant_acciones_html].valor), "%s", valor ? valor : "");
    acciones_html[cant_acciones_html].es_email = attr && valor_es_email_por_atributo(attr);
    cant_acciones_html++;
}

void agregar_sensor_html(const char *nombre, const char *op, const char *valor) {
    int i;
    if (!nombre || cant_sensores_html >= MAX_HTML_SENSORES) return;
    for (i = 0; i < cant_sensores_html; i++) {
        if (igual_icase(sensores_html[i].nombre, nombre) && igual_icase(sensores_html[i].valor, valor ? valor : "")) return;
    }
    snprintf(sensores_html[cant_sensores_html].nombre, sizeof(sensores_html[cant_sensores_html].nombre), "%s", nombre);
    snprintf(sensores_html[cant_sensores_html].operador, sizeof(sensores_html[cant_sensores_html].operador), "%s", op ? op : "");
    snprintf(sensores_html[cant_sensores_html].valor, sizeof(sensores_html[cant_sensores_html].valor), "%s", valor ? valor : "");
    cant_sensores_html++;
}

static void html_escape(FILE *f, const char *s) {
    if (!s) return;
    while (*s) {
        switch (*s) {
            case '&': fputs("&amp;", f); break;
            case '<': fputs("&lt;", f); break;
            case '>': fputs("&gt;", f); break;
            case '"': fputs("&quot;", f); break;
            default: fputc(*s, f); break;
        }
        s++;
    }
}

static void html_valor(FILE *f, const char *attr, const char *valor) {
    if (attr && valor_es_email_por_atributo(attr) && email_valido(valor)) {
        const char *arroba = strchr(valor, '@');
        char usuario[128];
        size_t n = arroba ? (size_t)(arroba - valor) : strlen(valor);
        if (n >= sizeof(usuario)) n = sizeof(usuario) - 1;
        memcpy(usuario, valor, n);
        usuario[n] = '\0';
        fputs("<a href=\"mailto:", f);
        html_escape(f, valor);
        fputs("\">Contactar a ", f);
        html_escape(f, usuario);
        fputs("</a>", f);
    } else {
        html_escape(f, valor);
    }
}

void generar_html(void) {
    FILE *f = fopen(archivo_html, "w");
    int i, j;
    if (!f) {
        fprintf(stderr, "[ERROR DE EJECUCION] No se pudo crear el archivo HTML: %s\n", archivo_html);
        return;
    }

    fprintf(f, "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n<meta charset=\"UTF-8\">\n");
    fprintf(f, "<title>SMART-HOME</title>\n</head>\n<body>\n");
    fprintf(f, "<h1>Dashboard SMART-HOME</h1>\n");

    fprintf(f, "<div style=\"border:1px solid green; padding:20px; margin:10px;\">\n");
    fprintf(f, "<h1>Estado de sensores y condiciones</h1>\n");
    if (cant_sensores_html == 0) {
        fprintf(f, "<p>No se detectaron condiciones sobre sensores.</p>\n");
    }
    for (i = 0; i < cant_sensores_html; i++) {
        fprintf(f, "<h2>");
        html_escape(f, sensores_html[i].nombre);
        if (strlen(sensores_html[i].operador) > 0) {
            fprintf(f, " ");
            html_escape(f, sensores_html[i].operador);
            fprintf(f, " ");
            html_escape(f, sensores_html[i].valor);
        }
        fprintf(f, "</h2>\n");
    }
    fprintf(f, "</div>\n");

    fprintf(f, "<h1>Actuadores</h1>\n");
    for (i = 0; i < cant_acciones_html; i++) {
        int ya_impreso = 0;
        for (j = 0; j < i; j++) {
            if (igual_icase(acciones_html[i].dispositivo, acciones_html[j].dispositivo)) {
                ya_impreso = 1;
                break;
            }
        }
        if (ya_impreso) continue;

        fprintf(f, "<div style=\"border:1px solid gray; padding:20px; margin:10px;\">\n<h1>");
        html_escape(f, acciones_html[i].dispositivo);
        fprintf(f, "</h1>\n<ul>\n");
        for (j = i; j < cant_acciones_html; j++) {
            if (igual_icase(acciones_html[i].dispositivo, acciones_html[j].dispositivo)) {
                fprintf(f, "<li>");
                html_escape(f, acciones_html[j].atributo);
                fprintf(f, ": ");
                html_valor(f, acciones_html[j].atributo, acciones_html[j].valor);
                fprintf(f, "</li>\n");
            }
        }
        fprintf(f, "</ul>\n</div>\n");
    }

    fprintf(f, "</body>\n</html>\n");
    fclose(f);
}

int tiene_extension_smart(const char *ruta) {
    const char *punto = strrchr(ruta, '.');
    return punto != NULL && igual_icase(punto, ".smart");
}

void construir_nombre_html(const char *ruta) {
    const char *ultimo_sep1 = strrchr(ruta, '/');
    const char *ultimo_sep2 = strrchr(ruta, '\\');
    const char *base = ultimo_sep1 > ultimo_sep2 ? ultimo_sep1 : ultimo_sep2;
    const char *nombre = base ? base + 1 : ruta;
    const char *punto = strrchr(nombre, '.');
    size_t n = punto ? (size_t)(punto - nombre) : strlen(nombre);
    if (n > sizeof(archivo_html) - 6) n = sizeof(archivo_html) - 6;
    memcpy(archivo_html, nombre, n);
    archivo_html[n] = '\0';
    strcat(archivo_html, ".html");
}

void limpiar_ruta_ingresada(char *ruta) {
    size_t n;
    char *inicio = ruta;

    if (!ruta) return;

    while (*inicio && isspace((unsigned char)*inicio)) inicio++;
    if (inicio != ruta) memmove(ruta, inicio, strlen(inicio) + 1);

    n = strlen(ruta);
    while (n > 0 && isspace((unsigned char)ruta[n - 1])) {
        ruta[n - 1] = '\0';
        n--;
    }

    if (n >= 2 && ruta[0] == '"' && ruta[n - 1] == '"') {
        memmove(ruta, ruta + 1, n - 2);
        ruta[n - 2] = '\0';
    }
}

void esperar_enter_si_interactivo(int modo_interactivo) {
    int c;
    if (!modo_interactivo) return;

    printf("\nPresione Enter para cerrar...");
    fflush(stdout);

    while ((c = getchar()) != '\n' && c != EOF) {
        /* descartar caracteres pendientes */
    }
}
