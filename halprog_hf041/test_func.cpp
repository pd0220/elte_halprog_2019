#include "vector2.h"

//testing functions of vector2 struct
//every reference value is from wolframalpha.com or from own calculations
//main function
int main(int,char**)
{
    //test vectors will be v1=(8.81,4.26) and v2=(5.24,10.33)
    vector2<double> const v1={8.81,4.26};
    vector2<double> const v2={5.24,10.33};

    //dot product
    //dot product of v1 and v2 is 90.1702
    double dot_ref=90.1702;
    if(std::abs(dot(v1,v2)-dot_ref)>=1e-5)
    {
        return 1;
    }

    //length of a vector
    //length of v1 is approx. 9.785892907650
    double length_ref=9.785892907650;
    if(std::abs(length(v1)-9.785892907650)>=1e-5)
    {
        return 1;
    }

    //square length of a vector
    //square length of v2 is 134.1665
    double sqlength_ref=134.1665;
    if(std::abs(sqlength(v2)-134.1665)>=1e-5)
    {
        return 1;
    }

    //normalizing
    //normalized v1 is approx. v1_norm=(0.900276, 0.435321)
    vector2<double> v1_norm_ref={0.900276, 0.435321};
    vector2<double> v1_norm=normalize(v1);
    if(std::abs(v1_norm.x-v1_norm_ref.x)>=1e-5 && std::abs(v1_norm.y-v1_norm_ref.y)>=1e-5)
    {
        return 1;
    }

    //rotation around a given angle (phi=pi/2)
    //rotated v2 is v2_rot=(-10.33,5.24)
    vector2<double> v2_rot_ref={-10.33,5.24};
    vector2<double> v2_rot=rotate(v2,M_PI/2);
    if(std::abs(v2_rot.x-v2_rot_ref.x)>=1e-5 && std::abs(v2_rot.y-v2_rot_ref.y)>=1e-5)
    {
        return 1;
    }

    return 0;
}