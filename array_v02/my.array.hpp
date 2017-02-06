#ifndef __MY_ARRAY_HPP__
#define __MY_ARRAY_HPP__
#include"my.array.h"
#include"my.array.config.h"
#include"global.log.info.h"
#include"global.error.msg.h"
#include<cassert>// assert

#include<utility>// move
#include<cstring>// memcpy, memset
#include<cstdlib>// exit

#define __IS_SUBROUTINE_INLINE__ 0

#if __IS_SUBROUTINE_INLINE__
  #define __INLINE_SUBR__ inline
#else
  #define __INLINE_SUBR__
#endif

template<typename LHS_T, typename RHS_T> inline void cast_assign( LHS_T & lhs, RHS_T const & rhs ){ lhs = rhs; }
template<typename LHS_T, typename RHS_T> inline void placement_copy_construct( LHS_T * lhs, RHS_T const & rhs ){ new (lhs) LHS_T(rhs); }
template<typename T> inline void placement_construct( T * lhs ){ new (lhs) T(); }
template<typename T> inline void placement_move_construct( T * lhs, T && rhs ){ new (lhs) T(std::move(rhs)); }

#define __PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T, RHS_T )\
template<> inline void placement_copy_construct( LHS_T * lhs, RHS_T const & rhs ){ cast_assign( *lhs, rhs ); }\

#define __PLACEMENT_CONSTRUCT_SPEC2_1( LHS_T )\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,                  float );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,                 double );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,            long double );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,                   char );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,                  short );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,                    int );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,               long int );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T,          long long int );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T, unsigned          char );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T, unsigned         short );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T, unsigned           int );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T, unsigned      long int );\
__PLACEMENT_COPY_CONSTRUCT_SPEC2( LHS_T, unsigned long long int );\
template<> inline void placement_construct( LHS_T * lhs ){ *lhs = 0; }\
template<> inline void placement_move_construct( LHS_T * lhs, LHS_T && rhs ){ cast_assign( *lhs, rhs ); }

__PLACEMENT_CONSTRUCT_SPEC2_1( float );
__PLACEMENT_CONSTRUCT_SPEC2_1( double );
__PLACEMENT_CONSTRUCT_SPEC2_1( long double );
__PLACEMENT_CONSTRUCT_SPEC2_1( char );
__PLACEMENT_CONSTRUCT_SPEC2_1( short );
__PLACEMENT_CONSTRUCT_SPEC2_1( int );
__PLACEMENT_CONSTRUCT_SPEC2_1( long int );
__PLACEMENT_CONSTRUCT_SPEC2_1( long long int );
__PLACEMENT_CONSTRUCT_SPEC2_1( unsigned char );
__PLACEMENT_CONSTRUCT_SPEC2_1( unsigned short );
__PLACEMENT_CONSTRUCT_SPEC2_1( unsigned int );
__PLACEMENT_CONSTRUCT_SPEC2_1( unsigned long int );
__PLACEMENT_CONSTRUCT_SPEC2_1( unsigned long long int );

template<typename T>
class my_array_t: public my_array
{
public:
	typedef T value_type;
	typedef T * pointer;
	typedef T const * const_pointer;
	typedef T & reference;
	typedef T const & const_reference;
	typedef typename my_array::size_type size_type;
protected:
	void destroy_full();
	void destroy_head( const size_type v_size );// from 0'th to (v_size-1)'th
	void destroy_tail( const size_type v_begin );// from v_begin'th to (this->size()-1)'th

	void construct_full();
	template<typename U> void construct_full_s( U const & x );
	template<typename U> void construct_full_v( U const * v );
	void move_construct_full_v( T * v );

	void construct_head( const size_type v_size );// 0 -> (v_size-1)
	template<typename U> void construct_head_s( U const & x, const size_type v_size );// 0 -> (v_size-1)
	template<typename U> void construct_head_v( U const * v, const size_type v_size );
	void move_construct_head_v( T * v,  const size_type v_size );

