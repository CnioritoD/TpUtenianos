#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"

#define MAX_VALOR 127// Limite de caracteres para el valor del token, dejando espacio para el null terminator


/* Crea un token copiando el texto leido desde la entrada. */
static Token crear_token(TipoToken tipo, const char *inicio, int largo) {
    Token t;//nuevo token

    //largo es tamaño
    if (largo > MAX_VALOR) {
        largo = MAX_VALOR;
    }

    t.tipo = tipo;//machea el tipo del token
    memcpy(t.valor, inicio, largo);//copia el texto del token al campo valor (destino, origen, tamaño)
    t.valor[largo] = '\0';

    return t;
}

/* Crea tokens fijos, como =, ==, WHEN o EOF. */
static Token crear_token_fijo(TipoToken tipo, const char *texto) {
    Token t;

    t.tipo = tipo;
    strncpy(t.valor, texto, MAX_VALOR);
    t.valor[MAX_VALOR] = '\0';

    return t;
}

static int es_fin_linea(char c) {
    return c == '\0' || c == '\n' || c == '\r';
}

static int empieza_con(const char *texto, const char *prefijo) {
    return strncmp(texto, prefijo, strlen(prefijo)) == 0;
}

/* Pasamos a mayusculas para que WHEN, when y When sean lo mismo. */
static void pasar_a_mayusculas(char *destino, const char *origen) {
    int i = 0;

    while (origen[i] != '\0' && i < MAX_VALOR) {
        destino[i] = (char)toupper((unsigned char)origen[i]);
        i++;
    }

    destino[i] = '\0';
}

static int es_sensor_numerico(const char *p) {
    return strcmp(p, "SENSOR_TEMP") == 0 ||
           strcmp(p, "SENSOR_TEMP_INT") == 0 ||
           strcmp(p, "SENSOR_HUMEDAD") == 0 ||
           strcmp(p, "SENSOR_LUZ") == 0;
}

static int es_sensor_booleano(const char *p) {
    return strcmp(p, "SENSOR_MOVIMIENTO") == 0 ||
           strcmp(p, "SENSOR_HUMO") == 0;
}

static int es_dispositivo(const char *p) {
    return empieza_con(p, "FOCO_") ||
           empieza_con(p, "AIRE_") ||
           empieza_con(p, "PERSIANA_") ||
           empieza_con(p, "CERRADURA_") ||
           empieza_con(p, "RELOJ_") ||
           strcmp(p, "RELOJ") == 0 ||
           empieza_con(p, "ALTAVOZ_") ||
           empieza_con(p, "ALARMA_") ||
           strcmp(p, "ALARMA") == 0;
}

static int es_atributo(const char *p) {
    return strcmp(p, "ESTADO") == 0 ||
           strcmp(p, "BRILLO") == 0 ||
           strcmp(p, "COLOR") == 0 ||
           strcmp(p, "MODO") == 0 ||
           strcmp(p, "TEMP_OBJ") == 0 ||
           strcmp(p, "TEMP_OBJETIVO") == 0 ||
           strcmp(p, "TEMP_ACT") == 0 ||
           strcmp(p, "TEMP_ACTUAL") == 0 ||
           strcmp(p, "POSICION") == 0 ||
           strcmp(p, "HORA") == 0 ||
           strcmp(p, "FECHA") == 0 ||
           strcmp(p, "VOLUMEN") == 0 ||
           strcmp(p, "MUTE") == 0 ||
           strcmp(p, "MENSAJE") == 0 ||
           strcmp(p, "EMAIL") == 0 ||
           strcmp(p, "EMAIL_NOTIF") == 0 ||
           strcmp(p, "ACTIVADA") == 0;
}

static int es_booleano(const char *p) {
    return strcmp(p, "TRUE") == 0 ||
           strcmp(p, "FALSE") == 0 ||
           strcmp(p, "ON") == 0 ||
           strcmp(p, "OFF") == 0;
}

static int es_modo(const char *p) {
    return strcmp(p, "FRIO") == 0 ||
           strcmp(p, "CALOR") == 0 ||
           strcmp(p, "VENT") == 0;
}

static int es_color(const char *p) {
    return strcmp(p, "BLANCO") == 0 ||
           strcmp(p, "ROJO") == 0 ||
           strcmp(p, "AZUL") == 0 ||
           strcmp(p, "WHITE") == 0 ||
           strcmp(p, "RED") == 0 ||
           strcmp(p, "BLUE") == 0;
}

