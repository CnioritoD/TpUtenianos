#ifndef LEXER_H
#define LEXER_H

// Enumeración para los tipos de componentes léxicos (Tokens)
typedef enum {
    TOKEN_EOF,

    /* Palabras reservadas del lenguaje SMART-HOME. */
    TOKEN_WHEN,
    TOKEN_EVERY,
    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_ELSE,
    TOKEN_DO,
    TOKEN_END,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    /* Identificadores propios del lenguaje. */
    TOKEN_ID_SENSOR_NUM,
    TOKEN_ID_SENSOR_BOOL,
    TOKEN_ID_DISPOSITIVO,
    TOKEN_ATRIBUTO,
    TOKEN_ID,

    /* Literales y valores con formato propio. */
    TOKEN_BOOL,
    TOKEN_MODO,
    TOKEN_COLOR,
    TOKEN_TEXTO,
    TOKEN_EMAIL,
    TOKEN_HORA,
    TOKEN_FECHA,
    TOKEN_NUM_TEMP,
    TOKEN_PERCENT,
    TOKEN_TIME,
    TOKEN_LUX,
    TOKEN_NUMERO,

    /* Operadores y delimitadores. */
    TOKEN_IGUAL,
    TOKEN_IGUALDAD,
    TOKEN_DIFERENTE,
    TOKEN_MAYOR,
    TOKEN_MENOR,
    TOKEN_MAYOR_IGUAL,
    TOKEN_MENOR_IGUAL,
    TOKEN_PUNTO,
    TOKEN_PARENTESIS_ABRE,
    TOKEN_PARENTESIS_CIERRA,

    TOKEN_ERROR
} TipoToken;


// Estructura que representa a cada Token detectado
typedef struct {
    TipoToken tipo;   //tipo almacenado en el token
    char valor[128]; // Arreglo para almacenar el texto del token  
} Token;


//Devuelve el proximo token y avanza el puntero de lectura.
Token obtener_siguiente_token(const char **cadena);

//Convierte el TipoToken a texto para mostrarlo en pantalla.
const char *nombre_token(TipoToken tipo);

#endif
