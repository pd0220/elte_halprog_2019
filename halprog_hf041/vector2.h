#include <iostream>
#include <cmath>

//vector struct
template<typename T>
struct vector2
{
    T x, y;

    //setting vector values (=)
    vector2<T>& operator=(vector2<T> const& v)
    {
        x=v.x;
        y=v.y;
        return *this;
    }

    //summation (+=)
    template<typename t>
    auto& operator+=(vector2<t> const& v)
    {
        x+= v.x;
        y+= v.y;
        return *this;
    }

    //multiplication by scalar (*=)
    template<typename t>
    auto& operator*=(t const& a)
    {
        x*=a;
        y*=a;
        return *this;
    }

    //division by scalar (/=)
    template<typename t>
    auto& operator/=(t const& a)
    {
        x/=a;
        y/=a;
        return *this;
    }
};

//output stream
template<typename T>
std::ostream& operator<<(std::ostream& o,vector2<T> const& v)
{
    o<<"("<<v.x<<","<<v.y<<")";
    return o;
}

//input stream
template<typename T>
std::istream& operator>>(std::istream& i,vector2<T> const& v)
{
    i>>v.x;
    i>>v.y;
    return i;
}

//summation of vectors (+)
template<typename T1,typename T2>
auto operator+(vector2<T1> const& v1,vector2<T2> const& v2)
{
    using R=decltype(v1.x+v2.x);
    return vector2<R>{v1.x+v2.x,v1.y+v2.y};
}

//multiplication by a scalar (from right) (*)
template<typename Tv,typename T>
auto operator*(vector2<Tv> const& v,T const& a)
{
    using R = decltype(v.x*a);
    return vector2<R>{v.x*a,v.y*a};
}

//multiplication by a scalar (from left) (*)
template<typename Tv,typename T>
auto operator*(T const& a,vector2<Tv> const& v)
{
    using R=decltype(v.x*a);
    return vector2<R>{v.x*a,v.y*a};
}

//division by a scalar (/)
template<typename Tv,typename T>
auto operator/(vector2<Tv> const& v,T const& a)
{
    using R=decltype(v.x/a);
    return vector2<R>{v.x/a,v.y/a};
}

//dot product
template<typename T1,typename T2>
auto dot(vector2<T1> const& v1,vector2<T2> const& v2)
{
    return v1.x*v1.y+v1.y*v2.y;
}

//lenght a vector
template<typename T>
auto length(vector2<T> const& v)
{
    return std::sqrt(v.x*v.x+v.y*v.y);
}

//square lenght of a vector
template<typename T>
auto sqlenght(vector2<T> const& v)
{
    return v.x*v.x+v.y*v.y;
}

//normalize a vector
template<typename T>
vector2<T> normalize(vector2<T> const& v)
{
    return vector2<T>{v.x,v.y}/length(v);
}
