#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <numeric>

//calculating mean
double mean(const std::vector<double>& vec)
{
    double avg=std::accumulate(vec.begin(),vec.end(),0)/static_cast<int>(vec.size());

    return avg;
}


//linear fit function
std::array<double,2> linear_fit(const std::vector<double>& X,const std::vector<double>& Y)
{
    double b=std::accumulate(X.begin(),X.end(),0,double f=[](double a,double b){return a-b;};



    std::array<double,2> result;

    return result;
}

//main function
int main(int, char**)
{
    //given vectors
    const std::vector<double> X={1.0,2.0}, Y={1.0,2.0};

    std::cout<<"még lefut..."<<std::endl;
}
