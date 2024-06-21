%{
#include "common-headers.hh"
extern "C" void yyerror(char *s);
#include "parse.tab.h"

void store_token_name(std::string token_name, char *lexeme, int lineno);

%}
%option noyywrap
digit  [0-9]
ws	[ \t\n]*
operator [-+*/=]
letter [a-zA-Z_]
punct [();]
%%
{digit}+ 	{ 	
			store_token_name("NUM\t", yytext, yylineno);
			yylval.name= new string(yytext); return NUM; 
		}

{operator}	{	
			store_token_name("OPERATOR", yytext, yylineno);
			return yytext[0]; 
		}
{punct}		{	
			store_token_name("PUNCTUATION", yytext, yylineno);
			return yytext[0]; 
		}
int32|int16|int8|float16|float32 {
			store_token_name("TOKEN_DTYPE", yytext, yylineno);
			return TOKEN_DTYPE;
				}
{letter}({letter}|{digit})* { 
				
			store_token_name("ID\t", yytext, yylineno);
			yylval.name= new string(yytext); return ID; 
		}		
{ws}		;
.		{
			cerr << "Illegal Character \"" << yytext[0] << "\". Ignoring the rest of the input. " << endl;
			exit(1);
		}
