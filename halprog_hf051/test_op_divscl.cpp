#include "matrix.hh"

//multiplication by scalar test
//main function
int main(int,char**)
{
    //test matrix is m1={{4.5,3.4},{3.3,2.6}}
    //test scalar is a=1.2
    //ma=m1/a={{3.75,2.83333},{2.75,2.16667}} from WolframAlpha
    matrix<double> m1{{4.5,3.4,3.3,2.6}};
    double a{1.2};
    matrix<double> ma{{3.75,2.83333,2.75,2.16667}};

    //const&
    matrix<double> ma_d{m1/a};
    if(std::abs(ma(0,0)-ma_d(0,0))>1e-5 || std::abs(ma(0,1)-ma_d(0,1))>1e-5 || std::abs(ma(1,0)-ma_d(1,0))>1e-5 || std::abs(ma(1,1)-ma_d(1,1))>1e-5)
    {
        return 1;
    }

    //&&
    matrix<double> ma_dref{std::move(m1)/a};
    if(std::abs(ma(0,0)-ma_dref(0,0))>1e-5 || std::abs(ma(0,1)-ma_dref(0,1))>1e-5 || std::abs(ma(1,0)-ma_dref(1,0))>1e-5 || std::abs(ma(1,1)-ma_dref(1,1))>1e-5)
    {
        return 1;
    }

    return 0;
}