/* Lex3.l: nos permite contar los caracteres, palabras y líneas de un archivo. Similar a wc de sistemas UNIX
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   
*/ 
%{
#include <stdio.h>
int nc, np, nl;
%}
%%
	/*----- Sección de Reglas ----------------*/	
[^ \t\n]+	{ np++; nc += yyleng; }
[ \t]+		{ nc += yyleng; }
\n		{ nl++; nc++; }
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
	nc = np = nl = 0;
	yylex();
	printf ("caracteres:%d\tpalabras:%d\tlineas:%d\n", nc, np, nl);
	return 0;
}
	
