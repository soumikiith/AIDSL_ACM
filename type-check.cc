#include "common-headers.hh"
#include "ast.hh"

static bool types_same_p(Type_Info *type1, Type_Info *type2) {
    // Implement this function
    return false;
}

void type_check_assign(string name, Ast *rhs) {

    auto it = symtab.find(name);
    if (it == symtab.end()) {
        cerr << "Error: Variable " << name << " is undefined\n";
        exit(1);
    }

    Type_Info *id_type_info = it->second;
    assert(id_type_info);

    Type_Info *rhs_type_info = rhs->get_type_info();
    assert(rhs_type_info);

    if (!types_same_p(id_type_info, rhs_type_info)) {
        cerr << "Error: Types do not match for assignment\n";
        exit(1);
    }
}
