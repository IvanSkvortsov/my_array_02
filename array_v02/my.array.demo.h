#include"my.array.h"
#include"my.array.hpp"
#include<iostream>
#include<iomanip>
#include<cstdlib>// atoi
#include"print.met.h"
#include"foo.h"
#include<vector>
using namespace std;

template<typename T> inline void print_p( T const * p, const char * name )
{
	std::cout << std::setw(5) << name << " : [" << (void const * )p << "]  " << ( p ? *p : 0 ) << std::endl;
}
template<typename T> inline void print_t( const int i, T const & v )
{
	std::cout << std::setw(4) << i << ": " << std::setw(20) << (int)v << "  [" << (void const *)&v << "]" << std::endl;
}
template<typename T>
inline void print_v( T const & v, char const * name )
{
	std::cout << name << ".capacity: " << v.capacity() << std::endl;
	std::cout << name << ".size    : " << v.size() << std::endl;
	std::cout << name << ".data    : [" << v.data() << "]" << std::endl;
}

int my_array_demo( char * arg )
{
	const uint32_t size = atoi( arg );
	my_array a;
	print_v( a, "vec:a" );
	a.resize( size );
	print_v( a, "vec:a" );
	a.reserve( size + 3 );

	cout << "-------" << endl;
	my_array b( std::move(a) );
	print_v( a, "vec:a" );
	print_v( b, "vec:b" );

	cout << "-------" << endl;
	b.shrink_to_fit();
	print_v( b, "vec:b" );
	
	cout << "-------" << endl;
	my_array c;
	c.operator=( std::move(b) );
	print_v( b, "vec:b" );
	print_v( c, "vec:c" );

	cout << "-------" << endl;
	my_array d( c );
	print_v( d, "vec:d" );

	return 0;
}

template<typename T>
int my_array_t_demo( char * arg )
{
	const uint32_t size = atoi( arg );
	if( (int32_t)size <= 0 )
		return 1;
	my_array_t<int> a1;
	print_vec( a1, "a1" );
	cout << "-------" << endl;
	a1.resize( size );
	print_v( a1, "a1" );
	for(int i = 0; i < a1.size(); ++i )
		a1[i] = 2 * i + 1;
	cout << "-------" << endl;
	my_array_t<T> a2( a1 );// copy ctor [with T]
	print_v( a2, "a2" );

	cout << "-------" << endl;
	my_array_t<int> b1( size, 7 );// ctor [with T = int]
	print_v( b1, "b1" );
	cout << "-------" << endl;
	my_array_t<T> b2( b1 );// copy ctor [with T, with U = int]
	print_v( b2, "b2" );

	cout << "-------" << endl;
	my_array_t<T> c1{ 1, 4, 9};
	print_v( c1, "c1" );
	cout << "-------" << endl;
	my_array_t<int> c2{ 1, 4, 9};
	print_v( c2, "c2" );

	cout << "-------" << endl;
	vector<T> d1( 2 );
	print_v( d1, "d1" );
	vector<T> d2{1, 4, 9};
	print_v( d2, "d2" );
	/*
	cout << "-------" << endl;
	my_array_t<T> d1( 2 );
	print_vec( d1, "d1" );
	*/

	return 0;
}

int main( int argc, char ** argv )
{
	if( argc != 2 )
	{
		cerr << "Error: [main] usage './main.exe num'" << endl;
		return 1;
	}
	return my_array_t_demo<Foo<long double> >( argv[1] );
	//return my_array_t_demo<long double>( argv[1] );
	//return my_array_demo( argv[1] );
	//return my_array_t_demo<uint32_t>( argv[1] );
	//return my_array_demo<uint16_t>( argv[1] );
	//return my_array_demo<uint8_t>( argv[1] );
}