/* Validacion simple: usuario@dominio.ext, con extension de 2 a 4 letras. */
static int es_email(const char *texto) {
    const char *arroba = strchr(texto, '@');
    const char *punto = strrchr(texto, '.');
    int largo_extension;

    if (arroba == NULL || punto == NULL) return 0;
    if (arroba == texto) return 0;
    if (punto < arroba + 2) return 0;

    largo_extension = (int)strlen(punto + 1);
    return largo_extension >= 2 && largo_extension <= 4;
}

static int es_delimitador_email(char c) {
    return isspace((unsigned char)c) ||
           c == '\0' || c == '\n' || c == '\r' ||
           c == '=' || c == '<' || c == '>' || c == '!' ||
           c == '(' || c == ')' || c == '"';
}

/* Una palabra puede ser reservada, literal, sensor, dispositivo, atributo o ID comun. */
static TipoToken clasificar_palabra(const char *palabra) {
    char p[MAX_VALOR + 1];

    pasar_a_mayusculas(p, palabra);

    if (strcmp(p, "WHEN") == 0) return TOKEN_WHEN;
    if (strcmp(p, "EVERY") == 0) return TOKEN_EVERY;
    if (strcmp(p, "IF") == 0) return TOKEN_IF;
    if (strcmp(p, "THEN") == 0) return TOKEN_THEN;
    if (strcmp(p, "ELSE") == 0) return TOKEN_ELSE;
    if (strcmp(p, "DO") == 0) return TOKEN_DO;
    if (strcmp(p, "END") == 0) return TOKEN_END;
    if (strcmp(p, "AND") == 0) return TOKEN_AND;
    if (strcmp(p, "OR") == 0) return TOKEN_OR;
    if (strcmp(p, "NOT") == 0) return TOKEN_NOT;

    if (es_booleano(p)) return TOKEN_BOOL;
    if (es_modo(p)) return TOKEN_MODO;
    if (es_color(p)) return TOKEN_COLOR;
    if (es_sensor_numerico(p)) return TOKEN_ID_SENSOR_NUM;
    if (es_sensor_booleano(p)) return TOKEN_ID_SENSOR_BOOL;
    if (es_dispositivo(p)) return TOKEN_ID_DISPOSITIVO;
    if (es_atributo(p)) return TOKEN_ATRIBUTO;

    return TOKEN_ID;
}

static int es_comilla_curva_inicio(const char *p) {
    return (unsigned char)p[0] == 0xE2 &&
           (unsigned char)p[1] == 0x80 &&
           ((unsigned char)p[2] == 0x9C || (unsigned char)p[2] == 0x9D);
}

static int es_comilla_curva_cierre(const char *p) {
    return (unsigned char)p[0] == 0xE2 &&
           (unsigned char)p[1] == 0x80 &&
           (unsigned char)p[2] == 0x9D;
}

