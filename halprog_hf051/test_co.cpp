#include "matrix.hh"

//test for constructors
//main function
int main(int,char**)
{
    //default
    matrix<double> m_default;
    mat_if0(m_default);
    if(m_default.cend()!=m_default.cbegin() || m_default.end()!=m_default.begin())
    {
        return 1;
    }

    //list initialization and indexing
    matrix<double> m1{2,{3.1,2.3,1.1,6.5}};
    if(m1.size()!=4 || m1(0,0)!=3.1 || m1(0,1)!=2.3 || m1(1,0)!=1.1 || m1(1,1)!=6.5 || m1.N!=2)
    {
        return 1;
    }

    //copy
    matrix<double> m1_cpy{m1};
    mat_eq(m1,m1_cpy);

    //move
    matrix<double> m2{m1};
    matrix<double> m3{std::move(m2)};
    mat_eq(m3,m1);
    mat_if0(m2);

    //function of indexes
    matrix<double> m4([](int i,int j){ return i+j;},2);
    if(m4.size()!=4 || m4.N!=2 || m4(0,0)!=0 || m4(0,1)!=1 || m4(1,0)!=1 || m4(1,1)!=2)
    {
        return 1;
    }

    return 0;
}