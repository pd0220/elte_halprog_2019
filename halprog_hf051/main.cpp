#include "matrix.hh"

//main function
int main(int,char**)
{
    //ostream test
    matrix<double> m1([](int i,int j){return i+j;},4);
    std::cout<<m1<<std::endl;
    
    return 0;
} 