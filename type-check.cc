#include "common-headers.hh"
#include "ast.hh"

static bool
types_same_p (Type_Info *type1, Type_Info *type2)
{
	return (type1->get_base_type () == type2->get_base_type ()
		&& type1->get_number_of_dimensions () == type2->get_number_of_dimensions ()
		&& type1->get_size_of_first_dim () == type2->get_size_of_first_dim()
		&& type2->get_size_of_second_dim () == type2->get_size_of_second_dim());
}

void type_check_assign (string name, Ast *rhs)
{
	
	auto it = symtab.find (name);
	if (it == symtab.end ())
  	{
		cerr << "Error: Variable " << name << " is undefined\n";
		exit (1);
	}

	Type_Info *id_type_info = it->second; 
	assert (id_type_info);

	Type_Info *rhs_type_info = rhs->get_type_info ();
	assert (rhs_type_info);

	if (!types_same_p (id_type_info, rhs_type_info)) 
	{
		cerr << "Error: Types do not match for assignment\n";
		exit (1);
	}
}

Type_Info *
type_check_binary (Ast *left, Ast *right, string op_name)
{
	Type_Info *left_type = left->get_type_info();
	assert (left_type);

	Type_Info *right_type = right->get_type_info();
	assert (right_type);

	if (!types_same_p (left_type, right_type))
	{
		// TODO: Improve diagnostic
		cerr << "Error: Types do not match for binary operator " << op_name << "\n";
		exit (1);
	}

	return left_type;
}

Type_Info *
type_check_mult (Ast *left, Ast *right)
{
	Type_Info *left_type = left->get_type_info();
	assert (left_type);

	Type_Info *right_type = right->get_type_info();
	assert (right_type);

	// FIXME: Rewrite this to make it less verbose
	if (types_same_p (left_type, right_type))
		return left_type;
	else if (left_type->is_tensor_type () && !right_type->is_tensor_type())
	{
		if (left_type->get_base_type() != right_type->get_base_type())
		{
			cerr << "Error: Tensor and scalar have different base type\n";
			exit (1);
		}
		return left_type;
	} 
	else if (right_type->is_tensor_type () && !left_type->is_tensor_type())
	{
		if (right_type->get_base_type() != left_type->get_base_type())
		{
			cerr << "Error: Scalar and Tensor have different base type\n";
			exit (1);
		}
		return right_type;
	} 
	else
	{
		cerr << "Error: Invalid operands to multiply operator\n";
		exit (1);
	}
}

Type_Info *
type_check_matmul(Ast *left, Ast *right)
{
	Type_Info *left_type_info = left->get_type_info();
	assert (left_type_info);

	Type_Info *right_type_info = right->get_type_info();
	assert (right_type_info);

	if (!left_type_info->is_tensor_type()
	    || !right_type_info->is_tensor_type())
	{
		cerr << "Error: Operands for matmul should have tensor type\n";
		exit (1);
	}

	if (left_type_info->get_number_of_dimensions() != 2
	    || right_type_info->get_number_of_dimensions() != 2)
	{
		cerr << "Error: Tensor operands for matmul should have 2 dimensions\n";
		exit (1);
	}

	if (left_type_info->get_base_type() != right_type_info->get_base_type())
	{
		cerr << "Error: Base type for tensor operands do not match\n";
		exit (1);
	}

	if (left_type_info->get_size_of_second_dim() != right_type_info->get_size_of_first_dim())
	{
		cerr << "Error: Second dim of first tensor should match first dim of second tensor\n";
		exit (1);
	}

	var_type base_type = left_type_info->get_base_type();
	int fs = left_type_info->get_size_of_first_dim();
	int ss = right_type_info->get_size_of_second_dim();
	Type_Info *result_type_info = new Type_Info (base_type, 2, fs, ss);
	assert (result_type_info);
	return result_type_info;
} 
