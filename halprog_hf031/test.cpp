#include "Fit.h"

//test
//main funciton
int main(int, char**)
{
    //known result for vectors X={0.0,1.0,2.0,3.0,4.0,5.0} and Y={3.0,5.0,4.5,6.0,5.0,7.0}
    //fitted linear euation is y = 0.61428571*x + 3.54761905 from scipy.optimize.curve_fit python function
    const std::vector<double> X={0.0,1.0,2.0,3.0,4.0,5.0}, Y={3.0,5.0,4.5,6.0,5.0,7.0};

    //slope
    double B=0.61428571;
    double& B_ref=B;
    
    //y-intercept
    double M=3.54761905;
    double& M_ref=M;

    //linear fit
    std::array<double,2> result=linear_fit(X,Y);
    
    //test
    if(std::abs(B_ref-result[0])<1e-3 || std::abs(M_ref-result[1])<1.e-3)
    {
        return 0;
    }   
    else
    {
        return 1;
    }  
}
