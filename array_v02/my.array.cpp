#include"my.array.h"

#ifdef NDEBUG
  #define __assert__( expression )
#else
  #include<cassert>
  #define __assert__( expression ) assert( expression )
#endif

#define ARRAY_DATA( array_str ) ( (array_str) ? (array_str)->data : (void *)0 )
#define ARRAY_SIZE( array_str ) ( (array_str) ? (array_str)->size : (size_type)0 )

struct my_array::array_struct{ size_type size, data[]; };

void * my_array::data(){ return ARRAY_DATA( this->_M_data ); }
void const * my_array::data()const{ return ARRAY_DATA( this->_M_data ); }
typename my_array::size_type my_array::size()const
{
	__assert__( (this->_M_data != 0 ? this->_M_data->size != 0 : 1 ) );
	return ARRAY_SIZE( this->_M_data );
}

void my_array::free()
{
	__assert__( this->_M_data != 0 );// shouldn't be zero when deleting pointer
	::operator delete( this->_M_data );
	this->_M_data = 0;
}
void my_array::allocate( size_type __size )
{
	__assert__( this->_M_data == 0 );// should be zero when allocating pointer
	__assert__( __size > sizeof(size_type) );
	this->_M_data = (array_struct * )::operator new( __size + sizeof(size_type) );
	this->_M_data->size = __size;
}
int my_array::resize( size_type __size )
{
	if( this->size() == __size )
		return 0;
	else if( this->_M_data )
		this->free();
	if( __size )
	{
		this->allocate( __size );
		return 1;
	}
	return 0;// here (__size == 0)
}
my_array::my_array(): _M_data(){__my_array_login__( std::clog, this, function_name() ); }
my_array::my_array( my_array const & v ): _M_data( (array_struct * )( v.size() ? ::operator new( v.size() + sizeof(size_type) ) : (void *)0 ) )
{ 
	__my_array_login__( std::clog, this, function_name() );
	if( this->_M_data )
		this->_M_data->size = v.size();
}
my_array & my_array::operator=( my_array const & v )
{
	__my_array_login__( std::clog, this, function_name() );
	if( this == &v )
		return *this;
	const size_type v_size = v.size();
	this->resize( v_size );
}
my_array::~my_array()
{
	__my_array_login__( std::clog, this, function_name() );
	// if 'data' == 0; then 'array_struct' == 0; otherwise 'array_struct' != 0
	__assert__( ( this->data() == 0 ? this->_M_data == 0 : this->_M_data != 0 ) );
	if( this->_M_data ) this->free();
}
