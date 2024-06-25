#ifndef COMMON_HEADERS_HH
#define COMMON_HEADERS_HH

# include <stdio.h>
# include <argp.h>
# include <iostream>
# include <string>
# include <sstream>
# include <map>
# include <unordered_map>
# include <vector>
# include <assert.h>
# include <stdexcept>
# include "ast.hh"
# include "type-info.hh"

using namespace std;

struct Options {
	bool interpret=false;
	bool compile=false;
	bool show_ast=false;
	bool show_parse=false;
	bool show_tokens=false;
	bool show_symtab=false;
	bool sa_scan=false;
	bool sa_parse=false;
};

typedef enum {
	compiler,
} lpmode;

typedef enum {
	PLUS,
	MINUS,
	MULT,
	DIV,
	MATMUL,
	UMINUS,
	COPY,
} op_type;

extern struct argp_option options[]; 
extern lpmode mode;
extern unordered_map<string, Type_Info *> symtab;

Ast * process_ID(string * name);
Ast * process_NUM(string * name);
Ast * process_Expr(Ast *left, op_type op, Ast *right);
Ast * process_Asgn(string *lhs_name, Ast *rhs);
list<Ast *> * process_Stmt_List(list<Ast *> * ast_list, Ast *ast);
list<Ast *> * init_Stmt_List(Ast *ast);
int parse_opt (int key, char *arg, struct argp_state *state);

bool show_tokens();
bool show_parse();
bool show_ast();
bool stop_after_scanning();
bool stop_after_parsing();
lpmode lp_mode();
bool semantic_analysis();
int checked_stoi (string);

void type_check_assign(string, Ast *);
Type_Info *type_check_binary (Ast *, Ast *, string);
Type_Info *type_check_mult (Ast *, Ast *);
Type_Info *type_check_matmul (Ast *, Ast *);

void code_gen(list<Ast *> *);
string mangle_name(string);

#endif
