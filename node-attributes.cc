# include "common-headers.hh"

using namespace std;


Node_Attribute::Node_Attribute(int v)  
{ 
	value=v;  
	ast = NULL; 
	ast_list = NULL;
}

Node_Attribute::Node_Attribute(Ast *a) 
{ 
	value=0; 
	ast=a; 
	ast_list = NULL;
}

Node_Attribute::Node_Attribute(list <Ast *> *l) 
{ 
	value=0; 
	ast=NULL; 
	ast_list = l;
}

int Node_Attribute::get_value() 	
{ 
	return value; 
}

Ast * Node_Attribute::get_ast()		
{ 	
	assert (ast!=NULL && "Attempt to extract NULL AST from a Node Attribute") ; 
 	return ast; 
}

list <Ast*> * Node_Attribute::get_ast_list()		
{ 	
	assert (ast_list!=NULL && "Attempt to extract NULL AST List from a Node Attribute") ; 
	return ast_list; 
}

void Node_Attribute::append_ast(Ast *a) 
{ 
	assert (a!=NULL && "Attempt to append NULL AST") ; 
	ast_list->push_back(a);
}

list <Ast*> * Node_Attribute::init_ast_list(Ast * a)	
{ 
	assert (a!=NULL && "Attempt to create list with NULL AST") ; 

	list <Ast*> *l = new list <Ast*>; 
	return l;
}
	

