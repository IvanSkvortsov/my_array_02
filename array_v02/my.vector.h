#ifndef __MY_VECTOR_H__
#define __MY_VECTOR_H__
#include<cstdint>// uint32_t

#define __MY_VECTOR_LOG_INFO__
#define __MY_VECTOR_ERROR_MSG__
//#define __MY_VECTOR_NDEBUG__

class my_vector
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
	void reallocate( size_type );// It incapsulated due to a possible memory leak
public:
	my_vector();
	my_vector( my_vector const & );
	my_vector( my_vector && );
	my_vector( size_type __size );
	my_vector & operator=( my_vector const & );
	my_vector & operator=( my_vector && );
	~my_vector();

	void * data();
	void const * data()const;
	void * data(int i);
	void const * data(int i)const;
	size_type size()const;
	size_type capacity()const;
	void reserve( size_type );
	void shrink_to_fit();
};

#endif//__MY_VECTOR_H__
