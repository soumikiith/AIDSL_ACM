// C++ Program to implement
// template Array class
#include <iostream>
using namespace std;

template <typename T> class Tensor {
private:
    T* ptr;
    int dim;
    int row;
    int col;

public:
    int getDim()
    {
        return dim;
    }
    int getRow()
    {
        return row;
    }
    int getCol()
    {
        return col;
    }

    Tensor(int dim, int row, int col=1); //Parameterized Constructor
    Tensor(); //Default Constructor
    void output(); //Print tensor to stdout
    void assign(Tensor<T> t0);
    void set(int d, int r, int c); //set a tensor to a given dimension
    void assign(T t0);
    Tensor<T> trans(); //Transpose of a tensor
    Tensor<T> scalar_mul(T var); //scalar multiplication for tensors
    Tensor<T> scalar_div(T var); //scalar division for tensors
    Tensor<T> scalar_add(T var); //scalar addition for tensors
    Tensor<T> scalar_sub(T var); //scalar subtraction for tensors
    bool equals(Tensor<T> t0); //Check if two tensors are equal
    bool lt(Tensor<T> t0); //Check if one tensor is less than the other
    bool gt(Tensor<T> t0); //Check if one tensor is greater than the other
    bool leq(Tensor<T> t0); //Check if one tensor is less than or equal to the other
    bool geq(Tensor<T> t0); //Check if one tensor is greater than or equal to the other
    Tensor<T> add(Tensor<T> t0); //Add two tensors
    Tensor<T> sub(Tensor<T> t0); //Subtract two tensors
    Tensor<T> mul(Tensor<T> t0); //Multiply two tensors
    Tensor<T> div(Tensor<T> t0); //Divide two tensors
    Tensor<T> mm(Tensor<T> t0); //Matrix multiplication for two tensors
    Tensor<T> conv(Tensor<T> t0); //Matrix multiplication for two tensors
    T* operator[](size_t index) //Overload [] operator
    
    {
        return (ptr+index*col);
    }
    const T* operator[] (size_t index) const //Overload [] operator
    {
        return (ptr+index*col);
    }
    
    void operator=(Tensor<T> t0)//Assignment operator overload
    {
        this->assign(t0);
    }
    void operator=(T t0)//Assignment operator overload
    {
        this->assign(t0);
    }
    void input(); //Input tensor from stdin
    // Tensor<T> pre_incre();
    // Tensor<T> post_incre();
    // Tensor<T> pre_decre();
    // Tensor<T> post_decre();
    Tensor<T> negate();
};

// template <typename T> Tensor<T> Tensor<T>::pre_incre()
// {
//     Tensor<T> result(this->dim, this->row, this->col);
//     if(dim==1)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             ptr[i]++;
//             result.ptr[i] = ptr[i];
//         }
//     }
//     else if(dim==2)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             for(int j = 0; j<col; j++)
//             {
//                 *(ptr + i*col + j) = *(ptr + i*col + j) + 1;
//                 *(result.ptr + i*col + j) = *(ptr + i*col + j);
//             }
//         }
//     }
//     return result;
// }

// template <typename T> Tensor<T> Tensor<T>::post_incre()
// {
//     Tensor<T> result(this->dim, this->row, this->col);

//     if(dim==1)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             result.ptr[i] = this->ptr[i];
//             ptr[i]++;
//         }
//     }
//     else if(dim==2)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             for(int j = 0; j < col; j++)
//             {
//                 *(result.ptr + i*col + j) = *(ptr + i*col + j);
//                 *(ptr + i*col + j) = *(ptr + i*col + j) + 1;
//             }
//         }
//     }
//     return result;
// }

// template <typename T> Tensor<T> Tensor<T>::pre_decre()
// {
//     Tensor<T> result(this->dim, this->row, this->col);
//     if(dim==1)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             ptr[i]--;
//             result.ptr[i] = ptr[i];
//         }
//     }
//     else if(dim==2)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             for(int j = 0; j<col; j++)
//             {
//                 *(ptr + i*col + j) = *(ptr + i*col + j) - 1;
//                 *(result.ptr + i*col + j) = *(ptr + i*col + j);
//             }
//         }
//     }
//     return result;
// }

// template <typename T> Tensor<T> Tensor<T>::post_decre()
// {
//     Tensor<T> result(this->dim, this->row, this->col);
//     if(dim==1)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             result.ptr[i] = ptr[i];
//             ptr[i]--;
//         }
//     }
//     else if(dim==2)
//     {
//         for (int i = 0; i < row; i++)
//         {
//             for(int j = 0; j<col; j++)
//             {
//                 *(result.ptr + i*col + j) = *(ptr + i*col + j);
//                 *(ptr + i*col + j) = *(ptr + i*col + j) - 1;
//             }
//         }
//     }
//     return result;
// }

