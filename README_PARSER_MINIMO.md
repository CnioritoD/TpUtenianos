# Parser mínimo SMART-HOME

Esta rama `parser-minimo-ari` agrega una propuesta inicial de parser usando Bison.

No reemplaza la rama `FormatoEsperado`.
No modifica `smart_home.l`.
No modifica `lex.yy.c`.
No modifica `smart_home.exe`.

## Archivos agregados

- `parser.y`: parser mínimo con Bison.
- `smart_home_parser.l`: lexer Flex adaptado para devolver tokens al parser.

## Cómo compilar

Desde la carpeta del proyecto:

```bash
bison -d parser.y
flex -o lex.parser.c smart_home_parser.l
gcc parser.tab.c lex.parser.c -o smart_home_parser.exe
```

## Cómo ejecutar

Con un archivo `.smart`:

```bash
smart_home_parser.exe ejemplo_consigna.smart
```

## Resultado esperado

Si el archivo es válido:

```text
Analisis sintactico exitoso: archivo correctamente codificado.
```

Si hay errores:

```text
[ERROR SINTACTICO] Linea X: ...
```

## Nota

Esta es una base mínima para empezar a integrar el parser.
Puede requerir ajustes según los tokens exactos del lexer original y los ejemplos finales de la consigna.
