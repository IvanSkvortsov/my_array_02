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
inline void print_v( const std::size_t size, void const * data, char const * name )
{
	cout << name << ".size: " << size << endl;
	cout << name << ".data: [" << data << "]" << endl;
}

int my_array_demo( char * arg )
{
	const uint32_t size = atoi( arg );
	my_array a;
	print_v( a.size(), a.data(), "a" );
	a.resize( size );
	print_v( a.size(), a.data(), "a" );

	cout << "-------" << endl;
	my_array b( std::move(a) );
	print_v( b.size(), b.data(), "b" );
	print_v( a.size(), a.data(), "a" );
	
	cout << "-------" << endl;
	my_array c;
	c.operator=( std::move(b) );
	print_v( c.size(), c.data(), "c" );
	print_v( b.size(), b.data(), "b" );
	return 0;
}

template<typename T>
int my_array_t_demo( char * arg )
{
	const uint32_t size = atoi( arg );
	if( (int32_t)size <= 0 )
		return 1;
	/*
	my_array_t<T> a1;
	print_vec( a1, "a1" );
	cout << "-------" << endl;
	a1.resize( size );
	for(int i = 0; i < a1.size(); ++i )
		a1[i] = 2 * i + 1;
	print_vec( a1, "a1" );
	cout << "-------" << endl;
	my_array_t<T> a2( a1 );// copy ctor [with T, with U]
	print_vec( a2, "a2" );

	cout << "-------" << endl;
	my_array_t<int> b1( size, 7 );// ctor [with T = int]
	print_vec( b1, "b1" );
	cout << "-------" << endl;
	my_array_t<T> b2( b1 );// copy ctor [with T, with U = int]
	print_vec( b2, "b2" );
	*/

	cout << "-------" << endl;
	my_array_t<T> c1{ 1, 4, 9};
	print_vec( c1, "c1" );
	cout << "-------" << endl;
	my_array_t<int> c2{ 1, 4, 9};
	print_vec( c2, "c2" );

	cout << "-------" << endl;
	vector<T> d1( 2 );
	print_vec( d1, "d1" );
	vector<T> d2{1, 4, 9};
	print_vec( d2, "d2" );
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
	//return my_array_demo<uint64_t>( argv[1] );
	//return my_array_t_demo<uint32_t>( argv[1] );
	//return my_array_demo<uint16_t>( argv[1] );
	//return my_array_demo<uint8_t>( argv[1] );
}
