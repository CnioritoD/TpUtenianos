/*calculadora.1.l: scanner para detectar numeros enteros y operaciones basicas + - * / potencia. 
   rodrigovigil @ gmail . com
   
lex ejem1.1.l
 yacc -d ejem1.1.y
 cc -o ejem1.1 lex.yy.c y.tab.c -ly -ll -lm

*/
%option noyywrap
%{
#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
%}	

espacio           [ \t]+
digito           [0-9]
entero         {digito}+

%%

{espacio}         { /* Ignoramos espacios en blanco */ }
"exit"|"quit"|"q"|"bye"	{printf("Terminando programa\n");exit(0);}
{entero}	{
                 yylval.dval=atof(yytext);
                  return(NUMERO);
                }
"+"           return(MAS);
"-"           return(MENOS);
"*"           return(POR);
"/"           return(DIVIDE);
"^"           return(POTENCIA);
"#"           return(POWER);
"("           return(ABRE_PARENTESIS);
")"           return(CIERRA_PARENTESIS);
"\n"  return(END);

%%
