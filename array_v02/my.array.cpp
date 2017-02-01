#include"my.array.h"
#include"my.array.config.h"// header should always follow 'my.array.h', and precede 'global.*.h', 'assert.h' files;
#include"global.log.info.h"
#include"global.error.msg.h"
#include<cassert>// assert
#include<cstring>// memcpy

#define ARRAY_DATA( array_str, idx ) ( (array_str) ? (array_str)->data + (idx) : (void *)0 )
#define ARRAY_SIZE( array_str ) ( (array_str) ? (array_str)->size : (size_type)0 )
#define ARRAY_CAPACITY( array_str ) ( (array_str) ? (array_str)->capacity : (size_type)0 )

void * my_array::data(){ return ARRAY_DATA( this->_M_data, 0); }
void const * my_array::data()const{ return ARRAY_DATA( this->_M_data, 0); }
void * my_array::data(int i){ return ARRAY_DATA( this->_M_data, i ); }
void const * my_array::data(int i)const{ return ARRAY_DATA( this->_M_data, i ); }
typename my_array::size_type my_array::size()const
{
	assert( (this->_M_data != 0 ? this->_M_data->capacity != 0 : 1 ) );
	return ARRAY_SIZE( this->_M_data );
}
typename my_array::size_type my_array::capacity()const
{
	assert( (this->_M_data != 0 ? this->_M_data->capacity != 0 : 1 ) );
	return ARRAY_CAPACITY( this->_M_data );
}

void my_array::free()
{
	if( this->_M_data )
		::operator delete( this->_M_data );
	this->_M_data = 0;
}
void my_array::set_size( size_type __size )
{
	assert( __size <= this->capacity() );
	if( this->_M_data )
		this->_M_data->size = __size;
}
typename my_array::array_struct * my_array::allocate( size_type __size )
{
	assert( __size != 0 );
	array_struct * __arr_str = (array_struct * )::operator new( __size + sizeof(array_struct) );
	__arr_str->capacity = __size;
	return __arr_str;
}
void my_array::reallocate( size_type __size )
{
	__log_info__( this );
	const size_type t_size = this->size();
	array_struct * __new_array = this->allocate( __size );
	__new_array->size = t_size;
	memcpy( __new_array->data, this->data(), t_size );
	this->free();
	this->_M_data = __new_array;
}
void my_array::shrink_to_fit()
{
	__log_info__( this );
	if( this->size() != this->capacity() )
		this->reallocate( this->size() );
}
void my_array::reserve( size_type __size )
{
	assert( (long int)__size >= 0 );
	__log_info__( this );

	if( this->capacity() >= __size )
		return;
	size_type t_capacity = this->capacity();
	if( t_capacity == 0 )
		t_capacity = __size;
	while( t_capacity < __size )
		t_capacity <<= 1;
	this->reallocate( t_capacity );
}
void my_array::resize( size_type __size )
{
	assert( (long int)__size >= 0 );
	__log_info__( this );
	this->reserve( __size );
	this->set_size( __size );
}
my_array::my_array(): _M_data(){__log_info__( this ); }
my_array::my_array( my_array const & v ): _M_data( (array_struct * )( v.size() ? ::operator new( v.size() + sizeof(array_struct) ) : (void *)0 ) )
{ 
	__log_info__( this );
	if( this->_M_data )
	{
		this->_M_data->capacity = v.size();
		this->_M_data->size = v.size();
	}
}
my_array::my_array( my_array && v ): _M_data( v._M_data )
{ 
	__log_info__( this );
	v._M_data = 0;
}
my_array::my_array( size_type __size ): _M_data( (array_struct * )( __size ? ::operator new( __size + sizeof(array_struct) ) : (void *)0 ) )
{ 
	__log_info__( this );
	if( this->_M_data )
	{
		this->_M_data->capacity = __size;
		this->_M_data->size = __size;
	}
}
my_array & my_array::operator=( my_array const & v )
{
	__log_info__( this );
	if( this == &v )
		return *this;
	const size_type v_size = v.size();
	this->resize( v_size );
	return *this;
}
my_array & my_array::operator=( my_array && v )
{
	__log_info__( this );
	if( this == &v )
		return *this;
	std::swap( this->_M_data, v._M_data );
	return *this;
}
my_array::~my_array()
{
	__log_info__( this );
	this->free();
}