template <typename T> Tensor<T> Tensor<T>::negate()
{
    Tensor<T> result(this->dim, this->row, this->col);
    if(dim==1)
    {
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = -ptr[i];
        }
    }
    else if(dim==2)
    {
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
            {
                result[i*col+j] = -ptr[i*col+j];
            }
        }
    }
    return result;
}

template <typename T> void Tensor<T>::input()
{
    if(dim==1)
    {
        for (int i = 0; i < row; i++)
        {
	    cout <<"Give input element for index: "<<i<<"\n";
            cin >> ptr[i];
        }
    }
    else if(dim==2)
    {
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
		cout <<"Give input element for index: "<<i<<", "<<j<<"\n";
                cin >> ptr[i*col+j];
            }
        }
    }
}
//Default Constructor
template <typename T> Tensor<T>::Tensor()
{
    ptr = NULL;
    dim = 0;
    row = 0;
    col = 0;
}

//Parameterized Constructor
template <typename T> Tensor<T>::Tensor(int d, int r, int c)
{
    if(d==1)
    {
        ptr = (T*)malloc(r * sizeof(T));
        row = r;
        dim = d;
        col = 1;
    }
    else if(d==2)
    {
        ptr = (T*)malloc(r * c * sizeof(T));
        dim = d;
        row = r;
        col = c;
    }
    else
    {
        cout << "ERROR-while-allocation: Invalid dimension \n Only 2D and 1D are allowed. Have you given any other dimension ?" << endl;
        exit(1);
    }
}

//Set a tensor to a given dimension
template <typename T> void Tensor<T>::set(int d, int r, int c)
{
    if(d==1)
    {
        ptr = (T*)malloc(r * sizeof(T));
        row = r;
        dim = d;
        col = 1;
    }
    else if(d==2)
    {
        ptr = (T*)malloc(r * c * sizeof(T));
        dim=d;
        row = r;
        col = c;
    }
    else
    {
        cout << "ERROR-setter: Invalid dimension" << endl;
        exit(1);
    }
}

//Output a tensor
template <typename T> void Tensor<T>::output()
{
    if(dim==1)
    {
        for (int i = 0; i < row; i++)
            cout << " " << ptr[i];
        cout << endl;
    }
    else if(dim==2)
    {
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
                cout << " " << ptr[i*col + j];
            cout << endl;
        }
        cout << endl;
    }
}

//Less Than Operator
template <typename T> bool Tensor<T>::lt(Tensor<T> t0)
{
    int size_t1, size_t2;
    if(this->dim == 1)
    {
        size_t1 = this->row;
    }
    else if(this->dim == 2)
    {
        size_t1 = this->row * this->col;
    }
    if(t0.dim == 1)
    {
        size_t2 = t0.row;
    }
    else if(t0.dim == 2)
    {
        size_t2 = t0.row * t0.col;
    }
    if(size_t1 < size_t2)
    {
        return true;
    }
    return false;
}

//Greater Than Operator
template <typename T> bool Tensor<T>::gt(Tensor<T> t0)
{
    int size_t1, size_t2;
    if(this->dim == 1)
    {
        size_t1 = this->row;
    }
    else if(this->dim == 2)
    {
        size_t1 = this->row * this->col;
    }
    if(t0.dim == 1)
    {
        size_t2 = t0.row;
    }
    else if(t0.dim == 2)
    {
        size_t2 = t0.row * t0.col;
    }
    if(size_t1 > size_t2)
    {
        return true;
    }
    return false;
}

//Less Than or Equal Operator
template <typename T> bool Tensor<T>::leq(Tensor<T> t0)
{
    int size_t1, size_t2;
    if(this->dim == 1)
    {
        size_t1 = this->row;
    }
    else if(this->dim == 2)
    {
        size_t1 = this->row * this->col;
    }
    if(t0.dim == 1)
    {
        size_t2 = t0.row;
    }
    else if(t0.dim == 2)
    {
        size_t2 = t0.row * t0.col;
    }
    if(size_t1 <= size_t2)
    {
        return true;
    }
    return false;
}

//Greater Than or Equal Operator
template <typename T> bool Tensor<T>::geq(Tensor<T> t0)
{
    int size_t1, size_t2;
    if(this->dim == 1)
    {
        size_t1 = this->row;
    }
    else if(this->dim == 2)
    {
        size_t1 = this->row * this->col;
    }
    if(t0.dim == 1)
    {
        size_t2 = t0.row;
    }
    else if(t0.dim == 2)
    {
        size_t2 = t0.row * t0.col;
    }
    if(size_t1 >= size_t2)
    {
        return true;
    }
    return false;
}

