#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <initializer_list>

//general assumptions:
//(1) the user will use square matrices only
//(2) operations will only happen between objects that has the same type

//--------------------------------------------------------------------------------------------------------

//helper functions
namespace detail
{
	template<typename T1,typename T2,typename F>
	void transform_mat1(T1 const& m1,T2& m2,F f)
	{
		std::transform(m1.cbegin(),m1.cend(),m2.begin(),f);
	}

	template<typename T1,typename T2,typename T3,typename F>
	void transform_mat2(T1 const& m1,T2 const& m2,T3& m3, F f)
	{
		std::transform(m1.cbegin(),m1.cend(),m2.cbegin(),m3.begin(),f);
	}
}

//--------------------------------------------------------------------------------------------------------

//common lambdas:
auto add=[](auto const& x,auto const& y){return x+y;};
auto sub=[](auto const& x,auto const& y){return x-y;};

//--------------------------------------------------------------------------------------------------------

//matrix struct (square matrices only)
template<typename T>
struct matrix
{
    //variables
    std::vector<T> data;
    int N=std::sqrt(static_cast<int>(data.size()));

//--------------------------------------------------------------------------------------------------------

    //constructors
    //default
  	matrix()=default;
    //copy
	matrix(matrix const&)=default;
    //move
	matrix(matrix&&)=default;
    //copy assignment
	matrix<T>& operator=(matrix const&)=default;
    //move assignment
	matrix<T>& operator=(matrix&&)=default;
    //initializer list
    matrix(std::initializer_list<T> const&  i): data{i}{}
    //function of indexes
 	template<typename F>
	matrix(F f,int n)
	{
		data.resize(n);
        N=std::sqrt(static_cast<int>(data.size()));
		for(int i=0;i<n;i++)
        {
            data[i]=f(i);
        }
    }

//--------------------------------------------------------------------------------------------------------

    //indexing
    T & operator()(int i,int j)
    {
        return data[N*i+j];
    }

    T const& operator()(int i,int j) const
    {
        return data[N*i+j];
    }

//--------------------------------------------------------------------------------------------------------

