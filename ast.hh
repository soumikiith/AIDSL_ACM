
/* 
	The base AST class is Ast. The class hierarchy is as described below:

	- Ast
		- Expression_Ast
	  		- Base_Expr_Ast
				- Name_Expr_Ast	
				- Number_Expr_Ast
			- Unary_Expr_Ast
				- UMinus_Expr_Ast
			- Binary_Expr_Ast
				- Plus_Expr_Ast
				- Minus_Expr_Ast
				- Div_Expr_Ast
				- Mult_Expr_Ast
		- Statement_Ast
			- Assignment_Stmt_Ast

*/

#ifndef AST_HH
#define AST_HH

#include<string>
#include<iostream>
#include<iomanip>
#include<typeinfo>
#include<list>

#define AST_INDENT 4
#define INDENT_INCR 2


using namespace std;

class LocIndex;

class Ast;

///////////////////////////////////// Main Base Classes /////////////////////////////

class Ast
{

public:
	Ast();
	~Ast();

	virtual void print_ast(int space_count, ostream & file_buffer, bool top_level) = 0;

	void print_spaces_on_new_line (int sc, ostream & file_buffer);
	void print_spaces (int sc, ostream & file_buffer);
};

class Empty_Ast: public Ast
{
public:
	virtual void print_ast(int space_count, ostream & file_buffer, bool top_level) {}
};

class Expression_Ast: public Ast
{
};

class Binary_Expr_Ast: public Expression_Ast
{
	Ast *left_child;
	Ast *right_child;

public:
	Ast * get_left_child();
	Ast * get_right_child();
	void set_left_child(Ast *l);
	void set_right_child(Ast *r);

	virtual void print_ast(int space_count, ostream & file_buffer, bool top_level) = 0;

};

class Unary_Expr_Ast: public Expression_Ast
{
	Ast *opd;

public:
	Ast * get_opd();
	void set_opd(Ast *l);

	virtual void print_ast(int space_count, ostream & file_buffer, bool top_level) = 0;
	
};

class Base_Expr_Ast: public Expression_Ast
{
public:

	virtual void print_ast(int space_count, ostream & file_buffer, bool top_level) = 0;
	
};


class Statement_Ast: public Ast
{
public:
	Statement_Ast();
	~Statement_Ast();
};


//////////////////////////////////////// Operand Classes    ///////////////////////////////////////

class Name_Expr_Ast: public Base_Expr_Ast
{

	string expr_name;
public:
	Name_Expr_Ast(string & name);
	~Name_Expr_Ast();

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

template <class T>
class Number_Expr_Ast: public Base_Expr_Ast
{
	T constant;

public:
	Number_Expr_Ast(T number);
	~Number_Expr_Ast();

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};


//////////////////////////////////////// Expression Classes ///////////////////////////////////////

//Arithmetic Expressions Support

class Plus_Expr_Ast: public Binary_Expr_Ast
{
public:
	Plus_Expr_Ast(Ast * l, Ast * r);
	~Plus_Expr_Ast() {}

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

class Minus_Expr_Ast: public Binary_Expr_Ast
{
public:
	Minus_Expr_Ast(Ast * l, Ast * r);
	~Minus_Expr_Ast() {}

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

class Div_Expr_Ast: public Binary_Expr_Ast
{
public:
	Div_Expr_Ast(Ast * l, Ast * r);
	~Div_Expr_Ast() {}

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

class Mult_Expr_Ast: public Binary_Expr_Ast
{
public:
	Mult_Expr_Ast(Ast * l, Ast * r);
	~Mult_Expr_Ast() {}

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

class UMinus_Expr_Ast: public Unary_Expr_Ast
{
public:
	UMinus_Expr_Ast(Ast * l);
	~UMinus_Expr_Ast() {}
	
	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

//////////////////////////////////////// Statement Classes  ///////////////////////////////////////

class StmtList_Stmt_Ast: public Statement_Ast
{
	Ast *lhs;
	Ast *rhs;
public:
	StmtList_Stmt_Ast(Ast * temp_lhs, Ast * temp_rhs);
	~StmtList_Stmt_Ast();

	Ast * get_lhs();
	Ast * get_rhs();
	void set_lhs(Ast *l);
	void set_rhs(Ast *r);

	void print_ast(int space_count, ostream & file_buffer, bool top_level);
};

class Assignment_Stmt_Ast: public Statement_Ast
{
	Ast *lhs;
	Ast *rhs;
public:
	Assignment_Stmt_Ast(Ast * temp_lhs, Ast * temp_rhs);
	~Assignment_Stmt_Ast();

	Ast * get_lhs();
	Ast * get_rhs();
	void set_lhs(Ast *l);
	void set_rhs(Ast *r);

	void print_ast(int space_count, ostream & file_buffer, bool top_level);

};

#endif
