#include "matrix.hh"

//main function
int main(int,char**)
{
    //ostream test
    matrix<double> m1([](int i){ return i+1; }, 9);
    std::cout<<m1<<std::endl;
    return 0;
} 