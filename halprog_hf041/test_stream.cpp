#include "vector2.h"

//testing stream of vector2 struct
//main function
int main(int,char**)
{
    //test vector will be v1=(1.5,2.5)
    vector2<double> v1{1.5,2.5};
    std::stringstream ss1;
    ss1<<v1;

    vector2<double> v2;
    ss1>>v2;

    if(v1.x!=v2.x || v1.y!=v2.y)
    {
        return 1;
    }

    return 0;
}