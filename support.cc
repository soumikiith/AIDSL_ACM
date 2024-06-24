#include "common-headers.hh"

//////////////////////// PROCESSING REDUCTIONS /////////////////////////////////

int checked_stoi (string s)
{
	try
	{
		return stoi (s);
	}
	catch (const std::out_of_range& ex)
	{
	  std::cerr << "Number too large: " << s << ex.what() << std::endl;
	  exit(1);
	}
}

Type_Info *symtab_lookup (string id_name)
{
	auto it = symtab.find(id_name);
	if (it == symtab.end())
	{
		cerr << "Error: Variable " << id_name << " is undefined!\n";
		exit(1);
	}
	Type_Info *type_info = it->second;
	assert (type_info);
	return type_info;
}

Ast * process_NUM(string * name)
{
	int num = checked_stoi(*name);
	Ast * ast = new Number_Expr_Ast<int>(num);
	assert (ast != NULL);
	return ast;	
}

Ast * process_ID(string * name)
{
	string id_name = *name;
	Type_Info *type_info = symtab_lookup (id_name);
	Ast * ast = new Name_Expr_Ast(id_name, type_info);
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
	assert (lhs_name);
	string name = *lhs_name;
	type_check_assign (name, rhs);
	Ast * id = new Name_Expr_Ast(name, symtab_lookup(name));
	assert (id);
	Ast *ast = new Assignment_Stmt_Ast(id, rhs);
	assert (ast);
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
	if (this->base_type == INT8)
		return "int8";
	else if(this->base_type == INT32)
	{
		return "int32";
	}
	else if (this->base_type == FLOAT32)
	{
		return "float32";
	}
	else
		assert (0);
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
bool Type_Info::is_tensor_type()
{
	return this->dim_count > 0;
}
void Type_Info::check_dim_size (int dim_count, int fs, int ss)
{
	if (dim_count != 1 && dim_count != 2)
	{
		cerr << "Error: Invalid number of dimensions: " << dim_count << "\n";  
		exit (1);
	}

	if (fs < 1)
	{
		cerr << "Invalid size for first dimension " << fs << "\n";
		exit (1);
	}

	if (dim_count == 2 && ss < 1)
	{
		cerr << "Invalid size for second dimension " << ss << "\n";
		exit (1);
	}
}
