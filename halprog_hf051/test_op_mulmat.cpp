#include "Matrix.hh"

//multiplication by matrix test
//main function
int main(int,char**)
{
     //test matrices are m1={{4.5,3.4},{3.3,2.6}}, m2={{5.5,2.4},{12.1,3.9}}
     //m1*m2=m3={{65.89,24.06},{49.61,18.06}} from WolframAlpha
     matrix<double> m1{2,{4.5,3.4,3.3,2.6}};
     matrix<double> m1_ref1{m1};
     matrix<double> m1_ref2{m1};
     matrix<double> m2{2,{5.5,2.4,12.1,3.9}};
     matrix<double> m2_ref1{m2};
     matrix<double> m2_ref2{m2};
     matrix<double> m3{2,{65.89,24.06,49.61,18.06}};

    //const& - const&
    matrix<double> mmul1{m1*m2};
    mat_eq(m3,mmul1);

    //const& - &&
    matrix<double> mmul2{m1*std::move(m2_ref1)};
    mat_eq(m3,mmul2);
    mat_if0(m2_ref1);

    //&& - const&
    matrix<double> mmul3={std::move(m1_ref1)*m2};
    mat_eq(m3,mmul3);
    mat_if0(m1_ref1);


    //&& - &&
    matrix<double> mmul4={std::move(m1_ref2)*std::move(m2_ref2)};
    mat_eq(m3,mmul4);
    mat_if0(m1_ref2);

    return 0;
}