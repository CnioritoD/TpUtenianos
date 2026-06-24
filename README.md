# tp_sintaxis

Lexer para el lenguaje SMART-HOME.

## Compilacion

```bash
gcc -Wall -Wextra -std=c11 main.c lexer.c -o programa.exe
```

## Ejecucion interactiva

```bash
./programa.exe
```

El programa queda abierto para ingresar varias lineas. Para finalizar:

```txt
salir
```

## Ejecucion con archivo

```bash
./programa.exe entrada.txt
```

Ejemplo de `entrada.txt`:

```txt
IF sensor_humo == ON THEN alarma.activada = TRUE
WHEN sensor_temp > 20C THEN foco_living.estado = ON
```

## Abrir y ejecutar desde CMD

Abrir CMD y entrar a la carpeta del proyecto:

```cmd
cd "ruta de la carpeta del .exe"
```

Ejecutar en modo interactivo:

```cmd
programa.exe
```

Ejecutar leyendo el archivo de entrada:

```cmd
programa.exe entrada.txt
```
