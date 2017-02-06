#ifndef __MY_RANGE_ALLOCATOR_HPP__
#define __MY_RANGE_ALLOCATOR_HPP__
#include<utility>// move
#include<cstring>// memcpy

template<typename T>
class my_range_allocator
{
public:
	typedef T value_type;
	typedef T * pointer;
	typedef T const * const_pointer;
	typedef T & reference;
	typedef T const & const_reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;

	my_range_allocator(){}
	my_range_allocator( my_range_allocator<T> const & ){}
	template<typename U> my_range_allocator( my_range_allocator<U> const & ){}
	~my_range_allocator(){}

	static void construct( pointer data ){ new (data) value_type(); }
	static void construct( pointer data, const_reference x ){ new (data) value_type(x); }
	template<typename U> static void construct( pointer data, U const & x ){ new (data) value_type(x); }
	static void move_construct( pointer data, reference x ){ new (data) value_type( std::move(x) ); }
	static void destroy( pointer data ){ data->~value_type(); }
	static void assign( reference lhs ){ lhs = 0; }
	static void assign( reference lhs, const_reference rhs ){ lhs = rhs; }
	template<typename U> static void assign( reference lhs, U const & rhs ){ lhs = rhs; }

	static void construct( pointer data, size_type size );
	static void construct_v( pointer data, const_pointer v, size_type size );
	static void construct_s( pointer data, const_reference x, size_type size );
	template<typename U> static void construct_v( pointer data, U const * v, size_type size );
	template<typename U> static void construct_s( pointer data, U const & x, size_type size );
	static void move_construct_v( pointer data, pointer v, size_type size );
	static void destroy( pointer data, size_type size );
	static void assign( pointer data, size_type size );
	static void assign_v( pointer data, const_pointer v, size_type size );
	static void assign_s( pointer data, const_reference v, size_type size );
	template<typename U> static void assign_v( pointer data, U const * v, size_type size );
	template<typename U> static void assign_s( pointer data, U const & v, size_type size );
};

template<typename T> inline void my_range_allocator<T>::assign( pointer data, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::assign( *data );
}
template<typename T> inline void my_range_allocator<T>::assign_v( pointer data, const_pointer x, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::assign( *data, *x++ );
}
template<typename T> inline void my_range_allocator<T>::assign_s( pointer data, const_reference x, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::assign( *data, x );
}
template<typename T> template<typename U> inline void my_range_allocator<T>::assign_v( pointer data, U const * x, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::assign( *data, *x++ );
}
template<typename T> template<typename U> inline void my_range_allocator<T>::assign_s( pointer data, U const & x, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::assign( *data, x );
}
template<typename T> inline void my_range_allocator<T>::construct( pointer data, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::construct( data );
}
template<typename T> inline void my_range_allocator<T>::construct_v( pointer data, const_pointer v, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::construct( data, *v++ );
}
template<typename T> inline void my_range_allocator<T>::construct_s( pointer data, const_reference x, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::construct( data, x );
}
template<typename T> inline void my_range_allocator<T>::move_construct_v( pointer data, pointer v, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::move_construct( data, *v++ );
}
template<typename T> template<typename U> inline void my_range_allocator<T>::construct_v( pointer data, U const * v, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::construct( data, *v++ );
}
template<typename T> template<typename U> inline void my_range_allocator<T>::construct_s( pointer data, U const & x, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::construct( data, x );
}
template<typename T> inline void my_range_allocator<T>::destroy( pointer data, size_type size )
{
	for( const_pointer _end = data + size; data != _end; ++data )
		my_range_allocator<T>::destroy( data );
}

#define __MY_RANGE_ALLOCATOR_SPEC1( TYPE1 )\
template<> inline void my_range_allocator<TYPE1>::construct( pointer data, size_type size )\
{\
	memset( data, 0, size * sizeof(value_type) );\
}\
template<> inline void my_range_allocator<TYPE1>::construct_v( pointer data, const_pointer v, size_type size )\
{\
	memcpy( data, v, size * sizeof(value_type) );\
}\
template<> inline void my_range_allocator<TYPE1>::construct_s( pointer data, const_reference x, size_type size )\
{\
	my_range_allocator<TYPE1>::assign_s( data, x, size );\
}\
template<> inline void my_range_allocator<TYPE1>::move_construct_v( pointer data, pointer v, size_type size )\
{\
	memcpy( data, v, size * sizeof(value_type) );\
}\
template<> inline void my_range_allocator<TYPE1>::destroy( pointer data, size_type size ){}\
template<> inline void my_range_allocator<TYPE1>::construct( pointer data ){ memset( data, 0, sizeof(value_type) ); }\
template<> inline void my_range_allocator<TYPE1>::construct( pointer data, const_reference x )\
{\
	my_range_allocator<TYPE1>::assign( *data, x );\
}\
template<> inline void my_range_allocator<TYPE1>::move_construct( pointer data, reference x )\
{\
	my_range_allocator<TYPE1>::assign( *data, x );\
}\

#define __MY_RANGE_ALLOCATOR_SPEC2( TYPE1, TYPE2 )\
template<> template<> inline void my_range_allocator<TYPE1>::construct_v( pointer data, TYPE2 const * v, size_type size )\
{\
	my_range_allocator<TYPE1>::assign_v( data, v, size );\
}\
template<> template<> inline void my_range_allocator<TYPE1>::construct_s( pointer data, TYPE2 const & x, size_type size )\
{\
	my_range_allocator<TYPE1>::assign_s( data, x, size );\
}\
template<> template<> inline void my_range_allocator<TYPE1>::construct( pointer data, TYPE2 const & x )\
{\
	my_range_allocator<TYPE1>::assign( data, x );\
}

#define __MY_RANGE_ALLOCATOR_SPEC2_1( TYPE1 )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, char )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, short )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, int )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, long int )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, long long int )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, unsigned char )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, unsigned short )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, unsigned int )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, unsigned long int )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, unsigned long long int )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, float )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, double )\
__MY_RANGE_ALLOCATOR_SPEC2( TYPE1, long double )\
__MY_RANGE_ALLOCATOR_SPEC1( TYPE1 )

__MY_RANGE_ALLOCATOR_SPEC2_1( char );
__MY_RANGE_ALLOCATOR_SPEC2_1( short );
__MY_RANGE_ALLOCATOR_SPEC2_1( int );
__MY_RANGE_ALLOCATOR_SPEC2_1( long int );
__MY_RANGE_ALLOCATOR_SPEC2_1( long long int );
__MY_RANGE_ALLOCATOR_SPEC2_1( unsigned char );
__MY_RANGE_ALLOCATOR_SPEC2_1( unsigned short );
__MY_RANGE_ALLOCATOR_SPEC2_1( unsigned int );
__MY_RANGE_ALLOCATOR_SPEC2_1( unsigned long int );
__MY_RANGE_ALLOCATOR_SPEC2_1( unsigned long long int );
__MY_RANGE_ALLOCATOR_SPEC2_1( float );
__MY_RANGE_ALLOCATOR_SPEC2_1( double );
__MY_RANGE_ALLOCATOR_SPEC2_1( long double );

#endif//__MY_RANGE_ALLOCATOR_HPP__
