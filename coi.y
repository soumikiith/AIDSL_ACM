%{
#include "common-headers.hh"
#include "ast.hh"
extern "C" void yyerror(char *s);
extern int yylex(void);


%}
%union{
	string * name;
	Node_Attribute * node_attribute;
}
%token <name> NUM 
%token <name> ID

%left '+' '-'
%left '*' '/'
%right Uminus
%type <node_attribute> Expr
%type <node_attribute> Stmt
%type <node_attribute> StmtList
%start Start
%%
Start: StmtList 			{	if (show_parse()) cout << "Reducing by `Start: StmtList'\n";
						if (semantic_analysis()) process_finish($1); 
					}
	;
StmtList : StmtList Stmt		{ 
						if (show_parse()) cout << "Reducing by `StmtList : StmtList Stmt'\n";	
						if (semantic_analysis()) $$ = process_Stmt_List($1, $2); 
					}
      | Stmt				{ 
						if (show_parse()) cout << "Reducing by `StmtList : Stmt'\n";
						if (semantic_analysis()) $$ = init_Stmt_List($1); 
					}

Stmt : ID '=' Expr ';' 			{ 
						if (show_parse()) cout << "Reducing by `Stmt : ID = Expr ;'\n";
						if (semantic_analysis()) $$ = process_Asgn($1, $3); 
					} 
	;
Expr : Expr '+' Expr			{ 
						if (show_parse()) cout << "Reducing by `Expr : Expr + Expr'\n";
						if (semantic_analysis()) $$ = process_Expr($1, PLUS, $3); 
					}
	| Expr '*' Expr 		{ 
						if (show_parse()) cout << "Reducing by `Expr : Expr * Expr'\n";
						if (semantic_analysis()) $$ = process_Expr($1, MULT, $3); 
					}
	| Expr '/' Expr 		{ 
						if (show_parse()) cout << "Reducing by `Expr : Expr / Expr'\n";
						if (semantic_analysis()) $$ = process_Expr($1, DIV, $3); 
					}
	| Expr '-' Expr 		{ 
						if (show_parse()) cout << "Reducing by `Expr : Expr - Expr'\n";
						if (semantic_analysis()) $$ = process_Expr($1, MINUS, $3); 
					}
	| '-' Expr	%prec Uminus	{ 
						if (show_parse()) cout << "Reducing by `Expr : - Expr'\n";
						if (semantic_analysis()) $$ = process_Expr($2, UMINUS, NULL); 
					}
	| NUM 				{ 
						if (show_parse()) cout << "Reducing by `Expr : NUM'\n";
						if (semantic_analysis()) $$ = process_NUM($1); 
					}
	| ID 				{ 
						if (show_parse()) cout << "Reducing by `Expr : ID'\n";
						if (semantic_analysis()) $$ = process_ID($1); 
					}
	| '(' Expr ')'			{ 
						if (show_parse()) cout << "Reducing by `Expr : ( Expr )'\n";
						if (semantic_analysis()) $$ = $2; 
					}
	;
	
%%
