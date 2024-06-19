# include <stdio.h>
# include <argp.h>
# include <iostream>
# include <string>
# include <sstream>
# include <map>
# include <unordered_map>
# include <vector>
# include <assert.h>
#include <stdexcept>
# include "ast.hh"
# include "node-attributes.hh"

using namespace std;

struct Options {
	bool interpret=false;
	bool compile=false;
	bool show_ast=false;
	bool show_parse=false;
	bool show_tokens=false;
	bool sa_scan=false;
	bool sa_parse=false;
};

typedef enum {
		compiler,
		interpreter
	} lpmode;

typedef enum {
	PLUS,
	MINUS,
	MULT,
	DIV,
	UMINUS,
	COPY,
	} op_type;

extern struct argp_option options[]; 
extern lpmode mode;


Node_Attribute * process_ID(string * name);
Node_Attribute * process_NUM(string * name);
Node_Attribute * process_Expr(Node_Attribute *left, op_type op, Node_Attribute *right);
Node_Attribute * process_Asgn(string *lhs_name, Node_Attribute *rhs);
Node_Attribute * process_Stmt_List(Node_Attribute * na_list, Node_Attribute * na_ast);
Node_Attribute * init_Stmt_List(Node_Attribute * na_ast);
void process_finish(Node_Attribute *attr);
int parse_opt (int key, char *arg, struct argp_state *state);

bool show_tokens();
bool show_parse();
bool show_ast();
bool stop_after_scanning();
bool stop_after_parsing();
lpmode lp_mode();
bool semantic_analysis();
