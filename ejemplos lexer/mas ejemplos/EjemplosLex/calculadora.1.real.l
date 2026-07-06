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
{digito}+("."{digito}+)?(E("+"|"-")?{digito}+)?		{yylval.dval=atof(yytext);return (NUMERO);}
pi		{yylval.dval=3.141592;return PI;}
e		{yylval.dval=2.718228;return E;}
fi		{yylval.dval=1.618033;return FI;}
sen		{return SEN;}
cos		{return COS;}
tan		{return TAN;}
log		{return LOG;}
ln		{return LN;}
"+"           return(MAS);
"-"           return(MENOS);
"*"           return(POR);
"/"           return(DIVIDE);
"#"           return(POWER);
"("           return(ABRE_PARENTESIS);
")"           return(CIERRA_PARENTESIS);
"\n"  	      return(END);
.		{printf("Error: lexema no reconocido: %s",yytext);return 0;}
%%
