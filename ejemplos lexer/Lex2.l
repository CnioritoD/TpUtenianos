/* Lex2.l: retorna tipos de datos basico. 
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   Compiladores y Autómatas. 

	lex ejem1.1.l
	cc -o ejem1.1 lex.yy.c y.tab.c -ly -ll -lm
*/ 
%option noyywrap
%{
#include <stdio.h>
int palabra=0, id=0, numero=0;
int aux, i, cadnum;
%}
Numero		-?[0-9]+
Palabra		[a-zA-Z]+	
Comentario	\/\*([a-zA-Z0-9]*|[ \t]+)*\*\/ 
Identificador	[a-zA-Z][a-zA-Z0-9]*
Reservada	(si|para|mientras|segun|repetir|otra)
		/*IP		[0-9|\.]+*/
punto		[\.]
val05	 	([0-9]|[0-9][0-9]|[0-1][0-9][0-9]|2[0-5][0-5])
vIP 		{val05}{punto}{val05}{punto}{val05}{punto}{val05}
Espacio         [ \t]+


%%
		/*----- Sección de Reglas ----------------*/
"q"		{return 0;}
"quit"		{salir();return 0;}
"salir"		{salir();return 0;}
{vIP}		{printf("Se leyo una IPVer : %s\n", yytext);id++;}
{Reservada}	{printf("Se leyo la palabra Reservada: %s\n", yytext);palabra++;}
{Palabra}	{printf("Se leyo la palabra : %s\n", yytext);palabra++;}
{Numero}	{printf("Se leyo el numero : %d\n", atoi(yytext));numero++;}
{Comentario}	{printf("Se leyo un Comentario : %s\n", yytext);id++;}
{Identificador}	{printf("Se leyo un ID : %s\n", yytext);id++;}
{punto}		{printf("Se leyo un Punto : %s\n", yytext);id++;}
.	{printf("error\n\n"); return 0;}
%%
		/*----- Sección de Procedimientos --------*/
main(){
	printf("Lex2.l\nEste ejemplo, distingue entre un numero entero, palabras e identificadores.\nIntroduzca: quit,q o salir para terminar.\n");
	yylex();
}
salir(){
	printf("Se leyeron %d entradas, de las cuales se reconocieron\n%d\tEnteros\n%d\tPalabras.\ny\n%d\tIdentificadores\n", (palabra+numero+id), numero, palabra, id);
}
