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
	void transform1(T1 const& d1,T2& d2,F f)
    {
        std::transform(d1.cbegin(),d1.cend(),d2.begin(),f);
    }
	template<typename T1,typename T2,typename T3,typename F>
	void transform2(T1 const& d1,T2 const& d2,T3& d3,F f)
    {
        std::transform(d1.cbegin(),d1.cend(),d2.cbegin(),d3.begin(),f);
    }
}

//--------------------------------------------------------------------------------------------------------

//helper structs
struct index1{};
struct index2{};

index1 one;
index2 two;

//--------------------------------------------------------------------------------------------------------

//matrix multiplication function for square matrices
//4 types
template<typename T>
std::vector<T> mat_mul(std::vector<T> const& data1,std::vector<T> const& data2,int n)
{
    std::vector<T> tmp;
    tmp.resize(data1.size());
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=data1[n*i+k]*data2[n*k+j];
            }
            tmp[n*i+j]=val;
        }
    }
    return tmp;
}

template<typename T>
std::vector<T> mat_mul(std::vector<T> && data1,std::vector<T> const& data2,int n)
{
    std::vector<T> tmp_vec;
    tmp_vec.resize(n);
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=data1[n*i+k]*data2[n*k+j];
            }
            tmp_vec[j]=val;
        }
        for(int j{0};j<=n-1;j++)
        {
            data1[n*i+j]=tmp_vec[j];
        }
    }
    return std::move(data1);
}
template<typename T>
std::vector<T> mat_mul(std::vector<T> && data1,std::vector<T> && data2,int n)
{
    std::vector<T> tmp_vec;
    tmp_vec.resize(n);
    for(int i{0};i<=n-1;i++)
    {
        for(int j{0};j<=n-1;j++)
        {
            T val{0};
            for(int k{0};k<=n-1;k++)
            {
                val+=data1[n*i+k]*data2[n*k+j];
            }
            tmp_vec[j]=val;
        }
        for(int j{0};j<=n-1;j++)
        {
            data1[n*i+j]=tmp_vec[j];
        }
    }
    return std::move(data1);
}

//--------------------------------------------------------------------------------------------------------

//common lambdas:
auto add=[](auto const& x,auto const& y){return x+y;};
auto sub=[](auto const& x,auto const& y){return x-y;};

//--------------------------------------------------------------------------------------------------------

//matrix class (square matrices only)
template<typename T>
class matrix
{
    //variables
    int dim;
    std::vector<T> data;

//--------------------------------------------------------------------------------------------------------
    
    //constructors
    public:
    //default
    matrix():dim{0}{}
    //parameterized default #1
    matrix(int n):dim{n}
    {
        std::vector<T> vec(dim*dim,0.0);
        data.swap(vec);
    }
    //parameterized default #2
    matrix(int n,std::vector<T> const& vec): dim{n}, data{vec}
    {
        if(static_cast<double>(dim*dim)-static_cast<double>(vec.size()))
        {
            std::cout<<"Square matrix cannot be created."<<std::endl;
            std::exit(-1);
        }
    }
    //copy
    matrix(matrix const&)=default;
    //move
	matrix(matrix &&)=default;
    //copy assignment
	matrix<T>& operator=(matrix const&)=default;
    //move assignment
	matrix<T>& operator=(matrix &&)=default;
    //initializer list
    matrix(int n,std::initializer_list<T> const& i): dim{n}, data{i}
    {
        if(i.size()!=static_cast<size_t>(dim*dim))
        {
            std::cout<<"Initializer list is not appropriate for square matrix."<<std::endl;
            std::exit(-1);
        }
    }

    //function of 1 index
    template<typename F>
	matrix(index1,F f,int n)
    {
        dim=n;
		data.resize(static_cast<size_t>(n*n));
		for(int i{0};i<=n*n-1;i++)
        {
            data[i]=f(i);
        }
	}
    //function of 2 indices
    template<typename F>
    matrix(index2,F f,int n): dim{n}
    {
        data.resize(static_cast<size_t>(n*n));
        for(int i{0};i<=n-1;i++)
        {
            for(int j{0};j<=n-1;j++)
            {
                data[n*i+j]=f(i,j);
            }
        }
    }
//--------------------------------------------------------------------------------------------------------

