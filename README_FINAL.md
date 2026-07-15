# SMART-HOME - Utenianos - Entrega final

Esta version incluye lexer Flex, parser Bison, validaciones semanticas basicas y generacion de HTML para scripts validos.

## Regla de generacion de HTML

- Si hay errores lexicos: se informa el error y no se genera HTML.
- Si hay errores sintacticos: se informa el error y no se genera HTML.
- Si hay errores semanticos: se informa el error y no se genera HTML.
- Si no hay errores: se genera el archivo HTML correspondiente.

## Estructura de carpetas

- `doc/`: contiene el informe final con documentacion, gramatica, modo de ejecucion, limitaciones, consideraciones y ejemplos.
- `bin/`: contiene el ejecutable final listo para usar.
- `src/`: contiene las entradas fuente usadas por los generadores Flex/Bison.
- `prueba/`: contiene archivos `.smart` validos e invalidos para verificar el funcionamiento.

## Archivos principales

- `src/smart_home_parser.l`: lexer Flex conectado con Bison.
- `src/parser.y`: parser Bison, validaciones semanticas y generacion HTML.
- `bin/smart_home_parser.exe`: ejecutable final.
- `prueba/`: archivos `.smart` de prueba.

## Compilar parser final

Usar MSYS2 UCRT64 desde la carpeta principal del proyecto:

```bash
cd src
bison -d parser.y
flex -o lex.parser.c smart_home_parser.l
gcc -Wall -Wextra -std=c11 parser.tab.c lex.parser.c -o ../bin/smart_home_parser.exe
cd ..
```

Los archivos generados por Flex/Bison (`parser.tab.c`, `parser.tab.h`, `lex.parser.c`) no se incluyen como fuente principal de entrega porque se entregan las entradas al generador: `parser.y` y `smart_home_parser.l`.

## Ejecutar parser final

Desde la carpeta principal del proyecto:

```bash
./bin/smart_home_parser.exe "prueba/ejemplo_valido_catedra.smart"
```

Tambien se puede ejecutar con otros archivos:

```bash
./bin/smart_home_parser.exe "prueba/ejemplo_consigna.smart"
./bin/smart_home_parser.exe "prueba/ejemplo_errores_catedra.smart"
./bin/smart_home_parser.exe "prueba/error_semantico_puro.smart"
./bin/smart_home_parser.exe "prueba/pruebalexer.smart"
./bin/smart_home_parser.exe "prueba/pruebalexerinvalidos.smart"
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
Analisis lexico y sintactico exitoso.
Analisis semantico finalizado con N error(es).
No se genera HTML porque el archivo contiene errores semanticos.
```

Caso con errores lexicos o sintacticos:

```text
[ERROR LEXICO] Linea X: ...
[ERROR SINTACTICO] Linea X: ...
Analisis finalizado con errores lexicos o sintacticos. No se genera HTML.
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
