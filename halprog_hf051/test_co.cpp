#include "Matrix.hh"

//test for constructors
//main function
int main(int,char**)
{
    //default
    matrix<double> m_default;
    mat_if0(m_default);
    if(m_default.cend()!=m_default.cbegin() || m_default.end()!=m_default.begin())
    {
        return 1;
    }

    //list initialization and indexing
    matrix<double> m1{2,{3.1,2.3,1.1,6.5}};
    if(m1.size()!=static_cast<size_t>(4) || m1(0,0)!=3.1 || m1(0,1)!=2.3 || m1(1,0)!=1.1 || m1(1,1)!=6.5 || m1.get_dim()!=2)
    {
        return 1;
    }

    //parameterized default #1
    //test matrix is mp1t={{0,0},{0,0}}
    matrix<double> mp1t{2,{0.0,0.0,0.0,0.0}};
    matrix<double> mp1(2);
    mat_eq(mp1,mp1t);

    //parameterized default #2
    //test matrix is mp3t={{1.0,2.0},{3.0,4.0}}
    matrix<double> mp3t{2,{1.0,2.0,3.0,4.0}};
    std::vector<double> vp3{1.0,2.0,3.0,4.0};
    matrix<double> mp3(2,vp3);
    mat_eq(mp3,mp3t);

    //copy
    matrix<double> m1_cpy{m1};
    mat_eq(m1,m1_cpy);

    //move
    matrix<double> m2{m1};
    matrix<double> m3{std::move(m2)};
    mat_eq(m3,m1);
    mat_if0(m2);

    //function of 1 index
    //test matrix will be mit={{0.0,2.0},{4.0,6.0}}
    index1 one;
    matrix<double> mi(one,[](int i){return 2*i;},2);
    matrix<double> mit{2,{0.0,2.0,4.0,6.0}};
    mat_eq(mi,mit);

    //function of 2 indices
    //test matrix will be miit={{0.0,1.0,}{1.0,2,0}}
    index2 two;
    matrix<double> mii(two,[](int i,int j){return i+j;},2);
    matrix<double> miit{2,{0.0,1.0,1.0,2.0}};
    mat_eq(mii,miit);

    return 0;    
}