	void construct_tail( const size_type v_begin);// (v_begin) -> (this->size()-1)
	template<typename U> void construct_tail_s( U const & x, const size_type v_begin);// (v_begin) -> (this->size()-1)
	template<typename U> void construct_tail_v( U const * v, const size_type v_begin);
	void move_construct_tail_v( T * v,  const size_type v_begin);

	// assign: affects size and/or capacity of current array
	template<typename U> void assign( const size_type v_size, U const * const v_data, const int is_data_scalar );

	typedef struct my_array::array_struct array_struct;
	void set_size( size_type __size ){ this->my_array::set_size( __size * sizeof(value_type) ); }
public:
	my_array_t();
	my_array_t( my_array_t<T> const & v );// unless declared it is implicitly deleted because of move-ctor
	my_array_t( my_array_t<T> && v );
	my_array_t( std::initializer_list<T> init );// enables list-initialization, {T(1.05), T(4.1), ...}
	my_array_t( size_type __size );
	~my_array_t();
	// bonus =)
	template<typename U> my_array_t( my_array_t<U> const & v );// see copy-ctor comment
	template<typename U> my_array_t( U v_start, U v_end );
	template<typename U> my_array_t( size_type __size, U const & x );
	template<typename U> my_array_t( std::initializer_list<U> init );
	// operator=
	template<typename U> my_array_t<T> & operator=( my_array_t<U> const & v );
	my_array_t<T> & operator=( my_array_t<T> && v );
	// syntactic sugar to %assign( const size_type , U const * const , const int ):
	template<typename U> void assign( U const * v_data, U const * v_end ){ __log_info__( this ); this->assign( v_end - v_data, v_data, 0 ); }
	template<typename U> void assign( const size_type v_size, U const & x_data ){ __log_info__( this ); this->assign( v_size, &x_data, 1 ); }
	template<typename U> void assign( my_array_t<U> const & v ){ __log_info__( this ); this->assign( v.size(), v.data(), 0 ); }
	void resize( size_type __size ){ __log_info__( this ); this->assign( __size, (const_pointer)0, 0 ); }
	void reserve( size_type __size ){ __log_info__( this ); this->my_array::reserve( __size * sizeof(value_type) ); }
	// range_assign: doesn't affect size and capacity of current array
	template<typename U> void range_assign_v( U const * __x, const size_type __pos = 0u, const size_type __len = -1);
	template<typename U> void range_assign_s( U const & __x, const size_type __pos = 0u, const size_type __len = -1);
	template<typename U> void range_assign_full_v( U const * v_data );
	template<typename U> void range_assign_full_s( U const & v_data );
	template<typename U> void range_assign_head_v( const size_type v_size, U const * v_data );
	template<typename U> void range_assign_head_s( const size_type v_size, U const & v_data );
	template<typename U> void range_assign_tail_v( const size_type v_begin, U const * v_data );
	template<typename U> void range_assign_tail_s( const size_type v_begin, U const & v_data );
	template<typename U> void range_assign_mid_v( const size_type v_begin, const size_type v_size, U const * v_data );
	template<typename U> void range_assign_mid_s( const size_type v_begin, const size_type v_size, U const & v_data );
	// array like interface:
	pointer data(){ return (pointer )this->my_array::data(); }
	const_pointer data()const{ return (const_pointer )this->my_array::data(); }
	pointer data(int i){ return this->data() + i; }
	const_pointer data(int i)const{ return this->data() + i; }
	reference operator[]( size_type i ){ return *(this->data(i)); }
	const_reference operator[]( size_type i )const{ return *(this->data(i)); }
	size_type size()const{ return this->my_array::size()/sizeof(value_type); }
	size_type capacity()const{ return this->my_array::capacity()/sizeof(value_type); }
};

