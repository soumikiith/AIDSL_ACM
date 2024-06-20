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
		//ast->print_ast(4,cout, true);
	}
        //ast->print_spaces_on_new_line (4, cout);
	return ast;	
}

list<Ast *> * process_Stmt_List(list<Ast *> *ast_list, Ast *ast)
{
	if (show_ast())
		ast->print_ast(4, cout, true);

	assert (ast_list != NULL);
	ast_list->push_back(ast);
	return ast_list;	
}

list<Ast *> * init_Stmt_List(Ast *ast)
{
	if (show_ast())
		ast->print_ast(4, cout, true);
	
	list <Ast*> *ast_list = new list <Ast*>;
	assert (ast_list != NULL);
	ast_list->push_back(ast);
	return ast_list;	
}

////////////////////////// BEGIN AND ENDING ///////////////////////////////////////
#if 0
void process_finish(Node_Attribute * attr)
{}
	
  if ((lp_mode() == compiler) && (show_ast()))
	{
	// Now printing has been moved to per statement.
	// Hence this part has been commened out.
	// You can write any other ast list traversal here
	// for some other task, such as generating a dot
	// file to see the tree using graphviz or
	// generating the C++ code as the output of the
	// reference implementation

#if 0
		list <Ast*> * ast_list = attr->get_ast_list();

		for (auto it : *ast_list)
		{
			it->print_ast(4, cout, true);
			cout << endl;
		}

#endif 
	}
#endif
