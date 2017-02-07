#ifndef __MY_VECTOR_HPP__
#define __MY_VECTOR_HPP__
#include"my.vector.h"
#include"my.vector.config.h"
#include"global.log.info.h"
#include"global.error.msg.h"
#include<cassert>// assert
#include"my.range.allocator.hpp"
#include<cstdlib>// exit

#define __IS_SUBROUTINE_INLINE__ 0

#if __IS_SUBROUTINE_INLINE__
  #define __INLINE_SUBR__ inline
#else
  #define __INLINE_SUBR__
#endif

template<typename T, typename _RAlloc = my_range_allocator<T> >
class my_vector_t: public my_vector
{
public:
	typedef T value_type;
	typedef T * pointer;
	typedef T const * const_pointer;
	typedef T & reference;
	typedef T const & const_reference;
	typedef typename my_vector::size_type size_type;
	typedef std::ptrdiff_t difference_type;
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

	typedef struct my_vector::array_struct array_struct;
	void set_size( size_type __size ){ this->my_vector::set_size( __size * sizeof(value_type) ); }
public:
	my_vector_t();
	my_vector_t( my_vector_t<T,_RAlloc> const & v );// unless declared it is implicitly deleted because of move-ctor
	my_vector_t( my_vector_t<T,_RAlloc> && v );
	my_vector_t( std::initializer_list<T> init );// enables list-initialization, {T(1.05), T(4.1), ...}
	my_vector_t( size_type __size );
	~my_vector_t();
	// bonus =)
	template<class U, class range_allocator_type = my_range_allocator<U> >
		my_vector_t( my_vector_t<U,range_allocator_type> const & v );// see copy-ctor comment
	template<typename U> my_vector_t( U v_start, U v_end );
	template<typename U> my_vector_t( size_type __size, U const & x );
	template<typename U> my_vector_t( std::initializer_list<U> init );
	// operator=
	template<class U, class range_allocator_type = my_range_allocator<U> >
		my_vector_t<T,_RAlloc> & operator=( my_vector_t<U, range_allocator_type> const & v );
	my_vector_t<T,_RAlloc> & operator=( my_vector_t<T,_RAlloc> && v );
	// syntactic sugar to %assign( const size_type , U const * const , const int ):
	template<typename U> void assign( U const * v_data, U const * v_end ){ __log_info__( this ); this->assign( v_end - v_data, v_data, 0 ); }
	template<typename U> void assign( const size_type v_size, U const & x_data ){ __log_info__( this ); this->assign( v_size, &x_data, 1 ); }
	template<class U, class range_allocator_type = my_range_allocator<U> >
		void assign( my_vector_t<U, range_allocator_type> const & v ){ __log_info__( this ); this->assign( v.size(), v.data(), 0 ); }
	void resize( size_type __size ){ __log_info__( this ); this->assign( __size, (const_pointer)0, 0 ); }
	void reserve( size_type __size ){ __log_info__( this ); this->my_vector::reserve( __size * sizeof(value_type) ); }
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
	pointer data(){ return (pointer )this->my_vector::data(); }
	const_pointer data()const{ return (const_pointer )this->my_vector::data(); }
	pointer data(int i){ return this->data() + i; }
	const_pointer data(int i)const{ return this->data() + i; }
	reference operator[]( size_type i ){ return *(this->data(i)); }
	const_reference operator[]( size_type i )const{ return *(this->data(i)); }
	size_type size()const{ return this->my_vector::size()/sizeof(value_type); }
	size_type capacity()const{ return this->my_vector::capacity()/sizeof(value_type); }
};