template<typename T> my_array_t<T>::my_array_t(): my_array()
{
	__log_info__( this );
}
template<typename T>
template<typename U> my_array_t<T>::my_array_t( my_array_t<U> const & v ): my_array( v.size() * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_v( v.data() );
}
template<typename T> my_array_t<T>::my_array_t( my_array_t<T> const & v ): my_array( v.my_array::size() )
{
	__log_info__( this );
	this->construct_full_v( v.data() );
}
template<typename T> my_array_t<T>::my_array_t( my_array_t<T> && v ): my_array( std::move( v ) )
{
	__log_info__( this );
}
template<typename T>
template<typename U> my_array_t<T>::my_array_t( size_type __size, U const & x ): my_array( __size * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_s( x );
}
template<typename T> my_array_t<T>::my_array_t( size_type __size ): my_array( __size * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full();
}
template<typename T>
template<typename U> my_array_t<T>::my_array_t( U v_start, U v_end ):
	my_array( (v_end > v_start) && v_start ? (v_end - v_start) * sizeof(value_type) : (size_type)0 )
{
	__log_info__( this );
	if( v_start )
		this->construct_full_v( v_start );
}
template<typename T> my_array_t<T>::my_array_t( std::initializer_list<T> init ): my_array( init.size() * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_v( init.begin() );
}
template<typename T>
template<typename U> my_array_t<T>::my_array_t( std::initializer_list<U> init ): my_array( init.size() * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_v( init.begin() );
}

template<typename T> my_array_t<T>::~my_array_t()
{
	__log_info__( this );
	this->destroy_full();
}

#define __MY_ARRAY_T_RANGE_ASSIGN1__( __x, __pos, __len, liter )\
do{\
if( __len == 0 )\
	return;\
const size_type t_size = this->size();\
if( __pos == 0u && (__len >= t_size || (long int)__len < 0) )\
	return this->range_assign_full_##liter( __x );\
else if( __pos == 0u )\
	return this->range_assign_head_##liter( __len, __x );\
else if( (long int)__len < 0 || (__len + __pos) > t_size )\
	return this->range_assign_tail_##liter( __pos, __x );\
return this->range_assign_mid_##liter( __pos, __len, __x );\
} while(0);