Token obtener_siguiente_token(const char **cadena) {
    const char *inicio;

    /* Ignora espacios antes de buscar el siguiente token. */
    while (isspace((unsigned char)**cadena)) {
        (*cadena)++;
    }

    if (es_fin_linea(**cadena)) {
        return crear_token_fijo(TOKEN_EOF, "EOF");
    }

    /* Los comentarios comienzan con // y se descartan hasta el fin de linea. */
    if ((*cadena)[0] == '/' && (*cadena)[1] == '/') {
        while (!es_fin_linea(**cadena)) {
            (*cadena)++;
        }
        return crear_token_fijo(TOKEN_EOF, "EOF");
    }

    inicio = *cadena;

    /* Reconoce textos escritos entre comillas dobles. */
    if (**cadena == '"') {
        (*cadena)++;
        while (!es_fin_linea(**cadena) && **cadena != '"') {
            (*cadena)++;
        }

        if (**cadena == '"') {
            (*cadena)++;
            return crear_token(TOKEN_TEXTO, inicio, (int)(*cadena - inicio));
        }

        return crear_token(TOKEN_ERROR, inicio, (int)(*cadena - inicio));
    }

    /* Acepta comillas curvas si se copia texto desde el PDF. */
    if (es_comilla_curva_inicio(*cadena)) {
        *cadena += 3;
        while (!es_fin_linea(**cadena) && !es_comilla_curva_cierre(*cadena)) {
            (*cadena)++;
        }

        if (es_comilla_curva_cierre(*cadena)) {
            *cadena += 3;
            return crear_token(TOKEN_TEXTO, inicio, (int)(*cadena - inicio));
        }

        return crear_token(TOKEN_ERROR, inicio, (int)(*cadena - inicio));
    }

    /* Los operadores compuestos se leen antes que los operadores simples. */
    if ((*cadena)[0] == '=' && (*cadena)[1] == '=') {
        *cadena += 2;
        return crear_token_fijo(TOKEN_IGUALDAD, "==");
    }
    if ((*cadena)[0] == '!' && (*cadena)[1] == '=') {
        *cadena += 2;
        return crear_token_fijo(TOKEN_DIFERENTE, "!=");
    }
    if ((*cadena)[0] == '>' && (*cadena)[1] == '=') {
        *cadena += 2;
        return crear_token_fijo(TOKEN_MAYOR_IGUAL, ">=");
    }
    if ((*cadena)[0] == '<' && (*cadena)[1] == '=') {
        *cadena += 2;
        return crear_token_fijo(TOKEN_MENOR_IGUAL, "<=");
    }

    /* Operadores y simbolos de un solo caracter. */
    if (**cadena == '=') { (*cadena)++; return crear_token_fijo(TOKEN_IGUAL, "="); }
    if (**cadena == '>') { (*cadena)++; return crear_token_fijo(TOKEN_MAYOR, ">"); }
    if (**cadena == '<') { (*cadena)++; return crear_token_fijo(TOKEN_MENOR, "<"); }
    if (**cadena == '.') { (*cadena)++; return crear_token_fijo(TOKEN_PUNTO, "."); }
    if (**cadena == '(') { (*cadena)++; return crear_token_fijo(TOKEN_PARENTESIS_ABRE, "("); }
    if (**cadena == ')') { (*cadena)++; return crear_token_fijo(TOKEN_PARENTESIS_CIERRA, ")"); }

    /* Reconoce horas con formato HH:MM. */
    if (isdigit((unsigned char)(*cadena)[0]) &&
        isdigit((unsigned char)(*cadena)[1]) &&
        (*cadena)[2] == ':' &&
        isdigit((unsigned char)(*cadena)[3]) &&
        isdigit((unsigned char)(*cadena)[4])) {
        *cadena += 5;
        return crear_token(TOKEN_HORA, inicio, 5);
    }

    /* Reconoce fechas con formato DD/MM/AAAA. */
    if (isdigit((unsigned char)(*cadena)[0]) &&
        isdigit((unsigned char)(*cadena)[1]) &&
        (*cadena)[2] == '/' &&
        isdigit((unsigned char)(*cadena)[3]) &&
        isdigit((unsigned char)(*cadena)[4]) &&
        (*cadena)[5] == '/' &&
        isdigit((unsigned char)(*cadena)[6]) &&
        isdigit((unsigned char)(*cadena)[7]) &&
        isdigit((unsigned char)(*cadena)[8]) &&
        isdigit((unsigned char)(*cadena)[9])) {
        *cadena += 10;
        return crear_token(TOKEN_FECHA, inicio, 10);
    }

    /* Reconoce numeros solos o acompanados por unidades del lenguaje. */
    if (isdigit((unsigned char)**cadena) ||
        (**cadena == '-' && isdigit((unsigned char)(*cadena)[1]))) {

        if (**cadena == '-') {
            (*cadena)++;
        }

        while (isdigit((unsigned char)**cadena)) {
            (*cadena)++;
        }

        if (**cadena == '.' && isdigit((unsigned char)(*cadena)[1])) {
            (*cadena)++;
            while (isdigit((unsigned char)**cadena)) {
                (*cadena)++;
            }
        }

        if (**cadena == '%') {
            (*cadena)++;
            return crear_token(TOKEN_PERCENT, inicio, (int)(*cadena - inicio));
        }

        if (tolower((unsigned char)(*cadena)[0]) == 'l' &&
            tolower((unsigned char)(*cadena)[1]) == 'u' &&
            tolower((unsigned char)(*cadena)[2]) == 'x') {
            *cadena += 3;
            return crear_token(TOKEN_LUX, inicio, (int)(*cadena - inicio));
        }

        if ((*cadena)[0] == (char)0xC2 &&
            (*cadena)[1] == (char)0xB0 &&
            tolower((unsigned char)(*cadena)[2]) == 'c') {
            *cadena += 3;
            return crear_token(TOKEN_NUM_TEMP, inicio, (int)(*cadena - inicio));
        }

        /* En algunas terminales el simbolo de grado llega como ?. */
        if (**cadena == '?' && tolower((unsigned char)(*cadena)[1]) == 'c') {
            *cadena += 2;
            return crear_token(TOKEN_NUM_TEMP, inicio, (int)(*cadena - inicio));
        }

        if (tolower((unsigned char)**cadena) == 'c') {
            (*cadena)++;
            return crear_token(TOKEN_NUM_TEMP, inicio, (int)(*cadena - inicio));
        }

        if (tolower((unsigned char)**cadena) == 's' ||
            tolower((unsigned char)**cadena) == 'm' ||
            tolower((unsigned char)**cadena) == 'h') {
            (*cadena)++;
            return crear_token(TOKEN_TIME, inicio, (int)(*cadena - inicio));
        }

        return crear_token(TOKEN_NUMERO, inicio, (int)(*cadena - inicio));
    }

    /* Reconoce palabras, identificadores y correos electronicos. */
    if (isalpha((unsigned char)**cadena) || **cadena == '_') {
        const char *aux = *cadena;
        int tiene_arroba = 0;

        while (!es_delimitador_email(*aux)) {
            if (*aux == '@') {
                tiene_arroba = 1;
            }
            aux++;
        }

        if (tiene_arroba) {
            *cadena = aux;
            Token email = crear_token(TOKEN_EMAIL, inicio, (int)(*cadena - inicio));

            if (!es_email(email.valor)) {
                email.tipo = TOKEN_ERROR;
            }

            return email;
        }

        while (isalnum((unsigned char)**cadena) || **cadena == '_' || **cadena == '-') {
            (*cadena)++;
        }

        Token palabra = crear_token(TOKEN_ID, inicio, (int)(*cadena - inicio));
        palabra.tipo = clasificar_palabra(palabra.valor);
        return palabra;
    }

    /* Si el caracter no coincide con ninguna regla, se informa error lexico. */
    (*cadena)++;
    return crear_token(TOKEN_ERROR, inicio, 1);
}

