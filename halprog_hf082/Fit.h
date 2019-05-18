#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>

//calculating square of given object
auto sq=[](auto x){return x*x;};

//calculating mean of values
double mean(const std::vector<double>& vec)
{
    //check if the number of elements is 0
    if(static_cast<int>(vec.size())==0)
    {
        std::cout<<"Error\nThe given vector is empty."<<std::endl;
        exit(-1);
    }

    //calculating mean of set of numbers from definition
    double x=std::accumulate(vec.begin(),vec.end(),0.0)/static_cast<double>(vec.size());

    return x;
}

//calculating mean of squared values
double mean_sq(const std::vector<double>& vec)
{
    //check if the number of elements is 0
    if(static_cast<int>(vec.size())==0)
    {
        std::cout<<"Error\nThe given vector is empty."<<std::endl;
        exit(-1);
    }

    //calculating mean
    double x_sq=std::accumulate(vec.begin(),vec.end(),0.0,[](double a,double b){return a+sq(b);})/static_cast<double>(vec.size());

    return x_sq;
}

//substrack mean, multiply and sum
//sum_i (x_i-mean_x)*(y_i-mean_y)
double prod(const std::vector<double>& X,const std::vector<double>& Y,const double mean_X, const double mean_Y)
{
    //substrack, multiply and sum
    double result=std::inner_product(X.begin(),X.end(),Y.begin(),0.0,[](double a,double b){return a+b;},[mean_X,mean_Y](double x,double y){return (x-mean_X)*(y-mean_Y);});

    return result;
}

//linear fit function
std::array<double,2> linear_fit(const std::vector<double>& X,const std::vector<double>& Y)
{
    //check if given vectors are the same size
    if(X.size()!=Y.size())
    {
        std::cout<<"Error\nNumber of elements must be equal int the given vectors."<<std::endl;
        exit(-2);
    }
    //check if the given vectors have enough elements to fit
    if(static_cast<int>(X.size())<=1)
    {
        std::cout<<"Error\nLinear fit cannot be made through one point."<<std::endl;
        exit(-3);
    }

    //means
    double mean_X=mean(X);
    double mean_Y=mean(Y);

    //calculating slope
    double b1=prod(X,Y,mean_X,mean_Y);
    double b2=prod(X,X,mean_X,mean_X);
    double b=b1/b2;

    //calculating y-intercept
    double m=mean_Y-b*mean_X;

    //result array
    return std::array<double,2> {b,m};
}

//r^2 function
double r_squared(const std::vector<double>& X,const std::vector<double>& Y)
{
    //check if given vectors are the same size
    if(X.size()!=Y.size())
    {
        std::cout<<"Error\nNumber of elements must be equal int the given vectors."<<std::endl;
        exit(-2);
    }
    //check if the given vectors have enough elements to fit
    if(static_cast<int>(X.size())<=1)
    {
        std::cout<<"Error\nLinear fit cannot be made through one point."<<std::endl;
        exit(-3);
    }
    //check if Y vector is constant --> r^2 would be NaN
    if(std::equal(Y.begin()+1,Y.end(),Y.begin()))
    {
        std::cout<<"Error\nVector Y is constant, r^2 cannot be calculated."<<std::endl;
        exit(-4);
    }

    //means of values
    double mean_X=mean(X);
    double mean_Y=mean(Y);

    //means of squared values
    double mean_X2=mean_sq(X);
    double mean_Y2=mean_sq(Y);

    //mixed mean value
    double mean_X_mean_Y=mean_X*mean_Y;

    //multiply vectors X and Y with each other then calculating mean
    double mean_XY=std::inner_product(X.begin(),X.end(),Y.begin(),0.0)/static_cast<double>(X.size());;

    //calculating r^2
    double r_sq=sq((mean_XY-mean_X_mean_Y)/std::sqrt((mean_X2-sq(mean_X))*(mean_Y2-sq(mean_Y))));
    
    return r_sq;
}