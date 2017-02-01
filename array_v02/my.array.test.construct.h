#include<iostream>
#include<iomanip>
#include"my.array.hpp"
#include"print.met.h"
#include"foo.h"

template<typename T> int test_construct_full( const typename my_array_t<T>::size_type size = 4 );
template<typename T> int test_construct_head( const typename my_array_t<T>::size_type size = 4 );
template<typename T> int test_construct_tail( const typename my_array_t<T>::size_type size = 4 );
template<typename T> int test_construct();

int main()
{
	return test_construct<Foo<long double> >();
}

template<typename T> int test_construct()
{
	typedef typename my_array_t<T>::size_type size_type;
	using std::cerr;
	using std::endl;
	const size_type size = 5;
	int st = 0;
	st += test_construct_full<T>( size );
	st += test_construct_head<T>( size );
	st += test_construct_tail<T>( size );
	if( st )
	{
		cerr << "Error: from " << __PRETTY_FUNCTION__ << endl;
		return st;
	}
	return 0;
}

template<typename T> int test_construct_full( const typename my_array_t<T>::size_type size )
{
	__log_info__( test_construct_full<T> );
	using std::cerr;
	using std::cout;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: in function " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	int x = 1;
	const T v[size] = {1, 4, 5};
	my_array_t<T> a( size );// construct_full()
	print_vec( a, "vec:a", 1 );

	my_array_t<T> b( size, x );// construct_full_s( U const & )
	print_vec( b, "vec:b", 1 );

	my_array_t<T> c( v, v + size);// construct_full_v( U const * )
	print_vec( c, "vec:c", 1 );
	union{
		T * p;
		int i;
	} u;
	u.i = 102938;
	u.i = ~(u.i);
	const T * v2_start = u.p, * v2_end = 0;// v_end < v_start
	my_array_t<T> d( v2_start, v2_end);// error input parameter handling
	cout << "v_start: [" << v2_start << "], u.p: [" << u.p << "], u.i: " << u.i << endl;
	cout << "v_end  : [" << v2_end << "]" << endl;
	print_vec( d, "vec:d", 1 );
	return 0;
}

template<typename T> int test_construct_head( const typename my_array_t<T>::size_type size )
{
	/*
	__log_info__( test_construct_head<T> );
	using std::cerr;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: in function " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	int x = 1;
	const T v[size] = {1, 4, 5};
	my_array_t<T> a( size );// construct_full()
	my_array_t<T> b( size, x );// construct_full_s( U const & )
	my_array_t<T> c( v, v + size);// construct_full_v( U const * )
	print_vec( a, "vec:a", 1 );
	print_vec( b, "vec:b", 1 );
	print_vec( c, "vec:c", 1 );
	*/
	return 0;
}

template<typename T> int test_construct_tail( const typename my_array_t<T>::size_type size )
{
	__log_info__( test_construct_tail<T> );
	using std::cerr;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: in function " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	int x = 1;
	const T v[size] = {1, 4, 5};
	my_array_t<T> a;
	//a.assign( v, v + size );// construct_tail_v( U const *, size_type )
	a.assign( v, v + size );// construct_tail_v( U const *, size_type )
	print_vec( a, "vec:a", 1 );
	a.resize( size + 1 );// construct_tail( size_type )
	print_vec( a, "vec:a", 1 );
	a.assign( size + 2, x );// construct_tail_s( U const &, size_type )
	print_vec( a, "vec:a", 1 );
	return 0;
}

