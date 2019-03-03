#include <iostream>
#include <cmath>

//Newton's method to find the root of a given function
template<typename F,typename dF,typename CheckF,typename T>
double Newton(F f,dF df,T x0,CheckF checkf)
{
    //the result will be stored in this variable
    T xi;
    for(int i=0;;i++)
    {
        xi=x0-f(x0)/df(x0);
        if(checkf(xi,x0)==false)
        {
            break;
        }
        x0=xi;
    }
    return xi;
}

//check for limit to minimize number of iterations
bool check_iteration(double xi,double x0)
{
    double lim=1e-14;
    return std::abs(xi-x0)>lim;  
}

//main function
int main(int, char**)
{
    //set precision
    std::cout.precision(15);
    
    //result
    //squre root of 612.0
    double result=Newton([](double x){return x*x-612;},[](double x){return 2.0*x;},10.0,check_iteration);
    std::cout<<result<<std::endl; 
}
