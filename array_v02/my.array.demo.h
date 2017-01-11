#include"my.array.h"
#include"my.array.hpp"
#include<iostream>
#include<iomanip>
#include<cstdlib>// atoi
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
int my_array_demo( char * arg )
{
	const uint32_t size = atoi( arg );
	my_array_t<T> a;
	cout << "a.size: " << a.size() << endl;
	cout << "a.data: [" << (void *)a.data() << "]" << endl;
	a.resize( size );
	cout << "a.size: " << a.size() << endl;
	cout << "a.data: [" << (void *)a.data() << "]" << endl;
	T const * data = 0, * p = 0;
	data = a.data();
	p = ( data ? data + (a.size() - 1) : 0 );
	for(int i = 0; i < a.size(); ++i )
		a[i] = 2 * i + 1;
	for(int i = 0; i < a.size(); ++i )
		print_t( i, a[i] );
	cout << "a.size: " << a.size() << endl;
	print_p( data, "data" );
	print_p( p, "p" );
	for(int i = 0; i < a.size(); ++i )
		print_t( i, a[i] );
	my_array_t<T> b( a );
	print_p( data, "data" );
	print_p( p, "p" );
	cout << "b.size: " << b.size() << endl;
	for(int i = 0; i < b.size(); ++i )
		print_t( i, b[i] );
	return 0;
}

int main( int argc, char ** argv )
{
	if( argc != 2 )
	{
		cerr << "Error: [main] usage './main.exe num'" << endl;
		return 1;
	}
	return my_array_demo<long double>( argv[1] );
	//return my_array_demo<uint64_t>( argv[1] );
	//return my_array_demo<uint32_t>( argv[1] );
	//return my_array_demo<uint16_t>( argv[1] );
	//return my_array_demo<uint8_t>( argv[1] );
}
