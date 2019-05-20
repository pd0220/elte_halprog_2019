#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <initializer_list>
#include <string>
#include <sstream>
#include <future>
#include <thread>

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
struct index0{};
struct index1{};
struct index2{};

index0 zero;
index1 one;
index2 two;

//--------------------------------------------------------------------------------------------------------

//matrix multiplication function for square matrices
//3 types
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
std::vector<T> && mat_mul(std::vector<T> const& data1,std::vector<T> const& data2,std::vector<T> & data3,int n)
{
    std::vector<T> tmp_vec(n);
    if(&data3==&data1)
    {
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
                data3[n*i+j]=tmp_vec[j];
            }
        }
        return std::move(data3);
    }
    else
    {
        for(int i{0};i<=n-1;i++)
        {
            for(int j{0};j<=n-1;j++)
            {
                T val{0};
                for(int k{0};k<=n-1;k++)
                {
                    val+=data1[n*j+k]*data2[n*k+i];
                }
                tmp_vec[j]=val;
            }
            for(int j{0};j<=n-1;j++)
            {
                data3[n*j+i]=tmp_vec[j];
            }
        }
        return std::move(data3);
    }
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
    matrix(int n):dim{n},data{std::vector<T>(n*n,(T)0)}{}
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
    
    //function
    template<typename F>
    matrix(index0,F f,int n):dim{n}
    {
        data.resize(static_cast<size_t>(n*n));
        for(int i{0};i<=n*n-1;i++)
        {
            data[i]=f();
        }
    }
    
    //function of 1 index
    template<typename F>
    matrix(index1,F f,int n):dim{n}
    {
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
        auto mmulm=[&](int i,int j,int it0,int it1){T val{0};for(int k=it0;k<it1;k++) val+=(*this).data[dim*i+k]*m.data[dim*k+j];return val;};

        auto mmulm_par=[&](int i,int j){int max_num_of_threads=(int)std::thread::hardware_concurrency();
                                        auto max_num_of_threads_auto=std::thread::hardware_concurrency();
                                        std::vector<std::future<double>> futures(max_num_of_threads_auto);
                                        for(int m=0;m<max_num_of_threads;m++){auto it0=m*dim/max_num_of_threads_auto;
                                                                              auto it1=(m+1)*dim/max_num_of_threads_auto;
                                                                              futures[m]=std::async(mmulm,i,j,it0,it1);}
                                                                              auto parallel_result=std::accumulate(futures.begin(),futures.end(),0.0,[](double acc,std::future<double>& f){return acc+f.get();});
                                        return parallel_result;};
        
        matrix<T> tmp(two,mmulm_par,dim);
        (*this).data.swap(tmp.data);
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
    std::vector<T> const& get_data() const
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
        return matrix<T>(one,madd,n);
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
        return matrix<T>(one,msub,n);
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
        return matrix<T>(one,mmulscl,n);
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
        return matrix<T>(one,mmulscl,n);
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
        return matrix<T>(one,mdivscl,n);
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
        
        auto mmulm=[&](int i,int j,int it0,int it1){T val{0};for(int k=it0;k<it1;k++) val+=m1(i,k)*m2(k,j);return val;};

        auto mmulm_par=[&](int i,int j){int max_num_of_threads=(int)std::thread::hardware_concurrency();
                                        auto max_num_of_threads_auto=std::thread::hardware_concurrency();
                                        std::vector<std::future<double>> futures(max_num_of_threads_auto);
                                        for(int m=0;m<max_num_of_threads;m++){auto it0=m*n/max_num_of_threads_auto;
                                                                              auto it1=(m+1)*n/max_num_of_threads_auto;
                                                                              futures[m]=std::async(mmulm,i,j,it0,it1);}
                                                                              auto parallel_result=std::accumulate(futures.begin(),futures.end(),0.0,[](double acc,std::future<double>& f){return acc+f.get();});
                                        return parallel_result;};
        
        return matrix<T>(two,mmulm_par,n);        
    }
    friend matrix<T> && operator*(matrix<T> const& m1, matrix<T> && m2)
    {
        int n=m1.get_dim();
        auto mmulm=[&](int i,int j,int it0,int it1){T val{0};for(int k=it0;k<it1;k++) val+=m1(i,k)*m2(k,j);return val;};

        auto mmulm_par=[&](int i,int j){int max_num_of_threads=(int)std::thread::hardware_concurrency();
                                        auto max_num_of_threads_auto=std::thread::hardware_concurrency();
                                        std::vector<std::future<double>> futures(max_num_of_threads_auto);
                                        for(int m=0;m<max_num_of_threads;m++){auto it0=m*m1.get_dim()/max_num_of_threads_auto;
                                                                              auto it1=(m+1)*m1.get_dim()/max_num_of_threads_auto;
                                                                              futures[m]=std::async(mmulm,i,j,it0,it1);};
                                                                              auto parallel_result=std::accumulate(futures.begin(),futures.end(),0.0,[](double acc,std::future<double>& f){return acc+f.get();});
                                        return parallel_result;};
        
        matrix<T> tmp(two,mmulm_par,n);
        m2.data.swap(tmp.data);
        return std::move(m2);
    }
    friend matrix<T> && operator*(matrix<T> && m1, matrix<T> const& m2)
    {
        int n=m1.get_dim();
        auto mmulm=[&](int i,int j,int it0,int it1){T val{0};for(int k=it0;k<it1;k++) val+=m1(i,k)*m2(k,j);return val;};

        auto mmulm_par=[&](int i,int j){int max_num_of_threads=(int)std::thread::hardware_concurrency();
                                        auto max_num_of_threads_auto=std::thread::hardware_concurrency();
                                        std::vector<std::future<double>> futures(max_num_of_threads_auto);
                                        for(int m=0;m<max_num_of_threads;m++){auto it0=m*m1.get_dim()/max_num_of_threads_auto;
                                                                              auto it1=(m+1)*m1.get_dim()/max_num_of_threads_auto;
                                                                              futures[m]=std::async(mmulm,i,j,it0,it1);};
                                                                              auto parallel_result=std::accumulate(futures.begin(),futures.end(),0.0,[](double acc,std::future<double>& f){return acc+f.get();});
                                        return parallel_result;};
        
        matrix<T> tmp(two,mmulm_par,n);
        m1.data.swap(tmp.data);
        return std::move(m1);
    }
    friend matrix<T> && operator*(matrix<T> && m1, matrix<T> && m2)
    {
        int n=m1.get_dim();
        auto mmulm=[&](int i,int j,int it0,int it1){T val{0};for(int k=it0;k<it1;k++) val+=m1(i,k)*m2(k,j);return val;};

        auto mmulm_par=[&](int i,int j){int max_num_of_threads=(int)std::thread::hardware_concurrency();
                                        auto max_num_of_threads_auto=std::thread::hardware_concurrency();
                                        std::vector<std::future<double>> futures(max_num_of_threads_auto);
                                        for(int m=0;m<max_num_of_threads;m++){auto it0=m*m1.get_dim()/max_num_of_threads_auto;
                                                                              auto it1=(m+1)*m1.get_dim()/max_num_of_threads_auto;
                                                                              futures[m]=std::async(mmulm,i,j,it0,it1);};
                                                                              auto parallel_result=std::accumulate(futures.begin(),futures.end(),0.0,[](double acc,std::future<double>& f){return acc+f.get();});
                                        return parallel_result;};
        
        matrix<T> tmp(two,mmulm_par,n);
        m1.data.swap(tmp.data);
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
        auto restore_stream=[state=i.rdstate(),pos=i.tellg(),&i](){i.seekg(pos);i.clear();i.setstate(state);};

        std::string s_tmp;
        std::getline(i,s_tmp);
        std::stringstream ii(s_tmp);
    
        std::getline(ii,s_tmp,';');
        if(s_tmp.size()==0){restore_stream();return i;}
        int d_tmp=std::stoi(s_tmp);

        std::vector<T> v_tmp;

        for(int j{0};j<=d_tmp*d_tmp-2;j++)
        {
            std::getline(ii,s_tmp,',');
            if(s_tmp.size()==0){restore_stream();return i;}
            std::stringstream ss_tmp(s_tmp);
            T t_tmp;
            ss_tmp>>t_tmp;
            v_tmp.push_back(t_tmp);
        }

        std::getline(ii,s_tmp);
        if(s_tmp.size()==0){restore_stream();return i;}
        std::stringstream ss_tmp(s_tmp);
        T t_tmp;
        ss_tmp>>t_tmp;
        v_tmp.push_back(t_tmp);

        if(static_cast<size_t>(d_tmp*d_tmp)==v_tmp.size())
        {
            m.dim=d_tmp;
            m.data=std::move(v_tmp);
        }
        else
        {
            std::cout<<"Matrix dimension is not appropriate."<<std::endl;
            restore_stream();
        }
        
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
        std::cout<<"Given matrix size is not 0."<<std::endl;
        std::exit(-1);
    }
}