//Addition Operator
template <typename T> Tensor<T> Tensor<T>::add(Tensor<T> t0)
{
    Tensor<T> result = Tensor<T>(this->dim, this->row, this->col);
    if(this->dim != t0.dim)
    {
        cout << "ERROR-element-wise-addition: Dimension mismatch" << endl;
        exit(1);
    }
    if(dim==1)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR-element-wise-addition: Row mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] + t0.ptr[i];
        }
    }
    else if(dim==2)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR-element-wise-addition: Row mismatch" << endl;
            exit(1);
        }
        if(this->col != t0.col)
        {
            cout << "ERROR-element-wise-addition: Column mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
                result.ptr[i*col+j] = this->ptr[i*col+j] + t0.ptr[i*col+j];
        }
    }
    return result;
}

//Subtraction Operator
template <typename T> Tensor<T> Tensor<T>::sub(Tensor<T> t0)
{
    Tensor<T> result = Tensor<T>(this->dim, this->row, this->col);
    if(this->dim != t0.dim)
    {
        cout << "ERROR-element-wise-subtraction: Dimension mismatch" << endl;
        exit(1);
    }
    if(dim==1)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR-element-wise-subtraction: Row mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] - t0.ptr[i];
        }
    }
    else if(dim==2)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR-element-wise-subtraction: Row mismatch" << endl;
            exit(1);
        }
        if(this->col != t0.col)
        {
            cout << "ERROR-element-wise-subtraction: Column mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
                result.ptr[i*col+j] = this->ptr[i*col+j] - t0.ptr[i*col+j];
        }
    }
    return result;
}

//Multiplication Operator
template <typename T> Tensor<T> Tensor<T>::mul(Tensor<T> t0)
{
    Tensor<T> result = Tensor<T>(this->dim, this->row, this->col);
    if(this->dim != t0.dim)
    {
        cout << "ERROR-element-wise-multiplication: Dimension mismatch" << endl;
        exit(1);
    }
    if(dim==1)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR-element-wise-multiplication: Row mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] * t0.ptr[i];
        }
    }
    else if(dim==2)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR-element-wise-multiplication: Row mismatch" << endl;
            exit(1);
        }
        if(this->col != t0.col)
        {
            cout << "ERROR-element-wise-multiplication: Column mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
                result.ptr[i*col+j] = this->ptr[i*col+j] * t0.ptr[i*col+j];
        }
    }
    return result;
}

//Division Operator
template <typename T> Tensor<T> Tensor<T>::div(Tensor<T> t0)
{
    Tensor<T> result = Tensor<T>(this->dim, this->row, this->col);
    if(this->dim != t0.dim)
    {
        cout << "ERROR: Dimension mismatch" << endl;
        exit(1);
    }
    if(dim==1)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR: Row mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            if(t0.ptr[i]==0)
            {
                cout << "ERROR: Division by zero" << endl;
                exit(1);
            }
            result.ptr[i] = this->ptr[i] / t0.ptr[i];
        }
    }
    else if(dim==2)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR: Row mismatch" << endl;
            exit(1);
        }
        if(this->col != t0.col)
        {
            cout << "ERROR: Column mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
            {
                if(t0.ptr[i*col+j]==0)
                {
                    cout << "ERROR: Division by zero" << endl;
                    exit(1);
                }
                result.ptr[i*col+j] = this->ptr[i*col+j] / t0.ptr[i*col+j];
            }
        }
    }
    return result;
}

template <typename T> void Tensor<T>::assign(Tensor<T> t0)
{
    if(this->dim != t0.dim)
    {
        cout << "ERROR while assigning: Dimension mismatch" << endl;
        exit(1);
    }
    if(dim==1)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR while assigning: Row mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            this->ptr[i] = t0.ptr[i];
        }
    }
    else if(dim==2)
    {
        if(this->row != t0.row)
        {
            cout << "ERROR while assigning: Row mismatch" << endl;
            exit(1);
        }
        if(this->col != t0.col)
        {
            cout << "ERROR while assigning: Column mismatch" << endl;
            exit(1);
        }
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
                this->ptr[i*col+j] = t0.ptr[i*col+j];
        }
    }
}

template <typename T> void Tensor<T>::assign(T t0)
{
    for(int i = 0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {
            this->ptr[i*col+j] = t0;
        }
    }
}