const char *nombre_token(TipoToken tipo) {
    switch (tipo) {
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_WHEN: return "TOKEN_WHEN";
        case TOKEN_EVERY: return "TOKEN_EVERY";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_THEN: return "TOKEN_THEN";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_DO: return "TOKEN_DO";
        case TOKEN_END: return "TOKEN_END";
        case TOKEN_AND: return "TOKEN_AND";
        case TOKEN_OR: return "TOKEN_OR";
        case TOKEN_NOT: return "TOKEN_NOT";
        case TOKEN_ID_SENSOR_NUM: return "TOKEN_ID_SENSOR_NUM";
        case TOKEN_ID_SENSOR_BOOL: return "TOKEN_ID_SENSOR_BOOL";
        case TOKEN_ID_DISPOSITIVO: return "TOKEN_ID_DISPOSITIVO";
        case TOKEN_ATRIBUTO: return "TOKEN_ATRIBUTO";
        case TOKEN_ID: return "TOKEN_ID";
        case TOKEN_BOOL: return "TOKEN_BOOL";
        case TOKEN_MODO: return "TOKEN_MODO";
        case TOKEN_COLOR: return "TOKEN_COLOR";
        case TOKEN_TEXTO: return "TOKEN_TEXTO";
        case TOKEN_EMAIL: return "TOKEN_EMAIL";
        case TOKEN_HORA: return "TOKEN_HORA";
        case TOKEN_FECHA: return "TOKEN_FECHA";
        case TOKEN_NUM_TEMP: return "TOKEN_NUM_TEMP";
        case TOKEN_PERCENT: return "TOKEN_PERCENT";
        case TOKEN_TIME: return "TOKEN_TIME";
        case TOKEN_LUX: return "TOKEN_LUX";
        case TOKEN_NUMERO: return "TOKEN_NUMERO";
        case TOKEN_IGUAL: return "TOKEN_IGUAL";
        case TOKEN_IGUALDAD: return "TOKEN_IGUALDAD";
        case TOKEN_DIFERENTE: return "TOKEN_DIFERENTE";
        case TOKEN_MAYOR: return "TOKEN_MAYOR";
        case TOKEN_MENOR: return "TOKEN_MENOR";
        case TOKEN_MAYOR_IGUAL: return "TOKEN_MAYOR_IGUAL";
        case TOKEN_MENOR_IGUAL: return "TOKEN_MENOR_IGUAL";
        case TOKEN_PUNTO: return "TOKEN_PUNTO";
        case TOKEN_PARENTESIS_ABRE: return "TOKEN_PARENTESIS_ABRE";
        case TOKEN_PARENTESIS_CIERRA: return "TOKEN_PARENTESIS_CIERRA";
        case TOKEN_ERROR: return "TOKEN_ERROR";
        default: return "TOKEN_DESCONOCIDO";
    }
}
