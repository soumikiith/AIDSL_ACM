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

//Defining functions of Type_Info class
Type_Info::Type_Info(var_type bt)
{
	this->base_type = bt;
}
Type_Info::Type_Info(var_type bt, int nd, int fs, int ss)
{
	this->base_type = bt;
	this->dim_count = nd;
	this->first_dim_size = fs;
	this->second_dim_size = ss;
}
string Type_Info::base_type_name()
{
	if(this->base_type == INT32)
	{
		return "INT32";
	}
	else if (this->base_type == FLOAT32)
	{
		return "FLOAT32";
	}
}
var_type Type_Info::get_base_type()
{
	return this->base_type;
}
int Type_Info::get_number_of_dimensions()
{
	return this->dim_count;
}
int Type_Info::get_size_of_first_dim()
{
	return this->first_dim_size;
}
int Type_Info::get_size_of_second_dim()
{
	return this->second_dim_size;
}