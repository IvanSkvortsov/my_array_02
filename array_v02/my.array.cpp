#include"my.array.h"
#include"my.array.config.h"// header should always follow 'my.array.h', and precede 'global.*.h', 'assert.h' files;
#include"global.log.info.h"
#include"global.error.msg.h"
#include<cassert>// assert

#define ARRAY_DATA( array_str, idx ) ( (array_str) ? (array_str)->data + (idx) : (void *)0 )
#define ARRAY_SIZE( array_str ) ( (array_str) ? (array_str)->size : (size_type)0 )


void * my_array::data(){ return ARRAY_DATA( this->_M_data, 0); }
void const * my_array::data()const{ return ARRAY_DATA( this->_M_data, 0); }
void * my_array::data(int i){ return ARRAY_DATA( this->_M_data, i ); }
void const * my_array::data(int i)const{ return ARRAY_DATA( this->_M_data, i ); }
typename my_array::size_type my_array::size()const
{
	assert( (this->_M_data != 0 ? this->_M_data->size != 0 : 1 ) );
	return ARRAY_SIZE( this->_M_data );
}

void my_array::free()
{
	assert( this->_M_data != 0 );// shouldn't be zero when deleting pointer
	::operator delete( this->_M_data );
	this->_M_data = 0;
}
typename my_array::array_struct * my_array::allocate( size_type __size )
{
	assert( __size != 0 );
	array_struct * __arr_str = (array_struct * )::operator new( __size + sizeof(size_type) );
	__arr_str->size = __size;
	return __arr_str;
}
int my_array::resize( size_type __size )
{
	__log_info__( this );
	if( this->size() == __size )
		return 0;
	else if( this->size() != 0 )
		this->free();
	if( __size != 0 )
	{
		this->_M_data = this->allocate( __size );
		return 1;
	}
	return 0;
}
my_array::my_array(): _M_data(){__log_info__( this ); }
my_array::my_array( my_array const & v ): _M_data( (array_struct * )( v.size() ? ::operator new( v.size() + sizeof(size_type) ) : (void *)0 ) )
{ 
	__log_info__( this );
	if( this->_M_data )
		this->_M_data->size = v.size();
}
my_array::my_array( my_array && v ): _M_data( v._M_data )
{ 
	__log_info__( this );
	v._M_data = 0;
}
my_array::my_array( size_type __size ): _M_data( (array_struct * )( __size ? ::operator new( __size + sizeof(size_type) ) : (void *)0 ) )
{ 
	__log_info__( this );
	if( this->_M_data )
		this->_M_data->size = __size;
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
	// if 'data' == 0; then 'array_struct' == 0; otherwise 'array_struct' != 0
	assert( ( this->data() == 0 ? this->_M_data == 0 : this->_M_data != 0 ) );
	if( this->_M_data ) this->free();
}
