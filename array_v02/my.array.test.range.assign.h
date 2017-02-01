#include<iostream>
#include"my.array.hpp"
#include"print.met.h"
#include"foo.h"

template<typename T> int test_range_assign( const typename my_array::size_type size = 3 );
int main()
{
	return test_range_assign<Foo<long double> >( 4 );
}

template<typename T> inline void _print_vec_( T const & vec, const char * name, std::ostream & out = std::cout )
{
	print_vec( vec, name, 1, out );
	out << "------" << std::endl;
}

template<typename T> void test_range_assign_s( my_array_t<T> & a );
template<typename T> void test_range_assign_v( my_array_t<T> & a );

template<typename T> int test_range_assign( const typename my_array::size_type size = 3 )
{
	using std::cerr;
	using std::cout;
	using std::endl;
	if( (long int)size < 0 )
	{
		cerr << "Error: " << __PRETTY_FUNCTION__ << ", negative size (which is " << (long int)size << " )" << endl;
		return 1;
	}
	my_array_t<T> a( size, 1 );
	_print_vec_( a, "vec:a" );

	test_range_assign_s( a );
	test_range_assign_v( a );
}

template<typename T> inline void test_range_assign_s( my_array_t<T> & a )
{
	__log_info__( test_range_assign_s<T> );
	typedef typename my_array::size_type size_type;
	const size_type size = a.size();

	a.range_assign_full_s( 3 );
	_print_vec_( a, "vec:a" );

	a.range_assign_head_s( size - 1, 4 );
	_print_vec_( a, "vec:a" );
	a.range_assign_head_s( -1, 7 );
	_print_vec_( a, "vec:a" );
	a.range_assign_head_s( -5, 5 );
	_print_vec_( a, "vec:a" );

	a.range_assign_tail_s( 1, 9 );
	_print_vec_( a, "vec:a" );
	a.range_assign_tail_s( -1, 9 );
	_print_vec_( a, "vec:a" );
	a.range_assign_tail_s( size+1, 1 );
	_print_vec_( a, "vec:a" );

	a.range_assign_mid_s(  1, size-1, 31 );
	_print_vec_( a, "vec:a" );
	//a.range_assign_mid_s( -1, size-1, 17 );// error: wrong 1st argument (which is -1)
	//_print_vec_( a, "vec:a" );
	//a.range_assign_mid_s(  1, size+1, 7 );// error: wrong 2nd argument (which is size+1)
	//_print_vec_( a, "vec:a" );
	a.range_assign_mid_s(  0, size-2, 7 );
	_print_vec_( a, "vec:a" );

	a.range_assign_s( 1 );
	a.range_assign_s( 7, 1u );
	_print_vec_( a, "vec:a" );
	a.range_assign_s( 4, 2u );
	_print_vec_( a, "vec:a" );

	std::cout << std::endl;
}

template<typename T> inline void test_range_assign_v( my_array_t<T> & a )
{
	__log_info__( test_range_assign_v<T> );
	typedef typename my_array::size_type size_type;
	const size_type size = a.size();

	T vec[size] = {1, 3, 7};

	a.range_assign_head_v( size - 1, vec );
	_print_vec_( a, "vec:a" );
	a.range_assign_head_v( -1, vec );
	_print_vec_( a, "vec:a" );
	a.range_assign_head_v( -5, vec );
	_print_vec_( a, "vec:a" );

	a.range_assign_full_v( vec );
	_print_vec_( a, "vec:a" );

	a.range_assign_tail_v( 1, vec );
	_print_vec_( a, "vec:a" );
	a.range_assign_tail_v( -2, vec );
	_print_vec_( a, "vec:a" );
	a.range_assign_tail_v( size+1, vec );
	_print_vec_( a, "vec:a" );

	int vec2[size] = {7, 17, 31, 43};
	a.range_assign_mid_v( 1, size-1, vec2 );
	_print_vec_( a, "vec:a" );
	//a.range_assign_mid_v( -1, size-1, vec2 );// error: wrong 1st argument
	//_print_vec_( a, "vec:a" );
	//a.range_assign_mid_v( 1, size+1, vec2 );// error: wrong 2nd argument
	//_print_vec_( a, "vec:a" );
	a.range_assign_mid_v( 0, size-2, vec2 );
	_print_vec_( a, "vec:a" );

	a.range_assign_v( vec );
	_print_vec_( a, "vec:a" );
	a.range_assign_v( vec, 1u );
	_print_vec_( a, "vec:a" );
}

