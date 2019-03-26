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
    mat_eq(ma,ma_r);

    //const& (from left)
    matrix<double> ma_l{a*m12};
    mat_eq(ma,ma_l);

    //&& (from right)
    matrix<double> ma_r_ref{std::move(m11)*a};
    mat_eq(ma,ma_r_ref);
    mat_if0(m11);

    //&& (from left)
    matrix<double> ma_l_ref{a*std::move(m12)};
    mat_eq(ma,ma_l_ref);
    mat_if0(m12);

    return 0;
}