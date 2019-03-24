#include "matrix.hh"

//multiplication by matrix test
//main function
int main(int,char**)
{
     //test matrices are m1={{4.5,3.4},{3.3,2.6}}, m2={{5.5,2.4},{12.1,3.9}}
     //m1*m2=m3={{65.89,24.06},{49.61,18.06}} from WolframAlpha
     matrix<double> m1{{4.5,3.4,3.3,2.6}};
     matrix<double> m1_ref1{m1};
     matrix<double> m1_ref2{m1};
     matrix<double> m2{{5.5,2.4,12.1,3.9}};
     matrix<double> m2_ref1{m2};
     matrix<double> m2_ref2{m2};
     matrix<double> m3{{65.89,24.06,49.61,18.06}};

     //const& - const&
     matrix<double> mmul1{m1*m2};
     if(std::abs(m3(0,0)-mmul1(0,0))>1e-5 || std::abs(m3(0,1)-mmul1(0,1))>1e-5 || std::abs(m3(1,0)-mmul1(1,0))>1e-5 || std::abs(m3(1,1)-mmul1(1,1))>1e-5)
     {
        return 1;
     }

    //const& - &&
    matrix<double> mmul2{m1*std::move(m2_ref1)};
    if(std::abs(m3(0,0)-mmul2(0,0))>1e-5 || std::abs(m3(0,1)-mmul2(0,1))>1e-5 || std::abs(m3(1,0)-mmul2(1,0))>1e-5 || std::abs(m3(1,1)-mmul2(1,1))>1e-5)
    {
        return 1;
    }

    //&& - const&
    matrix<double> mmul3={std::move(m1_ref1)*m2};
    if(std::abs(m3(0,0)-mmul3(0,0))>1e-5 || std::abs(m3(0,1)-mmul3(0,1))>1e-5 || std::abs(m3(1,0)-mmul3(1,0))>1e-5 || std::abs(m3(1,1)-mmul3(1,1))>1e-5)
    {
        return 1;
    }

    //&& - &&
    matrix<double> mmul4={std::move(m1_ref2)*std::move(m2_ref2)};
    if(std::abs(m3(0,0)-mmul4(0,0))>1e-5 || std::abs(m3(0,1)-mmul4(0,1))>1e-5 || std::abs(m3(1,0)-mmul4(1,0))>1e-5 || std::abs(m3(1,1)-mmul4(1,1))>1e-5)
    {
        return 1;
    }

    return 0;
}