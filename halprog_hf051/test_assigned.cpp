#include "Matrix.hh"

//test assignments
//main function
int main(int,char**)
{
    //simple assignment
    matrix<double> m1{2,{3.1,2.3,1.1,6.5}};
    matrix<double> m2;
    m2=m1;
    mat_eq(m1,m2);

    //move assignment
    matrix<double> m3;
    m3=std::move(m1);
    mat_eq(m3,m2);
    mat_if0(m1);
    
    return 0;
}