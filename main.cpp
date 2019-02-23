#include <iostream>
#include <math.h>

//find the square root of "num" by starting the iteration from "x0" using Newton's method (number of interations can be set too)
double sqrt_newton(double num,double x0,int iteration)
{
    //"xi" will be the approximation for the square root of num after the iteration
    double xi;
    for(int i;i<=iteration;i++)
    {
        //applying Newton's method
        xi=x0-(x0*x0-num)/(2*x0);
        x0=xi;
    }
    return xi;
}

//main function
int main(int, char**)
{
    //set precision
    std::cout.precision(16);
    //asking for parameters
    std::cout<<"This program approximates the square root of a given number.\nYour number is:"<<std::endl;
    double num;
    std::cin>>num;
    std::cout<<"The iteration will start from an inital guess.\nYour inital guess is:"<<std::endl;
    double x0;
    std::cin>>x0;
    std::cout<<"You can set the number of iterations.\nNumber of iterations will be:"<<std::endl;
    int iteration;
    std::cin>>iteration;
    //result
    double num_sqrt=sqrt_newton(num,x0,iteration);
    std::cout<<"The approxiamte square root of "<<num<<" is "<<num_sqrt<<"."<<std::endl;
}
