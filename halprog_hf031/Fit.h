#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>

//calculating mean
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
    if(static_cast<int>(X.size())==1 || static_cast<int>(Y.size())==1)
    {
        std::cout<<"Error\nLinear fit cannot be made through one point."<<std::endl;
        exit(-3);
    }

    //means and difference vectors
    double mean_X=mean(X);
    double mean_Y=mean(Y);
    std::vector<double> X_alt, Y_alt;

    //allocating space
    X_alt.resize(X.size());
    Y_alt.resize(Y.size());

    //setting differece vectors via calculated means of vectors
    std::transform(X.begin(),X.end(),X_alt.begin(),[mean_X](double x){return x-mean_X;});
    std::transform(Y.begin(),Y.end(),Y_alt.begin(),[mean_Y](double y){return y-mean_Y;});

    //multiply vectors X and Y with each other and summing up the result
    double b1=std::inner_product(X_alt.begin(),X_alt.end(),Y_alt.begin(),0.0);
    //multiply the modified vector X with itself and summing up the result
    double b2=std::inner_product(X_alt.begin(),X_alt.end(),X_alt.begin(),0.0);

    //calculating slope
    double b=b1/b2;

    //calculating y-intercept
    double m=mean_Y-b*mean_X;

    //result array
    std::array<double,2> result={b,m};

    return result;
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
    if(static_cast<int>(X.size())==1 || static_cast<int>(Y.size())==1)
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
    std::vector<double> X2,Y2;
    //allocating space
    X2.resize(X.size());
    Y2.resize(Y.size());
    //setting the vectors of squared values
    std::transform(X.begin(),X.end(),X2.begin(),[](double x){return std::pow(x,2);});
    std::transform(Y.begin(),Y.end(),Y2.begin(),[](double y){return std::pow(y,2);});
    //calculating means
    double mean_X2=mean(X2);
    double mean_Y2=mean(Y2);

    //mixed mean value
    double mean_X_mean_Y=mean_X*mean_Y;

    //multiply vectors X and Y with each other then calculating mean
    double mean_XY=std::inner_product(X.begin(),X.end(),Y.begin(),0.0)/static_cast<double>(X.size());;

    //calculating r^2
    double r_sq=std::pow((mean_XY-mean_X_mean_Y)/std::sqrt((mean_X2-std::pow(mean_X,2))*(mean_Y2-std::pow(mean_Y,2))),2);
    
    return r_sq;
}