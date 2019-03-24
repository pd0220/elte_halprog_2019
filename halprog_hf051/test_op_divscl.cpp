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
    mat_eq(ma,ma_d);

    //&&
    matrix<double> ma_dref{std::move(m1)/a};
    mat_eq(ma,ma_dref);
    mat_if0(ma_dref);

    return 0;
}