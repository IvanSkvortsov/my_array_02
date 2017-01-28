#include<iostream>
#include"my.array.hpp"
#include"print.met.h"
#include"foo.h"

template<typename T> int test_assign( const typename my_array::size_type size = 3 );
int main()
{
	return test_assign<Foo<float> >();
}

template<typename T> int test_assign( const typename my_array::size_type size )
{
	using std::cerr;
	using std::cout;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	my_array_t<T> a( size, 5 );
	a.assign( size, 7 );// assign( size_type , U const & ) [with U = int]
	print_vec( a, "vec:a" );

	double x = 6;
	a.assign( size+1, x );// assign( size_type , U const & ) [with U = double]
	print_vec( a, "vec:a" );

	a.assign( size, &x, 1 );// assign( size_type , U const * const , const int )
	print_vec( a, "vec:a" );

	my_array_t<int> b( size+1, 1);
	a.assign( b );// assign( my_array_t<U> const & )
	print_vec( a, "vec:a" );

	a.assign( b.data(), b.data() + b.size() - 1 );// assign( U const * , U const * )
	print_vec( a, "vec:a" );

	a.assign( b.size(), b.data(), 0 );// assign( size_type , U const * const , const int )
	print_vec( a, "vec:a" );

	a.resize( b.size() - 1 );
	print_vec( a, "vec:a" );
	return 0;
}
