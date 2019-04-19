#include "Matrix.hh"
#include <random>
#include <chrono>
#include <fstream>

//main function
int main(int,char**)
{

    //random number generation
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<double> distr(0.,10.);

    //multiplication time measurement
    for(int n=50;n<=1050;n=n+100)
    {
        //creating random matrices
        matrix<double> m_rand1(zero,[&]{return distr(gen);},n);
        matrix<double> m_rand2(zero,[&]{return distr(gen);},n);
        matrix<double> m_rand3(zero,[&]{return distr(gen);},n);
        matrix<double> m_rand4(zero,[&]{return distr(gen);},n);
    
        //clock 00
        auto t0=std::chrono::high_resolution_clock::now();

        //newly allocated memory for matrix multiplication
        m_rand1*m_rand2;

        //clock 01
        auto t1=std::chrono::high_resolution_clock::now();

        //reused memory for matrix multiplication
        m_rand3*std::move(m_rand4);

        //clock 02
        auto t2=std::chrono::high_resolution_clock::now();

        //"measuring" time
        double t_alloc=(static_cast<std::chrono::duration<double,std::milli>>(t1-t0)).count();
        double t_reuse=(static_cast<std::chrono::duration<double,std::milli>>(t2-t1)).count();

        //write to file
        std::ofstream myfile;
        myfile.open("rand.txt",std::fstream::app);
        myfile<<t_alloc<<" "<<t_reuse<<"\n";
        myfile.close();
    }

    return 0;
}