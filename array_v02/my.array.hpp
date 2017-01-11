#ifndef __MY_ARRAY_HPP__
#define __MY_ARRAY_HPP__
#include"my.array.h"

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
private:
	void copy( my_array_t<T> const & v );
public:
	my_array_t();
	my_array_t( my_array_t<T> const & v );
	my_array_t<T> & operator=( my_array_t<T> const & v );
	~my_array_t();
	//
	pointer data(){ return (pointer )this->my_array::data(); }
	const_pointer data()const{ return (const_pointer )this->my_array::data(); }
	reference operator[]( size_type i ){ return ((pointer )(this->my_array::data()))[i]; }
	const_reference operator[]( size_type i )const{ return ((const_pointer )(this->my_array::data()))[i]; }
	size_type size()const{ return this->my_array::size()/sizeof(T); }
	void resize( size_type __size );
};

template<typename T> inline void my_array_t<T>::copy( my_array_t<T> const & v )
{
	assert( this->my_array::size() == v.my_array::size() );// sizes should be equal to each other when copying
	const size_type t_size = v.size();
	pointer t_data = this->data();
	const_pointer v_data = v.data();
	for(int i = 0; i < t_size; ++i, ++t_data, ++v_data )
		new (t_data) T(*v_data);
}
template<typename T> void my_array_t<T>::resize( size_type __size )
{
	int __st = this->my_array::resize( __size * sizeof(T) );
	if( __st == 0 )
		return;
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < t_size; ++i, ++p )
		new (p) T();
}
template<typename T> my_array_t<T> & my_array_t<T>::operator=( my_array_t<T> const & v )
{
	__login__( std::clog, this, function_name() );
	if( this == &v )
		return *this;
	int __st = this->my_array::resize( v.my_array::size() );
	if( __st == 0 )
		return *this;
	this->copy( v );
	return *this;
}
template<typename T> my_array_t<T>::my_array_t(): my_array(){ __login__( std::clog, this, function_name() ); }
template<typename T> my_array_t<T>::my_array_t( my_array_t<T> const & v ): my_array( v )
{
	__login__( std::clog, this, function_name() );
	this->copy( v );
}
template<typename T> my_array_t<T>::~my_array_t()
{
	__login__( std::clog, this, function_name() );
	const size_type t_size = this->size();
	pointer p = this->data();
	for(int i = 0; i < t_size; ++i, ++p )
		p->~T();
}

#include<cstring>// memcpy, memset
// Specialization
#define __MY_ARRAY_T_SPEC( _BUILT_IN_TYPE_ ) \
template<> void my_array_t<_BUILT_IN_TYPE_>::copy( my_array_t<_BUILT_IN_TYPE_> const & v )\
{\
	assert( this->my_array::size() == v.my_array::size() );/* sizes should be equal to each other when copying */\
	memcpy( this->data(), v.data(), v.my_array::size() );\
}\
template<> void my_array_t<_BUILT_IN_TYPE_>::resize( size_type __size )\
{\
	int __st = this->my_array::resize( __size * sizeof(_BUILT_IN_TYPE_) );\
	if( __st == 0 )\
		return;\
	memset( this->data(), 0, this->my_array::size() );\
}\
template<> my_array_t<_BUILT_IN_TYPE_>::~my_array_t(){ __login__( std::clog, this, function_name() ); }

#define __MY_ARRAY_CHARTYPE_SPEC( _CHAR_TYPE_ ) \
template<> inline typename my_array::size_type my_array_t<_CHAR_TYPE_>::size()const{ return this->my_array::size(); }

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
