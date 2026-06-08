# Documentación
 resumen
## Proyecto: Analizador Léxico (lexer)
Breve: Este proyecto contiene un lexer para un lenguaje SMART-HOME que reconoce palabras reservadas, identificadores, números con unidades, fechas, horas, textos y correos.

## Lexer.h

1 inclución de guardas
    #ifndef LEXER_H — comprueba si la macro LEXER_H NO está definida.
    #define LEXER_H — define la macro LEXER_H si no existía.

    Si el mismo archivo se incluye varias veces, la segunda inclusión verá LEXER_H ya definida y saltará todo el contenido, evitando redefiniciones de tipos/funciones y errores de compilación.

2 
    typedef enum {
    } TipoToken;

    typedef enum se utiliza para crear un tipo de dato enumerado personalizado y asignarle un alias. Esto permite definir un conjunto de constantes con nombre y declarar variables de ese tipo fácilmente, evitando escribir la palabra enum cada vez.

    obtener_siguiente_token
    nombre_token (cambiar a main)

## Main.c

    stdin: lectura estandar

## Lexer.c
crear_token 

crea y retornar una estructura `Token`.


1.  **Parámetros**:
    *   `tipo`: Un enumerador `TipoToken` que indica la categoría del token (por ejemplo, `TOKEN_WHEN`, `TOKEN_NUMERO`, `TOKEN_ID`, etc.).
    *   `inicio`: Un puntero a `const char` que marca el comienzo del lexema (la secuencia de caracteres que forma el token) en la cadena de entrada.
    *   `largo`: Un entero que especifica la longitud del lexema.

2.  **Copia el valor del token**:
    *   Verifica si `largo` es mayor que `MAX_VALOR` (un límite definido para el tamaño del valor del token). Si es así, trunca `largo` a `MAX_VALOR` para evitar desbordamientos.
    *   Asigna el `tipo` proporcionado al campo `t.tipo` de la estructura `Token`.
    *   Copia los caracteres desde `inicio` a `t.valor` usando `memcpy`. La cantidad de caracteres copiados es `largo`.
    *   Asegura que el valor del token sea una cadena terminada en nulo (`\0`) agregando un terminador nulo al final de `t.valor`.

3.  **Retorno**:
    *   Devuelve la estructura `Token` recién creada.

    En esencia, esta función toma una porción de la cadena de entrada (el lexema), le asigna un tipo y la guarda en una estructura `Token` para su posterior procesamiento por el analizador sintáctico.

4. memcpy(t.valor, inicio, largo)
    -t.valor: Es el destino. Es un arreglo de caracteres dentro de la estructura Token donde se almacenará el valor del token.
    -inicio: Es el origen. Es un puntero a la cadena de caracteres (const char *) que representa el lexema (la secuencia de caracteres leídos).
    -largo: Es el número de bytes a copiar desde inicio a t.valor.
    -Así, memcpy toma largo caracteres desde la posición de memoria apuntada por inicio y los copia en el arreglo t.valor.

4. (bis) 
       La principal diferencia entre `memcpy` y `strncpy` radica en su propósito y cómo manejan los caracteres nulos (`\0`):

    1.  **Propósito**:
        *   **`memcpy`**: Está diseñada para copiar un bloque de bytes de memoria de un lugar a otro. No interpreta los datos que copia; simplemente mueve bytes. Es adecuada para cualquier tipo de datos (enteros, estructuras, arrays, etc.), no solo cadenas.
        *   **`strncpy`**: Está diseñada específicamente para copiar cadenas de caracteres. Su comportamiento está intrínsecamente ligado a la búsqueda y manipulación del carácter nulo `\0`, que marca el final de una cadena en C.

    2.  **Manejo del Terminador Nulo (`\0`)**:
        *   **`memcpy`**: No presta atención a los caracteres nulos. Copiará exactamente el número de bytes especificado, incluso si esos bytes incluyen uno o más `\0`. Si necesitas que el destino sea una cadena de C terminada en nulo, debes agregar explícitamente el `\0` después de la llamada a `memcpy` (como se ve en `crear_token`).
        *   **`strncpy`**:
            *   Copia los caracteres del origen al destino hasta que encuentra un `\0` en el origen o hasta que copia el número máximo de bytes especificado (`num`).
            *   Si encuentra un `\0` en el origen antes de alcanzar `num` bytes, copia ese `\0` y luego **rellena el resto del buffer de destino con caracteres nulos** hasta que se hayan copiado `num` bytes en total.
            *   **Un punto crítico**: Si la cadena de origen es más larga o tiene exactamente `num` caracteres (sin un `\0` dentro de los primeros `num` caracteres), `strncpy` copiará `num` caracteres y **NO TERMINARÁ EL DESTINO CON UN `\0`**. Esto puede llevar a problemas si luego intentas tratar el destino como una cadena de C. Por esta razón, a menudo se añade explícitamente un `\0` al final del buffer de destino después de usar `strncpy`, como en `crear_token_fijo`: `t.valor[MAX_VALOR] = '\0';`.

    3.  **Comportamiento con el tamaño (`num`)**:
        *   **`memcpy`**: Siempre intenta copiar `num` bytes.
        *   **`strncpy`**: Copia *hasta* `num` bytes. Puede copiar menos si encuentra un `\0` en el origen, o puede copiar `num` bytes y no terminar la cadena si el origen es largo.

    4.  **Superposición de memoria**:
        *   Ambas funciones tienen un comportamiento **indefinido** si las áreas de memoria de origen y destino se superponen. Para copiar datos entre áreas de memoria que podrían superponerse, se debe usar `memmove`.

    **En resumen**:

    *   Usa **`memcpy`** cuando quieras copiar un bloque de datos de tamaño fijo, sin preocuparte por los caracteres nulos, o cuando los datos no sean necesariamente cadenas. Recuerda añadir un `\0` si el destino debe ser una cadena C.
    *   Usa **`strncpy`** cuando quieras copiar una cadena de caracteres y tengas un límite en el tamaño del buffer de destino. Ten mucho cuidado y siempre asegúrate de que el buffer de destino esté terminado en nulo, ya sea explícitamente o por el relleno de `strncpy` (si la cadena de origen es lo suficientemente corta).

    En lexer.c:
    *   `crear_token` usa `memcpy` porque ya sabe exactamente cuántos caracteres (`largo`) necesita copiar y añade el `\0` manualmente.
    *   `crear_token_fijo` usa `strncpy` y luego añade un `\0` al final del buffer (`t.valor[MAX_VALOR] = '\0';`) para garantizar la terminación nula, cubriendo el caso en que `strncpy` no lo haga automáticamente.     

5. nota:(mejorar el control de desbordamiento) 
    que tire un error o aviso que se trunco


