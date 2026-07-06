# SMART-HOME simple con Flex y Bison

Lexer y parser simple del lenguaje SMART-HOME.

El parser esta pensado para reconocer la estructura usada en los ejemplos completos de la carpeta `ejemplosValidosSmart`, sin validaciones semanticas complejas.

Archivos principales:

```txt
smart_home.l
smart_home.y
```

## Requisitos

Tener instalado MSYS2 con los paquetes de Flex, Bison y GCC para UCRT64.

Si falta alguno, abrir la terminal UCRT64 de MSYS2 e instalar:

```bash
pacman -S mingw-w64-ucrt-x86_64-flex mingw-w64-ucrt-x86_64-bison mingw-w64-ucrt-x86_64-gcc
```

## Compilar parser desde CMD

Abrir CMD y entrar a la carpeta del proyecto:

```cmd
cd C:\Users\yoque\Desktop\tp_sintaxis_ari-main
```

Generar el parser con Bison, el lexer con Flex y compilar el ejecutable:

```cmd
C:\msys64\usr\bin\bash.exe -lc "export PATH=/ucrt64/bin:/usr/bin:$PATH; cd /c/Users/yoque/Desktop/tp_sintaxis_ari-main && bison -d smart_home.y && flex smart_home.l && gcc -Wall -Wextra -std=c11 smart_home.tab.c lex.yy.c -o smart_home_parser.exe"
```

Los comandos generan automaticamente:

```txt
smart_home.tab.c
smart_home.tab.h
lex.yy.c
```

## Compilar si Flex, Bison y GCC ya estan en el PATH

Desde CMD, parado en la carpeta del proyecto:

```cmd
bison -d smart_home.y
flex smart_home.l
gcc -Wall -Wextra -std=c11 smart_home.tab.c lex.yy.c -o smart_home_parser.exe
```

## Ejecutar desde CMD

Leer un archivo de entrada:

```cmd
smart_home_parser.exe ejemplosValidosSmart\ejemplo_consigna.smart
```

Ejecutar en modo interactivo:

```cmd
smart_home_parser.exe
```

Para probar con otros archivos:

```cmd
smart_home_parser.exe ejemplosValidosSmart\ejemplo_consigna.smart
smart_home_parser.exe "ejemplosValidosSmart\Ejemplo válido.smart"
```

Nota: `pruebalexer.smart` y `pruebalexerinvalidos.smart` son pruebas del lexer, no programas completos para el parser.

## Compilar solo el lexer

El lexer todavia se puede ejecutar solo para listar tokens. Primero debe existir `smart_home.tab.h`, por eso se ejecuta Bison antes:

```cmd
C:\msys64\usr\bin\bash.exe -lc "export PATH=/ucrt64/bin:/usr/bin:$PATH; cd /c/Users/yoque/Desktop/tp_sintaxis_ari-main && bison -d smart_home.y && flex smart_home.l && gcc -DLEXER_STANDALONE -Wall -Wextra -std=c11 lex.yy.c -o smart_home_lexer.exe"
```
