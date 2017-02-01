#ifndef __MY_ARRAY_H__
#define __MY_ARRAY_H__
#include<cstdint>// uint32_t

#define __MY_ARRAY_LOG_INFO__
#define __MY_ARRAY_ERROR_MSG__
//#define __MY_ARRAY_NDEBUG__
#define __MY_ARRAY_IS_VIRTUAL_DESTRUCTOR__ 0

#if __MY_ARRAY_IS_VIRTUAL_DESTRUCTOR__
  #define __VIRTUAL_DTOR__ virtual
#else
  #define __VIRTUAL_DTOR__
#endif

class my_array
{
public:
	typedef uint32_t size_type;
	struct array_struct
	{
		size_type capacity, size;
		unsigned char data[];
	};
	static array_struct * allocate( size_type __size );
protected:
	array_struct * _M_data;
	void free();
	void set_size( size_type __size );
public:
	my_array();
	my_array( my_array const & );
	my_array( my_array && );
	my_array( size_type __size );
	my_array & operator=( my_array const & );
	my_array & operator=( my_array && );
	__VIRTUAL_DTOR__ ~my_array();

	void * data();
	void const * data()const;
	void * data(int i);
	void const * data(int i)const;
	size_type size()const;
	size_type capacity()const;
	void resize( size_type __size );
	void reserve( size_type );
	void reallocate( size_type );
	void shrink_to_fit();
};

#endif//__MY_ARRAY_H__
