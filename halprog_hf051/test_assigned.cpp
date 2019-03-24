#include "matrix.hh"

//test assignments
//main function
int main(int,char**)
{
    //simple assignment
    matrix<double> m1{{3.1,2.3,1.1,6.5}};
    matrix<double> m2;
    m2=m1;
    if(m1.size()!=m2.size() || m1.N!=m2.N || m1(0,0)!=m2(0,0) || m1(0,1)!=m2(0,1) || m1(1,0)!=m2(1,0) || m1(1,1)!=m2(1,1))
    {
        return 1;
    }

    //move assignment
    matrix<double> m3;
    m3=std::move(m1);
    if(m1.size()!=0 || m1.N!=m3.N || m3.size()!=4 || m3(0,0)!=3.1 || m3(0,1)!=2.3 || m3(1,0)!=1.1 || m3(1,1)!=6.5)
    {
        return 1;
    }

    return 0;
}