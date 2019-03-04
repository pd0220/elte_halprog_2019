#include <iostream>
#include <cmath>

//find the square root of "num" by starting the iteration from "x0" using Newton's method (number of interations can be set too)
double sqrt_newton(double num,double x0,int iteration)
{    
    //argument check
    if(num<0)
    {
        std::cout<<"ERROR\nSquare root of a negative number is not interpreted on the plain of real numbers."<<std::endl;
        exit(-1);
    }

    if(x0<=0)
    {
        std::cout<<"ERROR\nInitial guess must be positive."<<std::endl;
        exit(-1);
    }

    if(iteration<=0)
    {
        std::cout<<"ERROR\nNumber of iterations are not enough."<<std::endl;
        exit(-1);
    }

    //"xi" will be the approximation for the square root of num after the iteration
    double xi;
    for(int i=0;i<=iteration;i++)
    {
        //applying Newton's method
        xi=x0-(x0*x0-num)/(2*x0);
        x0=xi;
    }
    return xi;
}

//convergence check
void convergence_check()
{
    std::cout<<"This program approximates the square root of a given number.\n"<<std::endl;
    std::cout<<"For checking precision of approximation the square root of 612.0 is 24.738633753705963298928.\n"<<std::endl;
    std::cout<<"Our initial guess for the test will be 10.0.\n"<<std::endl;
    double A=24.738633753705963298928;
    //comparison with exact result
    for(int n=1;n<=5;n++)
    {
        double result=sqrt_newton(612.0,10.0,n);
        std::cout<<"Numerical result after "<<n<<" step(s): "<<result<<std::endl;
        std::cout<<"Difference between mentioned and numerical result after "<<n<<" steps: "<<std::abs(A-result)<<".\n"<<std::endl;
    }
}

//main function
int main(int, char**)
{
    //set precision
    std::cout.precision(16);

    //convergence check
    convergence_check();

    //asking for parameters
    std::cout<<"Your number is:"<<std::endl;
    double num;
    std::cin>>num;
    
    std::cout<<"The iteration will start from an initial guess.\nYour initial guess is:"<<std::endl;
    double x0;
    std::cin>>x0;
        
    std::cout<<"You can set the number of iterations.\nNumber of iterations will be:"<<std::endl;
    int iteration;
    std::cin>>iteration;
    
    
    //result
    double num_sqrt=sqrt_newton(num,x0,iteration);
    std::cout<<"The approxiamte square root of "<<num<<" is "<<num_sqrt<<"."<<std::endl;
}
