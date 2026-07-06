# SMART-HOME - Entrega final

Trabajo practico de lexer y parser para el lenguaje SMART-HOME.

## Estructura de entrega

- `src/`: archivos fuente del lexer y parser (`.l` y `.y`).
- `bin/`: ejecutables generados listos para usar.
- `doc/`: documentacion, gramatica, ejemplos y forma de ejecucion.

## Ejecucion rapida

Desde la raiz del proyecto:

```cmd
bin\smart_home_parser.exe doc\ejemplos\ejemplo_valido_catedra.smart
```

El parser valida el archivo `.smart` y, si corresponde, genera un HTML con el mismo nombre base del archivo de entrada.

La documentacion completa esta en `doc/README.md`.
