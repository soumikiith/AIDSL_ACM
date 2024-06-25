#include "ast.hh"
#include "common-headers.hh"
#include <string>
#include <iostream>
#include <fstream>

// genf will contain the resulting C++ code-gen by writing to out.cpp
static ofstream genf;

/* If identifier name happnes to be a C++ keyword, we need to 
   "mangle it", ie, suffix it so that it doesn't clash.
   For eg if identifier in our langauge is for,
   that would not be a valid C++ identifier since "for" is reserved keyword in C++.
   So we suffix it with _1 and change the name to "for_1".  */
string mangle_name(string name)
{
	return name + "_1";
}

static void
gen_prologue()
{
	genf << "int main()\n{\n";
}

static void
gen_epilogue()
{
	genf << "}\n";
}

static void
gen_decl(string name, Type_Info *type_info)
{
	if (!type_info->is_tensor_type())
	{
		// Generate scalar declaration of following form:
		// base_type<space>id_name<space>';'

		switch (type_info->get_base_type())
		{
			case INT32: genf << "int"; break;
			case INT8: genf << "char"; break;
			default: assert (0);
		}

		genf << " ";
		genf << mangle_name(name);
		genf << ";\n";
	}
}

static void
gen_declarations()
{
	for (auto& pair: symtab)
		gen_decl(pair.first, pair.second);
}

static void
gen_stmts (list<Ast *> *ast_stmt_list)
{
	if (!ast_stmt_list)
		return;
	for (Ast *ast: *ast_stmt_list)
	{
		ast->gencode(genf);
		if (!dynamic_cast<Empty_Ast *> (ast))
			genf << ";\n";		
	}
}

void code_gen(list<Ast *> *ast_stmt_list)
{
	genf.open("out.cpp");
	gen_prologue();
	gen_declarations();
	gen_stmts (ast_stmt_list);	
	gen_epilogue();
}