    //indexing
    T& operator()(int i,int j)
    {
        return data[dim*i+j];
    }
    T const& operator()(int i,int j) const
    {
        return data[dim*i+j];
    }
    T& operator[](int i)
    {
        return data[i];
    }
    T const& operator[](int i) const
    {
        return data[i];
    }

//--------------------------------------------------------------------------------------------------------

    //assignment operations
    //addtition assignment of matrices (+=)
    matrix<T>& operator+=(matrix<T> const& m)
    {
        detail::transform2((*this).data,m.data,(*this).data,add);
        return *this;
    }
    //substracion assignment of matrices (-=)
    matrix<T>& operator-=(matrix<T> const& m)
    {
        detail::transform2((*this).data,m.data,(*this).data,sub);
        return *this;
    }
    //multiplication assignment by scalar (*=)
    matrix<T>& operator*=(T const& scl)
    {
        detail::transform1((*this).data,(*this).data,[=](T const& x){return x*scl;});
        return *this;
    }
    //division assignment by scalar (/=)
    matrix<T>& operator/=(T const& scl)
    {
        detail::transform1((*this).data,(*this).data,[=](T const& x){return x/scl;});
        return *this;
    }
    //multiplication assignment by matrices (*=)
    matrix<T>& operator*=(matrix<T> const& m)
    {
        std::vector<T> tmp=mat_mul((*this).data,m.data,dim);        
        (*this).data.swap(tmp);
        return *this;
    }
    
//--------------------------------------------------------------------------------------------------------

    //inner functions
    //number of elements of the matrix
	int size() const
    {
		return static_cast<int>(data.size());
	}

//--------------------------------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------------------------------

    //getting variable values
    int get_dim() const
    {
        return (*this).dim;
    }
    std::vector<T> get_data() const&
    {
        return (*this).data;
    }
    std::vector<T> get_data() &
    {
        return (*this).data;
    }

//--------------------------------------------------------------------------------------------------------

    //addititon of matrices (+)
    //4 types
    friend matrix<T> operator+(matrix<T> const& m1,matrix<T> const& m2)
    {
        int n=m1.get_dim();
        auto madd=[&](int i){return m1[i]+m2[i];};
        matrix<T> result(one,madd,n);
        return result;
    }
    friend matrix<T> && operator+(matrix<T> const& m1,matrix<T> && m2)
    {
        detail::transform2(m1.get_data(),m2.get_data(),m2.data,add);
        return std::move(m2);     
    }
    friend matrix<T> && operator+(matrix<T> && m1,matrix<T> const& m2)
    {
        detail::transform2(m1.get_data(),m2.get_data(),m1.data,add);
        return std::move(m1);
    }
    friend matrix<T> && operator+(matrix<T> && m1, matrix<T> && m2)
    {
        detail::transform2(m1.get_data(),m2.get_data(),m1.data,add);
        return std::move(m1);
    }

//--------------------------------------------------------------------------------------------------------

    //substraction of matrices (-)
    //4 types
    friend matrix<T> operator-(matrix<T> const& m1, matrix<T> const& m2)
    {
        int n=m2.get_dim();
        auto msub=[&](int i){return m1[i]-m2[i];};
        matrix<T> result(one,msub,n);
        return result;
    }
    friend matrix<T> && operator-(matrix<T> const& m1, matrix<T> && m2)
    {
        detail::transform2(m1.get_data(),m2.get_data(),m2.data,sub);
        return std::move(m2);
    }
    friend matrix<T> && operator-(matrix<T> && m1, matrix<T> const& m2)
    {
        detail::transform2(m1.get_data(),m2.get_data(),m1.data,sub);
        return std::move(m1);
    }
    friend matrix<T> && operator-(matrix<T> && m1, matrix<T> && m2)
    {
        detail::transform2(m1.get_data(),m2.get_data(),m1.data,sub);
        return std::move(m1);
    }

//--------------------------------------------------------------------------------------------------------

    //multiplication by scalar (*)
    //2 types (from right)
    friend matrix<T> operator*(matrix<T> const& m,T const& scl)
    {
        int n=m.get_dim();
        auto mmulscl=[&](int i){return m[i]*scl;};
        matrix<T> result(one,mmulscl,n);
        return result;
    }
    friend matrix<T> && operator*(matrix<T> && m,T const& scl)
    {
        detail::transform1(m.get_data(),m.data,[&](T const& x){return x*scl;});
        return std::move(m);
    }
    //2 tpyes (from left)
    friend matrix<T> operator*(T const& scl,matrix<T> const& m)
    {
        int n=m.get_dim();
        auto mmulscl=[&](int i){return scl*m[i];};
        matrix<T> result(one,mmulscl,n);
        return result;
    }
    friend matrix<T> && operator*(T const& scl,matrix<T> && m)
    {
        detail::transform1(m.get_data(),m.data,[&](T const& x){return scl*x;});
        return std::move(m);
    }

//--------------------------------------------------------------------------------------------------------

