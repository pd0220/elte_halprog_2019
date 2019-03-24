#include "matrix.hh"

//operator assignment test
//main function
int main(int,char**)
{
    //test matrices are m1={{4.5,3.4},{3.3,2.6}}, m2={{5.5,2.4},{12.1,3.9}}
    //test scalar is a=1.2
    matrix<double> m1{{4.5,3.4,3.3,2.6}};
    matrix<double> m2{{5.5,2.4,12.1,3.9}};
    double a=1.2;

    //+=
    //m1+m2=madd={{10.0,5.8},{15.4,6.5}} from WolframAlpha
    matrix<double> madd{{10.0,5.8,15.4,6.5,}};
    matrix<double> m1_cpy1{m1};
    m1_cpy1+=m2;
    if(std::abs(madd(0,0)-m1_cpy1(0,0))>1e-5 || std::abs(madd(0,1)-m1_cpy1(0,1))>1e-5 || std::abs(madd(1,0)-m1_cpy1(1,0))>1e-5 || std::abs(madd(1,1)-m1_cpy1(1,1))>1e-5)
    {
        return 1;
    }

    //-=
    //m1-m2=msub={{-1.0,1.0},{-8.8,-1.3}} from WolframAlpha
    matrix<double> msub{{-1.0,1.0,-8.8,-1.3}};
    matrix<double> m1_cpy2{m1};
    m1_cpy2-=m2;
    if(std::abs(msub(0,0)-m1_cpy2(0,0))>1e-5 || std::abs(msub(0,1)-m1_cpy2(0,1))>1e-5 || std::abs(msub(1,0)-m1_cpy2(1,0))>1e-5 || std::abs(msub(1,1)-m1_cpy2(1,1))>1e-5)
    {
        return 1;
    }

    //*= (scalar)
    //m1*a=mmul_slc={{5.4,4.08},{3.96,3.12}} from WolframAlpha
    matrix<double> mmul_slc{{5.4,4.08,3.96,3.12}};
    matrix<double> m1_cpy3{m1};
    m1_cpy3*=a;
    if(std::abs(mmul_slc(0,0)-m1_cpy3(0,0))>1e-5 || std::abs(mmul_slc(0,1)-m1_cpy3(0,1))>1e-5  || std::abs(mmul_slc(1,0)-m1_cpy3(1,0))>1e-5 || std::abs(mmul_slc(1,1)-m1_cpy3(1,1))>1e-5)
    {
        return 1;
    }


    //*= (matrix)
    //m1*m2=mmul_mat={{65.89,24.06},{49.61,18.06}} from WolframAlpha
    matrix<double> mmul_mat{{65.89,24.06,49.61,18.06}};
    matrix<double> m1_cpy4{m1};
    m1_cpy4*=m2;
    if(std::abs(mmul_mat(0,0)-m1_cpy4(0,0))>1e-5 || std::abs(mmul_mat(0,1)-m1_cpy4(0,1))>1e-5 || std::abs(mmul_mat(1,0)-m1_cpy4(1,0))>1e-5 || std::abs(mmul_mat(1,1)-m1_cpy4(1,1))>1e-5)
    {
        return 1;
    }


    ///= (scalar)
    //m1/a=mdiv={{3.75,2.83333},{2.75,2.16667}} from WolframAlpha
    matrix<double> mdiv{{3.75,2.83333,2.75,2.16667}};
    matrix<double> m1_cpy5{m1};
    m1_cpy5/=a;
    if(std::abs(mdiv(0,0)-m1_cpy5(0,0))>1e-5 || std::abs(mdiv(0,1)-m1_cpy5(0,1))>1e-5 || std::abs(mdiv(1,0)-m1_cpy5(1,0))>1e-5 || std::abs(mdiv(1,1)-m1_cpy5(1,1))>1e-5)
    {
        return 1;
    }

    return 0;
}