template<class T, class _RAlloc> my_vector_t<T,_RAlloc>::my_vector_t(): my_vector()
{
	__log_info__( this );
}
template<class T, class _RAlloc> my_vector_t<T,_RAlloc>::my_vector_t( my_vector_t<T,_RAlloc> const & v ): my_vector( v.my_vector::size() )
{
	__log_info__( this );
	this->construct_full_v( v.data() );
}
template<class T, class _RAlloc> my_vector_t<T,_RAlloc>::my_vector_t( my_vector_t<T,_RAlloc> && v ): my_vector( std::move( v ) )
{
	__log_info__( this );
}
template<class T, class _RAlloc> my_vector_t<T,_RAlloc>::my_vector_t( size_type __size ): my_vector( __size * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full();
}
template<class T, class _RAlloc> template<class U, class range_allocator_type>
my_vector_t<T,_RAlloc>::my_vector_t( my_vector_t<U,range_allocator_type> const & v ): my_vector( v.size() * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_v( v.data() );
}
template<class T, class _RAlloc>
template<typename U> my_vector_t<T,_RAlloc>::my_vector_t( size_type __size, U const & x ): my_vector( __size * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_s( x );
}
template<class T, class _RAlloc>
template<typename U> my_vector_t<T,_RAlloc>::my_vector_t( U v_start, U v_end ):
	my_vector( (v_end > v_start) && v_start ? (v_end - v_start) * sizeof(value_type) : (size_type)0 )
{
	__log_info__( this );
	if( v_start )
		this->construct_full_v( v_start );
}
template<class T, class _RAlloc> my_vector_t<T,_RAlloc>::my_vector_t( std::initializer_list<T> init ): my_vector( init.size() * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_v( init.begin() );
}
template<class T, class _RAlloc>
template<typename U> my_vector_t<T,_RAlloc>::my_vector_t( std::initializer_list<U> init ): my_vector( init.size() * sizeof(value_type) )
{
	__log_info__( this );
	this->construct_full_v( init.begin() );
}

template<class T, class _RAlloc> my_vector_t<T,_RAlloc>::~my_vector_t()
{
	__log_info__( this );
	this->destroy_full();
}

#define __MY_VECTOR_T_RANGE_ASSIGN1__( __x, __pos, __len, liter )\
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

