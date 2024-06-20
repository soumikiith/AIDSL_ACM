#include "common-headers.hh"

int temp_count=0;
map <string, int> memory; // Stores values of variables during interpretation

//////////////////////// PROCESSING REDUCTIONS /////////////////////////////////

Ast * process_NUM(string * name)
{
	int num;

	try
	{
	  num = stoi(*name);
	} 
	catch (const std::out_of_range& ex)
	{
	  std::cerr << "Number too large: " << name << ex.what() << std::endl;
	  exit(1);
	}

	Ast * ast = new Number_Expr_Ast<int>(num);
	assert (ast != NULL);
	return ast;	
}

Ast * process_ID(string * name)
{
	Ast * ast = new Name_Expr_Ast(*name);
	assert (ast != NULL);
	return ast;	
}

Ast * process_Expr(Ast *left, op_type op, Ast *right)
{
	int result;
	Ast * ast;

	switch (op)
	{
		case PLUS:	ast = new Plus_Expr_Ast(left, right); break;
		case MINUS:	ast = new Minus_Expr_Ast(left, right); break;
		case MULT:	ast = new Mult_Expr_Ast(left, right); break;
		case DIV:	ast = new Div_Expr_Ast(left, right); break;
		case UMINUS:
			if (right != NULL)
			{
				exit(1);
			}
			else	ast = new UMinus_Expr_Ast(left);
			break;
		default:
			cerr << "Wrong operator type" << endl;
			exit(1);
			break;
	}
	return ast; 
}

Ast * process_Asgn(string *lhs_name, Ast *rhs)
{
	Ast *ast;
	if (lhs_name == NULL)
	{
		ast = rhs;
	}
	else
	{
		Ast * l = new Name_Expr_Ast(*lhs_name);
		Ast * r = rhs;
		ast = new Assignment_Stmt_Ast(l, r);
	}
	return ast;	
}

list<Ast *> * process_Stmt_List(list<Ast *> *ast_list, Ast *ast)
{
	assert (ast_list != NULL);
	ast_list->push_back(ast);
	return ast_list;	
}

list<Ast *> * init_Stmt_List(Ast *ast)
{
	list <Ast*> *ast_list = new list <Ast*>;
	assert (ast_list != NULL);
	ast_list->push_back(ast);
	return ast_list;	
}
