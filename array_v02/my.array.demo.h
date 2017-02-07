#include"my.array.hpp"
#include<iostream>
using namespace std;

inline void __log_info( std::ostream & out, void const * address, const char * function )
{
	out << "Log: [" << address << "] " << function << std::endl;
}
#define __log_info__( address ) __log_info( std::clog, address, __PRETTY_FUNCTION__ )

template<typename T>
struct Foo
{
	T data;
	Foo(): data(){ __log_info__( this ); }
	Foo( Foo<T> const & v ): data(v.data){ __log_info__( this ); }
	Foo( T const & x ): data(x){ __log_info__( this ); }
	template<typename U> Foo( U const & x ): data(x){ __log_info__( this ); }
	template<typename U> Foo( Foo<U> const & v ): data(v.data){ __log_info__( this ); }
	~Foo(){ __log_info__( this ); }
	operator T&(){ return this->data; }
	operator T const&()const{ return this->data; }

	Foo<T> & operator=( T const & v);
	Foo<T> & operator=( Foo<T> const & v);
	template<typename U> Foo<T> & operator=( U const & v);
	template<typename U> Foo<T> & operator=( Foo<U> const & v);

	std::ostream & operator<<( std::ostream & out )const{ out << this->data; return out;}
	std::istream & operator>>( std::istream & inp ){ inp >> this->data; return inp; }
};
template<typename T> Foo<T> & Foo<T>::operator=( T const & v )
{
	if( this == &v ) return *this;
	this->data = v;
	return *this;
}
template<typename T> Foo<T> & Foo<T>::operator=( Foo<T> const & v )
{
	if( this == &v ) return *this;
	this->data = v.data;
	return *this;
}
template<typename T> template<typename U> Foo<T> & Foo<T>::operator=( Foo<U> const & v)
{
	if( this == &v ) return *this;
	this->data = v.data;
	return *this;
}
template<typename T> template<typename U> Foo<T> & Foo<T>::operator=( U const & v )
{
	if( this == &v ) return *this;
	this->data = v;
	return *this;
}

template<typename T> inline void print_vec( T const & vec, const char * name )
{
	std::cout << name << ".size: " << vec.size() << std::endl;
	std::cout << name << ".data: [" << vec.data() << "]" << std::endl;
	for(int i = 0; i < vec.size(); ++i)
		std::cout << i << ": " << vec[i] << std::endl;
}

template<typename T>
int demo_arr()
{
	const std::size_t size = 4;
	my_array<T, size> a1;
	print_vec( a1, "a1" );
	const int x = 7;
	my_array<T, size> a2( x );
	print_vec( a2, "a2" );
	my_array<T, size> a3( x, 3 );
	print_vec( a3, "a3" );

	my_array<int, size> a4 = {1, 118};
	print_vec( a4, "a4" );

	my_array<T, size+1> a5( a4 );
	print_vec( a5, "a5" );
	my_array<T, size-1> a6( a4 );
	print_vec( a6, "a6" );
	return 0;
}

int main()
{
	return demo_arr<Foo<double> >();
}