template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_s( U const & __x, const size_type __pos, const size_type __len )
{
	__MY_VECTOR_T_RANGE_ASSIGN1__( __x, __pos, __len, s );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_v( U const * __x, const size_type __pos, const size_type __len )
{
	__MY_VECTOR_T_RANGE_ASSIGN1__( __x, __pos, __len, v );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_full_s( U const & x_data )
{
	this->range_assign_tail_s( 0, x_data );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_full_v( U const * v_data )
{
	this->range_assign_tail_v( 0, v_data );
}

template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_head_s( const size_type v_size, U const & x_data )
{
	const size_type t_size = this->size();
	_RAlloc::assign_s( this->data(), x_data, ( v_size > t_size ? t_size : v_size ) );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_head_v( const size_type v_size, U const * v_data )
{
	if( !v_data ) return;
	const size_type t_size = this->size();
	_RAlloc::assign_v( this->data(), v_data, ( v_size > t_size ? t_size : v_size ) );
}

template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_tail_s( const size_type v_begin, U const & x_data )
{
	const size_type t_size = this->size();
	if( v_begin >= t_size )
		return;
	_RAlloc::assign_s( this->data() + v_begin, x_data, t_size - v_begin );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_tail_v( const size_type v_begin, U const * v_data )
{
	if( !v_data ) return;
	const size_type t_size = this->size();
	if( v_begin >= t_size )
		return;
	_RAlloc::assign_v( this->data() + v_begin, v_data, t_size - v_begin );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_mid_s( const size_type v_begin, const size_type v_size, U const & x_data )
{
	if( v_begin + v_size > this->size() || (long int)v_begin < 0 || (long int)v_size < 0 )
	{
		__error_msg__( this, "incompatible value(s) of v_begin and/or v_size" );
		exit( 1 );
	}
	_RAlloc::assign_s( this->data() + v_begin, x_data, v_size );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::range_assign_mid_v( const size_type v_begin, const size_type v_size, U const * v_data )
{
	if( v_begin + v_size > this->size() || (long int)v_begin < 0 || (long int)v_size < 0 )
	{
		__error_msg__( this, "incompatible value(s) of v_begin and/or v_size" );
		exit( 1 );
	}
	_RAlloc::assign_v( this->data() + v_begin, v_data, v_size );
}

template<class T, class _RAlloc>
template<typename U> void my_vector_t<T,_RAlloc>::assign( const size_type v_size, U const * const v_data, const int is_data_scalar )
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

template<class T, class _RAlloc> template<typename U, typename range_allocator_type>
my_vector_t<T,_RAlloc> & my_vector_t<T,_RAlloc>::operator=( my_vector_t<U, range_allocator_type> const & v )
{
	__log_info__( this );
	if( this == &v )
		return *this;
	this->assign( v.size(), v.data(), 0 );
	return *this;
}
template<class T, class _RAlloc> my_vector_t<T,_RAlloc> & my_vector_t<T,_RAlloc>::operator=( my_vector_t<T,_RAlloc> && v )
{
	__log_info__( this );
	this->my_vector::operator=( std::move( v ) );
	return *this;
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::destroy_full()
{// destroy_full
	this->destroy_tail( 0 );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::destroy_head( const size_type v_size )
{// destroy_head
	const size_type t_size = this->size();
	if( v_size > t_size )
		return;
	_RAlloc::destroy( this->data(), v_size );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::destroy_tail( const size_type v_begin )
{// destroy_tail
	const size_type t_size = this->size();
	if( t_size <= v_begin )
		return;
	_RAlloc::destroy( this->data() + v_begin, t_size - v_begin );
	this->set_size( v_begin );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_full()
{// construct_full
	_RAlloc::construct( this->data(), this->size() );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_full_v( U const * x )
{// construct_full
	_RAlloc::construct_v( this->data(), x, this->size() );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::move_construct_full_v( T * x )
{// construct_full
	_RAlloc::move_construct_v( this->data(), x, this->size() );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_full_s( U const & x )
{// construct_full
	_RAlloc::construct_s( this->data(), x, this->size() );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_head_v( U const * x, const size_type v_size )
{// construct_head
	assert( (difference_type)v_size >= 0 && v_size <= this->size() );
	_RAlloc::construct_v( this->data(), x, v_size );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::move_construct_head_v( T * x, const size_type v_size )
{// move_construct_head
	assert( (difference_type)v_size >= 0 && v_size <= this->size() );
	_RAlloc::move_construct_v( this->data(), x, v_size );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_head( const size_type v_size )
{// construct_head
	assert( (difference_type)v_size >= 0 && v_size <= this->size() );
	_RAlloc::construct( this->data(), v_size );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_head_s( U const & x, const size_type v_size )
{// construct_head
	assert( (difference_type)v_size >= 0 && v_size <= this->size() );
	_RAlloc::construct_s( this->data(), x, v_size );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_tail_v( U const * x, const size_type v_begin )
{// construct_tail
	const size_type t_size = this->size();
	if( v_begin >= t_size )
		return;
	_RAlloc::construct_v( this->data() + v_begin, x, t_size - v_begin );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::move_construct_tail_v( T * x, const size_type v_begin )
{// move_construct_tail
	const size_type t_size = this->size();
	if( v_begin >= t_size )
		return;
	_RAlloc::move_construct_v( this->data() + v_begin, x, t_size - v_begin );
}
template<class T, class _RAlloc> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_tail( const size_type v_begin )
{// construct_tail
	const size_type t_size = this->size();
	if( v_begin >= t_size )
		return;
	_RAlloc::construct( this->data() + v_begin, t_size - v_begin );
}
template<class T, class _RAlloc>
template<typename U> __INLINE_SUBR__ void my_vector_t<T,_RAlloc>::construct_tail_s( U const & x, const size_type v_begin )
{// construct_tail
	const size_type t_size = this->size();
	if( v_begin >= t_size )
		return;
	_RAlloc::construct_s( this->data() + v_begin, x, t_size - v_begin );
}

// Specialization
#define __MY_VECTOR_T_SPEC1( TYPE ) \
template<> inline void my_vector_t<TYPE>::destroy_full(){}\
template<> inline void my_vector_t<TYPE>::destroy_head( const size_type v_size ){}\
template<> inline void my_vector_t<TYPE>::destroy_tail( const size_type v_begin ){}\
template<> inline void my_vector_t<TYPE>::construct_full()\
{\
	if( this->my_vector::_M_data )\
		memset( this->data(), 0, this->my_vector::size() );\
}\
template<> inline void my_vector_t<TYPE>::move_construct_full_v( TYPE * v_data )\
{\
	if( v_data && this->my_vector::_M_data )\
		memcpy( this->data(), v_data, this->my_vector::size() );\
}\
template<> inline void my_vector_t<TYPE>::construct_head( const size_type v_size )\
{\
	if( (long int)v_size < 0 || v_size >= this->size() )\
		this->construct_full();\
	else if( this->my_vector::_M_data )\
		memset( this->data(), 0, v_size * sizeof(value_type) );\
}\
template<> inline void my_vector_t<TYPE>::move_construct_head_v( TYPE * v_data, const size_type v_size )\
{\
	if( (long int)v_size < 0 || v_size >= this->size() )\
		this->construct_full_v( v_data );\
	else if( v_data && this->my_vector::_M_data )\
		memcpy( this->data(), v_data, v_size * sizeof(value_type) );\
}\
template<> inline void my_vector_t<TYPE>::construct_tail( const size_type v_begin )\
{\
	if( v_begin == 0u )\
		this->construct_full();\
	else if( this->my_vector::_M_data && v_begin <= this->size() )\
		memset( this->data() + v_begin, 0, this->my_vector::size() - v_begin * sizeof(value_type) );\
}\
template<> inline void my_vector_t<TYPE>::move_construct_tail_v( TYPE * v_data, const size_type v_begin )\
{\
	if( v_begin == 0u )\
		this->construct_full_v( v_data );\
	else if( v_data && this->my_vector::_M_data && v_begin <= this->size() )\
		memcpy( this->data() + v_begin, v_data, this->my_vector::size() - v_begin * sizeof(value_type) );\
}

#define __MY_VECTOR_T_SPEC2( TYPE1, TYPE2 )\
template<> template<> inline void my_vector_t<TYPE1>::construct_full_s<TYPE2>( TYPE2 const & x )\
{\
	this->range_assign_full_s( x );\
}\
template<> template<> inline void my_vector_t<TYPE1>::construct_full_v<TYPE2>( TYPE2 const * x )\
{\
	this->range_assign_full_v( x );\
}\
template<> template<> inline void my_vector_t<TYPE1>::construct_head_s<TYPE2>( TYPE2 const & x, const size_type v_size )\
{\
	this->range_assign_head_s( v_size, x );\
}\
template<> template<> inline void my_vector_t<TYPE1>::construct_head_v<TYPE2>( TYPE2 const * x, const size_type v_size )\
{\
	this->range_assign_head_v( v_size, x );\
}\
template<> template<> inline void my_vector_t<TYPE1>::construct_tail_s<TYPE2>( TYPE2 const & x, const size_type v_begin )\
{\
	this->range_assign_tail_s( v_begin, x );\
}\
template<> template<> inline void my_vector_t<TYPE1>::construct_tail_v<TYPE2>( TYPE2 const * x, const size_type v_begin )\
{\
	this->range_assign_tail_v( v_begin, x );\
}

#define __MY_VECTOR_T_SPEC2_1( TYPE1 )\
__MY_VECTOR_T_SPEC2( TYPE1, char );\
__MY_VECTOR_T_SPEC2( TYPE1, short );\
__MY_VECTOR_T_SPEC2( TYPE1, int );\
__MY_VECTOR_T_SPEC2( TYPE1, long int );\
__MY_VECTOR_T_SPEC2( TYPE1, long long int );\
__MY_VECTOR_T_SPEC2( TYPE1, unsigned char );\
__MY_VECTOR_T_SPEC2( TYPE1, unsigned short );\
__MY_VECTOR_T_SPEC2( TYPE1, unsigned int );\
__MY_VECTOR_T_SPEC2( TYPE1, unsigned long int );\
__MY_VECTOR_T_SPEC2( TYPE1, unsigned long long int );\
__MY_VECTOR_T_SPEC2( TYPE1, float );\
__MY_VECTOR_T_SPEC2( TYPE1, double );\
__MY_VECTOR_T_SPEC2( TYPE1, long double );

#define __MY_VECTOR_CHARTYPE_SPEC( _CHAR_TYPE_ ) \
template<> inline typename my_vector::size_type my_vector_t<_CHAR_TYPE_>::size()const{ return this->my_vector::size(); }

#define __MY_VECTOR_T_SPEC( TYPE )\
__MY_VECTOR_T_SPEC2_1( TYPE )\
__MY_VECTOR_T_SPEC1( TYPE )

__MY_VECTOR_CHARTYPE_SPEC( char );
__MY_VECTOR_CHARTYPE_SPEC( unsigned char );
__MY_VECTOR_T_SPEC( char );
__MY_VECTOR_T_SPEC( short );
__MY_VECTOR_T_SPEC( int );
__MY_VECTOR_T_SPEC( long int );
__MY_VECTOR_T_SPEC( long long int );
__MY_VECTOR_T_SPEC( unsigned char );
__MY_VECTOR_T_SPEC( unsigned short );
__MY_VECTOR_T_SPEC( unsigned int );
__MY_VECTOR_T_SPEC( unsigned long int );
__MY_VECTOR_T_SPEC( unsigned long long int );
__MY_VECTOR_T_SPEC( float );
__MY_VECTOR_T_SPEC( double );
__MY_VECTOR_T_SPEC( long double );

#endif//__MY_VECTOR_HPP__
