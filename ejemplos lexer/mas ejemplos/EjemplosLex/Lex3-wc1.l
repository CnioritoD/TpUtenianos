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
int main (int argc, char *argv[])
{
	if (argc == 2)
	{
		yyin = fopen (argv[1], "rt");
		if (yyin == NULL)
		{
			printf ("El archivo %s no se puede abrir\n", argv[1]);
			exit (-1);
		}
	}
	else yyin = stdin;
	
	yylex();
	printf ("caracteres:%d\tlineas:%d\n", caracter, linea);
	return 0;
}
	
