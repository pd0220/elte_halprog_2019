#include "Matrix.hh"

//iostream test
//main function
int main(int,char**)
{
     //test matrix is m1={{4.5,3.4},{3.3,2.6}}
    matrix<double> m1{2,{4.5,3.4,3.3,2.6}};
    
    std::stringstream ss1;
    ss1<<m1;
    std::string s1=ss1.str();
    
    matrix<double> m2(2);
    ss1>>m2;
    mat_eq(m1,m2);

    //test string will be str1("2;1.1,2.2,3.3,4.4")
    //test matrix will be x_ref={{1.1,2.2},{3.3,4.4}}
    std::string str("2;1.1,2.2,3.3,4.4");
    matrix<double> x_ref{2,{1.1,2.2,3.3,4.4}};
    std::stringstream ss_1;
    ss_1<<str;

    matrix<double> x(2);
    ss_1>>x;

    mat_eq(x,x_ref);

    //test vector will be y={{3.14,42.1},{44.3,44.2}}
    //test string will be str_ref("2;3.14,42.1,44.3,44.2")
    matrix<double> y{2,{3.14,42.1,44.3,44.2}};
    std::stringstream ssy;
    ssy<<y;
    std::string str_ref("2;3.14,42.1,44.3,44.2");

    if(str_ref!=ssy.str())
    {
        std::cout<<"prob"<<std::endl;
        return 1;
    }
    
    return 0;
}