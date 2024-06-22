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
punct [();,\[\]]
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

int32		{
			store_token_name ("TK_INT32", yytext, yylineno);
			return TK_INT32;
		}

int8		{
			store_token_name ("TK_INT8", yytext, yylineno);
			return TK_INT8;
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
