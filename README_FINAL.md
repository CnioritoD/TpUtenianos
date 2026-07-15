# SMART-HOME - Utenianos - Entrega final

Esta version incluye lexer Flex, parser Bison, validaciones semanticas y generacion de HTML para scripts validos.
El codigo fuente esta separado en modulos para que la gramatica, el flujo principal, las validaciones y la salida HTML sean faciles de revisar.

## Regla de generacion de HTML

- Si hay errores lexicos: se informa el error y no se genera HTML.
- Si hay errores sintacticos: se informa el error y no se genera HTML.
- Si hay errores semanticos: se informa el error y no se genera HTML.
- Si no hay errores: se genera el archivo HTML correspondiente.

## Estructura de carpetas

- `doc/`: contiene el informe final con documentacion, gramatica, modo de ejecucion, limitaciones, consideraciones y ejemplos.
- `bin/`: contiene el ejecutable final listo para usar.
- `src/`: contiene los archivos fuente editables. Los archivos generados por Flex/Bison se crean al compilar.
- `prueba/`: contiene archivos `.smart` validos e invalidos para verificar el funcionamiento.

## Archivos principales

- `src/lexer_smart_home.l`: lexer Flex conectado con Bison.
- `src/parser.y`: parser Bison con la gramatica y acciones semanticas.
- `src/main.c`: entrada del programa, apertura del archivo y flujo de salida.
- `src/semantica_html.c`: validaciones semanticas, utilidades y generacion HTML.
- `src/semantica_html.h`: tipos compartidos e interfaz usada por el parser y el programa principal.
- `bin/smart_home_parser.exe`: ejecutable final.
- `prueba/`: archivos `.smart` de prueba.

## Instalar herramientas

Para compilar desde Windows se recomienda usar MSYS2 UCRT64.
Abrir la terminal **MSYS2 UCRT64** e instalar las herramientas necesarias:

```bash
pacman -S --needed bison flex mingw-w64-ucrt-x86_64-gcc
```

Verificar que quedaron disponibles:

```bash
bison --version
flex --version
gcc --version
```

Si se compila desde PowerShell o CMD, agregar estas carpetas al `PATH`:

```text
C:\msys64\usr\bin
C:\msys64\ucrt64\bin
```

## Compilar parser final

Usar MSYS2 UCRT64 desde la carpeta principal del proyecto:

```bash
cd src
bison -d -o parser_smart_home.c parser.y
flex -o lexer_smart_home.c lexer_smart_home.l
gcc -Wall -Wextra -std=c11 main.c parser_smart_home.c lexer_smart_home.c semantica_html.c -o ../bin/smart_home_parser.exe
cd ..
```

Los archivos generados por Flex/Bison (`parser_smart_home.c`, `parser_smart_home.h`, `lexer_smart_home.c`) no se versionan como fuente principal porque se pueden regenerar desde `parser.y` y `lexer_smart_home.l`.
Si se desea dejar `src/` limpio despues de compilar, se pueden borrar esos tres archivos generados.

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

## Probar todos los ejemplos

Desde la carpeta principal del proyecto:

```bash
./bin/smart_home_parser.exe "prueba/ejemplo_consigna.smart"
./bin/smart_home_parser.exe "prueba/ejemplo_valido_catedra.smart"
./bin/smart_home_parser.exe "prueba/error_semantico_puro.smart"
./bin/smart_home_parser.exe "prueba/ejemplo_errores_catedra.smart"
./bin/smart_home_parser.exe "prueba/pruebalexer.smart"
./bin/smart_home_parser.exe "prueba/pruebalexerinvalidos.smart"
```

Los dos primeros casos deben finalizar con codigo `0`. El archivo `error_semantico_puro.smart` debe finalizar con codigo `2`. Los archivos con errores lexicos o sintacticos deben finalizar con codigo `1`.

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
- `fecha`: formato DD/MM/AAAA con dia real del mes y anios bisiestos.
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
