# Lexer SMART-HOME en formato Flex

Esta rama contiene directamente los archivos del lexer del lenguaje SMART-HOME en formato Flex.

El archivo principal es:

```txt
smart_home.l
```

## Generar el C desde Flex

Desde la terminal UCRT64 de MSYS2, parado en la raiz de esta rama:

```bash
flex smart_home.l
gcc -Wall -Wextra -std=c11 lex.yy.c -o smart_home.exe
```

El comando `flex smart_home.l` genera automaticamente:

```txt
lex.yy.c
```

## Ejecutar

Con archivo:

```bash
./smart_home.exe ejemplo_consigna.smart
```

O ingresando texto por teclado:

```bash
./smart_home.exe
```

## Nota

Esta rama deja solo los archivos del formato esperado para la entrega con Flex. El lexer manual en C queda fuera de esta rama para que la entrega muestre claramente el archivo `.l`.
