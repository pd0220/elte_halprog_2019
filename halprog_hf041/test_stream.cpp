#include "vector2.h"

//testing stream of vector2 struct
//main function
int main(int,char**)
{
    //test vector will be v=(1.5,2.5)
    vector2<double> v{1.5,2.5};
    std::stringstream ss;
    ss<<v;

    vector2<double> w;
    ss>>w;

    if(v.x!=w.x || v.y!=w.y)
    {
        return 1;
    }

    //test string will be str1("1.1,2.2")
    //test vector will be x_ref=(1.1,2.2)
    std::string str("1.1,2.2");
    vector2<double> x_ref{1.1,2.2};
    std::stringstream ss_1;
    ss_1<<str;

    vector2<double> x;
    ss_1>>x;

    if(x_ref.x!=x.x || x_ref.y!=x.y)
    {
        return 1;
    }

    //test vector will be y=(3.14,42.1)
    //test string will be str_ref("3.14,42.1")
    vector2<double> y{3.14,42.1};
    std::stringstream ssy;
    ssy<<y;
    std::string str_ref("3.14,42.1");

    if(str_ref!=ssy.str())
    {
        std::cout<<"prob"<<std::endl;
        return 1;
    }

    return 0;
}
