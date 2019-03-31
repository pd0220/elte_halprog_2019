#include "matrix.hh"

//iostream test
//main function
int main(int,char**)
{
    //test matrix is m1={{4.5,3.4},{3.3,2.6}}
    matrix<double> m1{2,{4.5,3.4,3.3,2.6}};
    
    std::stringstream ss1;
    ss1<<m1;
    std::string s1=ss1.str();
    
    matrix<double> m2(2);
    ss1>>m2;
    mat_eq(m1,m2);

    return 0;
}