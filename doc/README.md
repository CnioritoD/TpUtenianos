# SMART-HOME - Utenianos - Entrega final

Esta entrega incluye lexer Flex, parser Bison, validaciones semanticas basicas y generacion de HTML.

## Estructura

- `src/smart_home_parser.l`: lexer Flex conectado con Bison.
- `src/parser.y`: parser Bison, validaciones semanticas y generacion HTML.
- `src/smart_home.l`: lexer original para mostrar reconocimiento de tokens.
- `bin/smart_home_parser.exe`: ejecutable principal de la entrega final.
- `bin/smart_home_lexer.exe`: ejecutable auxiliar para ver tokens.
- `doc/ejemplos/`: archivos `.smart` validos e invalidos para probar.
- `doc/GRAMATICA.md`: gramatica usada por el parser.

## Requisitos para recompilar

Usar MSYS2 UCRT64 con Flex, Bison y GCC:

```bash
pacman -S mingw-w64-ucrt-x86_64-flex mingw-w64-ucrt-x86_64-bison mingw-w64-ucrt-x86_64-gcc
```

## Compilar parser final

Desde la raiz del proyecto:

```bash
mkdir -p build bin
bison -d -o build/parser.tab.c src/parser.y
flex -o build/lex.parser.c src/smart_home_parser.l
gcc -Wall -Wextra -std=c11 -Ibuild build/parser.tab.c build/lex.parser.c -o bin/smart_home_parser.exe
```

## Compilar lexer auxiliar

```bash
mkdir -p build bin
flex -o build/lex.yy.c src/smart_home.l
gcc -Wall -Wextra -std=c11 build/lex.yy.c -o bin/smart_home_lexer.exe
```

## Ejecutar parser final

```bash
./bin/smart_home_parser.exe "doc/ejemplos/ejemplo_valido_catedra.smart"
```

Tambien se puede ejecutar con otros archivos:

```bash
./bin/smart_home_parser.exe "doc/ejemplos/ejemplo_errores_catedra.smart"
./bin/smart_home_parser.exe "doc/ejemplos/error_semantico_puro.smart"
./bin/smart_home_parser.exe "doc/ejemplos/pruebalexer.smart"
./bin/smart_home_parser.exe "doc/ejemplos/pruebalexerinvalidos.smart"
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

## Ejecutar lexer auxiliar

```bash
./bin/smart_home_lexer.exe "doc/ejemplos/ejemplo_valido_catedra.smart"
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

## Limitaciones conocidas

- La validacion de fechas controla rangos basicos de dia, mes y anio, pero no calcula dias por mes ni anios bisiestos.
- El HTML se genera en el directorio desde donde se ejecuta el programa.
- El parser espera archivos con extension `.smart`.
- Si hay errores lexicos o sintacticos, no se genera HTML.
