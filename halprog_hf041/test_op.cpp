#include "vector2.h"

//testing operators from vector2 struct
//every reference value is from wolframalpha.com or from own calculations
//main function
int main(int,char**)
{
    //test vectors will be v1=(8.81,4.26) and v2=(5.24,10.33)
    vector2<double> const v1={8.81,4.26};
    vector2<double> const v2={5.24,10.33};

    //operator =
    vector2<double> v1_copy=v1;
    if(std::abs(v1.x-v1_copy.x)>=1e-5 && std::abs(v1.y-v1_copy.y)>=1e-5)
    {
        return 1;
    }

    //operator + and +=
    //sum of v1 and v2 is v_sum=(14.05,14.59)
    vector2<double> v_sum={14.05,14.59};
    vector2<double> v_sum1=v1+v2, v_sum2=v2;
    v_sum2+=v2;
    if(std::abs(v_sum.x-v_sum1.x)>=1e-5 && std::abs(v_sum.x-v_sum2.x)<=1e-5 && std::abs(v_sum.y-v_sum1.y)>=1.e-5 && std::abs(v_sum.y-v_sum2.y)>=1e-5)
    {
        return 1;
    }

    //operator - and -=
    //v2 substracted from v1 is v_sub=(3.57,-6.07)
    vector2<double> v_sub={3.57,-6.07};
    vector2<double> v_sub1=v1-v2, v_sub2=v2;
    v_sub2-=v2;
    if(std::abs(v_sub.x-v_sub1.x)>=1e-5 && std::abs(v_sub.x-v_sub2.x)<=1e-5 && std::abs(v_sub.y-v_sub1.y)>=1.e-5 && std::abs(v_sub.y-v_sub2.y)>=1e-5)
    {
        return 1;
    }

    //operator * and *=
    //v1 multiplied by a=2.5 is v_mul=(22.025,10.65)
    vector2<double> v_mul={22.025,10.65};
    double a=2.5;
    vector2<double> v_mul1=v1*a, v_mul2=a*v1, v_mul3=v1;
    v_mul3*=a;
    if(std::abs(v_mul.x-v_mul1.x)>=1e-5 && std::abs(v_mul.x-v_mul2.x)>=1e-5 && std::abs(v_mul.x-v_mul3.x)>=1e-5 && std::abs(v_mul.y-v_mul1.y)>=1e-5 && std::abs(v_mul.y-v_mul2.y)>=1e-5 && std::abs(v_mul.y-v_mul3.y)>=1e-5)
    {
        return 1;
    }

    //operator / and /=
    //v2 divided by b=3.2 is v_div=(1.6375,3.228125)
    vector2<double> v_div={1.6375,3.228125};
    double b=3.2;
    vector2<double> v_div1=v2/b, v_div2=v2;
    v_div2/=b;
    if(std::abs(v_div.x-v_div1.x)>=1e-5 && std::abs(v_div.x-v_div2.x)>=1e-5 && std::abs(v_div.y-v_div1.y)>=1e-5 && std::abs(v_div.y-v_div2.y)>=1e-5)
    {
        return 1;
    }
    
    return 0;
}