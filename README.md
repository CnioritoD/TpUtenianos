# Lexer SMART-HOME con Flex

Lexer del lenguaje SMART-HOME escrito en formato Flex.

Archivo principal:

```txt
smart_home.l
```

## Requisitos

Tener instalado MSYS2 con los paquetes de Flex y GCC para UCRT64.

Si falta alguno, abrir la terminal UCRT64 de MSYS2 e instalar:

```bash
pacman -S mingw-w64-ucrt-x86_64-flex mingw-w64-ucrt-x86_64-gcc
```

## Compilar desde CMD

Abrir CMD y entrar a la carpeta del proyecto:

```cmd
cd C:\Users\yoque\Desktop\tp_sintaxis_ari-main
```

Generar `lex.yy.c` con Flex y compilar el ejecutable:

```cmd
C:\msys64\usr\bin\bash.exe -lc "export PATH=/ucrt64/bin:/usr/bin:$PATH; cd /c/Users/yoque/Desktop/tp_sintaxis_ari-main && flex smart_home.l && gcc -Wall -Wextra -std=c11 lex.yy.c -o smart_home.exe"
```

El comando `flex smart_home.l` genera automaticamente:

```txt
lex.yy.c
```

## Compilar si Flex y GCC ya estan en el PATH

Desde CMD, parado en la carpeta del proyecto:

```cmd
flex smart_home.l
gcc -Wall -Wextra -std=c11 lex.yy.c -o smart_home.exe
```

## Ejecutar desde CMD

Leer un archivo de entrada:

```cmd
smart_home.exe ejemplo_consigna.smart
```

Ejecutar en modo interactivo:

```cmd
smart_home.exe
```

Para probar con otros archivos:

```cmd
smart_home.exe entrada.txt
smart_home.exe entrada2.txt
```
