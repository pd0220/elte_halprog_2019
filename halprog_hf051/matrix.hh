#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <initializer_list>
#include <string>
#include <sstream>

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

//matrix multiplication function for square matrices
//2 types
template<typename T>
std::vector<T> mat_mul(std::vector<T> const& data1,std::vector<T> const& data2)
{
    std::vector<T> tmp;
    double N{std::sqrt(data1.size())};
    //check if given matrices are square matrices
    if(N-std::floor(N)!=0)
    {
        std::cout<<"Given matrices are not square matrices."<<std::endl;
        std::exit(-1);
    }
    N=static_cast<int>(N);
    tmp.resize(data1.size());
    for(int i{0};i<=N-1;i++)
    {
        for(int j{0};j<=N-1;j++)
        {
            T val{0};
            for(int k{0};k<=N-1;k++)
            {
                val+=data1[N*i+k]*data2[N*k+j];
            }
            tmp[N*i+j]=val;
        }
    }
    return tmp;
}

template<typename T>
std::vector<T> mat_mul(std::vector<T> && data1,std::vector<T> const& data2)
{
    std::vector<T> tmp_vec;
    double N{std::sqrt(data1.size())};
    //check if given matrices are square matrices
    if(N-std::floor(N)!=0)
    {
        std::cout<<"Given matrices are not square matrices."<<std::endl;
        std::exit(-1);
    }
    N=static_cast<int>(N);
    tmp_vec.resize(N);
    for(int i{0};i<=N-1;i++)
    {
        for(int j{0};j<=N-1;j++)
        {
            T val{0};
            for(int k{0};k<=N-1;k++)
            {
                val+=data1[N*i+k]*data2[N*k+j];
            }
            tmp_vec[j]=val;
        }
        for(int j{0};j<=N-1;j++)
        {
            data1[N*i+j]=tmp_vec[j];
        }
    }
    return std::move(data1);
}

//--------------------------------------------------------------------------------------------------------

//matrix struct (square matrices only)
template<typename T>
struct matrix
{
    //variables
    int N;
    std::vector<T> data;

//--------------------------------------------------------------------------------------------------------

    //constructors
    //default
  	matrix():N{0}
    {
        data.resize(static_cast<size_t>(N));
    }
    //parameterized default
    matrix(int n):N{n}
    {
        data.resize(static_cast<size_t>(N*N));
        std::transform(data.cbegin(),data.cend(),data.begin(),[](auto const& x){return 0*x;});
    }
    //copy
	matrix(matrix const&)=default;
    //move
	matrix(matrix&&)=default;
    //copy assignment
	matrix<T>& operator=(matrix const&)=default;
    //move assignment
	matrix<T>& operator=(matrix&&)=default;
    //initializer list
    matrix(int n,std::initializer_list<T> const& i):N{n},data{i}
    {
        if(i.size()!=static_cast<size_t>(N*N))
        {
            std::cout<<"Initializer list is not appropriate for matrix dimension."<<std::endl;
            std::exit(-1);
        }
    }
    //function of 2 indices
 	template<typename F>
	matrix(F f,int n)
	{
		data.resize(static_cast<size_t>(n*n));
        N=n;
        for(int i=0;i<=N-1;i++)
        {
            for(int j=0;j<=N-1;j++)
            {
                data[N*i+j]=f(i,j);
            }
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
        detail::transform_mat2((*this).data,m.data,(*this).data,add);
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //substracion assignment of matrices (-=)
    matrix<T>& operator-=(matrix<T> const& m)
    {
        detail::transform_mat2((*this).data,m.data,(*this).data,sub);
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //multiplication assignment by scalar (*=)
    matrix<T>& operator*=(T const& scl)
    {
        detail::transform_mat1((*this).data,(*this).data,[=](T const& x){return x*scl;});
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //division assignment by scalar (/=)
    matrix<T>& operator/=(T const& scl)
    {
        detail::transform_mat1((*this).data,(*this).data,[=](T const& x){return x/scl;});
        return *this;
    }

//--------------------------------------------------------------------------------------------------------

    //multiplication assignment of matrices (*=)
    matrix<T>& operator*=(matrix<T> const& m)
    {
        int n=(*this).N;
        std::vector<T> tmp=mat_mul((*this).data,m.data);        
        (*this).data.swap(tmp);
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
    result.N=m1.N;
    result.data=mat_mul(m1.data,m2.data);
    return result;
}

template<typename T>
matrix<T> && operator*(matrix<T> const& m1,matrix<T> && m2)
{
    std::vector<T> tmp=mat_mul(m1.data,m2.data);
    m2.data.swap(tmp);
    return std::move(m2);
}

template<typename T>
matrix<T> && operator*(matrix<T> && m1,matrix<T> const& m2)
{
    std::vector<T> tmp=mat_mul(m1.data,m2.data);
    m1.data.swap(tmp);
    return std::move(m1);
}

template<typename T>
matrix<T> && operator*(matrix<T> && m1,matrix<T> && m2)
{
    std::vector<T> tmp=mat_mul(m1.data,m2.data);
    m1.data.swap(tmp);
    return std::move(m1);
}

//--------------------------------------------------------------------------------------------------------

//ostream  
template<typename T>
std::ostream& operator<<(std::ostream& o,matrix<T> const& m)
{
    int n{m.N};
    o<<n<<',';
	if(n>0)
	{
		for(int i=0;i<=n*n-1;i++)
		{
            o<<m.data[i]<<",";
		}
	}
	return o;
}

//istream
template<typename T>
std::istream& operator>>(std::istream& i,matrix<T> & m)
{
    std::string tmp;
    std::getline(i,tmp);
    std::stringstream ii(tmp);
    std::getline(ii,tmp,',');
    m.N=std::stoi(tmp);
    for(int j=0;j<=m.N*m.N-1;j++)
    {
        std::getline(ii,tmp,',');
        m.data[j]=std::stod(tmp);
    }
    return i;
}

//further functions for unit tests
//check if two 2x2 matrices are equal
template<typename T>
void mat_eq(matrix<T> const& m1,matrix<T> const& m2)
{
    double eps{1e-10};
    if(std::abs(m1(0,0)-m2(0,0))>eps || std::abs(m1(0,1)-m2(0,1))>eps || std::abs(m1(1,0)-m2(1,0))>eps || std::abs(m1(1,1)-m2(1,1))>eps)
    {
        std::cout<<"Elements are not equal in given matrices."<<std::endl;
        std::exit(-1);
    }
    if(m1.size()!=m2.size() || m1.N!=m2.N)
    {
        std::cout<<"Matrix variables are not equal in given matrices."<<std::endl;
        std::exit(-1);
    }
    if(m1.size()!=static_cast<size_t>(4) || m2.size()!=static_cast<size_t>(4) || m1.N!=2 || m2.N!=2)
    {
        std::cout<<"Given matrices are not 2X2."<<std::endl;
        std::exit(-1);
    }
}

//check .data.size() are 0
template<typename T>
void mat_if0(matrix<T> const& m)
{
    if(m.size()!=static_cast<size_t>(0))
    {
        std::cout<<"Given matrix size are not 0."<<std::endl;
        std::exit(-1);
    }
}
