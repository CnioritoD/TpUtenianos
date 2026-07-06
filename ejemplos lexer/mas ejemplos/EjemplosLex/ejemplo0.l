/* Lex1.l: retorna tipos de datos basico: digito, numero entero, real, palabra espacio
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   
*/ 
%option noyywrap
%{
#include <stdio.h>
%}
		/*Palabra		[a-zA-Z|\.]+	*/
		/*Identificador	[a-zA-Z][a-zA-Z0-9]*	*/
Digito 		(0|1|2|3|4|5|6|7|8|9)
Entero		-?[0-9]+
Real		-?[0-9]+\.[0-9]+
Palabra		[a-zA-Z]+
Identificador	[a-zA-Z][a-zA-Z0-9]*	
Espacio         [ \t]+

%%
		/*----- Sección de Reglas ----------------*/
"q"		{return 0;}
{Digito}	{printf("DIGITO\n");}
{Entero}	{printf("NUMERO\n");}
{Real}		{printf("NUMERO REAL\n");}
{Palabra}	{printf("PALABRA\n");}
{Identificador}       {printf("ID\n");}
{Espacio}       {printf("ESPACIO\n"); /* Ignoramos espacios en blanco */ }
.		;
%%
		/*----- Sección de Procedimientos --------*/
main(){
	printf("Lex0.l\nEste ejemplo, distingue entre un numero entero, palabras \nIntroduzca q  para terminar.\n");
	yylex();
}

