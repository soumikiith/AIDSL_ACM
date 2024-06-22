%{
#include "common-headers.hh"
#include "ast.hh"
extern "C" void yyerror(char *s);
extern int yylex(void);

void display_stmt_list (list<Ast *> *);

%}
%union{
	string * name;
	Ast *ast;
	list<Ast *> *ast_list;	
}
%token <name> NUM 
%token <name> ID
%token TK_INT8
%token TK_INT32

%left '+' '-'
%left '*' '/'
%right Uminus
%type <ast> Expr
%type <ast> Stmt
%type <ast_list> StmtList
%start Start
%%
Start: StmtList 			{	if (show_parse()) cout << "Reducing by `Start: StmtList'\n";
						if (show_ast ()) display_stmt_list ($1);
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
	| Decl_Stmt ';'			{
						$$ = new Empty_Ast(); 
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

Decl_Stmt: Scalar_Decl_Stmt | Tensor_Decl_Stmt

Tensor_Decl_Stmt : ID'('NUM','Base_Type')''['NUM']'| ID'('NUM','Base_Type')''['NUM']''['NUM']'

Scalar_Decl_Stmt: Base_Type ID

Base_Type: TK_INT32
	 | TK_INT8
	
%%

void display_stmt_list (list<Ast *> *ast_stmt_list)
{
	if (!ast_stmt_list)
		return;
	for (auto ast: *ast_stmt_list)
	{
		ast->print_ast (4, cout, true);
		cout << "\n";
	}
}
