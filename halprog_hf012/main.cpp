#include <iostream>
#include <math.h>

//numeric integration for previously determined function according to Newton-Cotes formula: Composite Trapezoidal Rule
//the function will be: f(x)=cos(x)*exp(-x^2) (from the website of the course)
double y(double x)
{
return cos(x)*exp(-x*x);
}

//integration function
double integrate(int n,double x0,double x1)
{
//h parameter
double h=(x1-x0)/n;
//result of the summation
double sum=0;
//summation
for(int i=1;i<=n-1;i++)
{
double x=x0+i*h;
sum+=y(x);
}
//the result will be stored in this variable
return h/2*(y(x0)+2*sum+y(x1));
}

//checking if the result converges when increasing the number of steps
void convergence_check(double x0,double x1)
{
std::cout<<"Checking for convergence:"<<std::endl;
for(int n=1;n<=10;n++)
{
std::cout<<"Integration result for "<<n<<" step(s): "<<integrate(n,x0,x1)<<std::endl;
}
}

//main function
int main(int, char**)
{
//set precision
std::cout.precision(16);
//asking for parameters
std::cout<<"This program numerically integrates the f(x)=cos(x)*exp(-x^2) function within given limits."<<std::endl;
std::cout<<"Your lower limit is:"<<std::endl;
double x0;
std::cin>>x0;
std::cout<<"Your upper limit"<<std::endl;
double x1;
std::cin>>x1;
//if upper limit is less than lower limit the program returns with error
if(x0>x1)
{
std::cout<<"ERROR\nUpper limit is less than lower limit."<<std::endl;
exit(-1);
}
std::cout<<"Number of steps between lower and upper limits:"<<std::endl;
int n;
std::cin>>n;
//if number of steps is less than 1 the program returns with error
if(n<0)
{
std::cout<<"ERROR\nNumber of steps is not enough."<<std::endl;
exit(-1);
}
//integration result
double result=integrate(n,x0,x1);
std::cout<<"The result of the integration is: "<<result<<"."<<std::endl;
/*
//check the convergence
convergence_check(x0,x1);
*/
}

