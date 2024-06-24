%{
#include "common-headers.hh"
#include "ast.hh"
extern "C" void yyerror(char *s);
extern int yylex(void);

void display_stmt_list (list<Ast *> *);

unordered_map<string, Type_Info *> symtab;
void display_symtab ();
%}
%union{
	string * name;
	Ast *ast;
	list<Ast *> *ast_list;	
	var_type base_type;
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
%type <base_type> Base_Type
%start Start
%%
Start: StmtList 			{	if (show_parse()) cout << "Reducing by `Start: StmtList'\n";
						if (show_ast ()) display_stmt_list ($1);
						display_symtab ();
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
						if (semantic_analysis())
						{
							string name = *$1;
							$$ = process_Asgn($1, $3);
						}
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
						if (semantic_analysis())
						{
							string name = *$1;
							if (symtab.find (name) == symtab.end ())
							{
								cerr << "Error: Undefined variable " << name << "\n";
								exit (1);
							}
							$$ = process_ID($1); 
						}
					}
	| '(' Expr ')'			{ 
						if (show_parse()) cout << "Reducing by `Expr : ( Expr )'\n";
						if (semantic_analysis()) $$ = $2; 
					}
	;

Decl_Stmt: Scalar_Decl_Stmt | Tensor_Decl_Stmt

Tensor_Decl_Stmt : ID '(' NUM ',' Base_Type ')' '[' NUM ']'
{
	string id_name = *$1;
	if (symtab.find (id_name) != symtab.end ())
	{
		cerr << "Error: Variable " << id_name << " is redeclared\n";
		exit (1);
	}

	var_type base_type = $5;
	int dim_count = checked_stoi(*$3);
	int first_dim_size = checked_stoi(*$8);

	Type_Info::check_dim_size (dim_count, first_dim_size, 0); 
	Type_Info *type_info = new Type_Info (base_type, dim_count, first_dim_size, 0);
	assert (type_info);
	symtab[id_name] = type_info;
}
	| ID '(' NUM ',' Base_Type ')' '[' NUM ']' '[' NUM ']'
{
	string id_name = *$1;
	if (symtab.find (id_name) != symtab.end ())
	{
		cerr << "Error: Variable " << id_name << " is redeclared\n";
		exit (1);
	}

	var_type base_type = $5;
	int dim_count = checked_stoi(*$3);
	int first_dim_size = checked_stoi(*$8);
	int second_dim_size = checked_stoi(*$11);

	Type_Info::check_dim_size (dim_count, first_dim_size, second_dim_size); 
	Type_Info *type_info = new Type_Info (base_type, dim_count, first_dim_size, second_dim_size);
	assert (type_info);
	symtab[id_name] = type_info;
}
		 

Scalar_Decl_Stmt: Base_Type ID	{
					string id_name = *$2;
					if (symtab.find (id_name) != symtab.end ())
					{
						cerr << "Error: Variable " << id_name << " is redeclared\n";
						exit (1);
					}

					var_type base_type = $1;
					Type_Info *type_info = new Type_Info(base_type);
					assert (type_info != NULL);
					symtab[id_name] = type_info;
				}

Base_Type: TK_INT32	{ $$ = INT32; }
	 | TK_INT8	{ $$ = INT8; }
	
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

void display_symtab()
{
	cout << "Displaying Symbol Table:\n";
	for (auto& pair: symtab)
	{
		string name = pair.first;
		Type_Info *type_info = pair.second;
		assert (type_info);

		cout << name << ": " << type_info->base_type_name ();
		if (type_info->is_tensor_type())
		{
			int dim_count = type_info->get_number_of_dimensions ();
			cout << " (dim_count = " << dim_count << ", first_dim_size = "
			     << type_info->get_size_of_first_dim ();
			if (dim_count == 2)
				cout << ", second_dim_size = " << type_info->get_size_of_second_dim();
			cout << ")";
		}
		cout << "\n";
	}
}
