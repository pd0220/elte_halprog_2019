#include "matrix.hh"

//addtion test
//main function
int main(int,char**)
{
    //test matrices are m1={{4.5,3.4},{3.3,2.6}}, m2={{5.5,2.4},{12.1,3.9}}
    //m1+m2=m3={{10.0,5.8},{15.4,6.5}} from WolframAlpha
    matrix<double> m1{{4.5,3.4,3.3,2.6}};
    matrix<double> m1_ref1{m1};
    matrix<double> m1_ref2{m1};
    matrix<double> m2{{5.5,2.4,12.1,3.9}};
    matrix<double> m2_ref1{m2};
    matrix<double> m2_ref2{m2};
    matrix<double> m3{{10.0,5.8,15.4,6.5}};

    //const& - const&
    matrix<double> madd1{m1+m2};
    if(std::abs(m3(0,0)-madd1(0,0))>1e-5 || std::abs(m3(0,1)-madd1(0,1))>1e-5 || std::abs(m3(1,0)-madd1(1,0))>1e-5 || std::abs(m3(1,1)-madd1(1,1))>1e-5)
    {
        return 1;
    }

    //const& - &&
    matrix<double> madd2{m1+std::move(m2_ref1)};
    if(std::abs(m3(0,0)-madd2(0,0))>1e-5 || std::abs(m3(0,1)-madd2(0,1))>1e-5 || std::abs(m3(1,0)-madd2(1,0))>1e-5 || std::abs(m3(1,1)-madd2(1,1))>1e-5)
    {
        return 1;
    }

    //&& - const&
    matrix<double> madd3{std::move(m1_ref1)+m2};
    if(std::abs(m3(0,0)-madd3(0,0))>1e-5 || std::abs(m3(0,1)-madd3(0,1))>1e-5 || std::abs(m3(1,0)-madd3(1,0))>1e-5 || std::abs(m3(1,1)-madd3(1,1))>1e-5)
    {
        return 1;
    }

    //&& - &&
    matrix<double> madd4{std::move(m1_ref2)+std::move(m2_ref2)};
    if(std::abs(m3(0,0)-madd4(0,0))>1e-5 || std::abs(m3(0,1)-madd4(0,1))>1e-5 || std::abs(m3(1,0)-madd4(1,0))>1e-5 || std::abs(m3(1,1)-madd4(1,1))>1e-5)
    {
        return 1;
    }

    return 0;
}