
#include<iostream>
#include<fstream>
#include<typeinfo>

using namespace std;

#include "common-headers.hh"
#include "ast.hh"

Ast::Ast()
{
	type_info = NULL;
}

Ast::~Ast()
{}



////////////////////////////////////////////////////////////////

Ast * Unary_Expr_Ast::get_opd()
{
	stringstream msg;
	msg << "opd is NULL for reading an object of class " << typeid(*this).name();

	assert (opd !=NULL && "The operand of a unary AST cannot be NULL");
	return opd;
}

void Unary_Expr_Ast::set_opd(Ast *o)
{
	stringstream msg;
	msg << "opd is NULL for setting in an object of class " << typeid(*this).name();

	assert (o !=NULL && "The operand of a unary AST cannot be NULL");
	opd = o;
}

void Output_Expr_Ast::gencode(ofstream& genf)
{
	Ast *opd = get_opd();
	assert (opd);
	Type_Info *type_info = opd->get_type_info ();
	assert (type_info);

	if (!type_info->is_tensor_type())
	{
		genf << "cout << ";
		opd->gencode(genf);
	}
}

////////////////////////////////////////////////////////////////

Ast * Binary_Expr_Ast::get_left_child()
{
	stringstream msg;
	msg << "lopd is NULL for reading an object of class " << typeid(*this).name();

	assert (left_child !=NULL && "The left child of a binary AST cannot be NULL");
	return left_child;
}

Ast * Binary_Expr_Ast::get_right_child()
{
	stringstream msg;
	msg << "ropd is NULL for reading an object of class " << typeid(*this).name();

	assert (right_child !=NULL && "The right child of a binary AST cannot be NULL");
	return right_child;
}


void Binary_Expr_Ast::set_left_child(Ast *l)
{
	stringstream msg;
	msg << "lopd is NULL for setting in an object of class " << typeid(*this).name();

	assert (l !=NULL && "The left child of a binary AST cannot be NULL");
	left_child = l;
}

void Binary_Expr_Ast::set_right_child(Ast *r)
{
	stringstream msg;
	msg << "ropd is NULL for setting in an object of class " << typeid(*this).name();

	assert (r !=NULL && "The right child of a binary AST cannot be NULL");
	right_child = r;
}

////////////////////////////////////////////////////////////////

Statement_Ast::Statement_Ast()
{}

Statement_Ast::~Statement_Ast()
{}

Assignment_Stmt_Ast::Assignment_Stmt_Ast(Ast * l, Ast * r)
{
	assert (l !=NULL && "The LHS of an assignment cannot be NULL");
	assert (r !=NULL && "The RHS of an assignment cannot be NULL");

	set_lhs(l);
	set_rhs(r);
}

Assignment_Stmt_Ast::~Assignment_Stmt_Ast()
{
}

void Assignment_Stmt_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
	/*
	 *if (top_level)
     *    print_spaces_on_new_line (sc, file_buffer);
	 */

    	print_spaces (sc, file_buffer);
	file_buffer << "Asgn:";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "LHS (";
	get_lhs()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
        //print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << ")";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "RHS (";
	get_rhs()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
        //print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << ")";

	if (top_level)
		file_buffer << endl;
}

Ast * Assignment_Stmt_Ast::get_lhs()
{
	assert (lhs !=NULL && "The LHS of an assignment cannot be NULL");
	return lhs;
}

Ast * Assignment_Stmt_Ast::get_rhs()
{
	assert (rhs !=NULL && "The RHS of an assignment cannot be NULL");
	return rhs;
}


void Assignment_Stmt_Ast::set_lhs(Ast *l)
{
	assert (l !=NULL && "The LHS of an assignment cannot be NULL");
	lhs = l;
}

void Assignment_Stmt_Ast::set_rhs(Ast *r)
{
	assert (r !=NULL && "The RHS of an assignment cannot be NULL");
	rhs = r;
}

void Assignment_Stmt_Ast::gencode(ofstream& genf)
{
	Ast *left = get_lhs();
	assert (left);
	left->gencode(genf);

	genf << " = ";

	Ast *right = get_rhs();
	assert (right);
	right->gencode(genf);
}

///////////////////////////////////////////////////////////////////////////////

template <class DATA_TYPE>
Number_Expr_Ast<DATA_TYPE>::Number_Expr_Ast(DATA_TYPE number)
{
	constant = number;
	Type_Info *type_info = new Type_Info(INT32);
	assert (type_info);
	set_type_info (type_info);
}

template <class DATA_TYPE>
Number_Expr_Ast<DATA_TYPE>::~Number_Expr_Ast()
{}


template <class DATA_TYPE>
void Number_Expr_Ast<DATA_TYPE>::print_ast(int sc, ostream & file_buffer, bool top_level)
{
	// Ignore the space count sc
	if (top_level)
        	print_spaces_on_new_line (sc, file_buffer);
	
	file_buffer << "Num : " << constant;
}

template <class DATA_TYPE>
void Number_Expr_Ast<DATA_TYPE>::gencode(ofstream& genf)
{
	genf << constant;
}
///////////////////////////////////////////////////////////////////////////////


