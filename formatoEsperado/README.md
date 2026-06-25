# Formato esperado con Flex

Esta carpeta contiene el lexer del lenguaje SMART-HOME en formato `.l`.

## Generar el C desde Flex

Desde la terminal UCRT64 de MSYS2, parado en esta carpeta:

```bash
flex smart_home.l
gcc -Wall -Wextra -std=c11 lex.yy.c -o smart_home.exe
```

Tambien se puede ejecutar desde la carpeta principal:

```bash
cd formatoEsperado
flex smart_home.l
gcc -Wall -Wextra -std=c11 lex.yy.c -o smart_home.exe
```

## Ejecutar

Con archivo:

```bash
./smart_home.exe ../entrada.txt
```

O ingresando texto por teclado:

```bash
./smart_home.exe
```

## Nota

Este `.l` no reemplaza tu lexer manual. Es una version alternativa para entregar en el formato usado por Flex.
