# Lexer SMART-HOME

Analizador lexico escrito en C para reconocer los componentes basicos del lenguaje SMART-HOME.

## Archivos

- `main.c`: punto de entrada del programa. Lee una linea por consola o un archivo recibido por argumento y muestra los tokens encontrados.
- `lexer.h`: define los tipos de token, la estructura `Token` y las funciones publicas del analizador lexico.
- `lexer.c`: contiene las reglas de reconocimiento de palabras reservadas, identificadores, literales, operadores, unidades y comentarios.
- `programa.exe`: ejecutable compilado para probar el scanner en Windows.

## Uso

Modo interactivo:

```powershell
.\programa.exe
```

Con archivo:

```powershell
.\programa.exe prueba.smart
```
