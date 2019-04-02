#include "Matrix.hh"

//addtion test
//main function
int main(int,char**)
{
    //test matrices are m1={{4.5,3.4},{3.3,2.6}}, m2={{5.5,2.4},{12.1,3.9}}
    //m1+m2=m3={{10.0,5.8},{15.4,6.5}} from WolframAlpha
    matrix<double> m1{2,{4.5,3.4,3.3,2.6}};
    matrix<double> m1_ref1{m1};
    matrix<double> m1_ref2{m1};
    matrix<double> m2{2,{5.5,2.4,12.1,3.9}};
    matrix<double> m2_ref1{m2};
    matrix<double> m2_ref2{m2};
    matrix<double> m3{2,{10.0,5.8,15.4,6.5}};

    //const& - const&
    matrix<double> madd1{m1+m2};
    mat_eq(m3,madd1);

    //const& - &&
    matrix<double> madd2{m1+std::move(m2_ref1)};
    mat_eq(m3,madd2);
    mat_if0(m2_ref1);

    //&& - const&
    matrix<double> madd3{std::move(m1_ref1)+m2};
    mat_eq(m3,madd3);
    mat_if0(m1_ref1);

    //&& - &&
    matrix<double> madd4{std::move(m1_ref2)+std::move(m2_ref2)};
    mat_eq(m3,madd4);
    mat_if0(m1_ref2);
  
    return 0;
}