#include "Fit.h"

//testing r^2 method
//main funciton
int main(int, char**)
{
    //known result for vectors X={0.0,1.0,2.0,3.0,4.0,5.0} and Y={3.0,5.0,4.5,6.0,5.0,7.0}
    //exact (approx) result is calculetad by hand and calculator r^2=0.717127896
    const std::vector<double> X={0.0,1.0,2.0,3.0,4.0,5.0}, Y={3.0,5.0,4.5,6.0,5.0,7.0};

    //exact result
    double R_sq=0.717127896;
    double& R_sq_ref=R_sq;
    

    //r^2
    double r_sq=r_squared(X,Y);

    //test
    //test
    if(std::abs(R_sq_ref-r_sq)<1e-3)
    {
        return 0;
    }   
    else
    {
        return 1;
    }
}