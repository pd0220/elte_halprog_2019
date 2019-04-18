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

    //creating random matrices
    for(int n=10;n<=100;n=n+10)
    {
        //empty vectors
        std::vector<double> v_rand1(n*n);
        std::vector<double> v_rand2{v_rand1};

        //creating random vectors
        std::generate(v_rand1.begin(),v_rand1.end(),[&]{return distr(gen);});
        std::generate(v_rand2.begin(),v_rand2.end(),[&]{return distr(gen);});

        //creating random matrices
        matrix<double> m_rand1(one,[&](int i){return v_rand1[i];},n);
        matrix<double> m_rand2(one,[&](int i){return v_rand2[i];},n);

        //clock 00
        auto t0=std::chrono::high_resolution_clock::now();

        //newly allocated memory for matrix multiplication
        m_rand1*m_rand2;

        //clock 01
        auto t1=std::chrono::high_resolution_clock::now();

        //reused memory for matrix multiplication
        m_rand1*std::move(m_rand2);

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