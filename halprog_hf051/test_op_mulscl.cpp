#include "matrix.hh"

//multiplication by scalar test
//main function
int main(int,char**)
{
    //test matrix is m1={{4.5,3.4},{3.3,2.6}}
    //test scalar is a=1.2
    //ma_r=m1*a=ma={{5.4,4.08},{3.96,3.12}} from WolframAlpha
    //ma_l=a*m1=ma={{5.4,4.08},{3.96,3.12}}
    matrix<double> m11{{4.5,3.4,3.3,2.6}};
    matrix<double> m12{m11};
    double a{1.2};
    matrix<double> ma{{5.4,4.08,3.96,3.12}};

    //const& (from right)
    matrix<double> ma_r{m11*a};
    if(std::abs(ma(0,0)-ma_r(0,0))>1e-5 || std::abs(ma(0,1)-ma_r(0,1))>1e-5 || std::abs(ma(1,0)-ma_r(1,0))>1e-5 || std::abs(ma(1,1)-ma_r(1,1))>1e-5)
    {
        return 1;
    }

    //const& (from left)
    matrix<double> ma_l{a*m12};
    if(std::abs(ma(0,0)-ma_l(0,0))>1e-5 || std::abs(ma(0,1)-ma_l(0,1))>1e-5 || std::abs(ma(1,0)-ma_l(1,0))>1e-5 || std::abs(ma(1,1)-ma_l(1,1))>1e-5)
    {
        return 1;
    }

    //&& (from right)
    matrix<double> ma_r_ref{std::move(m11)*a};
    if(std::abs(ma(0,0)-ma_r_ref(0,0))>1e-5 || std::abs(ma(0,1)-ma_r_ref(0,1))>1e-5 || std::abs(ma(1,0)-ma_r_ref(1,0))>1e-5 || std::abs(ma(1,1)-ma_r_ref(1,1))>1e-5)
    {
        return 1;
    }

    //&& (from left)
    matrix<double> ma_l_ref{a*std::move(m12)};
    if(std::abs(ma(0,0)-ma_l_ref(0,0))>1e-5 || std::abs(ma(0,1)-ma_l_ref(0,1))>1e-5 || std::abs(ma(1,0)-ma_l_ref(1,0))>1e-5 || std::abs(ma(1,1)-ma_l_ref(1,1))>1e-5)
    {
        return 1;
    }

    return 0;
}