template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_s( U const & __x, const size_type __pos, const size_type __len )
{
	__MY_ARRAY_T_RANGE_ASSIGN1__( __x, __pos, __len, s );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_v( U const * __x, const size_type __pos, const size_type __len )
{
	__MY_ARRAY_T_RANGE_ASSIGN1__( __x, __pos, __len, v );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_full_s( U const & x_data )
{
	this->range_assign_tail_s( 0, x_data );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_full_v( U const * v_data )
{
	this->range_assign_tail_v( 0, v_data );
}

template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_head_s( const size_type v_size, U const & x_data )
{
	const size_type t_size = this->size(), r_size = ( v_size > t_size ? t_size : v_size );
	pointer t_data = this->data();
	for(size_type i = 0; i < r_size; ++i, ++t_data )
		cast_assign( *t_data, x_data );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_head_v( const size_type v_size, U const * v_data )
{
	assert( v_data );
	const size_type t_size = this->size(), r_size = ( v_size > t_size ? t_size : v_size );
	pointer t_data = this->data();
	for(size_type i = 0; i < r_size; ++i, ++t_data, ++v_data )
		cast_assign( *t_data, *v_data );
}

template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_tail_s( const size_type v_begin, U const & x_data )
{
	const size_type t_size = this->size();
	pointer t_data = this->data() + v_begin;
	for(size_type i = v_begin; i < t_size; ++i, ++t_data )
		cast_assign( *t_data, x_data );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_tail_v( const size_type v_begin, U const * v_data )
{
	assert( v_data );
	const size_type t_size = this->size();
	pointer t_data = this->data() + v_begin;
	for(size_type i = v_begin; i < t_size; ++i, ++t_data, ++v_data )
		cast_assign( *t_data, *v_data );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_mid_s( const size_type v_begin, const size_type v_size, U const & x_data )
{
	if( v_begin + v_size > this->size() || (long int)v_begin < 0 || (long int)v_size < 0 )
	{
		__error_msg__( this, "incompatible value(s) of v_begin and/or v_size" );
		exit( 1 );
	}
	pointer t_data = this->data() + v_begin;
	for(size_type i = 0; i < v_size; ++i, ++t_data )
		cast_assign( *t_data, x_data );
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::range_assign_mid_v( const size_type v_begin, const size_type v_size, U const * v_data )
{
	if( v_begin + v_size > this->size() || (long int)v_begin < 0 || (long int)v_size < 0 )
	{
		__error_msg__( this, "incompatible value(s) of v_begin and/or v_size" );
		exit( 1 );
	}
	pointer t_data = this->data() + v_begin;
	for(size_type i = 0; i < v_size; ++i, ++t_data, ++v_data )
		cast_assign( *t_data, *v_data );
}

template<typename T>
template<typename U> void my_array_t<T>::assign( const size_type v_size, U const * const v_data, const int is_data_scalar )
{
	__log_info__( this );
	this->destroy_tail( v_size );// compare: this->size() < v_size; if true; then destroy; else return;
	if( v_size == 0 )
		return;
	this->reserve( v_size );//  compare: this->capacity() < v_size; if true; then reallocate; else return;
	if( v_data == 0 && is_data_scalar )
	{// reserve
		return;
		//__error_msg__( this, "pointer 'v_data' shouldn't be zero, when data is scalar" );
		//exit(1);
	}
	const size_type t_size = this->size();
	this->set_size( v_size );
	if( v_data == 0 )
	{// resize
		this->construct_tail( t_size );
	} else if( is_data_scalar )
	{// assign (scalar)
		this->range_assign_head_s( t_size, *v_data );
		this->construct_tail_s( *v_data, t_size );
	} else
	{// assign (vector)
		this->range_assign_head_v( t_size, v_data );
		this->construct_tail_v( v_data + t_size, t_size );
	}
}

template<typename T>
template<typename U> my_array_t<T> & my_array_t<T>::operator=( my_array_t<U> const & v )
{
	__log_info__( this );
	if( this == &v )
		return *this;
	this->assign( v.size(), v.data(), 0 );
	return *this;
}
template<typename T> my_array_t<T> & my_array_t<T>::operator=( my_array_t<T> && v )
{
	__log_info__( this );
	this->my_array::operator=( std::move( v ) );
	return *this;
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::destroy_full()
{// destroy_full
	this->destroy_tail( 0 );
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::destroy_head( const size_type v_size )
{// destroy_head
	assert( v_size <= this->size() );
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < v_size; ++i, ++p )
		p->~T();
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::destroy_tail( const size_type v_begin )
{// destroy_tail
	const size_type t_size = this->size();
	if( t_size <= v_begin )
		return;
	pointer p = this->data() + v_begin;
	for(int i = v_begin; i < t_size; ++i, ++p )
		p->~T();
	this->set_size( v_begin );
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::construct_full()
{// construct_full
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < t_size; ++i, ++p )
		placement_construct( p );// new (p) T();
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::construct_full_v( U const * x )
{// construct_full
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < t_size; ++i, ++p )
		placement_copy_construct( p, *x++ );// new (p) T(*x++)
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::move_construct_full_v( T * x )
{// construct_full
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < t_size; ++i, ++p )
		placement_move_construct( p, *x++ );// new (p) T(std::move(*x++));
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::construct_full_s( U const & x )
{// construct_full
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < t_size; ++i, ++p )
		placement_copy_construct( p, x );// new (p) T(x)
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::construct_head_v( U const * x, const size_type v_size )
{// construct_head
	assert( v_size >= 0 && v_size <= this->size() );
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < v_size; ++i, ++p )
		placement_copy_construct( p, *x++ );// new (p) T(*x++)
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::move_construct_head_v( T * x, const size_type v_size )
{// move_construct_head
	assert( v_size >= 0 && v_size <= this->size() );
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < v_size; ++i, ++p )
		placement_move_construct( p, *x++ );// new (p) T(std::move(*x++));
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::construct_head( const size_type v_size )
{// construct_head
	assert( v_size >= 0 && v_size <= this->size() );
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < v_size; ++i, ++p )
		placement_construct( p );// new (p) T();
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::construct_head_s( U const & x, const size_type v_size )
{// construct_head
	assert( v_size >= 0 && v_size <= this->size() );
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < v_size; ++i, ++p )
		placement_copy_construct( p, x );// new (p) T(x)
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::construct_tail_v( U const * x, const size_type v_begin )
{// construct_tail
	assert( v_begin >= 0 );
	const size_type t_size = this->size();
	pointer p = this->data() + v_begin;
	for(int i = v_begin; i < t_size; ++i, ++p )
		placement_copy_construct( p, *x++ );// new (p) T(*x++)
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::move_construct_tail_v( T * x, const size_type v_begin )
{// move_construct_tail
	assert( v_begin >= 0 );
	const size_type t_size = this->size();
	pointer p = this->data() + v_begin;
	for(int i = v_begin; i < t_size; ++i, ++p )
		placement_move_construct( p, *x++ );// new (p) T(std::move(*x++));
}
template<typename T> __INLINE_SUBR__ void my_array_t<T>::construct_tail( const size_type v_begin )
{// construct_tail
	assert( v_begin >= 0 );
	const size_type t_size = this->size();
	pointer p = this->data() + v_begin;
	for(int i = v_begin; i < t_size; ++i, ++p )
		placement_construct( p );// new (p) T();
}
template<typename T>
template<typename U> __INLINE_SUBR__ void my_array_t<T>::construct_tail_s( U const & x, const size_type v_begin )
{// construct_tail
	assert( v_begin >= 0 );
	const size_type t_size = this->size();
	pointer p = this->data() + v_begin;
	for(int i = v_begin; i < t_size; ++i, ++p )
		placement_copy_construct( p, x );// new (p) T(x)
}

#include<cstring>// memcpy, memset
// Specialization
#define __MY_ARRAY_T_SPEC1( TYPE ) \
template<> inline void my_array_t<TYPE>::destroy_full(){}\
template<> inline void my_array_t<TYPE>::destroy_head( const size_type v_size ){}\
template<> inline void my_array_t<TYPE>::destroy_tail( const size_type v_begin ){}\
template<> inline void my_array_t<TYPE>::construct_full()\
{\
	if( this->my_array::_M_data )\
		memset( this->data(), 0, this->my_array::size() );\
}\
template<> inline void my_array_t<TYPE>::move_construct_full_v( TYPE * v_data )\
{\
	if( v_data && this->my_array::_M_data )\
		memcpy( this->data(), v_data, this->my_array::size() );\
}\
template<> inline void my_array_t<TYPE>::construct_head( const size_type v_size )\
{\
	if( (long int)v_size < 0 || v_size >= this->size() )\
		this->construct_full();\
	else if( this->my_array::_M_data )\
		memset( this->data(), 0, v_size * sizeof(value_type) );\
}\
template<> inline void my_array_t<TYPE>::move_construct_head_v( TYPE * v_data, const size_type v_size )\
{\
	if( (long int)v_size < 0 || v_size >= this->size() )\
		this->construct_full_v( v_data );\
	else if( v_data && this->my_array::_M_data )\
		memcpy( this->data(), v_data, v_size * sizeof(value_type) );\
}\
template<> inline void my_array_t<TYPE>::construct_tail( const size_type v_begin )\
{\
	if( v_begin == 0u )\
		this->construct_full();\
	else if( this->my_array::_M_data && v_begin <= this->size() )\
		memset( this->data() + v_begin, 0, this->my_array::size() - v_begin * sizeof(value_type) );\
}\
template<> inline void my_array_t<TYPE>::move_construct_tail_v( TYPE * v_data, const size_type v_begin )\
{\
	if( v_begin == 0u )\
		this->construct_full_v( v_data );\
	else if( v_data && this->my_array::_M_data && v_begin <= this->size() )\
		memcpy( this->data() + v_begin, v_data, this->my_array::size() - v_begin * sizeof(value_type) );\
}

#define __MY_ARRAY_T_SPEC2( TYPE1, TYPE2 )\
template<> template<> inline void my_array_t<TYPE1>::construct_full_s<TYPE2>( TYPE2 const & x )\
{\
	this->range_assign_full_s( x );\
}\
template<> template<> inline void my_array_t<TYPE1>::construct_full_v<TYPE2>( TYPE2 const * x )\
{\
	this->range_assign_full_v( x );\
}\
template<> template<> inline void my_array_t<TYPE1>::construct_head_s<TYPE2>( TYPE2 const & x, const size_type v_size )\
{\
	this->range_assign_head_s( v_size, x );\
}\
template<> template<> inline void my_array_t<TYPE1>::construct_head_v<TYPE2>( TYPE2 const * x, const size_type v_size )\
{\
	this->range_assign_head_v( v_size, x );\
}\
template<> template<> inline void my_array_t<TYPE1>::construct_tail_s<TYPE2>( TYPE2 const & x, const size_type v_begin )\
{\
	this->range_assign_tail_s( v_begin, x );\
}\
template<> template<> inline void my_array_t<TYPE1>::construct_tail_v<TYPE2>( TYPE2 const * x, const size_type v_begin )\
{\
	this->range_assign_tail_v( v_begin, x );\
}

#define __MY_ARRAY_T_SPEC2_1( TYPE1 )\
__MY_ARRAY_T_SPEC2( TYPE1, char );\
__MY_ARRAY_T_SPEC2( TYPE1, short );\
__MY_ARRAY_T_SPEC2( TYPE1, int );\
__MY_ARRAY_T_SPEC2( TYPE1, long int );\
__MY_ARRAY_T_SPEC2( TYPE1, long long int );\
__MY_ARRAY_T_SPEC2( TYPE1, unsigned char );\
__MY_ARRAY_T_SPEC2( TYPE1, unsigned short );\
__MY_ARRAY_T_SPEC2( TYPE1, unsigned int );\
__MY_ARRAY_T_SPEC2( TYPE1, unsigned long int );\
__MY_ARRAY_T_SPEC2( TYPE1, unsigned long long int );\
__MY_ARRAY_T_SPEC2( TYPE1, float );\
__MY_ARRAY_T_SPEC2( TYPE1, double );\
__MY_ARRAY_T_SPEC2( TYPE1, long double );

#define __MY_ARRAY_CHARTYPE_SPEC( _CHAR_TYPE_ ) \
template<> inline typename my_array::size_type my_array_t<_CHAR_TYPE_>::size()const{ return this->my_array::size(); }

#define __MY_ARRAY_T_SPEC( TYPE )\
__MY_ARRAY_T_SPEC2_1( TYPE )\
__MY_ARRAY_T_SPEC1( TYPE )

__MY_ARRAY_CHARTYPE_SPEC( char );
__MY_ARRAY_CHARTYPE_SPEC( unsigned char );
__MY_ARRAY_T_SPEC( char );
__MY_ARRAY_T_SPEC( short );
__MY_ARRAY_T_SPEC( int );
__MY_ARRAY_T_SPEC( long int );
__MY_ARRAY_T_SPEC( long long int );
__MY_ARRAY_T_SPEC( unsigned char );
__MY_ARRAY_T_SPEC( unsigned short );
__MY_ARRAY_T_SPEC( unsigned int );
__MY_ARRAY_T_SPEC( unsigned long int );
__MY_ARRAY_T_SPEC( unsigned long long int );
__MY_ARRAY_T_SPEC( float );
__MY_ARRAY_T_SPEC( double );
__MY_ARRAY_T_SPEC( long double );

#endif//__MY_ARRAY_HPP__
