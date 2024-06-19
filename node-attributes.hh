#include "ast.hh"

using namespace std;


// This class stores the attributes of the nodes creted during parsing.
class Node_Attribute 	
{	
	int value;		// Relevant only for interpretation
	Ast * ast;      	// Relevant only for compilation
	list <Ast *> *ast_list;	// Relevant only for compilation

   public:
	Node_Attribute() { }
	Node_Attribute(int v);
	Node_Attribute(Ast *a);
	Node_Attribute(list <Ast *> *l);
	~Node_Attribute();

	int get_value();
	Ast * get_ast();
	list <Ast*> * get_ast_list();
	void append_ast(Ast *a);
	list <Ast*> * init_ast_list(Ast * a);
	
};