Plus_Expr_Ast::Plus_Expr_Ast(Ast * l, Ast * r, Type_Info *type_info)
{
	assert (l !=NULL && "The left child of a PLUS AST cannot be NULL");
	assert (r !=NULL && "The right child of a PLUS AST cannot be NULL");

	set_left_child(l);
	set_right_child(r);
	set_type_info(type_info);
}

void Plus_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
        print_spaces_on_new_line (sc, file_buffer);
	file_buffer << "Arith: Plus";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "L_Opd (";
	get_left_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "R_Opd (";
	get_right_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";
}

/////////////////////////////////////////////////////////////////

Minus_Expr_Ast::Minus_Expr_Ast(Ast * l, Ast * r, Type_Info *type_info)
{
	assert (l !=NULL && "The left child of a MINUS AST cannot be NULL");
	assert (r !=NULL && "The right child of a MINUS AST cannot be NULL");

	set_left_child(l);
	set_right_child(r);
	set_type_info(type_info);
}

void Minus_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
        print_spaces_on_new_line (sc, file_buffer);
	file_buffer << "Arith: Minus";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "L_Opd (";
	get_left_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "R_Opd (";
	get_right_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";
}

//////////////////////////////////////////////////////////////////

Mult_Expr_Ast::Mult_Expr_Ast(Ast * l, Ast * r, Type_Info *type_info)
{
	assert (l !=NULL && "The left child of a MULT AST cannot be NULL");
	assert (r !=NULL && "The right child of a MULT AST cannot be NULL");

	set_left_child(l);
	set_right_child(r);
	set_type_info(type_info);
}

void Mult_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
        print_spaces_on_new_line (sc, file_buffer);
	file_buffer << "Arith: Mult";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "L_Opd (";
	get_left_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "R_Opd (";
	get_right_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";
}


MatMul_Expr_Ast::MatMul_Expr_Ast(Ast * l, Ast * r, Type_Info *type_info)
{	
	assert (l);
	assert (r);
	set_left_child(l);
	set_right_child(r);
	set_type_info(type_info);
}

void MatMul_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
        print_spaces_on_new_line (sc, file_buffer);
	file_buffer << "Arith: MatMul";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "L_Opd (";
	get_left_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "R_Opd (";
	get_right_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";
}

////////////////////////////////////////////////////////////////////

Div_Expr_Ast::Div_Expr_Ast(Ast * l, Ast * r, Type_Info *type_info)
{
	assert (l !=NULL && "The left child of a DIV AST cannot be NULL");
	assert (r !=NULL && "The right child of a DIV AST cannot be NULL");

	set_left_child(l);
	set_right_child(r);
	set_type_info(type_info);
}

void Div_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
        print_spaces_on_new_line (sc, file_buffer);
	file_buffer << "Arith: Div";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "L_Opd (";
	get_left_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "R_Opd (";
	get_right_child()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";
}


//////////////////////////////////////////////////////////////////////

UMinus_Expr_Ast::UMinus_Expr_Ast(Ast * l)
{

	assert (l !=NULL && "The child of a UNARY MINUS AST cannot be NULL");

	set_opd(l);
}

void UMinus_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
        print_spaces_on_new_line (sc, file_buffer);
	file_buffer << "Arith: Uminus";

        print_spaces_on_new_line (sc+INDENT_INCR, file_buffer);
	file_buffer << "L_Opd (";
	get_opd()->print_ast(sc+2*INDENT_INCR, file_buffer, false);
	file_buffer << ")";
}

//////////////////////////////////////////////////////////////////////

template class Number_Expr_Ast<double>;
template class Number_Expr_Ast<int>;
///////////////////////////////////////////////////////////////////////////////



void Ast::print_spaces_on_new_line (int sc, ostream & file_buffer)
{
	file_buffer << "\n";
	for (int i=0; i<sc; i++)
		file_buffer << " ";
}

void Ast::print_spaces (int sc, ostream & file_buffer)
{
	for (int i=0; i<sc; i++)
		file_buffer << " ";
}


/////////////////////////////////////////////////////////////////

Name_Expr_Ast::Name_Expr_Ast(string & name, Type_Info *type_info)
{
	expr_name = name;
	set_type_info (type_info);
}

Name_Expr_Ast::~Name_Expr_Ast()
{}


void Name_Expr_Ast::print_ast(int sc, ostream & file_buffer, bool top_level)
{
	// Ignore the space count sc
	if (top_level)
        	print_spaces_on_new_line (sc, file_buffer);
	
	file_buffer << "Name : " << expr_name;
}

void Name_Expr_Ast::gencode(ofstream& genf)
{
	genf << mangle_name(expr_name);
}

#if 0
int main()
{
	
// 	Code to test the class.

//	Create objects by calling the constructors and supplying string values or
//	numeric values as needed.
//	The call different methods on the class and print them.

	string * a = new string ("distance");
	string * b = new string ("speed");
	string * c = new string ("time");

	Ast *o1 = new Name_Expr_Ast(*b,1);
	Ast *o2 = new Name_Expr_Ast(*b,1);

	Ast *l = new Name_Expr_Ast(*a,1);
	Ast *r = new Mult_Expr_Ast(o1,o2,1);

	Ast *s = new Assignment_Stmt_Ast(l, r, 1);

	s->print_ast(4, cout, true);

	return 0;
}

#endif
