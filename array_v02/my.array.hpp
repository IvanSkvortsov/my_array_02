#ifndef __MY_ARRAY_HPP__
#define __MY_ARRAY_HPP__
#include"my.array.h"
#include<cassert>

template<typename T, std::size_t _Size, typename _RAlloc>
my_array<T,_Size,_RAlloc>::my_array()
{
	_RAlloc::construct( this->data(), this->size() );
}
template<typename T, std::size_t _Size, typename _RAlloc>
my_array<T,_Size,_RAlloc>::my_array( my_array<T,_Size,_RAlloc> const & v )
{// copy-ctor
	_RAlloc::construct_v( this->data(), v.data(), this->size() );
}
template<typename T, std::size_t _Size, typename _RAlloc>
my_array<T,_Size,_RAlloc>::my_array( T const & x, size_type __size )
{
	this->construct_full_s( x, 0, __size );
}
template<typename T, std::size_t _Size, typename _RAlloc>
my_array<T,_Size,_RAlloc>::my_array( std::initializer_list<T> init )
{
	this->construct_full_v( init.begin(), 0, init.size() );
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> my_array<T,_Size,_RAlloc>::my_array( U const * __start, U const * __end )
{
	this->construct_full_v( __start, 0, __end - __start );

}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> my_array<T,_Size,_RAlloc>::my_array( U const & x, size_type __size )
{
	this->construct_full_s( x, 0, __size );
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> my_array<T,_Size,_RAlloc>::my_array( std::initializer_list<U> init )
{
	this->construct_full_v( init.begin(), 0, init.size() );
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U, std::size_t v_size, typename range_allocator_type>
my_array<T,_Size,_RAlloc>::my_array( my_array<U, v_size, range_allocator_type> const & v )
{
	this->construct_full_v( v.data(), 0, v.size() );
}
template<typename T, std::size_t _Size, typename _RAlloc>
my_array<T,_Size,_RAlloc>::~my_array()
{
	_RAlloc::destroy( this->data(), this->size() );
}

template<typename T, std::size_t _Size, typename _RAlloc>
my_array<T,_Size,_RAlloc> & my_array<T,_Size,_RAlloc>::operator=( my_array<T,_Size,_RAlloc> const & v )
{
	if( this == &v )
		return *this;
	this->range_assign_v( v.data(), 0, v.size() );
	return *this;
}
template<typename T, std::size_t _Size, typename _RAlloc> template<typename U, std::size_t v_size, typename range_allocator_type>
my_array<T,_Size,_RAlloc> & my_array<T,_Size,_RAlloc>::operator=( my_array<U, v_size, range_allocator_type> const & v )
{
	if( this == &v )
		return *this;
	this->range_assign_v( v.data(), 0, v.size() );
	return *this;
}

#define __MY_ARRAY_CONSTR_FULL__( v_data, __pos, __len, liter )\
do{\
	if( __pos >= this->size() )\
		return;\
	_RAlloc::construct( this->data(), __pos );\
	const size_type pos_p_len = __pos + __len;\
	if( (difference_type)__len < 0 || (pos_p_len) >= this->size() )\
	{\
		assert( __pos < this->size() );\
		_RAlloc::construct_##liter( this->data() + __pos, v_data, this->size() - __pos );\
	} else {\
		assert( (pos_p_len) < this->size() );\
		_RAlloc::construct( this->data(), __pos );\
		_RAlloc::construct_##liter( this->data() + __pos, v_data, __len );\
		_RAlloc::construct( this->data() + pos_p_len, this->size() - pos_p_len );\
	}\
}while(0);

template<typename T, std::size_t _Size, typename _RAlloc>
void my_array<T,_Size,_RAlloc>::construct_full_v( T const * v_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_CONSTR_FULL__( v_data, __pos, __len, v );
}
template<typename T, std::size_t _Size, typename _RAlloc>
void my_array<T,_Size,_RAlloc>::construct_full_s( T const & x_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_CONSTR_FULL__( x_data, __pos, __len, s );
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> void my_array<T,_Size,_RAlloc>::construct_full_v( U const * v_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_CONSTR_FULL__( v_data, __pos, __len, v );
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> void my_array<T,_Size,_RAlloc>::construct_full_s( U const & x_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_CONSTR_FULL__( x_data, __pos, __len, s );
}

#define __MY_ARRAY_RANGEASSIGN__( v_data, __pos, __len, liter )\
do{\
	if( __pos >= this->size() )\
		return;\
	const size_type pos_p_len = __pos + __len;\
	if( (difference_type)__len < 0 || (pos_p_len) >= this->size() )\
	{\
		assert( __pos < this->size() );\
		_RAlloc::assign_##liter( this->data() + __pos, v_data, this->size() - __pos );\
	} else {\
		assert( (pos_p_len) < this->size() );\
		_RAlloc::assign_##liter( this->data() + __pos, v_data, __len );\
	}\
}while(0);

template<typename T, std::size_t _Size, typename _RAlloc>
void my_array<T,_Size,_RAlloc>::range_assign_v( T const * v_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_RANGEASSIGN__( v_data, __pos, __len, v )\
}
template<typename T, std::size_t _Size, typename _RAlloc>
void my_array<T,_Size,_RAlloc>::range_assign_s( T const & x_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_RANGEASSIGN__( x_data, __pos, __len, s )\
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> void my_array<T,_Size,_RAlloc>::range_assign_v( U const * v_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_RANGEASSIGN__( v_data, __pos, __len, v )\
}
template<typename T, std::size_t _Size, typename _RAlloc>
template<typename U> void my_array<T,_Size,_RAlloc>::range_assign_s( U const & x_data, size_type __pos, size_type __len )
{
	__MY_ARRAY_RANGEASSIGN__( x_data, __pos, __len, s )\
}

#endif//__MY_ARRAY_HPP__
