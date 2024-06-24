#ifndef TYPE_INFO_HH
#define TYPE_INFO_HH

#include <string>

typedef enum
{
        INT8,
        INT32,
        FLOAT32
}var_type;

class Type_Info {
        var_type base_type;
        int dim_count = 0;
        int first_dim_size = 0;
        int second_dim_size = 0;

public:
        Type_Info (var_type bt);
        Type_Info (var_type bt, int nd, int fs, int ss);
        std::string base_type_name();
        var_type get_base_type();
        int get_number_of_dimensions();
        int get_size_of_first_dim();
        int get_size_of_second_dim();
        bool is_tensor_type();
        static void check_dim_size (int, int, int = 0);
};

#endif