template <typename T> Tensor<T> Tensor<T>::conv(Tensor<T> t0)
{
    //implement 2D-Convolution
    Tensor<T> result(this->dim, this->row, this->col);
    int mid_row = t0.row/2;
    int mid_col = t0.col/2;
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < this->col; j++)
        {
            for (int k = 0; k < t0.row; k++)
            {
                for (int l = 0; l < t0.col; l++)
                {
                    int row_x = i+k-mid_row;
                    int row_y = j+l-mid_col;
                    if(row_x>=0 && row_x<this->row && row_y>=0 && row_y<this->col)
                    {
                        *(result.ptr+i*col+j) += *(ptr + row_x*col + row_y) * *(t0.ptr+k*t0.col+l);
                    }
                }
            }
        }
    }
    return result;
}

template <typename T> bool Tensor<T>::equals(Tensor<T> t0)
{
    if(this->dim != t0.dim)
    {
        return false;
    }
    if(dim==1)
    {
        if(this->row != t0.row)
        {
            return false;
        }
        for (int i = 0; i < row; i++)
        {
            if(this->ptr[i] != t0.ptr[i])
            {
                return false;
            }
        }
    }
    else if(dim==2){
        if(this->row != t0.row)
        {
            return false;
        }
        if(this->col != t0.col)
        {
            return false;
        }
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j<col; j++)
            {
                if(this->ptr[i*col+j] != t0.ptr[i*col+j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

template <typename T> Tensor<T> Tensor<T>::scalar_add(T var)
{
    if(dim==1)
    {
    	Tensor<T> result(this->dim, this->row, 1);
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] + var;
        }
        return result;
    }
    else if(dim==2)
    {
    	Tensor<T> result(this->dim, this->row, this->col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                *(result.ptr+i*col+j) =  *(ptr+i*col+j) + var;
            }
        }
        return result;
    }
}
template <typename T> Tensor<T> Tensor<T>::scalar_sub(T var)
{
    if(dim==1)
    {
    	Tensor<T> result(this->dim, this->row, 1);
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] - var;
        }
        return result;
    }
    else if(dim==2)
    {
    	Tensor<T> result(this->dim, this->row, this->col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                *(result.ptr+i*col+j) =  *(ptr+i*col+j) - var;
            }
        }
        return result;
    }
}

template <typename T> Tensor<T> Tensor<T>::scalar_div(T var)
{
    if(var==0)
    {
        cout << "ERROR: Division by zero" << endl;
        exit(1);
    }
    if(dim==1)
    {
    	Tensor<T> result(this->dim, this->row, 1);
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] / var;
        }
        return result;
    }
    else if(dim==2)
    {
	Tensor<T> result(this->dim, this->row, this->col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                *(result.ptr+i*col+j) =  *(ptr+i*col+j) / var;
            }
        }
        return result;
    }
}

template <typename T> Tensor<T> Tensor<T>::scalar_mul(T var)
{
    if(dim==1)
    {
    	Tensor<T> result(this->dim, this->row, 1);
        for (int i = 0; i < row; i++)
        {
            result.ptr[i] = this->ptr[i] * var;
        }
        return result;
    }
    else if(dim==2)
    {
    	Tensor<T> result(this->dim, this->row, this->col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                *(result.ptr+i*col+j) =  *(ptr+i*col+j) * var;
            }
        }
        return result;
    }
}

template <typename T> Tensor<T> Tensor<T>::mm(Tensor<T> t0)
{
    if(this->dim != 2 || t0.dim != 2)
    {
        cout << "ERROR: Dimension must be two: Matrix multiplication not possible" << endl;
        exit(1);
    }
    //implement matrix multiplication
    Tensor<T> result(this->dim, this->row, t0.col);
    if(this->col != t0.row)
    {
        cout << "ERROR: Matrix multiplication not possible" << endl;
        exit(1);
    }
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < t0.col; j++)
        {
            for (int k = 0; k < this->col; k++)
            {
                *(result.ptr+i*t0.col+j) += *(ptr+i*col+k) * *(t0.ptr+k*t0.col+j);
            }
        }
    }
    return result;
}

template <typename T> Tensor<T> Tensor<T>::trans()
{
    if(this->dim == 1)
    {
        Tensor<T> result(2, this->row, this->row);

        for (int i = 0; i < this->row; i++)
        {
            for(int j = 0; j < this->row; j++)
            {
                *(result.ptr+i*row+j) = 0;
            }
        }
        for(int i = 0; i < this->row; i++)
        {
            *(result.ptr+i*row) = *(ptr+i);
        }
        return result;
    }
    else if(this->dim == 2)
    {
        Tensor<T> result(this->dim, this->col, this->row);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->col; j++)
            {
                *(result.ptr+j*row+i) = *(ptr+i*col+j);
            }
        }
        return result;
    }
    
}
