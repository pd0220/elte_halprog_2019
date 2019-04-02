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
//2 types
template<typename T>
std::vector<T> mat_mul(std::vector<T> const& data1,std::vector<T> const& data2)
{
    std::vector<T> tmp;
    double dim{std::sqrt(data1.size())};
    //check if given matrices are square matrices
    if(dim-std::floor(dim)!=0)
    {
        std::cout<<"Given matrices are not square matrices."<<std::endl;
        std::exit(-1);
    }
    dim=static_cast<int>(dim);
    tmp.resize(data1.size());
    for(int i{0};i<=dim-1;i++)
    {
        for(int j{0};j<=dim-1;j++)
        {
            T val{0};
            for(int k{0};k<=dim-1;k++)
            {
                val+=data1[dim*i+k]*data2[dim*k+j];
            }
            tmp[dim*i+j]=val;
        }
    }
    return tmp;
}

template<typename T>
std::vector<T> mat_mul(std::vector<T> && data1,std::vector<T> const& data2)
{
    std::vector<T> tmp_vec;
    double dim{std::sqrt(data1.size())};
    //check if given matrices are square matrices
    if(dim-std::floor(dim)!=0)
    {
        std::cout<<"Given matrices are not square matrices."<<std::endl;
        std::exit(-1);
    }
    dim=static_cast<int>(dim);
    tmp_vec.resize(dim);
    for(int i{0};i<=dim-1;i++)
    {
        for(int j{0};j<=dim-1;j++)
        {
            T val{0};
            for(int k{0};k<=dim-1;k++)
            {
                val+=data1[dim*i+k]*data2[dim*k+j];
            }
            tmp_vec[j]=val;
        }
        for(int j{0};j<=dim-1;j++)
        {
            data1[dim*i+j]=tmp_vec[j];
        }
    }
    return std::move(data1);
}

//--------------------------------------------------------------------------------------------------------

//common lambdas:
auto add=[](auto const& x,auto const& y){return x+y;};
auto sub=[](auto const& x,auto const& y){return x-y;};

//--------------------------------------------------------------------------------------------------------

//matrix struct (square matrices only)
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
    matrix():dim{0}
    {
        data.resize(static_cast<T>(0));
    }
    //parameterized default #1
    matrix(int n):dim{n}
    {
        data.resize(static_cast<size_t>(dim*dim));
        std::transform(data.cbegin(),data.cend(),data.begin(),[](auto const& x){return 0*x;});
    }
    //paramterized default #2
    matrix(std::vector<T> vec):data{vec}
    {
        double n=std::sqrt(static_cast<double>(vec.size()));
        if(n-std::floor(n)!=0.)
        {
            std::cout<<"Square matrix cannot be created."<<std::endl;
            std::exit(-1);
        }
        dim=static_cast<int>(n);
    }
    //parameterized default #3
    matrix(int n,std::vector<T> vec): dim{n}, data{vec}
    {
        if(static_cast<double>(dim)-std::sqrt(static_cast<double>(vec.size())))
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
        double N=std::sqrt(static_cast<double>(n));
        if(N-std::floor(N)!=0)
            {
                std::cout<<"Matrix dimension is not appropriate."<<std::endl;
                std::exit(-1);
            }
        dim=static_cast<int>(N);
		data.resize(static_cast<size_t>(n));
		for(int i=0;i<=n-1;i++)
        {
            data[i]=f(i);
        }
	}
    //function of 2 indices
    template<typename F>
    matrix(index2,F f,int n): dim{n}
    {
        data.resize(static_cast<size_t>(n*n));
        for(int i=0;i<=n-1;i++)
        {
            for(int j=0;j<=n-1;j++)
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
    T const & operator()(int i,int j)const
    {
        return data[dim*i+j];
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
        std::vector<T> tmp=mat_mul((*this).data,m.data);        
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
    std::vector<T> get_data() const
    {
        return (*this).data;
    }

//--------------------------------------------------------------------------------------------------------

    //addititon of matrices (+)
    //4 types
    friend matrix<T> operator+(matrix<T> const& m1,matrix<T> const& m2)
    {
        int n=m1.get_dim();
        auto madd=[&](int i){std::vector<T> vec;vec.resize(static_cast<size_t>(n*n));detail::transform2(m1.get_data(),m2.get_data(),vec,add);return vec[i];};
        matrix<T> result(one,madd,n*n);
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
        auto msub=[&](int i){std::vector<T> vec;vec.resize(static_cast<size_t>(n*n));detail::transform2(m1.get_data(),m2.get_data(),vec,sub);return vec[i];};
        matrix<T> result(one,msub,n*n);
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
        auto mmulscl=[&](int i){std::vector<T> vec;vec.resize(static_cast<size_t>(n*n));detail::transform1(m.get_data(),vec,[&](T const& x){return x*scl;});return vec[i];};
        matrix<T> result(one,mmulscl,n*n);
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
        auto mmulscl=[&](int i){std::vector<T> vec;vec.resize(static_cast<size_t>(n*n));detail::transform1(m.get_data(),vec,[&](T const& x){return scl*x;});return vec[i];};
        matrix<T> result(one,mmulscl,n*n);
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
        auto mdivscl=[&](int i){std::vector<T> vec;vec.resize(static_cast<size_t>(n*n));detail::transform1(m.get_data(),vec,[&](T const& x){return x/scl;});return vec[i];};
        matrix<T> result(one,mdivscl,n*n);
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
        auto mmulm=[&](int i){std::vector<T> vec=mat_mul(m1.get_data(),m2.get_data());return vec[i];};
        matrix<T> result(one,mmulm,n*n);
        return result;
    }
    friend matrix<T> && operator*(matrix<T> const& m1, matrix<T> && m2)
    {
        std::vector<T> tmp=mat_mul(m1.get_data(),m2.get_data());
        m2.data.swap(tmp);
        return std::move(m2);
    }
    friend matrix<T> && operator*(matrix<T> && m1, matrix<T> const& m2)
    {
        std::vector<T> tmp=mat_mul(m1.get_data(),m2.get_data());
        m1.data.swap(tmp);
        return std::move(m1);
    }
    friend matrix<T> && operator*(matrix<T> && m1, matrix<T> && m2)
    {
        std::vector<T> tmp=mat_mul(m1.get_data(),m2.get_data());
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
                o<<m.get_data()[j]<<",";
            }
            o<<m.get_data()[n*n-1];
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





