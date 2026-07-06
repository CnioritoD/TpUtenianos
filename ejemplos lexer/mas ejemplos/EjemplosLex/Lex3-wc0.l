/* Lex3.l: nos permite contar los caracteres, palabras y líneas de un archivo. Similar a wc de sistemas UNIX
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   
*/ 
%{
#include <stdio.h>
int caracter=0, palabra=0, linea=0;
%}
%%
	/*----- Sección de Reglas ----------------*/	

.		{ ++caracter; }
\n		{ ++caracter; ++linea; }
%%
	/*----- Sección de Procedimientos --------*/
main ()
{
	yylex();
	printf ("caracteres:%d\tlineas:%d\n", caracter, linea);
	return 0;
}
	