    //division by scalar (/)
    //2 types
    friend matrix<T> operator/(matrix<T> const& m,T const& scl)
    {
        int n=m.get_dim();
        auto mdivscl=[&](int i){return m[i]/scl;};
        matrix<T> result(one,mdivscl,n);
        return result;
    }
    friend matrix<T> && operator/(matrix<T> && m, T const& scl)
    {
        detail::transform1(m.get_data(),m.data,[&](T const& x){return x/scl;});
        return std::move(m);
    }


//--------------------------------------------------------------------------------------------------------

    //multiplication of matrices (*)
    //4 types
    friend matrix<T> operator*(matrix<T> const& m1, matrix<T> const& m2)
    {
        int n=m1.get_dim();
        auto mmulm=[&](int i){return mat_mul(m1.get_data(),m2.get_data(),n)[i];};
        matrix<T> result(one,mmulm,n);
        return result;
    }
    friend matrix<T> && operator*(matrix<T> const& m1, matrix<T> && m2)
    {
        std::vector<T> tmp=mat_mul(m1.get_data(),m2.get_data(),m1.get_dim());
        m2.data.swap(tmp);
        return std::move(m2);
    }
    friend matrix<T> && operator*(matrix<T> && m1, matrix<T> const& m2)
    {
        std::vector<T> tmp=mat_mul(m1.get_data(),m2.get_data(),m1.get_dim());
        m1.data.swap(tmp);
        return std::move(m1);
    }
    friend matrix<T> && operator*(matrix<T> && m1, matrix<T> && m2)
    {
        std::vector<T> tmp=mat_mul(m1.get_data(),m2.get_data(),m1.get_dim());
        m1.data.swap(tmp);
        return std::move(m1);
    }
   
//--------------------------------------------------------------------------------------------------------

    //ostream
    friend std::ostream& operator<<(std::ostream& o,matrix<T> const& m)
    {
        int n=m.get_dim();
        o<<n<<";";
        if(n>0)
        {
            for(int j{0};j<=n*n-2;j++)
            {
                o<<m[j]<<",";
            }
            o<<m[n*n-1];
        }
        return o;
    }

//--------------------------------------------------------------------------------------------------------

    //istream
    friend std::istream& operator>>(std::istream& i,matrix<T> & m)
    {
        auto restore_stream=[state=i.rdstate(),pos=i.tellg(),&i](){i.seekg(pos);i.setstate(state);};

        std::string tmp;
        std::getline(i,tmp);
        std::stringstream ii(tmp);
        
        std::getline(ii,tmp,';');
        if(tmp.size()==0){restore_stream();return i;}
        m.dim=std::stoi(tmp);
        int n=m.get_dim();

        for(int j=0;j<=n*n-2;j++)
        {
            std::getline(ii,tmp,',');
            if(tmp.size()==0){restore_stream();return i;}
            m.data[j]=std::stod(tmp);
        }
        
        std::getline(ii,tmp);
        if(tmp.size()==0){restore_stream();return i;}
        m.data[n*n-1]=std::stod(tmp);

        return i;
    }
};

//--------------------------------------------------------------------------------------------------------

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
    if(m1.size()!=m2.size() || m1.get_dim()!=m2.get_dim())
    {
        std::cout<<"Matrix variables are not equal in given matrices."<<std::endl;
        std::exit(-1);
    }
    if(m1.size()!=static_cast<size_t>(4) || m2.size()!=static_cast<size_t>(4) || m1.get_dim()!=2 || m2.get_dim()!=2)
    {
        std::cout<<"Given matrices are not 2X2."<<std::endl;
        std::exit(-1);
    }
}

//--------------------------------------------------------------------------------------------------------

//check if size is 0
template<typename T>
void mat_if0(matrix<T> const& m)
{
    if(m.size()!=static_cast<size_t>(0))
    {
        std::cout<<"Given matrix size are not 0."<<std::endl;
        std::exit(-1);
    }
}