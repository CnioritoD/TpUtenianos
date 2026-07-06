# Gramatica SMART-HOME

La gramatica utilizada por el parser esta implementada en `src/parser.y`.

```bnf
programa ::= lista_instrucciones

lista_instrucciones ::= instruccion
                      | lista_instrucciones instruccion

instruccion ::= bloque_when
              | bloque_every
              | bloque_if
              | asignacion

bloque_when ::= WHEN condicion DO lista_acciones END

bloque_every ::= EVERY TIME DO lista_acciones END

bloque_if ::= IF condicion THEN lista_acciones opt_else END

opt_else ::= vacio
           | ELSE lista_acciones

lista_acciones ::= accion
                 | lista_acciones accion

accion ::= asignacion
         | bloque_if

asignacion ::= dispositivo_atributo "=" valor

dispositivo_atributo ::= dispositivo "." atributo

dispositivo ::= ID_DISPOSITIVO
              | ID

atributo ::= ATRIBUTO
           | ID

condicion ::= condicion OR termino_logico
            | termino_logico

termino_logico ::= termino_logico AND factor_logico
                 | factor_logico

factor_logico ::= NOT factor_logico
                | "(" condicion ")"
                | comparacion
                | BOOL
                | ID_SENSOR_BOOL

comparacion ::= operando operador_comparacion operando

operando ::= ID_SENSOR_NUM
           | ID_SENSOR_BOOL
           | dispositivo_atributo
           | valor

operador_comparacion ::= "=="
                       | "!="
                       | ">"
                       | "<"
                       | ">="
                       | "<="

valor ::= BOOL
        | MODO
        | COLOR
        | EMAIL
        | TEXTO
        | HORA
        | FECHA
        | NUM_TEMP
        | PERCENT
        | TIME
        | LUX
        | NUMERO
        | ID
```

## Tokens principales

- Palabras reservadas: `WHEN`, `EVERY`, `IF`, `THEN`, `ELSE`, `DO`, `END`, `AND`, `OR`, `NOT`.
- Sensores numericos: `SENSOR_TEMP`, `SENSOR_TEMP_INT`, `SENSOR_HUMEDAD`, `SENSOR_LUZ`.
- Sensores booleanos: `SENSOR_MOVIMIENTO`, `SENSOR_HUMO`.
- Dispositivos: prefijos `FOCO_`, `AIRE_`, `PERSIANA_`, `CERRADURA_`, `RELOJ_`, `ALTAVOZ_`, `ALARMA_`, y nombres `RELOJ`, `ALARMA`.
- Atributos: `ESTADO`, `BRILLO`, `COLOR`, `MODO`, `TEMP_OBJ`, `TEMP_OBJETIVO`, `TEMP_ACT`, `TEMP_ACTUAL`, `POSICION`, `HORA`, `FECHA`, `VOLUMEN`, `MUTE`, `MENSAJE`, `EMAIL`, `EMAIL_NOTIF`, `ACTIVADA`.
