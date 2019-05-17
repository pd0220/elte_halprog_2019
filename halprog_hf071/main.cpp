#include <chrono>
#include <random>
#include <fstream>
#include "Matrix.hh"

int main(int,char**)
{
    //random number generation
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<double> distr(0.,10.);            


    for(int n=1000;n<=100000;n=n+1000)
    {
        //creating random matrices
        matrix<double> m_rand1(zero,[&]{return distr(gen);},n);
        matrix<double> m_rand2(zero,[&]{return distr(gen);},n);
        
        //clock 00
        auto t0=std::chrono::high_resolution_clock::now();

        //parallel multiplication
        m_rand1*m_rand2;

        //clock 01
        auto t1=std::chrono::high_resolution_clock::now();

        //"measuring" time
        double t=(static_cast<std::chrono::duration<double,std::milli>>(t1-t0)).count();
        
        //write to file
        std::ofstream myfile;
        //myfile.open("par_test.txt",std::fstream::app);
        myfile.open("norm_test.txt",std::fstream::app);
        myfile<<t<<"\n";
        myfile.close();
    }   

    return 0;
}

