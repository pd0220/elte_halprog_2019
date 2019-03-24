#include "matrix.hh"

//test for constructors
//main function
int main(int,char**)
{
    //default
    matrix<double> m_default;
    if(m_default.size()!=0 || m_default.cend()!=m_default.cbegin() || m_default.end()!=m_default.begin() || m_default.N!=0)
    {
        return 1;
    }

    //list initialization and indexing
    matrix<double> m1{{3.1,2.3,1.1,6.5}};
    if(m1.size()!=4 || m1(0,0)!=3.1 || m1(0,1)!=2.3 || m1(1,0)!=1.1 || m1(1,1)!=6.5 || m1.N!=2)
    {
        return 1;
    }

    //copy
    matrix<double> m1_cpy{m1};
    if(m1_cpy.size()!=4 || m1_cpy(0,0)!=m1(0,0) || m1_cpy(0,1)!=m1(0,1) || m1_cpy(1,0)!=m1(1,0) || m1_cpy(1,1)!=m1(1,1) || m1_cpy.N!=m1.N)
    {
        return 1;
    }

    //move
    matrix<double> m2{m1};
    matrix<double> m3{std::move(m2)};
    if(m2.size()!=0 || m3.size()!=4 || m3(0,0)!=3.1 || m3(0,1)!=2.3 || m3(1,0)!=1.1 || m3(1,1)!=6.5 || m3.N!=m2.N)
    {
        return 1;
    }

    //function of indexes
    matrix<double> m4([](int i){ return i+1; }, 4);
    if(m4.size()!=4 || m4.N!=2 || m4(0,0)!=1 || m4(0,1)!=2 || m4(1,0)!=3 || m4(1,1)!=4)
    {
        return 1;
    }

    return 0;
}