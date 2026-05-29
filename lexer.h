#ifndef LEXER_H
#define LEXER_H

// Enumeración para los tipos de componentes léxicos (Tokens) de TU gramática
typedef enum {
    TOKEN_EOF,
    TOKEN_WHEN, 
    TOKEN_EVERY, 
    TOKEN_DO, 
    TOKEN_END, 
    TOKEN_IF, 
    TOKEN_THEN, 
    TOKEN_ELSE,
    TOKEN_ID,          // Para nombres como "sensor", "temp", "aire"
    TOKEN_NUMERO,      // Para valores numéricos como 25
    TOKEN_PUNTO,       // Para el símbolo .
    TOKEN_IGUAL,       // Para el símbolo =
    TOKEN_ERROR
} TipoToken;

// Estructura que representa a cada Token detectado
typedef struct {
    TipoToken tipo;
    char valor[32]; // Arreglo para almacenar el texto del token
} Token;

// Declaración de la función del lexer respetando la original
Token obtener_siguiente_token(const char **cadena);

#endif // LEXER_H