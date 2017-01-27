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
		size_type size;
		unsigned char data[];
	};
	static array_struct * allocate( size_type __size );
protected:
	array_struct * _M_data;
	void free();
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
	size_type size()const;
	int resize( size_type __size );// return value: 0 - if __size -eq this->size(), or if __size -eq 0; 1 - otherwise
};

#endif//__MY_ARRAY_H__
