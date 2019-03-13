#include "vector2.h"

//main function
int main(int, char**)
{
    std::cout<<"Test vector will be v0.\nIts x-value:"<<std::endl;
    vector2<double> v0;
    std::cin>>v0.x;
    std::cout<<"Its y-value:"<<std::endl;
    std::cin>>v0.y;    
    std::cout<<"Print it v0:\n"<<"v0="<<v0<<"."<<std::endl;

    vector2<double> v1={1.0,1.0};
    vector2<double> v2={2.0,2.0};
    std::cout<<"v1 and v2 test vectors are:\nv1="<<v1<<std::endl;
    std::cout<<"v2="<<v2<<std::endl;

    std::cout<<"Adding them up:\nv1+v2="<<v1+v2<<std::endl;
    std::cout<<"Summation is commutative:\nv2+v1="<<v2+v1<<std::endl;
    
    double a=2;
    std::cout<<"Multiplied by a scalar (a="<<a<<"):\nv1*a="<<v1*a<<std::endl;
    std::cout<<"Multiplication is commutative:\na*v1="<<a*v1<<std::endl;
    
    std::cout<<"Division by a scalar:\nv1/a="<<v1/a<<std::endl;
    
    std::cout<<"Dot product of v1 and v1:\ndot(v1,v2)="<<dot(v1,v1)<<std::endl;
    
    std::cout<<"Length of v2:\n||v2||="<<length(v2)<<std::endl;
    std::cout<<"Square length v2:\n||v2||^2="<<sqlenght(v2)<<std::endl;
    std::cout<<"Normalized v2 is:\nv2_norm="<<normalize(v2)<<std::endl;
    
    v1+=v1;
    std::cout<<"Special operators can be used:\n(1) v1+=v1 --> "<<v1<<std::endl;
    v2*=a;
    std::cout<<"(2) v2*=a --> "<<v2<<std::endl;
    v0/=a;
    
    std::cout<<"(3) v0/=a --> "<<v0<<std::endl;
    vector2<double> v3={1,1};
    double phi=3.14159265/2;
    vector2<double> v3_rot;
    v3_rot=rotate(v3,phi);
    std::cout<<"Rotate v3 (v3="<<v3<<") vector with 90 degrees:\nv1_rot="<<v3_rot<<std::endl;

    return 0;
}
