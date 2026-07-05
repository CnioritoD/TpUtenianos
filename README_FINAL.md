# SMART-HOME - Utenianos - Entrega final

Esta version incluye lexer Flex, parser Bison, validaciones semanticas basicas y generacion de HTML.

## Regla de generacion de HTML

- Si hay errores lexicos o sintacticos: no se genera HTML.
- Si hay errores semanticos: se informa el error y se genera HTML parcial.
- Si no hay errores: se genera HTML correcto.

## Archivos principales

- `smart_home_parser.l`: lexer Flex conectado con Bison.
- `parser.y`: parser Bison + validaciones semanticas + generacion HTML.
- `smart_home.l`: lexer original para mostrar reconocimiento de tokens.
- `pruebas/`: archivos `.smart` validos e invalidos.

## Compilar parser final

Usar terminal MSYS2 UCRT64 desde la carpeta del proyecto:

```bash
bison -d parser.y
flex -o lex.parser.c smart_home_parser.l
gcc -Wall -Wextra -std=c11 parser.tab.c lex.parser.c -o smart_home_parser.exe
```

## Ejecutar parser final

```bash
./smart_home_parser.exe "pruebas/ejemplo_valido_catedra.smart"
```

Tambien se puede ejecutar con otros archivos:

```bash
./smart_home_parser.exe "pruebas/ejemplo_errores_catedra.smart"
./smart_home_parser.exe "pruebas/pruebalexer.smart"
./smart_home_parser.exe "pruebas/pruebalexerinvalidos.smart"
```

## Salida esperada

Caso valido:

```text
Analisis lexico y sintactico exitoso.
Analisis semantico exitoso.
HTML generado correctamente: ejemplo_valido_catedra.html
```

Caso con errores semanticos:

```text
[ERROR SEMANTICO] Linea X: ...
HTML generado parcialmente: ejemplo_errores_catedra.html
```

Caso con errores lexicos o sintacticos:

```text
[ERROR LEXICO] Linea X: ...
[ERROR SINTACTICO] Linea X: ...
Analisis finalizado con errores lexicos o sintacticos. No se genera HTML.
```

## Compilar lexer original para mostrar tokens

```bash
flex smart_home.l
gcc -Wall -Wextra -std=c11 lex.yy.c -o smart_home.exe
./smart_home.exe "pruebas/ejemplo_valido_catedra.smart"
```

## Validaciones semanticas implementadas

- `brillo`, `posicion`, `volumen`: 0% a 100%.
- `sensor_luz`: 0 a 1000 lux.
- `sensor_humedad`: 0% a 100%.
- `sensor_temp` / `sensor_temp_int`: -10C a 50C.
- `temp_obj`: 16C a 30C.
- `hora`: 00:00 a 23:59.
- `fecha`: formato DD/MM/AAAA con rangos basicos.
- `email`: estructura usuario@dominio.extension y sin puntos consecutivos.
- atributos de solo lectura: `aire_*.temp_act`, `reloj_*.hora`, `reloj_*.fecha`.
- atributos permitidos segun tipo de dispositivo.
- valores esperados por atributo: ON/OFF, TRUE/FALSE, colores, modos, texto, email, etc.

## Traduccion HTML

- Crea un archivo con el mismo nombre base del `.smart` y extension `.html`.
- Genera seccion de sensores/condiciones con borde verde.
- Genera actuadores en `div` con borde gris.
- Nombre de actuador en `h1`.
- Atributos y valores como `ul/li`.
- Emails como `<a href="mailto:...">Contactar a usuario</a>`.
