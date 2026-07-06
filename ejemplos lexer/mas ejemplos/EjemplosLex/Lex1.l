/* Lex1.l: retorna tipos de datos basico: numero o palabra
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   
*/ 
%option noyywrap
%{
#include <stdio.h>
int palabra=0, numero=0;
%}
		/*Palabra		[a-zA-Z|\.]+	*/
		/*Identificador	[a-zA-Z][a-zA-Z0-9]*	*/
Numero		-?[0-9]+
Palabra		[a-zA-Z]+	

%%
		/*----- Sección de Reglas ----------------*/
"q"		{return 0;}
"salir"		{salir();return 0;}
{Palabra}	{printf("Se leyo la palabra : %s\n", yytext);palabra++;}
{Numero}	{printf("Se leyo el numero : %d\n", atoi(yytext));numero++;}
.	{printf("ERROR LEXEMA NO RECONOCIDO");return 0;}
		
%%
		/*----- Sección de Procedimientos --------*/
main(){
	printf("Lex1.l\nEste ejemplo, distingue entre un numero entero, palabras \nIntroduzca q o salir para terminar.\n");
	yylex();
}
salir(){
	printf("Se leyeron %d entradas, de las cuales se reconocieron\n%d\tEnteros\n%d\tPalabras.", (palabra+numero), numero, palabra);
}
