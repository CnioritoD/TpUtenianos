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
%token  MAS	MENOS	POR	DIVIDE	POWER
%token  ABRE_PARENTESIS        CIERRA_PARENTESIS
%token	<dval>	PI	E	FI
%token	SEN	COS	TAN
%token	LN	LOG
%token  END
						/* tipo de agrupacion y precedencia de  tokens operadores. */
 						/*La precedencia es asignada en orden inverso al que aparecen, mas presedencia ultimo operador declarado*/
%left   MAS	MENOS				/*Asociatividad indican si el operador se agrupa a la derecha o a la izquierda*/
%left   POR	DIVIDE
%left   NEG
	/*%right  POWER*/
%right  POWER

%type <dval> Exp
%type <dval> Fact
%start Input

%%

Input:	Line					/*El reemplazo del no terminal se representa con : */
	| Input Line				/*diferentes reglas se separan con pipe | */
        ;					/*siempre finaliza con ; */



Line:	END
        | Exp END                { printf("El Resultado es: %f\n",$1); }		/*acciones cuando se aplica la regla*/
        | error END              { yyerrok; }
	;

						/*$n son variables mapeadas a la partde derecha de la regla, comenzando por izq*/
Exp:	Fact                  { $$=$1; }/*N  tomara una vez resuelto es el valor asignado a la variable $$*/

        | Fact MAS Exp         { $$=$1+$3; }
        | Fact MENOS Exp   { $$=$1-$3; }
        | Fact POR Exp     { $$=$1*$3; }
        | Fact DIVIDE Exp  { $$=$1/$3; }
        | MENOS Exp %prec NEG    { $$=-$2; }		/*%prec cambiar la precedencia de un operador dependiendo del contexto*/
        
	;
Fact		:	Fact POWER Fact	{$$=pow($1,$3);}
		| ABRE_PARENTESIS Exp CIERRA_PARENTESIS { $$=$2; }	/* |	'(' exp ')'	{$$=$2;}*/		
		|	NUMERO		{$$=$1;}
		|	PI		{$$=$1;}
		|	FI		{$$=$1;}
		|	E		{$$=$1;}
		|	SEN ABRE_PARENTESIS Exp CIERRA_PARENTESIS	{$$=sin($3);}
		|	COS ABRE_PARENTESIS Exp CIERRA_PARENTESIS	{$$=cos($3);}
		|	TAN ABRE_PARENTESIS Exp CIERRA_PARENTESIS	{$$=tan($3);}	
		|	LN ABRE_PARENTESIS Exp CIERRA_PARENTESIS	{$$=log($3);}
		|	LOG ABRE_PARENTESIS Exp CIERRA_PARENTESIS	{$$=log10($3);}
		;
%%
int yyerror(char *s) {
  printf("%s\n",s);
}

int main(void) {
	printf("Parser de Expresiones aritmeticas básicas\n");
  yyparse();
}
