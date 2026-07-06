/*calculadora.1.Y: PARSER para operaciones aritmeticas basicas
   rodrigovigil @ gmail . com
   Compiladores y Autómatas. Gastón Dachary
	uso: 	yacc -d calculadora.1.y
		cc -o calculadora lex.yy.c y.tab.c -ly -ll -lm
*/
%{
#include <math.h>  /* */
#include <stdio.h>
%}

%union{				/* se definen miembros cuyos correspondientes tipos de datos serán usados para dar el tipo de dato a los tokens*/
        double dval;
}
						/*Definicion de tokens y opcional tipo de dato . Etiquetas, serán traducidos en numeros. */
%token  <dval> NUMERO 				/* NUMERO sera del tipo de miembro de dval, es decir, un double */
%token  MAS	MENOS	POR	DIVIDE	POTENCIA	POWER
%token  ABRE_PARENTESIS        CIERRA_PARENTESIS
%token  END

						/* tipo de agrupacion y precedencia de  tokens operadores. */
 						/*La precedencia es asignada en orden inverso al que aparecen, mas presedencia ultimo operador declarado*/
%left   POR	DIVIDE		MAS		MENOS				/*Asociatividad indican si el operador se agrupa a la derecha o a la izquierda*/
/*%left   POR	DIVIDE*/
%left   NEG
	/*%right  POWER*/
%right  POTENCIA	POWER

%type <dval> Expression
%start Input

%%

Input:	Line					/*El reemplazo del no terminal se representa con : */
	| Input Line				/*diferentes reglas se separan con pipe | */
        ;					/*siempre finaliza con ; */



Line:	END
        | Expression END                { printf("El Resultado es: %f\n",$1); }		/*acciones cuando se aplica la regla*/
        ;

								/*$n son variables mapeadas a la partde derecha de la regla, comenzando por izq*/
Expression:	NUMERO                  { $$=$1; }/*N  tomara una vez resuelto es el valor asignado a la variable $$*/

        | NUMERO MAS Expression         { $$=$1+$3; }
        | Expression MENOS Expression   { $$=$1-$3; }
        | Expression POR Expression     { $$=$1*$3; }
        | Expression DIVIDE Expression  { $$=$1/$3; }
        | MENOS Expression %prec NEG    { $$=-$2; }			/*%prec cambiar la precedencia de un operador dependiendo del contexto*/
        | Expression POTENCIA Expression     { $$=pow($1,$3); }
        | Expression POWER Expression   { $$=pow($1,$3); }
        | ABRE_PARENTESIS Expression CIERRA_PARENTESIS { $$=$2; }
	;
%%
int yyerror(char *s) {
  printf("%s\n",s);
}

int main(void) {
	printf("Parser de Expresiones aritmeticas básicas\n");
  yyparse();
}
