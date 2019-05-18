#include "Fit.h"

//main function
int main(int, char**)
{
    //given vectors
    const std::vector<double> X={1.0,2.0,3.0}, Y={1.0,1.8,2.9};
    
    //linear fit
    std::array<double,2> result=linear_fit(X,Y);

    //r^2
    double r_sq=r_squared(X,Y);
    
    //printing the equation of the fitted linear function
    std::cout<<"Equation of the fitted linear function:\ny(x) = "<<result[0]<<"*x + "<<result[1]<<std::endl;
    std::cout<<"Value of r^2 is: "<<r_sq<<std::endl;
    
    return 0;
}