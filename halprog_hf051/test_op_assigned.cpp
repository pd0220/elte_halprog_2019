#include "matrix.hh"

//operator assignment test
//main function
int main(int,char**)
{
    //test matrices are m1={{4.5,3.4},{3.3,2.6}}, m2={{5.5,2.4},{12.1,3.9}}
    //test scalar is a=1.2
    matrix<double> m1{2,{4.5,3.4,3.3,2.6}};
    matrix<double> m2{2,{5.5,2.4,12.1,3.9}};
    double a=1.2;

    //+=
    //m1+m2=madd={{10.0,5.8},{15.4,6.5}} from WolframAlpha
    matrix<double> madd{2,{10.0,5.8,15.4,6.5,}};
    matrix<double> m1_cpy1{m1};
    m1_cpy1+=m2;
    mat_eq(madd,m1_cpy1);

    //-=
    //m1-m2=msub={{-1.0,1.0},{-8.8,-1.3}} from WolframAlpha
    matrix<double> msub{2,{-1.0,1.0,-8.8,-1.3}};
    matrix<double> m1_cpy2{m1};
    m1_cpy2-=m2;
    mat_eq(msub,m1_cpy2);

    //*= (scalar)
    //m1*a=mmul_slc={{5.4,4.08},{3.96,3.12}} from WolframAlpha
    matrix<double> mmul_slc{2,{5.4,4.08,3.96,3.12}};
    matrix<double> m1_cpy3{m1};
    m1_cpy3*=a;
    mat_eq(mmul_slc,m1_cpy3);

    //*= (matrix)
    //m1*m2=mmul_mat={{65.89,24.06},{49.61,18.06}} from WolframAlpha
    matrix<double> mmul_mat{2,{65.89,24.06,49.61,18.06}};
    matrix<double> m1_cpy4{m1};
    m1_cpy4*=m2;
    mat_eq(mmul_mat,m1_cpy4);

    ///= (scalar)
    //m1/a=mdiv={{3.75,2.83333},{2.75,2.16667}} from WolframAlpha
    matrix<double> mdiv{2,{3.75,2.8333333333333333,2.75,2.1666666666666667}};
    matrix<double> m1_cpy5{m1};
    m1_cpy5/=a;
    mat_eq(mdiv,m1_cpy5);

    return 0;
}