#include<iostream>
#include<iomanip>
#include"my.vector.hpp"
#include"print.met.h"
#include"foo.h"

template<typename T> int test_ctor( const typename my_vector::size_type size = 3 );
int main()
{
	return test_ctor<Foo<long double> >();
}

template<typename T> int test_ctor( const typename my_vector::size_type size )
{
	using std::cerr;
	using std::cout;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	my_vector_t<T> a;// ctor()
	a.resize( size );
	my_vector_t<int> b( size );// ctor( size_type )
	my_vector_t<T> c( a );// copy-ctor
	my_vector_t<T> d( b );// copy-ctor
	print_vec( a, "vec:a", 1 );
	print_vec( b, "vec:b", 1 );
	print_vec( c, "vec:c", 1);
	print_vec( d, "vec:d", 1 );
	my_vector_t<T> e( std::move(a) );// move-ctor
	my_vector_t<T> f = {1, 3, 8};// copy list-initialization
	my_vector_t<T> g{1, 3, 8};// direct list-initialization
	my_vector_t<int> h{1, 3, 8};// direct list-initialization
	my_vector_t<T> k( size, 2 );// ctor( size_type , U const & )
	cout << "------" << endl;
	print_vec( a, "vec:a", 1 );
	print_vec( e, "vec:e", 1 );
	print_vec( f, "vec:f", 1 );
	print_vec( g, "vec:g", 1 );
	print_vec( h, "vec:h", 1 );
	print_vec( k, "vec:k", 1 );
	int v[size] = {1, 3, 8};
	my_vector_t<T> l( v, v + size );
	print_vec( l, "vec:l", 1 );
	return 0;
}
