/* Lex1.l: retorna tipos de datos basico: numero o palabra
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   
  
 lex fuente.l
 yacc -d ejem1.1.y
 cc -o ejem1.1 lex.yy.c y.tab.c -ly -ll -lm

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
espacio		[ \t]+

%%
		/*----- Sección de Reglas ----------------*/
"q"		{return 0;}
"salir"		{salir();return 0;}
"SELECT"	{printf("encontre token SELECT");}
{Palabra}	{printf("Se leyo la palabra : %s\n", yytext);palabra++;}
{Numero}	{printf("Se leyo el numero : %d\n", atoi(yytext));numero++;}
{espacio}	{}
.	{printf("ERROR LEXEMA NO RECONOCIDO");}
		
%%
		/*----- Sección de Procedimientos --------*/
main(){
	printf("Lex1.l\nEste ejemplo, distingue entre un numero entero, palabras \nIntroduzca q o salir para terminar.\n");
	yylex();
}
salir(){
	printf("Se leyeron %d entradas, de las cuales se reconocieron\n%d\tEnteros\n%d\tPalabras.\n", (palabra+numero), numero, palabra);
}
