#include<iostream>
#include<iomanip>
#include"my.array.hpp"
#include"print.met.h"
#include"foo.h"

template<typename T> int test_ctor( const typename my_array::size_type size = 3 );
int main()
{
	return test_ctor<Foo<long double> >();
}

template<typename T> int test_ctor( const typename my_array::size_type size )
{
	using std::cerr;
	using std::cout;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	my_array_t<T> a;// ctor()
	a.resize( size );
	my_array_t<int> b( size );// ctor( size_type )
	my_array_t<T> c( a );// copy-ctor
	my_array_t<T> d( b );// copy-ctor
	print_vec( a, "vec:a" );
	print_vec( b, "vec:b" );
	print_vec( c, "vec:c" );
	print_vec( d, "vec:d" );
	my_array_t<T> e( std::move(a) );// move-ctor
	my_array_t<T> f = {1, 3, 8};// copy list-initialization
	my_array_t<T> g{1, 3, 8};// direct list-initialization
	my_array_t<int> h{1, 3, 8};// direct list-initialization
	my_array_t<T> k( size, 2 );// ctor( size_type , U const & )
	cout << "------" << endl;
	print_vec( a, "vec:a" );
	print_vec( e, "vec:e" );
	print_vec( f, "vec:f" );
	print_vec( g, "vec:g" );
	print_vec( h, "vec:h" );
	print_vec( k, "vec:k" );
	int v[size] = {1, 3, 8};
	my_array_t<T> l( v, v + size );
	print_vec( l, "vec:l" );
	return 0;
}