    //addtition assignment of matrices (+=)
    matrix<T>& operator+=(matrix<T> const& m)
    {
        detail::transform_mat2(this->data,m.data,this->data,add);
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //substracion assignment of matrices (-=)
    matrix<T>& operator-=(matrix<T> const& m)
    {
        detail::transform_mat2(this->data,m.data,this->data,sub);
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //multiplication assignment by scalar (*=)
    matrix<T>& operator*=(T const& scl)
    {
        detail::transform_mat1(this->data,this->data,[=](T const& x){return x*scl;});
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //division assignment by scalar (/=)
    matrix<T>& operator/=(T const& scl)
    {
        detail::transform_mat1(this->data,this->data,[=](T const& x){return x/scl;});
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //multiplication assignment of matrices (*=)
    matrix<T>& operator*=(matrix<T> const& m)
    {
        matrix<T> result;
        int n=this->N;
        std::vector<T> tmp;
        for(int i{0};i<=n-1;i++)
        {
            for(int j{0};j<=n-1;j++)
            {
                T val{0};
                for(int k{0};k<=n-1;k++)
                {
                    val+=this->data[this->N*i+k]*m(k,j);
                }
                tmp.push_back(val);
            }
        }
        this->data.swap(tmp);
        return *this;
    } 

//--------------------------------------------------------------------------------------------------------

    //number of elements of the matrix
	int size() const
	{
		return static_cast<int>(data.size());
	}

	//begin and end for compatibility with STL:
	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
    }
};

//--------------------------------------------------------------------------------------------------------

//addititon of matrices (+)
//4 types
template<typename T>
matrix<T> operator+(matrix<T> const& m1,matrix<T> const& m2)
{
    matrix<T> result;
    result.data.resize(m1.data.size());
    result.N=m1.N;
    detail::transform_mat2(m1.data,m2.data,result.data,add);
    return result;
}

template<typename T>
matrix<T> && operator+(matrix<T> && m1,matrix<T> const& m2)
{
    detail::transform_mat2(m1.data,m2.data,m1.data,add);
    return std::move(m1);
}

template<typename T>
matrix<T> && operator+(matrix<T> const& m1,matrix<T> && m2)
{
    detail::transform_mat2(m1.data,m2.data,m2.data,add);
    return std::move(m2);
}

template<typename T>
matrix<T> && operator+(matrix<T> && m1,matrix<T> && m2)
{
    detail::transform_mat2(m1.data,m2.data,m1.data,add);
    return std::move(m1);
}

//--------------------------------------------------------------------------------------------------------

//substracion of matrices (-)
//4 types
template<typename T>
matrix<T> operator-(matrix<T> const& m1,matrix<T> const& m2)
{
    matrix<T> result;
    result.data.resize(m1.data.size());
    result.N=m1.N;
    detail::transform_mat2(m1.data,m2.data,result.data,sub);
    return result;
}

template<typename T>
matrix<T> && operator-(matrix<T> && m1,matrix<T> const& m2)
{
    detail::transform_mat2(m1.data,m2.data,m1.data,sub);
    return std::move(m1);
}

template<typename T>
matrix<T> && operator-(matrix<T> const& m1,matrix<T> && m2)
{
    detail::transform_mat2(m1.data,m2.data,m2.data,sub);
    return std::move(m2);
}

template<typename T>
matrix<T> && operator-(matrix<T> && m1,matrix<T> && m2)
{
    detail::transform_mat2(m1.data,m2.data,m1.data,sub);
    return std::move(m1);
}

//--------------------------------------------------------------------------------------------------------

//multiplication by scalar (*)
//2 types (from right)
template<typename T>
matrix<T> operator*(matrix<T> const& m,T const& scl)
{
    matrix<T> result;
    result.data.resize(m.data.size());
    result.N=m.N;
    detail::transform_mat1(m.data,result.data,[=](T const& x){return x*scl;});
    return result;
}

template<typename T>
matrix<T> && operator*(matrix<T> && m,T const& scl)
{
    detail::transform_mat1(m.data,m.data,[=](T const& x){return x*scl;});
    return std::move(m);
}

//2 types (from left)
template<typename T>
matrix<T> operator*(T const& scl,matrix<T> const& m)
{
    matrix<T> result;
    result.data.resize(m.data.size());
    result.N=m.N;
    detail::transform_mat1(m.data,result.data,[=](T const& x){return scl*x;});
    return result;
}

template<typename T>
matrix<T> && operator*(T const& scl,matrix<T> && m)
{
    detail::transform_mat1(m.data,m.data,[=](T const& x){return scl*x;});
    return std::move(m);
}

//--------------------------------------------------------------------------------------------------------

//division by scalar (/)
//2 types
template<typename T>
matrix<T> operator/(matrix<T> const& m,T const& scl)
{
    matrix<T> result;
    result.data.resize(m.data.size());
    result.N=m.N;
    detail::transform_mat1(m.data,result.data,[=](T const& x){return x/scl;});
    return result;
}

template<typename T>
matrix<T> && operator/(matrix<T> && m,T const& scl)
{
    detail::transform_mat1(m.data,m.data,[=](T const& x){return x/scl;});
    return std::move(m);
}

//--------------------------------------------------------------------------------------------------------

//multiplication of matrices (*)
//4 types
template<typename T>
matrix<T> operator*(matrix<T> const& m1,matrix<T> const& m2)
{
    matrix<T> result;
    int n{m1.N};
    result.N=n;
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=m1(i,k)*m2(k,j);
            }
            result.data.push_back(val);
        }
    }
    return result;
}

template<typename T>
matrix<T> && operator*(matrix<T> const& m1,matrix<T> && m2)
{
    int n{m1.N};
    std::vector<T> tmp;
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=m1(i,k)*m2(k,j);
            }
            tmp.push_back(val);
        }
    }
    m2.data.swap(tmp);
    return std::move(m2);
}

template<typename T>
matrix<T> && operator*(matrix<T> && m1,matrix<T> const& m2)
{
    int n{m1.N};
    std::vector<T> tmp;
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=m1(i,k)*m2(k,j);                         
            }
            tmp.push_back(val);
        }
    }
    m1.data.swap(tmp);
    return std::move(m1);
}

template<typename T>
matrix<T> && operator*(matrix<T> && m1,matrix<T> && m2)
{
    int n{m1.N};
    std::vector<T> tmp;
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=m1(i,k)*m2(k,j);
            }
            tmp.push_back(val);
        }
    }
    m1.data.swap(tmp);
    return std::move(m1);
}

//--------------------------------------------------------------------------------------------------------

//ostream  
template<typename T>
std::ostream& operator<<(std::ostream& o,matrix<T> const& m)
{
	int n{m.N};
	if(n>0)
	{
		for(int i=0;i<=n-1;i++)
		{
            o<<" ";
            for(int j=0;j<=n-1;j++)
            {
                o<<m(i,j)<<" ";
            }
            o<<"\n";
		}
	}
	return o;
}