#ifndef __MY_ARRAY_H__
#define __MY_ARRAY_H__
#include"my.range.allocator.hpp"

template<typename T, std::size_t _Size, typename _RAlloc = my_range_allocator<T> >
class my_array
{
public:
	typedef T value_type;
	typedef T * pointer;
	typedef T const * const_pointer;
	typedef T & reference;
	typedef T const & const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
protected:
	T _M_ptr[];
	unsigned char _M_data[_Size * sizeof(value_type)];

	void construct_full_s( T const & x, size_type __pos = 0, size_type __len = -1 );
	void construct_full_v( T const * v, size_type __pos = 0, size_type __len = -1 );
	template<typename U> void construct_full_s( U const & x, size_type __pos = 0, size_type __len = -1 );
	template<typename U> void construct_full_v( U const * v, size_type __pos = 0, size_type __len = -1 );
public:
	my_array();
	my_array( my_array<T, _Size, _RAlloc> const & v );
	my_array( T const & x, size_type __size = -1 );
	my_array( std::initializer_list<T> init );
	template<typename U> my_array( U const & x, size_type __size = -1 );
	template<typename U> my_array( U const * __start, U const * __end );
	template<typename U> my_array( std::initializer_list<U> init );
	template<typename U, std::size_t v_size, typename range_allocator_type = my_range_allocator<U> >
		my_array( my_array<U, v_size, range_allocator_type> const & v );
	~my_array();

	my_array<T,_Size,_RAlloc> & operator=( my_array<T,_Size,_RAlloc> const & v );
	template<typename U, std::size_t v_size, typename range_allocator_type = my_range_allocator<U> >
		my_array<T,_Size,_RAlloc> & operator=( my_array<U,v_size,range_allocator_type> const & v );

	void range_assign_s( T const & x, size_type __pos = 0, size_type __len = -1 );
	void range_assign_v( T const * v, size_type __pos = 0, size_type __len = -1 );
	template<typename U> void range_assign_s( U const & x, size_type __pos = 0, size_type __len = -1 );
	template<typename U> void range_assign_v( U const * v, size_type __pos = 0, size_type __len = -1 );

	pointer data(){ return this->_M_ptr; }
	const_pointer data()const{ return this->_M_ptr; }
	pointer data(difference_type i){ return this->_M_ptr + i; }
	const_pointer data(difference_type i)const{ return this->_M_ptr + i; }
	reference operator[]( difference_type i ){ return this->_M_ptr[i]; }
	const_reference operator[]( difference_type i )const{ return this->_M_ptr[i]; }

	size_type size()const{ return _Size; }
};

#endif//__MY_ARRAY_H__
