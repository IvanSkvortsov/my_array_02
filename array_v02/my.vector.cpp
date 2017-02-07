#include"my.vector.h"
#include"my.vector.config.h"// header should always follow 'my.vector.h', and precede 'global.*.h', 'assert.h' files;
#include"global.log.info.h"
#include"global.error.msg.h"
#include<cassert>// assert
#include<cstring>// memcpy

#define VECTOR_DATA( array_str, idx ) ( (array_str) ? (array_str)->data + (idx) : (void *)0 )
#define VECTOR_SIZE( array_str ) ( (array_str) ? (array_str)->size : (size_type)0 )
#define VECTOR_CAPACITY( array_str ) ( (array_str) ? (array_str)->capacity : (size_type)0 )

void * my_vector::data(){ return VECTOR_DATA( this->_M_data, 0); }
void const * my_vector::data()const{ return VECTOR_DATA( this->_M_data, 0); }
void * my_vector::data(int i){ return VECTOR_DATA( this->_M_data, i ); }
void const * my_vector::data(int i)const{ return VECTOR_DATA( this->_M_data, i ); }
typename my_vector::size_type my_vector::size()const
{
	assert( (this->_M_data != 0 ? this->_M_data->capacity != 0 : 1 ) );
	return VECTOR_SIZE( this->_M_data );
}
typename my_vector::size_type my_vector::capacity()const
{
	assert( (this->_M_data != 0 ? this->_M_data->capacity != 0 : 1 ) );
	return VECTOR_CAPACITY( this->_M_data );
}

void my_vector::free()
{
	if( this->_M_data )
		::operator delete( this->_M_data );
	this->_M_data = 0;
}
void my_vector::set_size( size_type __size )
{
	assert( __size <= this->capacity() );
	if( this->_M_data )
		this->_M_data->size = __size;
}
typename my_vector::array_struct * my_vector::allocate( size_type __size )
{
	assert( __size != 0 );
	array_struct * __arr_str = (array_struct * )::operator new( __size + sizeof(array_struct) );
	__arr_str->capacity = __size;
	return __arr_str;
}
void my_vector::reallocate( size_type __size )
{
	// Warning! It may cause a memory leak
	__log_info__( this );
	const size_type t_size = this->size();
	array_struct * __new_array = this->allocate( __size );
	__new_array->size = t_size;
	memcpy( __new_array->data, this->data(), t_size );
	this->free();
	this->_M_data = __new_array;
}
void my_vector::shrink_to_fit()
{
	__log_info__( this );
	if( this->size() != this->capacity() )
		this->reallocate( this->size() );
}
void my_vector::reserve( size_type __size )
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
my_vector::my_vector(): _M_data(){__log_info__( this ); }
my_vector::my_vector( my_vector const & v ): _M_data( (array_struct * )( v.size() ? ::operator new( v.size() + sizeof(array_struct) ) : (void *)0 ) )
{ 
	__log_info__( this );
	if( this->_M_data )
	{
		this->_M_data->capacity = v.size();
		this->_M_data->size = v.size();
	}
}
my_vector::my_vector( my_vector && v ): _M_data( v._M_data )
{ 
	__log_info__( this );
	v._M_data = 0;
}
my_vector::my_vector( size_type __size ): _M_data( (array_struct * )( __size ? ::operator new( __size + sizeof(array_struct) ) : (void *)0 ) )
{ 
	__log_info__( this );
	if( this->_M_data )
	{
		this->_M_data->capacity = __size;
		this->_M_data->size = __size;
	}
}
my_vector & my_vector::operator=( my_vector const & v )
{
	__log_info__( this );
	if( this == &v )
		return *this;
	const size_type v_size = v.size();
	this->reserve( v_size );
	return *this;
}
my_vector & my_vector::operator=( my_vector && v )
{
	__log_info__( this );
	if( this == &v )
		return *this;
	std::swap( this->_M_data, v._M_data );
	return *this;
}
my_vector::~my_vector()
{
	__log_info__( this );
	this->free();
}
