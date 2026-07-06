/* Lex3.l: nos permite listar url de un archivo dado. 
   Ejemplo para mostrar Lex.
   rodrigovigil @ gmail . com
   
*/ 
%{
#include <stdio.h>

%}
%%
	/*----- Sección de Reglas ----------------*/	
https:\/\/[^ \n<>"]*	{
			printf("%s\n",yytext);
			}
http:\/\/[^ \n<>"]*	{
			printf("%s\n",yytext);
			}

.|\n		;
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
	return 0;
}
	
